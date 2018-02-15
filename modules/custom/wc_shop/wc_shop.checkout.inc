<?php

/**
 * @file
 * Checkout shopping implementation functions.
 */


/**
 * Check out page callback
 */
function wc_shop_checkout() {
  // cart
  $cart = wc_shop_get_cart();
  if (empty($cart)) {
    drupal_goto("shop");
  }

  $vars['cart'] = theme('wc_shop_cart_checkout', array('cart' => $cart));
  $vars['checkout_form'] = drupal_get_form("wc_shop_checkout_form");

  return theme('wc_shop_checkout', array('cart' => $cart, 'vars' => $vars));
}


function wc_shop_checkout_form($form, &$form_state) {
  $card_types = array(
    'mastercard' => 'Mastercard',
    'visa' => 'Visa',
    'discover' => 'Discover',
    'am' => 'American express'
  );

  // Billing
  $form['billing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Billing Information'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 1,
  );

  $form['billing']['billing_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('First Name')),
    '#required' => TRUE,
  );

  $form['billing']['billing_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Last Name')),
    '#required' => TRUE,
  );

  $form['billing']['billing_company'] = array(
    '#type' => 'textfield',
    '#title' => t('Company'),
    '#size' => 60,
    '#attributes' => array('placeholder' => t('Company')),
    '#maxlength' => 128,
  );

  $form['billing']['billing_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#attributes' => array('placeholder' => t('Address')),
    '#size' => 120,
    '#required' => TRUE,
  );

  $form['billing']['billing_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('City')),
    '#required' => TRUE,
  );

  $form['billing']['billing_state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('State')),
    '#required' => TRUE,
  );

  $form['billing']['billing_zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 6,
    '#maxlength' => 6,
    '#attributes' => array('placeholder' => t('Zip')),
    '#required' => TRUE,
  );

  $form['billing']['billing_home_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Home Phone'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Home Phone')),
  );

  $form['billing']['billing_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Email')),
    '#required' => TRUE,
  );


  // Shipping
  $form['shipping'] = array(
    '#type' => 'fieldset',
    '#title' => t('Shipping Information'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 2,
  );

  $form['shipping']['same_as_billing'] = array(
    '#type' => 'checkbox',
    '#title' => t('Same as Billing Information'),
    '#attributes' => array('class' => array('shop-copy-information')),
  );


  $form['shipping']['shipping_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('First Name')),
  );

  $form['shipping']['shipping_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Last Name')),
  );

  $form['shipping']['shipping_company'] = array(
    '#type' => 'textfield',
    '#title' => t('Company'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Company')),
  );
  $form['shipping']['shipping_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#size' => 120,
    '#attributes' => array('placeholder' => t('Address')),
  );

  $form['shipping']['shipping_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('City')),
  );

  $form['shipping']['shipping_state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('State')),
  );

  $form['shipping']['shipping_zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 6,
    '#maxlength' => 6,
    '#attributes' => array('placeholder' => t('Zip')),
  );


  // Payment
  $form['payment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Payment Information'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 3,
  );

  $form['payment']['card'] = array(
    '#type' => 'select',
    '#title' => t('Select card type'),
    '#options' => $card_types,
  );

  $form['payment']['exp'] = array(
    '#type' => 'masked_input',
    '#title' => t('Expiration Date'),
    '#mask' => '99-99',
    '#attributes' => array('placeholder' => 'mm-yy', 'autocomplete' => 'off'),
    '#size' => 5,
    '#required' => TRUE,
  );

  $form['payment']['code'] = array(
    '#type' => 'masked_input',
    '#title' => t('Security Code'),
    '#mask' => '999?9',
    '#attributes' => array('placeholder' => 'SECURITY CODE', 'autocomplete' => 'off'),
    '#size' => 5,
    '#required' => TRUE,
  );

  $form['payment']['number'] = array(
    '#title' => t('Card Number'),
    '#type' => 'masked_input',
    '#mask' => '9999-9999-9999-999?9',
    '#value_callback' => 'wc_payment_masked_input_clean_mask_value',
    '#attributes' => array('placeholder' => t('Card Number'), 'autocomplete' => 'off'),
    '#required' => TRUE,
  );

  $form['payment']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name as it appears on card'),
    '#attributes' => array('placeholder' => t('Name as it appears on card'), 'autocomplete' => 'off'),
    '#required' => TRUE,
  );


  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'), '#weight' => 10);
  $form['submit']['#prefix'] = '<div class="btn-wrapp"><div class="btn-submit">';
  $form['submit']['#suffix'] = '</div></div>';

  $form['#attached']['js'][] = drupal_get_path("module", "wc_shop") . "/js/wc_shop.js";
  $form['#attached']['css'][] = drupal_get_path("module", "wc_shop") . "/css/wc_shop.css";

  return $form;
}


