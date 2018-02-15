<?php

/**
 * @file
 * Customize the e-mails sent by Webform after successful submission.
 *
 * This file may be renamed "webform-mail-[nid].tpl.php" to target a
 * specific webform e-mail on your site. Or you can leave it
 * "webform-mail.tpl.php" to affect all webform e-mails on your site.
 *
 * Available variables:
 * - $node: The node object for this webform.
 * - $submission: The webform submission.
 * - $email: The entire e-mail configuration settings.
 * - $user: The current user submitting the form.
 * - $ip_address: The IP address of the user submitting the form.
 *
 * The $email['email'] variable can be used to send different e-mails to different users
 * when using the "default" e-mail template.
 */


if (class_exists('Wcomponents') != TRUE) {
  /**
   * Class Wcomponents
   * Prepare webform values for render email
   */
  class Wcomponents {
    private $data = array();
    private $components = array();

    function __construct($w_data, $w_components) {
      $this->data = $w_data;
      foreach ($w_components as $w_component) {
        $this->components[$w_component['form_key']] = $w_component;
      }
    }

    private function getCid($name) {
      return (isset($this->components[$name]['cid'])) ? $this->components[$name]['cid'] : NULL;
    }

    public function getTitle($name) {
      return isset($this->components[$name]['name']) ? $this->components[$name]['name'] : "";
    }


    public function getFirstValue($name) {
      $values = $this->getValues($name);
      return isset($values[0]) ? $values[0] : "";
    }

    public function getElementValue($name) {
      return (isset($this->components[$name]['value'])) ? $this->components[$name]['value'] : "";
    }

    public function getFirstObject($name) {
      return array('title' => $this->getTitle($name), 'value' => $this->getFirstValue($name));
    }

    public function getValues($name) {
      $result =  (isset($this->data[$this->getCid($name)]['value'])) ? $this->data[$this->getCid($name)]['value'] : "";
      if (empty($result)){
        $result =  (isset($this->data[$this->getCid($name)])) ? $this->data[$this->getCid($name)] : "";
      }
      return $result;
    }

    public function debug() {
      //dsm($this->data);
      //dsm($this->components);
    }
  }
}

$w_data = (isset($submission->data)) ? $submission->data : array();

// for "resend"
if (!isset($node->webform['components'])) {
  $node = node_load(157);
}

$w_components = isset($node->webform['components']) ? $node->webform['components'] : array();
$comp = new Wcomponents($w_data, $w_components);

//$comp->debug();

?>


<?php
$lName = $comp->getFirstValue("last_name");
$fName = $comp->getFirstValue("first_name");
$personal_information_name = (!empty($lName) && !empty($fName)) ? ($lName . ", " . $fName) : ($lName . $fName);
?>

<table
  style="width: 800px; background: #ffffff; font-family: Arial, Helvetica CY, Nimbus Sans L, sans-serif; font-size: 12px; line-height: 16px; border-collapse: collapse;">
<thead>
<tr>
  <td><h1><?php print t('Application for Employment'); ?></h1></td>
</tr>
<tr>
  <td>&nbsp;</td>
