<?php
/*
* Updated: Alex Estrada, PayJunction
* Date: May 10, 2010
* File: quicklink.php
* Description: Implementation of the Trinity Gateway Service API v1.2 in PHP.
* 

--Protecting your Website and Payment Applications from Man-In-The-Middle-Attacks--
Our API allows merchants and developers to connect to PayJunction via an encrypted SSL communications link. In order for your website or payment application to verify that your connection to PayJunction has not been intercepted, all code that connects to PayJunction must verify then authenticity of our SSL certificate by performing strict server certificate verification against PayJunction's root certificate authority. It has come to our attention that some merchants have disabled the SSL certificate verification for testing purpose; while the SSL connection remains secure, it is possible that an attacker could try to initiate a Man-In-The-Middle attack in an attempt to intercept your website's or applications connection to PayJunction.

Common Mistake: Anyone website or application that does not verify the authenticity of PayJunction's SSL certificate upon connecting to our QuickLink API.

Solution: Turn SSL verification on prior to connecting to PayJunction for transaction authorizations. In the event that your website is unable to verify the authenticity of PayJunction's root certificate, your website and/or application should not transmit any transaction information and should reject your customer's transactions. If you believe your application is unable to verify the authenticity of PayJunction's certificate, contact our support department.

--PayJunction Security Requirements and Best Practices for Merchants and Developers--
https://www.payjunction.com/trinity/support/view.action?knowledgeBase.knbKnowledgeBaseId=451

--Please note--
There is no warranty for the programs or example code provided in PayJunction's support center. The copyright holders and/or other parties provide the program "as is" without warranty of any kind, either expressed or implied, including, but not limited to, the implied warranties of merchantability and fitness for a particular purpose. The entire risk as to the quality and performance of the program is with you. Should the program prove defective, you assume the cost of all necessary servicing, repair or correction. It is the merchant's responsibility to ensure their systems meet the PCI requirements. PayJunction's Gateway Agreement have been updated to include the referenced "PayJunction Security Requirements and Best Practices for Merchants and Developers;" it is the merchant's responsibility to review this knowledge base on a regular basis for the security of the merchant's account and to protect cardholder data.

Please contact us if you have any questions.

With Kindest Regards,
The PayJunction Team
support@payjunction.com
*/

class QuickLink {
	// Testing Server URL	
	//private $server = "https://www.payjunctionlabs.com/quick_link";
	
	// Live Server URL
	//private $server = "https://www.payjunction.com/quick_link";

    private $server = "";
	private $security='';
	private $logon;
	private $password;
    private $error = "";
	
	/**
	 * Loads the username and password for this account
	 * @param logon The username identifying your account
	 * @param password The password for your account
	 */
	function quicklink($server, $logon, $password) 	// PHP constructor
	{
        $this->server = $server;
		$this->logon = $logon;
		$this->password = $password;
	}

	/**
	 * Dynamically controls the AVS and CVV independent of the settings in the web interface.
	 * Can be applied to one-time transactions, instant transactions, recurring transactions,
	 * and recurring instant transactions.  A value string is formed with each entry delimited
	 * by the "|" character in the format AVS|CVV|PREAUTH|AVSFORCE|CVVFORCE.
	 * @param newAVS Address Verification System (possible values: AWZ, XY, WZ, AW, AZ, A, X, Y, W, Z)
	 * @param newCVV Cardholder Verification Number
	 * @param newPreAuth Pre-authorize card
	 * @param newAVSforce Override AVS
	 * @param newCVVforce Override CVV
	 */
	public function setSecurity($newAVS, $newCVV, $newPreAuth, $newAVSforce, $newCVVforce)
	{
		//if all values are given, update security variable so that later the
		//new security value can be sent to Trinity Gateway Service
		if($newAVS!="" && $newCVV!="" && $newPreAuth!="" && $newAVSforce!="" && $newCVVforce!="")
		{
			$this->security = $newAVS . "|" . $newCVV . "|" . $newPreAuth . "|" . $newAVSforce . "|" . $newCVVforce;
			echo "security settings changed: ". $this->security;
		}
		//if any of the arguments are empty, do not update security.  The reason
		//for this is that one might expect that any values left blank will remain
		//the same as the settings in the web interface.  In reality they cause 
		//Trinity to revert the relevant security setting to the default value which 
		//is not necessarily secure
		else
			echo "no change in security - must provide all values";
	}

