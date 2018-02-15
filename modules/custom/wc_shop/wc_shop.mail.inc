<?php

/**
 * @file
 * Mail implementation functions.
 */


/**
 * Prepare shop emails
 * @param $result
 * @param $data
 */
function wc_shop_prepare_mail($result, $data, $key = "store") {

  // Prepare Emails
  $data['error_message'] = (isset($result['message'])) ? $result['message'] : "";
  $data['pid'] = (isset($result['data']['pid'])) ? $result['data']['pid'] : "";
  $data['transaction_id'] = (isset($result['data']['dc_transaction_id'])) ? $result['data']['dc_transaction_id'] : "-1";
  $data['transaction_date'] = (isset($result['data']['dc_transaction_date'])) ? $result['data']['dc_transaction_date'] : "-1";

  $data['key'] = $key;

  $admin_emails = variable_get('wc_shop_email_settings_all', "");
  if (empty($admin_emails)){
    $admin_emails = variable_get('site_mail', ini_get('sendmail_from'));
  }

  if (isset($result['status']) && $result['status']) {
    _wc_shop_prepare_gift_cards_data($data, $admin_emails);
    // send to user and admin
    $to = (isset($data['email'])) ? $data['email'] : NULL;
    $subject = t("Receipt #@payment_id as of @transaction_date.", array("@payment_id" => $data['pid'], "@transaction_date" => $data['transaction_date']));
    $html_body = theme("wc_shop_user_mail", array("data" => $data));
    wc_shop_send_mail($to, $subject, $html_body);

    watchdog("admin_emails", "<pre>" . var_export($admin_emails, true) . "</pre>");
    $subject = "New Purchase Notification.";
    $html_body = theme("wc_shop_admin_mail", array("data" => $data));
    wc_shop_send_mail($admin_emails, $subject, $html_body);
  }
  else {
//    // ERRORS : send to admin only
//    $subject = "New Purchase Notification. - Error";
//    $html_body = theme("wc_shop_admin_mail", array("data" => $data));
//    wc_shop_send_mail($admin_emails, $subject, $html_body);
  }
}




function _wc_shop_prepare_gift_cards_data(&$data, &$admin_emails){
  // send to different admins and prepare
  $cart_sites = wc_shop_get_session_cart_sites();
  if (!empty($cart_sites)){
    $order_data = unserialize($data['order_data']);
    if (isset($order_data['cart']) && is_array($order_data['cart'])){
      foreach($order_data['cart'] as $vid => $cart_item){
        if (isset($cart_sites[$vid])){
          foreach($cart_sites[$vid] as $type => $count){
            $admin_emails .= ", " . _wc_shop_get_emails_by_key($type);
            $order_data['cart'][$vid]['gift_type'][$type] = array(
              'title' => _wc_shop_get_titles_by_key($type),
              'count' => $count,
            );
          }
        }
      }
    }
    $data['order_data'] = serialize($order_data);
  }
}


/**
 * Send shop emails
 * @param $to
 * @param $subject
 * @param $html_body
 * @return bool
 */
function wc_shop_send_mail($to, $subject, $html_body) {
  $module = 'wc_shop';
  $key = "wc_shop_shop";
  $from = variable_get('site_mail', ini_get('sendmail_from'));
  $language = language_default();
  $params = array(
    'subject' => $subject,
    'body' => $html_body,
  );
  $params['headers']['Content-Type'] = "text/html; charset=UTF-8; format=flowed; delsp=yes";
  $params['plain'] = FALSE;
  $params['plaintext'] = NULL ;

  $to = str_replace(",,",",", $to);
  $to = str_replace(", ,",",", $to);

  $mail = drupal_mail($module, $key, $to, $language, $params, $from, TRUE);
  if($mail['result']) {
    return TRUE;
  } else {
    $error_msg = 'Failed to send the email in wc_shop_send_mail Module';
    watchdog('wc_shop_send_mail', $error_msg, array(), WATCHDOG_ALERT);
    return FALSE;
  }



}

/**
 * Implements hook_mail().
 */
function wc_shop_mail($key, &$message, $params) {
  if ($key == 'wc_shop_shop') {
    $message['headers'] = array_merge($message['headers'], $params['headers']);
    $message['subject'] = $params['subject'];
    $message['body'][] = $params['body'];
  }
}