</tr>
</thead>
<tbody>
<tr>
  <td style="padding: 0 0 30px 0">
    <div style="border: 1px solid #ccc9c2; position: relative; padding: 10px">
      <h4
        style="margin: 0; font-size: 16px; line-height: 20px; display: inline-block;  padding: 0 4px 0 4px; position: absolute; top: -10px; left: 10px; background-color: #ffffff">
        <?php print t('Personal Information'); ?></h4>
      <table style="width: 100%">
        <tbody>
        <tr>
          <td style="padding: 0;">
            <table style="width: 100%;">
              <tbody>
              <tr>
                <td style="border: 1px solid #ccc9c2; padding: 4px;">
                  <strong><?php print t('Name (Last Name, First):'); ?></strong><br>
                  <span><?php print $personal_information_name; ?></span>
                </td>
                <td style="border: 1px solid #ccc9c2; padding: 4px;">
                  <strong><?php print t('Email Address:'); ?></strong><br>
                  <span><?php print $comp->getFirstValue("email_address"); ?></span>
                </td>
                <td style="border: 1px solid #ccc9c2; padding: 4px;">
                  <strong><?php print t('Social Security No.:'); ?></strong> <br>
                  <span><?php print $comp->getFirstValue("social_security_number"); ?></span>
                </td>
              </tr>
              <tr>
                <td style="padding: 0">
                  <table style="border-collapse: collapse; width: 100%;">
                    <tbody>
                    <tr>
                      <td style="border: 1px solid #ccc9c2; padding: 4px;">
                        <strong><?php print t('Present Address:'); ?></strong><br>
                        <span><?php print $comp->getFirstValue("current_address"); ?></span>
                      </td>
                      <td style="padding: 0; width: 2px"></td>
                      <td style="border: 1px solid #ccc9c2; padding: 4px;">
                        <strong><?php print t('City:'); ?></strong><br>
                        <span><?php print $comp->getFirstValue("city"); ?></span>
                      </td>
                    </tr>
                    </tbody>
                  </table>
                </td>
                <td style="padding: 0">
                  <table style="border-collapse: collapse; width: 100%;">
                    <tbody>
                    <tr>
                      <td style="border: 1px solid #ccc9c2; padding: 4px;">
                        <strong><?php print t('State:'); ?></strong><br>
                        <span><?php print $comp->getFirstValue("state"); ?></span>
                      </td>
                      <td style="padding: 0; width: 2px"></td>
                      <td style="border: 1px solid #ccc9c2; padding: 4px;">
                        <strong><?php print t('Zip Code:'); ?></strong><br>
                        <span><?php print $comp->getFirstValue("zip"); ?></span>
                      </td>
                    </tr>
                    </tbody>
                  </table>
                </td>
                <td style="padding: 0">&nbsp;</td>
              </tr>
              <tr>
                <td style="border: 1px solid #ccc9c2; padding: 4px;">
                  <strong><?php print t('Home Phone No.:'); ?></strong><br>
                  <span><?php print $comp->getFirstValue("home_phone_number"); ?></span>
                </td>
                <td style="border: 1px solid #ccc9c2; padding: 4px;">
                  <strong><?php print t('Refered By:'); ?></strong><br>
                  <span><?php print $comp->getFirstValue("referred_by"); ?></span>
                </td>
                <td style="border: 1px solid #ccc9c2; padding: 4px;">
                  <strong><?php print t('Cell Phone No.:'); ?></strong><br>
                  <span><?php print $comp->getFirstValue("cell_phone_number"); ?></span>
                </td>
              </tr>
              <tr>
                <td style="padding: 0;" colspan="2">
                  <table style="border-collapse: collapse; width: 100%;">
                    <tbody>
                    <tr>
                      <td style="border: 1px solid #ccc9c2; padding: 4px;">
                        <strong><?php print t('Emergency Contact:'); ?></strong><br>
                        <span><?php print $comp->getFirstValue("emergency_contact"); ?></span>
                      </td>
                      <td style="padding: 0; width: 2px"></td>
                      <td style="border: 1px solid #ccc9c2; padding: 4px;">
                        <strong><?php print t('Relation:'); ?></strong><br>
                        <span><?php print $comp->getFirstValue("relation"); ?></span>
                      </td>
                      <td style="padding: 0; width: 2px"></td>
                      <td style="border: 1px solid #ccc9c2; padding: 4px;">
                        <strong><?php print t('Phone No.:'); ?></strong><br>
                        <span><?php print $comp->getFirstValue("phone_number"); ?></span>
                      </td>
                    </tr>
                    </tbody>
                  </table>
                </td>
                <td style="padding: 0">&nbsp;</td>
              </tr>
              </tbody>
            </table>
          </td>
        </tbody>
      </table>
    </div>
  </td>