	/**
	 * Requests authorization of card from Trinity Gateway Information
	 * @param name The name of the cardholder
	 * @param number The 13-16 digit credit card number
	 * @param exp_month The numeric (1 through 12) expiration month of the credit card
	 * @param exp_year The two- or four-digit expiration year of the credit card
	 * @param cvs The card verification value of the credit card, a three- or four-digit number
	 * @param address The street or post office box for the address of the cardholder
	 * @param city The city of the address of the cardholder
	 * @param state The state of the address of the cardholder
	 * @param zip The zip or postal code of the address of the cardholder
	 * @param amount The amount to transact
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Authorize ($name, $number, $exp_month, $exp_year, $cvs, $address, $city, $state, $zip, $amount, $transaction_id)
	{
		//process one-time or instant authorize request on credit card
		return Process("AUTHORIZATION", $address, $city, $state, $zip, $amount, $name, $number, $exp_month, $exp_year, $cvs, '', '', '', '', '', $transaction_id, '');
	}
	
	/**
	 * Requests charge from Trinity Gateway Information
	 * @param name The name of the cardholder
	 * @param number The 13-16 digit credit card number
	 * @param exp_month The numeric (1 through 12) expiration month of the credit card
	 * @param exp_year The two- or four-digit expiration year of the credit card
	 * @param cvs The card verification value of the credit card, a three- or four-digit number
	 * @param address The street or post office box for the address of the cardholder
	 * @param city The city of the address of the cardholder
	 * @param state The state of the address of the cardholder
	 * @param zip The zip or postal code of the address of the cardholder
	 * @param amount The amount to transact
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Charge ($name, $number, $exp_month, $exp_year, $cvs, $address, $city, $state, $zip, $amount, $transaction_id, $notes)
	{
		//process one-time or instant charge request on credit card
		return $this->Process("AUTHORIZATION_CAPTURE", $address, $city, $state, $zip, $amount, $name, $number, $exp_month, $exp_year, $cvs, "", "", "", "", "", $transaction_id, "", $notes);
	}
	
	/**
	 * Requests refund from Trinity Gateway Information
	 * @param name The name of the cardholder
	 * @param number The 13-16 digit credit card number
	 * @param exp_month The numeric (1 through 12) expiration month of the credit card
	 * @param exp_year The two- or four-digit expiration year of the credit card
	 * @param cvs The card verification value of the credit card, a three- or four-digit number
	 * @param address The street or post office box for the address of the cardholder
	 * @param city The city of the address of the cardholder
	 * @param state The state of the address of the cardholder
	 * @param zip The zip or postal code of the address of the cardholder
	 * @param amount The amount to transact
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Refund ($name, $number, $exp_month, $exp_year, $cvs, $address, $city, $state, $zip, $amount, $transaction_id)
	{
		//process one-time or instant refund request on credit card
		return $this->Process("CREDIT", $address, $city, $state, $zip, $amount, $name, $number, $exp_month, $exp_year, $cvs, "", "", "", "", $transaction_id, "");
	}
	/**
	 * Requests recurring authorization from Trinity Gateway Information.  The card for
	 * the transaction will be billed according to the schedule specified.  The recurring
	 * transaction will also be accessible from the Trinity Point of Sale system at
	 * http://www.PayJunction.com Note: subsequent editing and management of the 
	 * recurring transaction must be made from the Trinity Point of Sale web system.
	 * @param name The name of the cardholder
	 * @param number The 13-16 digit credit card number
	 * @param exp_month The numeric (1 through 12) expiration month of the credit card
	 * @param exp_year The two- or four-digit expiration year of the credit card
	 * @param cvs The card verification value of the credit card, a three- or four-digit number
	 * @param address The street or post office box for the address of the cardholder
	 * @param city The city of the address of the cardholder
	 * @param state The state of the address of the cardholder
	 * @param zip The zip or postal code of the address of the cardholder
	 * @param amount The amount to transact
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @param limit Number of approved transactions you want to run on the schedule
	 * @param periodic_number Unit length of time between transactions
	 * @param periodic_type "day", "week", "month"
	 * @param start YYYY-MM-DD Note: must be a valid date that exists
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Schedule_Authorize ($name, $number, $exp_month, $exp_year, $cvs, $address, $city, $state, $zip, $amount, $transaction_id, $create, $limit, $periodic_number, $periodic_type, $start	)
	{
		//process one-time or instant authorize request on recurring transaction of credit card
		return $this->Process("AUTHORIZATION", $address, $city, $state, $zip, $amount, $name, $number, $exp_month, $exp_year, $cvs, $create, $limit, $periodic_number,$periodic_type, $start, $transaction_id, "");
	}

	/**
	 * Requests recurring charge from Trinity Gateway Information.  The card for the
	 * transaction will be billed according to the schedule specified.  The recurring
	 * transaction will also be accessible from the Trinity Point of Sale system at
	 * http://www.PayJunction.com  Note: subsequent editing and management of the 
	 * recurring transaction must be made from the Trinity Point of Sale web system.
	 * @param name The name of the cardholder
	 * @param number The 13-16 digit credit card number
	 * @param exp_month The numeric (1 through 12) expiration month of the credit card
	 * @param exp_year The two- or four-digit expiration year of the credit card
	 * @param cvs The card verification value of the credit card, a three- or four-digit number
	 * @param address The street or post office box for the address of the cardholder
	 * @param city The city of the address of the cardholder
	 * @param state The state of the address of the cardholder
	 * @param zip The zip or postal code of the address of the cardholder
	 * @param amount The amount to transact
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @param limit Number of approved transactions you want to run on the schedule
	 * @param periodic_number Unit length of time between transactions
	 * @param periodic_type "day", "week", "month"
	 * @param start YYYY-MM-DD Note: must be a valid date that exists
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Schedule_Charge ($name, $number, $exp_month, $exp_year, $cvs, $address, $city, $state, $zip, $amount, $transaction_id, $create, $limit, $periodic_number, $periodic_type, $start)
	{
		//process one-time or instant charge request on recurring transaction of credit card
		return $this->Process("AUTHORIZATION_CAPTURE", $address, $city, $state, $zip, $amount, $name, $number, $exp_month, $exp_year, $cvs, $create, $limit, $periodic_number, $periodic_type, $start, $transaction_id, "");
	}

	/**
	 * Requests recurring refund from Trinity Gateway Information.  The card for the
	 * transaction will be billed according to the schedule specified.  The recurring
	 * transaction will also be accessible from the Trinity Point of Sale system at
	 * http://www.PayJunction.com  Note: subsequent editing and management of the 
	 * recurring transaction must be made from the Trinity Point of Sale web system.
	 * @param name The name of the cardholder
	 * @param number The 13-16 digit credit card number
	 * @param exp_month The numeric (1 through 12) expiration month of the credit card
	 * @param exp_year The two- or four-digit expiration year of the credit card
	 * @param cvs The card verification value of the credit card, a three- or four-digit number
	 * @param address The street or post office box for the address of the cardholder
	 * @param city The city of the address of the cardholder
	 * @param state The state of the address of the cardholder
	 * @param zip The zip or postal code of the address of the cardholder
	 * @param amount The amount to transact
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @param limit Number of approved transactions you want to run on the schedule
	 * @param periodic_number Unit length of time between transactions
	 * @param periodic_type "day", "week", "month"
	 * @param start YYYY-MM-DD Note: must be a valid date that exists
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Schedule_Refund ($name, $number, $exp_month, $exp_year, $cvs, $address, $city, $state, $zip, $amount, $transaction_id, $create, $limit, $periodic_number, $periodic_type, $start)
	{
		//process one-time or instant refund request on recurring transaction of credit card
		return $this->Process("CREDIT", $address, $city, $state, $zip, $amount, $name, $number, $exp_month, $exp_year, $cvs, $create, $limit, $periodic_number, $periodic_type, $start, $transaction_id, "");
	}

	/**
	 * Updates the posture of a transaction before the batch closes.  Commonly used to
	 * void a transaction or to toggle a transaction from authorization to capture.
	 * @param posture "capture", "void", "hold"
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Posture ($posture, $transaction_id)
	{
		//process request to update the posture of a transaction
		return $this->Process ("update", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", $transaction_id, $posture);
	}
	
	/**
	 * Initiates settlement independent of the web settings.  Note: this feature should
	 * only be used by advanced clients that need custom settlement behaviors.
	 * @return Results returned by Trinity Gateway Service for the desired transaction
	 */
	public function Settlement()
	{
		//process request to initiate settlement
		return $this->Process("settle", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "");
	}

