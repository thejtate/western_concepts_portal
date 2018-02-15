<?php

class PayjunctionClient
{

    public $userAgent;
    public $endpoint;
    public $curl;

    public function __construct($options)
    {
        $this->options = $options;

        $this->userAgent = 'PayJunctionPHPClient/' .
            '(BrandedCrate; PHP v' .
            phpversion() .
            ')';

        $this->endpoint = $options['endpoint_url'];
    }

    /**
     * @description initializes the curl handle with default configuration and settings
     * @return $this
     */
    public function initCurl()
    {
        $this->curl = curl_init();

        curl_setopt($this->curl, CURLOPT_SSL_VERIFYPEER, 1);
        curl_setopt($this->curl, CURLOPT_SSL_VERIFYHOST, 2);
        curl_setopt($this->curl, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($this->curl, CURLOPT_FORBID_REUSE, true);
        curl_setopt($this->curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
        curl_setopt($this->curl, CURLOPT_USERPWD, $this->options['username'] . ":" . $this->options['password']);
        curl_setopt($this->curl, CURLOPT_HTTPHEADER, array(
            "X-PJ-Application-Key: {$this->options['appkey']}",
            "User-Agent: $this->userAgent",
        ));

        return $this;
    }


    /**
     * @param $response
     * @return bool|mixed
     * @throws PayjunctionException
     */
    public function processResponse($response)
    {
        $contentType = curl_getinfo($this->curl, CURLINFO_CONTENT_TYPE);
        $responseCode = curl_getinfo($this->curl, CURLINFO_HTTP_CODE);
        $contentLength = curl_getinfo($this->curl, CURLINFO_CONTENT_LENGTH_DOWNLOAD);

        // the content is json, so parse it
        if ($contentType == 'application/json') {
            $response = json_decode($response);
        }

        // error, throw an exception
        if ($responseCode < 200 || $responseCode >= 300) {
            throw new PayjunctionException($response, $responseCode);
        }

        // successful, but no content. return true
        if ($contentLength == 0) {
            return true;
        }

        return $response;
    }


    /**
     * @description processes a curl post request
     * @param $path
     * @param null $params
     * @return array|mixed
     */
    public function post($path, $params = null)
    {
        $this->initCurl();

        curl_setopt($this->curl, CURLOPT_POST, true);
        curl_setopt($this->curl, CURLOPT_URL, $this->endpoint . $path);

        if (is_object($params) || is_array($params)) {
            curl_setopt($this->curl, CURLOPT_POSTFIELDS, http_build_query($params));
        }

        return $this->processResponse(curl_exec($this->curl));
    }

    /**
     * @description processes a curl get request
     * @param $path
     * @param null $params
     * @return array|mixed
     */
    public function get($path, $params = null)
    {
        $this->initCurl();

        //create the query string if there are any parameters that need to be passed
        $query_string = "";
        if (!is_null($params)) {
            $query_string = "?" . http_build_query($params, '', '&');
        }

        curl_setopt($this->curl, CURLOPT_HTTPGET, true);
        curl_setopt($this->curl, CURLOPT_URL, $this->endpoint . $path . $query_string);


        $response = $this->processResponse(curl_exec($this->curl));
        $responseCode = curl_getinfo($this->curl, CURLINFO_HTTP_CODE);

        // for some reason payjunction returns 204 instead of 404
        if ($responseCode === 204) {
            return false;
        }

        return $response;
    }


    /**
     * @description processes a curl put request
     * @param $path
     * @param null $params
     * @return array|mixed
     */
    public function put($path, $params = null)
    {
        $this->initCurl();

        curl_setopt($this->curl, CURLOPT_CUSTOMREQUEST, "PUT");
        if (is_object($params) || is_array($params)) {
            curl_setopt($this->curl, CURLOPT_POSTFIELDS, http_build_query($params));
        }
        curl_setopt($this->curl, CURLOPT_URL, $this->endpoint . $path);

        return $this->processResponse(curl_exec($this->curl));
    }

    /**
     * @description processes a curl delete request
     * @param $path
     * @param null $params
     * @return array|mixed
     */
    public function del($path, $params = null)
    {
        $this->initCurl();

        curl_setopt($this->curl, CURLOPT_CUSTOMREQUEST, "DELETE");

        if (is_object($params) || is_array($params)) {
            curl_setopt($this->curl, CURLOPT_POSTFIELDS, http_build_query($params));
        }
        curl_setopt($this->curl, CURLOPT_URL, $this->endpoint . $path);

        return $this->processResponse(curl_exec($this->curl));
    }


    /**
     * @description returns an instance of the receipt client
     * @return PayjunctionReceiptClient
     */
    public function receipt()
    {
        if (!isset($this->receiptClient) && isset($this->options)) {
            $this->receiptClient = new PayjunctionReceiptClient($this->options);
        }
        return $this->receiptClient;
    }


    /**
     * @description returns an instance of the transaction client
     * @return PayjunctionTransactionClient
     */
    public function transaction()
    {
        if (!isset($this->transactionClient) && isset($this->options)) {
            $this->transactionClient = new PayjunctionTransactionClient($this->options);
        }
        return $this->transactionClient;

    }
}
