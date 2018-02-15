<?php
/**
 * @file Wcportal rewards card members functionality
 */


function wcportal_custom_rewards_card_member_block() {
  $rewards_form = drupal_get_form("wcportal_custom_rewards_card_member_form");
  return render($rewards_form);
}


function wcportal_custom_rewards_card_member_form($form, &$form_state) {
  $card_types = array(
    'mastercard' => 'Mastercard',
    'visa' => 'Visa',
    'discover' => 'Discover',
    'am' => 'American express'
  );

  // Personal information
  $form['personal_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Personal Information'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 1,
  );

  $form['personal_information']['personal_information_first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('First Name')),
    '#required' => TRUE,
  );

  $form['personal_information']['personal_information_last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Last Name')),
    '#required' => TRUE,
  );

  $form['personal_information']['personal_information_birthday'] = array(
    '#type' => 'date_select',
    '#date_format' => 'm-Y',
    '#date_year_range' => '-100:+0',
    '#date_label_position' => 'within',
    '#default_value' => '',
    '#title' => t('Birthday'),
    '#required' => FALSE,
  );


  $form['personal_information']['personal_information_company'] = array(
    '#type' => 'textfield',
    '#title' => t('Company'),
    '#size' => 60,
    '#attributes' => array('placeholder' => t('Company')),
    '#maxlength' => 128,
  );
  $form['personal_information']['personal_information_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#attributes' => array('placeholder' => t('Address')),
    '#size' => 60,
    '#required' => TRUE,
  );

  $form['personal_information']['personal_information_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('City')),
    '#required' => TRUE,
  );

  $form['personal_information']['personal_information_state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('State')),
    '#required' => TRUE,
  );

  $form['personal_information']['personal_information_zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 6,
    '#maxlength' => 6,
    '#attributes' => array('placeholder' => t('Zip')),
    '#required' => TRUE,
  );

  $form['personal_information']['personal_information_home_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Home Phone'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Home Phone')),
  );

  $form['personal_information']['personal_information_email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Email')),
    '#required' => TRUE,
  );

  // Payment Information
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

  $form['payment']['number'] = array(
    '#type' => 'masked_input',
    '#mask' => '9999-9999-9999-999?9',
    '#value_callback' => 'wc_payment_masked_input_clean_mask_value',
    '#title' => t('Card Number'),
    '#attributes' => array('placeholder' => t('Card Number'), 'autocomplete' => 'off'),
    '#required' => TRUE,
  );

  $form['payment']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name as it appears on card'),
    '#attributes' => array('placeholder' => t('Name as it appears on card'), 'autocomplete' => 'off'),
    '#required' => TRUE,
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

  $form['#attached']['js'][] = drupal_get_path("module", "wcportal_custom") . "/js/wcportal_rewards_card_members.js";
  $form['#attached']['css'][] = drupal_get_path("module", "wcportal_custom") . "/css/wcportal_rewards_card_member.css";

  $form['submit'] = array('#type' => 'submit', '#value' => t('Check out'), '#weight' => 10);
  $form['submit']['#prefix'] = '<div class="btn-wrapp"><div class="btn-submit">';
  $form['submit']['#suffix'] = '</div></div>';

  return $form;
}


function wcportal_custom_rewards_card_member_form_validate($form, &$form_state) {
  if (module_exists("wc_payment")) {
    $values = (isset($form_state['values'])) ? $form_state['values'] : array();
    $price = variable_get('wc_shop_settings_rewards_card_price', 0);
    $shipping = variable_get('wc_shop_settings_shipping_price', 0);

    $subtotal = $price;
    $total = $subtotal + $shipping;
    $amount = $total;

    $order_data = array(
      'cart' => wcportal_custom_rewards_card_member_create_cart($price),
      'total' => array(
        'subtotal' => $subtotal,
        'total' => $total,
        'shipping' => $shipping,
      ),
    );

    $exp = (isset($values['exp'])) ? $values['exp'] : " - ";
    $exp = explode("-", $exp);
    if (count($exp) >= 2) {
      list($exp_month, $exp_year) = $exp;

      $data = array(
        'first_name' => (isset($values['personal_information_first_name'])) ? $values['personal_information_first_name'] : "",
        'last_name' => (isset($values['personal_information_last_name'])) ? $values['personal_information_last_name'] : "",
        'birthday' => (isset($values['personal_information_birthday'])) ? $values['personal_information_birthday'] : "",
        'address' => (isset($values['personal_information_address'])) ? $values['personal_information_address'] : "",
        'city' => (isset($values['personal_information_city'])) ? $values['personal_information_city'] : "",
        'state' => (isset($values['personal_information_state'])) ? $values['personal_information_state'] : "",
        'zip' => (isset($values['personal_information_zip'])) ? $values['personal_information_zip'] : "",
        'email' => (isset($values['personal_information_email'])) ? $values['personal_information_email'] : "",
        'phone' => (isset($values['personal_information_home_phone'])) ? $values['personal_information_home_phone'] : "",
        'company' => (isset($values['personal_information_company'])) ? $values['personal_information_company'] : "",
        'number' => (isset($values['number'])) ? $values['number'] : "",
        'exp_month' => $exp_month,
        'exp_year' => $exp_year,
        'cvs' => (isset($values['code'])) ? $values['code'] : "",
        'card_name' => (isset($values['name'])) ? $values['name'] : "",
        'amount' => $amount,
        'notes' => "rewards_card_member",
        'description' => "rewards_card_member",
        'order_data' => serialize($order_data),
      );

      $result = wc_payment_make_payment($data);

      wc_shop_prepare_mail($result, $data);

      if (!isset($result['status']) || !$result['status']) {
        $form_state['error'] = TRUE;
        form_set_error('', $result['message']);
        return FALSE;
      }
    }
    else {
      form_set_error('', t("Please fill required fields"));
      return FALSE;
    }
  }
  return TRUE;
}

function wcportal_custom_rewards_card_member_form_submit($form, &$form_state) {
  drupal_set_message(t("Thank you! We will email you when your product ships. Save the receipt sent to your email for your records."));
}


/**
 * Emulate cart for saving to database.
 * @param $price
 * @return array
 */
function wcportal_custom_rewards_card_member_create_cart($price) {
  $cart = array();
  $node = new StdClass();
  $node->title = t("Rewards Card Members");
  $cart[0] = array(
    'price' => $price,
    'count' => 1,
    'node' => $node
  );
  return $cart;
}