function wc_shop_checkout_form_validate($form, &$form_state) {

  if (module_exists("wc_payment")) {
    $values = (isset($form_state['values'])) ? $form_state['values'] : array();
    $order_data = wc_shop_checkout_prepare_cart();

    $session_sites = &wc_shop_get_session_cart_sites();
    $sites = _wc_shop_get_sites();

    foreach ($order_data['cart'] as $key => $row) {
      if (isset($session_sites[$key]) && !empty($session_sites[$key])){
        $order_data['cart'][$key]['sites'] = '';

        foreach ($session_sites[$key] as $site => $cart_amount) {
          $order_data['cart'][$key]['sites'] .= $sites[$site] . ': ' . $cart_amount . '<br/>';
        }
      }
    }

    $amount = (isset($order_data['total']['total']) && !empty($order_data['total']['total'])) ? $order_data['total']['total'] : 0.00;

    //zip should be numeric
    if (isset($values['billing_zip']) && !empty($values['billing_zip']) && !is_numeric($values['billing_zip'])){
      form_set_error("billing_zip", t('Zip should be numeric.'));
      return false;
    }
    if (isset($values['shipping_zip']) && !empty($values['shipping_zip']) && !is_numeric($values['shipping_zip'])){
      form_set_error("shipping_zip", t('Zip should be numeric.'));
      return false;
    }


    // required fields validation
    $required_fields = array('billing_first_name', 'billing_last_name', 'billing_address', 'billing_city', 'billing_state', 'billing_zip', 'billing_email', 'billing_home_phone');
    $validate_status = TRUE;
    foreach($required_fields as $field) {
      if (isset($values[$field]) && empty($values[$field])){
        form_set_error($field, t('Please fill required fields.'));
        $validate_status = FALSE;
      }
    }

    if (!$validate_status) {
      return FALSE;
    }



    $exp = (isset($values['exp'])) ? $values['exp'] : "  - ";
    $exp = explode("-", $exp);
    if (count($exp) >= 2) {
      list($exp_month, $exp_year) = $exp;
      $data = array(
        'first_name' => (isset($values['billing_first_name'])) ? $values['billing_first_name'] : "",
        'last_name' => (isset($values['billing_last_name'])) ? $values['billing_last_name'] : "",
        'address' => (isset($values['billing_address'])) ? $values['billing_address'] : "",
        'city' => (isset($values['billing_city'])) ? $values['billing_city'] : "",
        'state' => (isset($values['billing_state'])) ? $values['billing_state'] : "",
        'zip' => (isset($values['billing_zip']) && is_numeric($values['billing_zip'])) ? $values['billing_zip'] : NULL,
        'email' => (isset($values['billing_email'])) ? $values['billing_email'] : "",
        'phone' => (isset($values['billing_home_phone'])) ? $values['billing_home_phone'] : "",
        'company' => (isset($values['billing_company'])) ? $values['billing_company'] : "",

        'billing_first_name' => (isset($values['billing_first_name'])) ? $values['billing_first_name'] : "",
        'billing_last_name' => (isset($values['billing_last_name'])) ? $values['billing_last_name'] : "",

        'shipping_first_name' => (isset($values['shipping_first_name'])) ? $values['shipping_first_name'] : "",
        'shipping_last_name' => (isset($values['shipping_last_name'])) ? $values['shipping_last_name'] : "",
        'shipping_address' => (isset($values['shipping_address'])) ? $values['shipping_address'] : "",
        'shipping_city' => (isset($values['shipping_city'])) ? $values['shipping_city'] : "",
        'shipping_state' => (isset($values['shipping_state'])) ? $values['shipping_state'] : "",
        'shipping_zip' => (isset($values['shipping_zip'])) ? $values['shipping_zip'] : "",
        'shipping_company' => (isset($values['shipping_company'])) ? $values['shipping_company'] : "",

        'number' => (isset($values['number'])) ? $values['number'] : "",
        'exp_month' => $exp_month,
        'exp_year' => $exp_year,
        'cvs' => (isset($values['code'])) ? $values['code'] : "",
        'card_name' => (isset($values['name'])) ? $values['name'] : "",
        'amount' => $amount,
        'notes' => "portal",
        'description' => "store",
        'order_data' => serialize($order_data),
      );

      $result = wc_payment_make_payment($data);
      wc_shop_prepare_mail($result, $data);


      if (!isset($result['status']) || !$result['status']) {
        $form_state['error'] = TRUE;
        form_set_error('', $result['message']);
        return FALSE;
      }
      // decrease stock
      wc_shop_decrease_products($order_data);
    } else {
      return FALSE;
    }
  }
  return TRUE;
}


function wc_shop_checkout_form_submit($form, &$form_state) {
  wc_shop_clear_cart();
  drupal_set_message(t("Thank you! We will email you when your product ships. Save the receipt sent to your email for your records."));
}


/**
 * Prepare cart to save in database
 * @return string
 */
function wc_shop_checkout_prepare_cart() {
  $cart = wc_shop_get_cart();

  $data = array(
    'cart' => $cart,
    'total' => wc_shop_get_cart_total($cart),
  );

  return $data;
}


/**
 * Desrease number product in stock
 *
 * @param $order_data
 */
function wc_shop_decrease_products($order_data) {
  if (isset($order_data['cart']) && is_array($order_data['cart'])) {
    foreach ($order_data['cart'] as $vid => $data) {
      $count = (isset($data['count'])) ? $data['count'] : 0;
      $variant = field_collection_item_load($vid);
      if (isset($variant->field_store_product_stock[LANGUAGE_NONE][0]['value'])) {
        $variant->field_store_product_stock[LANGUAGE_NONE][0]['value'] -= $count;
      }
      $variant->save();
    }
  }
}