</tr>
<tr>
  <td style="padding: 0 0 30px 0">
    <div style="border: 1px solid #ccc9c2; position: relative; padding: 10px">
      <h4
        style="margin: 0; font-size: 16px; line-height: 20px; display: inline-block;  padding: 0 4px 0 4px; position: absolute; top: -10px; left: 10px; background-color: #ffffff">
        <?php print t('Employment Desired'); ?></h4>
      <table style="width: 100%;">
        <tbody>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Type of Employment Desired:'); ?></strong><br>
            <span><?php print $comp->getFirstValue("type_of_employment"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;" colspan="2">
            <strong><?php print t('Position:'); ?></strong>
            <span><?php print $comp->getFirstValue("choose_a_position"); ?></span>
          </td>
        </tr>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Times Available:'); ?></strong><br>
            <?php $values = $comp->getValues("times_available"); ?>
            <?php if (!empty($values)) : ?>
              <?php foreach ($values as $value): ?>
                <span><?php print $value; ?></span><br>
              <?php endforeach; ?>
            <?php endif; ?>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Date You Can Start:'); ?></strong>
            <span><?php print $comp->getFirstValue("date_you_can_start"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Salary Desired:'); ?></strong>
            <span><?php print $comp->getFirstValue("salary_desired"); ?></span>
          </td>
        </tr>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Are You Employed:'); ?></strong>
            <span><?php print $comp->getFirstValue("are_you_currently_employed"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('If Yes, May We Inquire Your Present Employer?:'); ?></strong>
            <span><?php print $comp->getFirstValue("if_yes_may_we_contact_your_current_employer"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Please Initial:'); ?></strong>
            <span><?php print $comp->getFirstValue("please_initial"); ?></span>
          </td>
        </tr>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Ever Applied With Us Before?:'); ?></strong>
            <span><?php print $comp->getFirstValue("have_you_ever_applied_with_us_before"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Where?:'); ?></strong><br>
            <span><?php print $comp->getFirstValue("if_yes_where"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('When?:'); ?></strong><br>
            <span><?php print $comp->getFirstValue("when"); ?></span>
          </td>
        </tr>
        </tbody>
      </table>
    </div>
  </td>
</tr>
<tr>
  <td style="padding-bottom: 30px">
    <div style="border: 1px solid #ccc9c2; position: relative; padding: 10px">
      <h4
        style="margin: 0; font-size: 16px; line-height: 20px; display: inline-block;  padding: 0 4px 0 4px; position: absolute; top: -10px; left: 10px; background-color: #ffffff">
        <?php print t('Education History'); ?></h4>
      <table style="width: 100%;">
        <thead>
        <tr>
          <th>
            &nbsp;
          </th>
          <th style="color: #6d1020">
            <?php print t('Name and Location of <br>School'); ?>
          </th>
          <th style="color: #6d1020">
            <?php print t('Years'); ?>
          </th>
          <th style="color: #6d1020">
            <?php print t('Graduate?'); ?>
          </th>
          <th style="color: #6d1020">
            <?php print t('Subject<br>Studied'); ?>
          </th>
        </tr>
        </thead>
        <tbody>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Grammar School'); ?></strong><br>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("grammar_school"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("grammar_school_years"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("grammar_school_graduated"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("grammar_school_subjects_studied"); ?></span>
          </td>
        </tr>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('High School'); ?></strong><br>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("high_school"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("high_school_years"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("high_school_graduated"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("high_school_subjects_studied"); ?></span>
          </td>
        </tr>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('College'); ?></strong><br>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("college"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("college_years"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("college_graduated"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("college_subjects_studied"); ?></span>
          </td>
        </tr>
        <tr>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <strong><?php print t('Trade or Business School'); ?></strong> <br>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("trade_or_businnes_school"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("trade_years"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("trade_graduated"); ?></span>
          </td>
          <td style="border: 1px solid #ccc9c2; padding: 4px;">
            <span><?php print $comp->getFirstValue("trade_subjects_studied"); ?></span>
          </td>
        </tr>
        </tbody>
      </table>
    </div>
  </td>
</tr>
<tr>
  <td style="padding-bottom: 30px">
    <div style="border: 1px solid #ccc9c2; position: relative; padding: 10px">
      <h4
        style="margin: 0; font-size: 16px; line-height: 20px; display: inline-block;  padding: 0 4px 0 4px; position: absolute; top: -10px; left: 10px; background-color: #ffffff">
        <?php print t('Previous employment (List below last four employers, starting with last one first).'); ?></h4>
      <table style="width: 100%;">
        <thead>
        <tr>
          <th style="color: #6d1020"><?php print t('Date (Month <br>and Year)'); ?></th>
          <th style="color: #6d1020"><?php print t('Name, Address, and Phone No. of <br>Employer'); ?></th>
          <th style="color: #6d1020"><?php print t('Salary'); ?></th>
          <th style="color: #6d1020"><?php print t('Position'); ?></th>
          <th style="color: #6d1020"><?php print t('Reason For <br>Leaving'); ?></th>
        </tr>
        </thead>
        <tbody>
        <?php for ($i = 1; $i <= 4; $i++): ?>
          <tr>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <strong><?php print t('From:'); ?>&nbsp;</strong>
              <span><?php print $comp->getFirstValue("employment_history_" . $i . "_from"); ?></span><br>
              <strong><?php print t('To:'); ?>&nbsp;</strong>
              <span><?php print $comp->getFirstValue("employment_history_" . $i . "_to"); ?></span><br>
            </td>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <?php
              $company = $comp->getFirstValue("employment_history_" . $i . "_company");
              $phone = $comp->getFirstValue("employment_history_" . $i . "_phone");
              $address = $comp->getFirstValue("employment_history_" . $i . "_address");
              $city = $comp->getFirstValue("employment_history_" . $i . "_city");
              $state = $comp->getFirstValue("employment_history_" . $i . "_state");
              $zip = $comp->getFirstValue("employment_history_" . $i . "_zip");
              ?>

              <?php if (!empty($company)) : ?><strong><?php print t('Company:'); ?>&nbsp;</strong>
                <span><?php print $company; ?></span><br><?php endif; ?>
              <?php if (!empty($phone)) : ?><strong><?php print t('Phone:'); ?>&nbsp;</strong>
                <span><?php print $phone; ?></span><br><?php endif; ?>
              <?php if (!empty($address)) : ?><strong><?php print t('Address:'); ?>&nbsp;</strong>
                <span><?php print $address; ?></span><br><?php endif; ?>
              <?php if (!empty($city)) : ?><strong><?php print t('City:'); ?>&nbsp;</strong>
                <span><?php print $city; ?></span><br><?php endif; ?>
              <?php if (!empty($state)) : ?><strong><?php print t('St:'); ?>&nbsp;</strong>
                <span><?php print $state; ?></span><br><?php endif; ?>
              <?php if (!empty($zip)) : ?><strong><?php print t('Zip:'); ?>&nbsp;</strong>
                <span><?php print $zip; ?></span><br><?php endif; ?>
            </td>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <span><?php print $comp->getFirstValue("employment_history_" . $i . "_salary"); ?></span>
            </td>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <span><?php print $comp->getFirstValue("employment_history_" . $i . "_position"); ?></span>
            </td>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <span><?php print $comp->getFirstValue("employment_history_" . $i . "_reason_for_leaving"); ?></span>
            </td>
          </tr>
        <?php endfor; ?>

        </tbody>
      </table>
    </div>
  </td>
</tr>
<tr>
  <td style="padding-bottom: 30px">
    <div style="border: 1px solid #ccc9c2; position: relative; padding: 10px">
      <h4
        style="margin: 0; font-size: 16px; line-height: 20px; display: inline-block;  padding: 0 4px 0 4px; position: absolute; top: -10px; left: 10px; background-color: #ffffff">
        <?php print t('References (List below last four employers, starting with last one first).'); ?>
      </h4>
      <table style="width: 100%;">
        <thead>
        <tr>
          <th style="color: #6d1020"><?php print t('Name'); ?></th>
          <th style="color: #6d1020"><?php print t('Address'); ?></th>
          <th style="color: #6d1020"><?php print t('Business'); ?></th>
          <th style="color: #6d1020"><?php print t('Phone No'); ?></th>
        </tr>
        </thead>
        <tbody>
        <?php for ($i = 1; $i <= 4; $i++): ?>
          <tr>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <span><?php print $comp->getFirstValue("references_" . $i . "_name"); ?></span>
            </td>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <span><?php print $comp->getFirstValue("references_" . $i . "_address"); ?></span>
            </td>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <span><?php print $comp->getFirstValue("references_" . $i . "_business"); ?></span>
            </td>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <span><?php print $comp->getFirstValue("references_" . $i . "_phone"); ?></span>
            </td>
          </tr>
        <?php endfor; ?>
        </tbody>
      </table>
    </div>
  </td>
</tr>

<tr>
  <td style="padding-bottom: 30px">
    <div style="border: 1px solid #ccc9c2; position: relative; padding: 10px">
      <h4
        style="margin: 0; font-size: 16px; line-height: 20px; display: inline-block;  padding: 0 4px 0 4px; position: absolute; top: -10px; left: 10px; background-color: #ffffff">
        <?php print t('Availability'); ?>
        <?php
        $week = array(
          'monday' => t('Monday'),
          'tuesday' => t('Tuesday'),
          'wednesday' => t('Wednesday'),
          'thursday' => t('Thursday'),
          'friday' => t('Friday'),
          'saturday' => t('Saturday'),
          'sunday' => t('Sunday'),
        );
        ?>
      </h4>
      <table style="width: 100%;">
        <thead>
        <tr>
          <?php foreach ($week as $key => $day): ?>
            <th style="color: #6d1020"><?php print $day; ?></th>
          <?php endforeach; ?>
        </tr>
        </thead>
        <tbody>
        <tr>
          <?php foreach ($week as $key => $day): ?>
            <td style="border: 1px solid #ccc9c2; padding: 4px;">
              <strong><?php print t('Am:'); ?>&nbsp;</strong>
              <span><?php print $comp->getFirstValue("availability_" . $key . "_am_from"); ?></span><br>
              <strong><?php print t('To:'); ?>&nbsp;</strong>
              <span><?php print $comp->getFirstValue("availability_" . $key . "_am_to"); ?></span><br><br>

              <strong><?php print t('Pm:'); ?>&nbsp;</strong>
              <span><?php print $comp->getFirstValue("availability_" . $key . "_pm_from"); ?></span><br>
              <strong><?php print t('To:'); ?>&nbsp;</strong>
              <span><?php print $comp->getFirstValue("availability_" . $key . "_pm_to"); ?></span><br>
            </td>
          <?php endforeach; ?>
        </tr>
        </tbody>
      </table>
    </div>
  </td>
</tr>

<tr>
  <td style="padding-bottom: 30px">
    <div style="border: 1px solid #ccc9c2; position: relative; padding: 10px">
      <h4
        style="margin: 0; font-size: 16px; line-height: 20px; display: inline-block;  padding: 0 4px 0 4px; position: absolute; top: -10px; left: 10px; background-color: #ffffff">
        <?php print t('Authorization'); ?></h4>
      <?php print $comp->getElementValue("description"); ?>
      <span>
          <br>
          <br>
          <br>
          <br>
        </span>

      <p>
        <strong><?php print t('Date:'); ?></strong> <br>
        <span><?php print $comp->getFirstValue("date"); ?></span> <br>
        <strong><?php print t('Signed:'); ?></strong> <br>
        <span><?php print $comp->getFirstValue("signed"); ?></span> <br>
      </p>
    </div>
  </td>
</tr>
<tr>
  <td style="padding-bottom: 30px">
    <table style="width: 100%;">
      <tbody>
      <tr>
        <td style="border-bottom: 1px solid #000000; padding: 4px; width: 30%;">
          <strong>Date:&nbsp;</strong><span> </span>
        </td>
        <td style="padding: 4px; width: 10px"></td>
        <td style="border-bottom: 1px solid #000000; padding: 4px;">
          <strong>Interviewed By:&nbsp;</strong><span> </span>
        </td>
      </tr>
      </tbody>
    </table>
  </td>
</tr>
<tr>
  <td style="padding-bottom: 30px">
    <table style="width: 100%;">
      <thead>
      <tr>
        <th colspan="5" style="color: #6d1020"><?php print t('Remarks') ?></th>
      </tr>
      </thead>
      <tbody>
      <tr>
        <td colspan="5" style="border: 1px solid #ccc9c2; padding: 4px;">
          <br>
          <br>
          <br>
          <br>
          <br>
          <br>
          <br>
        </td>
      </tr>
      <tr>
        <td colspan="3" style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Neatness') ?></strong>
        </td>
        <td colspan="2" style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Character') ?></strong>
        </td>
      </tr>
      <tr>
        <td colspan="3" style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Personality') ?></strong>
        </td>
        <td colspan="2" style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Ability') ?></strong>
        </td>
      </tr>
      <tr>
        <td style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Hired') ?></strong>
        </td>
        <td style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Position') ?></strong>
        </td>
        <td style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Will Report') ?></strong>
        </td>
        <td style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Salary/Wages') ?></strong>
        </td>
        <td style="border: 1px solid #ccc9c2; padding: 4px;">
          <strong><?php print t('Other') ?></strong>
        </td>
      </tr>
      </tbody>
    </table>
  </td>
</tr>
<tr>
  <td style="padding-bottom: 30px">
    <table style="width: 100%">
      <tbody>
      <tr>
        <td style="border-bottom: 1px solid transparent; padding: 4px; width: 100px">
          <strong><?php print t('Approved') ?></strong></td>
        <td style="border-bottom: 1px solid #000000; padding: 4px;"></td>
        <td style="padding: 4px; width: 10px"></td>
        <td style="border-bottom: 1px solid #000000; padding: 4px;"></td>
        <td style="padding: 4px; width: 10px"></td>
        <td style="border-bottom: 1px solid #000000; padding: 4px;"></td>
      </tr>
      <tr>
        <td style="padding: 2px 4px; width: 100px">&nbsp;</td>
        <td style="padding:2px 4px;">
          <span style="font-size: 11px; color: #CCC9C2;"><?php print t('Employment Manager') ?></span>
        </td>
        <td style="padding: 4px; width: 10px"></td>
        <td style="padding: 2px 4px;">
          <span style="font-size: 11px; color: #CCC9C2;"><?php print t('Department Head') ?></span>
        </td>
        <td style="padding: 4px; width: 10px"></td>
        <td style="padding: 2px 4px;">
          <span style="font-size: 11px; color: #CCC9C2;"><?php print t('General Manager') ?></span>
        </td>
      </tr>
      </tbody>
    </table>
  </td>
</tr>
</tbody>
</table>