	public function printResults($response)
	{

		foreach($response as $key=>$val)
		{
			echo $key . " = " . $val. "<br>";
		}
	}

	/**
	 * Processes and sends to Trinity Gateway Information a URL encoded form data set of
	 * the information taken from the credit card for transactions and other requests, 
	 * such as posture update and settlement, in URL encoded format.
	 * @param transaction_type The action to take on the transaction (Possible actions:
	 * 		AUTHORIZATION, AUTHORIZATION_CAPTURE, CREDIT)
	 * @param address The street or post office box for the address of the cardholder
	 * @param city The city of the address of the cardholder
	 * @param state The state of the address of the cardholder
	 * @param zip The zip or postal code of the address of the cardholder
	 * @param amount The amount to transact
	 * @param name The name of the cardholder
	 * @param number The 13-16 digit credit card number
	 * @param exp_month The numeric (1 through 12) expiration month of the credit card
	 * @param exp_year The two- or four-digit expiration year of the credit card
	 * @param cvs The card verification value of the credit card, a three- or four-digit number
	 * @param limit Number of approved transactions you want to run on the schedule
	 * @param periodic_number Unit length of time between transactions
	 * @param periodic_type "day", "week", "month"
	 * @param start YYYY-MM-DD Note: must be a valid date that exists
	 * @param transaction_id The transaction ID returned from a previous transaction (uses
	 * 		name, number, exp_month, exp_year, and cvs of previous transaction)
	 * @param posture "capture", "void", "hold"
	 * @return
	 */
	private function Process ($transaction_type, $address, $city, $state, $zip, $amount, $name, $number, $expiration_month, $expiration_year, $cvs, $create, $limit, $periodic_number, $periodic_type, $start, $transaction_id, $posture, $notes = "")
	{

        $this->error = "";
		//build encoded string to send to Trinity Gateway Service
		//any empty arguments ("") are not added to the string,
		//because this sometimes causes conflicts with Trinity
		$data = $this->encode("dc_logon", $this->logon);
		$data .= $this->encode("dc_password", $this->password);
		$data .= $this->encode("dc_transaction_type", $transaction_type);
		$data .= $this->encode("dc_version", "1.2");
		$data .= $this->encode("dc_address", $address);
		$data .= $this->encode("dc_city", $city);
		$data .= $this->encode("dc_state", $state);
		$data .= $this->encode("dc_zipcode", $zip);
		$data .= $this->encode("dc_transaction_amount", $amount);
        $data .= $this->encode("dc_name", $name);
		$data .= $this->encode("dc_number", $number);
		$data .= $this->encode("dc_expiration_month", $expiration_month);
		$data .= $this->encode("dc_expiration_year", $expiration_year);
		$data .= $this->encode("dc_verification_number", $cvs);
		$data .= $this->encode("dc_schedule_create", $create);
		$data .= $this->encode("dc_schedule_limit", $limit);
		$data .= $this->encode("dc_schedule_periodic_number", $periodic_number);
		$data .= $this->encode("dc_schedule_periodic_type", $periodic_type);
		$data .= $this->encode("dc_schedule_start", $start);
		$data .= $this->encode("dc_transaction_id", $transaction_id);
		$data .= $this->encode("dc_posture", $posture);
        $data .= $this->encode("dc_notes", $notes);


		//if security was updated, add it to the data string
		if($this->security != ""){
			echo "updated security";
			$data .= "&" . urlencode("dc_security") . "=" . urlencode($this->security);
		}
		
		$ch = curl_init($this->server);
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, 1);
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, 2);		
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS, $data);
		curl_setopt($ch, CURLOPT_FOLLOWLOCATION, 0);
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		$content = curl_exec($ch);
		$curl_errno = curl_errno($ch);
		$curl_error = curl_error($ch);
		curl_close($ch);
		
		if ($curl_errno) {  // If curl had an error, output the error code and message.
            $this->error = $curl_error;
			return array();
		} else {
			// Parse response
			$content = explode(chr (28), $content); // The ASCII field seperator character is the delimiter
			foreach ($content as $key_value) {
				list ($key, $value) = explode("=", $key_value);
				$response[$key] = $value;
			}
			//return results of request
			return $response;
		}
	}

	/**
	 * Encodes a Trinity Gateway Service argument as an application/x-www-form-
	 * urlencoded form data set.
	 * @param name Variable name familiar to Trinity Gateway Service (of the format dc_XXX)
	 * @param value Value collected from card to perform required transaction
	 * @return Formatted string with name and value
	 */
	private function encode ($name, $value)
	{

		//return URL encoded string such that it can later be concatenated
		//with the string being sent to Trinity Gateway Service
		if ($value != NULL && strlen($value) > 0)
		{
			return ("&".urlencode($name) ."=" .urlencode($value));
		}
		return "";
	}


  /**
   * Validate payment responce
   * @param $response
   * @param $amount
   * @param $notes
   * @return bool
   */
  public function validateResponce($response, $amount, $notes){
      if (
        isset($response['dc_response_code']) &&
        ($response['dc_response_code'] == "00" || $response["dc_response_code"] == "85") &&
        isset($response['dc_notes']) &&
        $response['dc_notes'] == $notes &&
        isset($response['dc_capture_amount']) &&
        round($response['dc_capture_amount'], 2) == round($amount, 2)
      ) {
        return TRUE;
      } else {
        $error = (!empty($this->error)) ? $this->error : $error = $this->parseError(-1);
        $this->error = (isset($response['dc_response_code'])) ? $this->parseError($response['dc_response_code']): $error;
        if (isset($response['dc_response_message']) && !empty($response['dc_response_message'])) {
          $this->error .= "<br/>" . $response['dc_response_message'];
        }

        return FALSE;

      }
    }

  /**
   * Get payment error
   * @return string
   */
  public function getError(){
      return $this->error;
  }


  private function parseError($code){
    $codes = array(
      'FE'=> 'There was a format error with your Trinity Gateway Service (API) request.',
      'AE'=> 'Address verification failed because address did not match.',
      'ZE'=> 'Address verification failed because zip did not match.',
      'XE'=> 'Address verification failed because zip and address did not match.',
      'YE'=> 'Address verification failed because zip and address did not match.',
      'OE'=> 'Address verification failed because address or zip did not match.',
      'UE'=> 'Address verification failed because cardholder address unavailable.',
      'RE'=> 'Address verification failed because address verification system is not working.',
      'SE'=> 'Address verification failed because address verification system is unavailable.',
      'EE'=> 'Address verification failed because transaction is not a mail or phone order.',
      'GE'=> 'Address verification failed because international support is unavailable.',
      'CE'=> 'Declined because CVV2/CVC2 code did not match.',
      'NL'=> 'Aborted because of a system error, please try again later.',
      'AB'=> 'Aborted because of an upstream system error, please try again later.',
      '04'=> 'Declined. Pick up card.',
      '07'=> 'Declined. Pick up card (Special Condition).',
      '41'=> 'Declined. Pick up card (Lost).',
      '43'=> 'Declined. Pick up card (Stolen).',
      '13'=> 'Declined because of the amount is invalid.',
      '14'=> 'Declined because the card number is invalid.',
      '80'=> 'Declined because of an invalid date.',
      '05'=> 'Declined. Do not honor.',
      '51'=> 'Declined because of insufficient funds.',
      'N4'=> 'Declined because the amount exceeds issuer withdrawal limit.',
      '61'=> 'Declined because the amount exceeds withdrawal limit.',
      '62'=> 'Declined because of an invalid service code (restricted).',
      '65'=> 'Declined because the card activity limit exceeded.',
      '93'=> 'Declined because there a violation (the transaction could not be completed).',
      '06'=> 'Declined because address verification failed.',
      '54'=> 'Declined because the card has expired.',
      '15'=> 'Declined because there is no such issuer.',
      '96'=> 'Declined because of a system error.',
      'N7'=> 'Declined because of a CVV2/CVC2 mismatch.',
      'M4'=> 'Declined.',
      'DT'=> 'Duplicate Transaction',
    );
    return (isset($codes[$code])) ? $codes[$code]: "An unknown error has occurred.";
  }
}



