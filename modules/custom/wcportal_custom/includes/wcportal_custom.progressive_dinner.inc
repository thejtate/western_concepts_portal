<?php
/**
 * @file
 * Progressing dining reservation form functionality.
 */

/**
 * Get array of available time
 * @return array
 *  'database time format' => 'Display time format'
 */
function wcportal_custom_progressive_dinner_available_time() {
  return array(
    '18:00:00' => '6:00 PM',
    '19:00:00' => '7:00 PM',
  );
}


function wcportal_custom_progressive_dinner_reservation_form($form, &$form_state) {
  $card_types = array(
    'mastercard' => 'Mastercard',
    'visa' => 'Visa',
    'discover' => 'Discover',
    'am' => 'American express'
  );


  $form['#prefix'] = '<div id="progressive-dinner-reservation-form-wrapper">';
  $form['#suffix'] = '</div>';

  //Personal Information
  $form['party'] = array(
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 1,
    '#tree' => TRUE,
    '#attributes' => array('class' => array('form-fieldset')),
  );

  $form['party']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name of your party'),
    '#size' => 60,
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['party']['date'] = array(
    '#type' => 'date_popup',
    '#title' => t('Date'),
    '#date_type' => DATE_DATETIME,
    '#date_timezone' => date_default_timezone(),
    '#date_format' => DATE_FORMAT_DATE,
    '#date_increment' => 1,
    '#date_year_range' => '-0:+3',
    '#datepicker_options' => array(
      'minDate' => +14,
      'dinnerReservationDateRange' => 1, //flag for finding in js this datepicker field
    ),
    '#ajax' => array(
      'callback' => '_ajax_dinner_available_time_for_date',
      'wrapper' => 'ajax-replace-time',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ),
    ),
    '#required' => TRUE,
  );

  $available_time = wcportal_custom_progressive_dinner_available_time();

  $form['party']['time'] = array(
    '#type' => 'select',
    '#title' => t('Time'),
    '#options' => $available_time,
    '#required' => TRUE,
    '#disabled' => TRUE,
    '#empty_option' => t('Select date'),
  );

  //date change ajax processing, get available time
  if (!empty($form_state['values']['party']['date'])) {
    $reserved_time_array = wcportal_custom_check_reserved_dinner_time($form_state['values']['party']['date']);
    //remove time that already reserved for this date
    foreach ($form['party']['time']['#options'] as $key => $value) {
      if (in_array($key, $reserved_time_array)) {
        unset($form['party']['time']['#options'][$key]);
      }
    }
    //set first time as default
    if(!empty($form['party']['time']['#options'])) {
      $form['party']['time']['#default_value'] = key($form['party']['time']['#options']);
      $form['party']['time']['#disabled'] = FALSE;
      if(!empty($form['party']['time']['#empty_option'])) {
        unset($form['party']['time']['#empty_option']);
      }
    } else {
      //set flag if all available times for this date are sold out
      $form['party']['all_day_time_reserved'] = array(
        '#type' => 'value',
        '#value' => TRUE
      );
    }
  }

  $form['party']['guests'] = array(
    '#type' => 'select',
    '#title' => t('No. of guests'),
    '#options' => array(
      '1' => '1',
      '2' => '2',
      '3' => '3',
      '4' => '4',
      '5' => '5',
      '6' => '6',
      '7' => '7',
      '8' => '8',
      '9' => '9',
      '10' => '10',
    ),
    '#default_value' => 1,
    '#ajax' => array(
      'callback' => '_ajax_dinner_total_price_callback',
      'wrapper' => 'ajax-replace-total-price',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ),
    ),
    '#required' => TRUE,
  );

  $price = variable_get('wc_shop_settings_progressive_dinner_price', 0);
  $form['party']['total'] = array(
    '#type' => 'textfield',
    '#title' => t('Your total ($@price per guest)', array('@price' => $price)),
    '#size' => 5,
    '#maxlength' => 128,
    '#default_value' => 1 * $price,
    //'#required' => TRUE,
    '#disabled' => TRUE,
  );

  // number of guest changed, ajax processing, calculate total amount
  if (!empty($form_state['values']['party']['guests'])) {
    $form['party']['total']['#value'] = variable_get('wc_shop_settings_progressive_dinner_price', 0) * $form_state['values']['party']['guests'];
  }

  $form['party']['description'] = array(
    '#type' => 'item',
    '#markup' => '<p>' . t('Because these dinners are so unique, we do require a minimum of two weeks advanced reservation. Availability of a Western Concepts Progressive Dinner is limited to Tuesday, Wednesday or Thursday evening.') . '</p>',
  );

  //Personal Information
  $form['personal_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Personal Information'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 2,
    '#tree' => TRUE,
    '#attributes' => array('class' => array('form-fieldset')),
  );

  $form['personal_info']['first_name'] = array(
    '#type' => 'textfield',
    '#title' => t('First Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('First Name')),
    '#required' => TRUE,
  );

  $form['personal_info']['last_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Last Name'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Last Name')),
    '#required' => TRUE,
  );

  $form['personal_info']['company'] = array(
    '#type' => 'textfield',
    '#title' => t('Company'),
    '#size' => 60,
    '#attributes' => array('placeholder' => t('Company')),
    '#maxlength' => 128,
  );
  $form['personal_info']['address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#attributes' => array('placeholder' => t('Address')),
    '#size' => 120,
    '#required' => TRUE,
  );

  $form['personal_info']['city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('City')),
    '#required' => TRUE,
  );

  $form['personal_info']['state'] = array(
    '#type' => 'textfield',
    '#title' => t('State'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('State')),
    '#required' => TRUE,
  );

  $form['personal_info']['zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip'),
    '#size' => 6,
    '#maxlength' => 6,
    '#attributes' => array('placeholder' => t('Zip')),
    '#required' => TRUE,
  );

  $form['personal_info']['home_phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Home Phone'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Home Phone')),
  );

  $form['personal_info']['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email'),
    '#size' => 60,
    '#maxlength' => 128,
    '#attributes' => array('placeholder' => t('Email')),
    '#required' => TRUE,
  );


  // Payment
  $form['payment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Payment Information'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#weight' => 3,
    '#tree' => TRUE,
    '#attributes' => array('class' => array('form-fieldset')),
    '#required' => TRUE,
  );

  $form['payment']['card'] = array(
    '#type' => 'select',
    '#title' => t('Select card type'),
    '#options' => $card_types,
    '#required' => TRUE,
  );

  $form['payment']['exp'] = array(
    '#type' => 'masked_input',
    '#title' => t('Expiration Date'),
    '#mask' => '99-99',
    '#attributes' => array('placeholder' => 'mm-yy'),
    '#size' => 5,
    '#required' => TRUE,
  );

  $form['payment']['code'] = array(
    '#type' => 'masked_input',
    '#title' => t('Security Code'),
    '#mask' => '999?9',
    '#attributes' => array('placeholder' => 'SECURITY CODE'),
    '#size' => 5,
    '#required' => TRUE,
  );

  $form['payment']['number'] = array(
    '#type' => 'masked_input',
    '#mask' => '9999-9999-9999-999?9',
    '#value_callback' => 'wc_payment_masked_input_clean_mask_value',
    '#title' => t('Card Number'),
    '#attributes' => array('placeholder' => t('Card Number')),
    '#required' => TRUE,
  );

  $form['payment']['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name as it appears on card'),
    '#attributes' => array('placeholder' => t('Name as it appears on card')),
    '#required' => TRUE,
  );


  $form['submit'] = array('#type' => 'submit', '#value' => t('Submit'), '#weight' => 10);
  $form['submit']['#prefix'] = '<div class="btn-wrapp"><div class="btn-submit">';
  $form['submit']['#suffix'] = '</div></div>';

  $form['#attached']['js'][] = drupal_get_path('module', 'wcportal_custom') . '/js/wcportal_reservation_dinner.js';
  $form['#attached']['css'][] = drupal_get_path("module", "wcportal_custom") . "/css/wcportal_reservation_dinner.css";

  $form['#attributes'] = array(
    'class' => array('dinner-reservation-form'),
  );

  return $form;
}


function wcportal_custom_progressive_dinner_reservation_form_validate(&$form, &$form_state) {
  if (module_exists('inline_messages')) {
    //HACK for form inline message, use custom inline_message function,
    //because default inline_messages_form_alter() bugged for this form
    if(!empty($form_state['clicked_button']['#value']) && $form_state['clicked_button']['#value'] == $form['submit']['#value']) {
      $form_id = $form['#form_id'];
      wcportal_custom_inline_messages_form_alter($form, $form_state, $form_id);
    }
  }

  $is_date_valid = wcportal_custom_progressive_dinner_validate_date($form, $form_state);

  if (module_exists("wc_payment") && $is_date_valid &&
    !empty($form_state['clicked_button']['#value']) && $form_state['clicked_button']['#value'] == t('Submit')) {

    $values = (isset($form_state['values'])) ? $form_state['values'] : array();
    $r_name = (isset($values['party']['name'])) ? $values['party']['name'] : "";
    $r_date = (isset($values['party']['date'])) ? $values['party']['date'] : "";
    $r_time = (isset($values['party']['time'])) ? $values['party']['time'] : "";
    $r_number_of_guests = (isset($values['party']['guests'])) ? $values['party']['guests'] : 0;

    $total = variable_get('wc_shop_settings_progressive_dinner_price', 0) * $r_number_of_guests;
    $amount = $total;
    $order_data = array(
      'cart' => wcportal_custom_progressive_dinner_reservation_create_cart($total, $r_name, $r_date, $r_time, $r_number_of_guests),
      'total' => array(
        'subtotal' => $total,
        'total' => $total,
        'shipping' => 0,
      ),
    );

    $exp = (isset($values['payment']['exp'])) ? $values['payment']['exp'] : " - ";
    $exp = explode("-", $exp);
    if (count($exp) >= 2 && !empty($r_name) && !empty($r_date) && !empty($r_time) && !empty($r_number_of_guests)) {
      list($exp_month, $exp_year) = $exp;
      $data = array(
        'first_name' => (isset($values['personal_info']['first_name'])) ? $values['personal_info']['first_name'] : "",
        'last_name' => (isset($values['personal_info']['last_name'])) ? $values['personal_info']['last_name'] : "",
        'address' => (isset($values['personal_info']['address'])) ? $values['personal_info']['address'] : "",
        'city' => (isset($values['personal_info']['city'])) ? $values['personal_info']['city'] : "",
        'state' => (isset($values['personal_info']['state'])) ? $values['personal_info']['state'] : "",
        'zip' => (isset($values['personal_info']['zip'])) ? $values['personal_info']['zip'] : "",
        'email' => (isset($values['personal_info']['email'])) ? $values['personal_info']['email'] : "",
        'phone' => (isset($values['personal_info']['home_phone'])) ? $values['personal_info']['home_phone'] : "",
        'company' => (isset($values['personal_info']['company'])) ? $values['personal_info']['company'] : "",
        'number' => (isset($values['payment']['number'])) ? $values['payment']['number'] : "",
        'exp_month' => $exp_month,
        'exp_year' => $exp_year,
        'cvs' => (isset($values['payment']['code'])) ? $values['payment']['code'] : "",
        'card_name' => (isset($values['payment']['name'])) ? $values['payment']['name'] : "",
        'amount' => $amount,
        'notes' => "progressive_dinner_reservation",
        'description' => "progressive_dinner_reservation",
        'order_data' => serialize($order_data),
      );

      $result = wc_payment_make_payment($data);

      wc_shop_prepare_mail($result, $data, "progressive_dinner");

      $data['pid'] = (isset($result['data']['pid'])) ? $result['data']['pid'] : "";

      if(isset($result['status']) && $result['status']) {
        wcportal_custom_progressive_dinner_reservation_save($data);
      }

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

/**
 * Save dinner reservation
 */
function wcportal_custom_progressive_dinner_reservation_save($data) {
    $order_data = unserialize($data['order_data']);
    $data = array(
      'pid' => $data['pid'],
      'party_date' => $order_data['cart'][0]['r_date'] . ' ' . $order_data['cart'][0]['r_time'],
      'guests_count' => $order_data['cart'][0]['count'],
      'party_name' => $order_data['cart'][0]['r_name'],
    );

    wcportal_custom_save_progressive_dinner_reservation($data);
}

function wcportal_custom_progressive_dinner_reservation_form_submit($form, &$form_state) {
  drupal_set_message(t("Thanks so much for your reservation. Your personal concierge should be contacting you soon.."));
}

/**
 * Form ajax callback, calculate total price
 */
function _ajax_dinner_total_price_callback($form, $form_state) {
  return $form['party']['total'];
}

/**
 * Form ajax callback, calculate available time
 */
function _ajax_dinner_available_time_for_date($form, $form_state) {
  if(empty($form['party']['all_day_time_reserved']['#value'])) {
    return $form['party']['time'];
  } else {
    $commands = array();
    $commands[] = ajax_command_alert('Sorry, all available times for this date are sold out. Please choose a different date. Thank you.');
    return array('#type' => 'ajax', '#commands' => $commands);
  }

}

/**
 * Save dinner reservation to database
 *
 */
function wcportal_custom_save_progressive_dinner_reservation($data) {
  drupal_write_record('dinner_reservation', $data);
}

/**
 * Delete dinner reservation
 *
 * @param integer $pid
 * Order payment id
 */
function wcportal_custom_delete_dinner_reservation($pid) {
  db_delete('dinner_reservation')
    ->condition('pid', $pid)
    ->execute();
}

/**
 * Get array of already reserved date times
 *
 * @param $date
 * Date in Y-m-d format
 * @return array of time
 * in H:i:s format
 */
function wcportal_custom_check_reserved_dinner_time($date) {
  $res = db_select('dinner_reservation', 'd')
    ->fields('d', array('party_date'))
    ->condition('d.party_date', $date . '%', 'LIKE')
    ->execute()
    ->fetchCol(0);

  $time_array = array();

  foreach ($res as $date_time) {
    $time_array[] = date('H:i:s', strtotime($date_time));
  }

  return $time_array;
}

/**
 * Check if this datetime already reserved
 *
 * @param string $datetime
 * DateTime in "Y-m-d H:i:s" format
 * @return string
 * return reservation array data if this datetime reserved or FALSE
 */
function wcportal_custom_check_reserved_dinner_date_time($datetime) {
  $res = db_select('dinner_reservation', 'd')
    ->fields('d')
    ->condition('d.party_date', $datetime)
    ->execute()
    ->fetchAssoc();

  return $res;
}

/**
 * Get days where all time already reserved
 */
function wcportal_custom_get_full_reserved_days() {

  $max_time_count = count(wcportal_custom_progressive_dinner_available_time());

  $default_timezone = new DateTimeZone(date_default_timezone());
  $start_date = new DateTime('now +14day', $default_timezone);

  $query = db_select('dinner_reservation', 'd')
    ->fields('d', array('party_date'))
    ->condition('d.party_date', $start_date->format('Y-m-d'), '>');

  $query->addExpression("DATE_FORMAT(party_date, '%Y-%c-%e')", 'day');//format 2013-1-5
  $query->addExpression('COUNT(*)', 'day_count');
  $query->having('day_count >= :max_count', array(':max_count' => $max_time_count));
  $query->groupBy('day');

  $res = $query->execute()
    ->fetchAll();

  $dates_array = array();

  foreach ($res as $raw) {
    $dates_array[] = $raw->day;
  }

  return $dates_array;
}


/**
 * Emulate cart for saving to database.
 * @param $price
 * @return array
 */
function wcportal_custom_progressive_dinner_reservation_create_cart($price, $r_name, $r_date, $r_time, $r_number_of_guests) {
  $cart = array();
  $node = new StdClass();
  $node->title = t("Progressive Dinner Reservation");
  $cart[0] = array(
    'price' => $price,
    'r_name' => $r_name,
    'r_date' => $r_date,
    'r_time' => $r_time,
    'r_number_of_guests' => $r_number_of_guests,
    'count' => 1,
    'node' => $node
  );
  return $cart;
}

/**
 * Function for display inline message,
 * based on inline_messages_form_alter()
 * @see inline_messages_form_alter();
 */
function wcportal_custom_inline_messages_form_alter(&$form, &$form_state, $form_id) {
  // hide the preview button?
  if (variable_get('inline_messages_hide_preview', FALSE)) {
    unset($form['preview']);
  }

  // change the comment form submit button if specified
  if ($form_id == 'comment_form') {
    if (variable_get('inline_messages_form_comment_submit', NULL)) {
      $form['submit']['#value'] = variable_get('inline_messages_form_comment_submit', NULL);
    }
  }

  $enabled = TRUE;

  // add the js, make sure the scrollto plugin exists first
  if ($enabled && file_exists(variable_get('inline_messages_scrollto_path', SCROLLTO_PATH_DEFAULT))) {
    // add submit handler to store the form_id
    //$form['#submit'][] = 'inline_messages_submit_form';

    // a page can have multiple forms, so we need to get the id of the submitted
    // form to target. if a form is still in progress (aka error, multistep) we
    // can use $form_state. after a form is completed we need to use the
    // session variable.
    if (
      (isset($form_state['input']['form_id']) && $form_state['input']['form_id'] == $form_id) ||
      (isset($_SESSION['form_submitted']) && $_SESSION['form_submitted'] == $form_id)
    ) {
      // add js
      drupal_add_js(drupal_get_path('module', 'inline_messages') . '/js/inline_messages.js');
      if(!empty($form['#id'])) {
        drupal_add_js(array('form_submitted' => $form['#id']), 'setting');
      } else {
        drupal_add_js(array('form_submitted' => str_replace('_', '-', inline_messages_form_id($form['']))), 'setting');
      }



      $settings = array(
        'duration' => (int) variable_get('inline_messages_scrollto_duration', 0),
        'offset' => (int) variable_get('inline_messages_scrollto_offset', 0)
      );
      drupal_add_js(array('inline_messages_scrollto' => $settings), 'setting');
      drupal_add_js(variable_get('inline_messages_scrollto_path', SCROLLTO_PATH_DEFAULT), array('group' => JS_LIBRARY));

      // unset session
      if (isset($_SESSION['form_submitted'])) unset($_SESSION['form_submitted']);
    }
  }
}

/**
 * Date and time form validation
 */
function wcportal_custom_progressive_dinner_validate_date(&$form, &$form_state) {
  if(!empty($form_state['values']['party']['date']) && !empty($form_state['values']['party']['time'])) {
    $date_string = $form_state['values']['party']['date'] . ' ' . $form_state['values']['party']['time'];
    //check +14 days advanced reservation
    $default_timezone = new DateTimeZone(date_default_timezone());
    $input_date = DateTime::createFromFormat('Y-m-d H:i:s', $date_string, $default_timezone);
    $start_date = new DateTime('now +14day', $default_timezone);
    if(!empty($input_date)) {

      if($input_date < $start_date) {
        form_set_error('party][date', 'Choose other Date. We do require a minimum of two weeks advanced reservation');
        return FALSE;
      } else {
        //check if this date already reserved
        if(wcportal_custom_check_reserved_dinner_date_time($date_string)) {
          form_set_error('party][date', 'Please choose a different Date or Time. Time for this date is sold out.');
          return FALSE;
        }

      }

    }
  }
  return TRUE;
}

/**
 * Implements hook_wc_payment_orders_status_update_alter().
 */
function wcportal_custom_wc_payment_orders_status_update_alter(&$pid, &$new_status) {

  $order = wcportal_custom_get_order_by_pid($pid);
  if($order['description'] == 'progressive_dinner_reservation') {

    $old_status = $order['order_status'];
    if(($old_status == ORDER_STATUS_FAILED || $old_status == ORDER_STATUS_TEST_FAILED)
        && ($new_status == ORDER_STATUS_COMPLETE || $new_status == ORDER_STATUS_IN_PROGRESS || $new_status == ORDER_STATUS_SUCCESS || $new_status == ORDER_STATUS_TEST_SUCCESS)) {
      //reserve this dinner time
      $order_data = unserialize($order['order_data']);
      $party_name = !empty($order_data['cart'][0]['r_name']) ? $order_data['cart'][0]['r_name'] : '';
      $party_date = !empty($order_data['cart'][0]['r_date']) ? $order_data['cart'][0]['r_date'] : '';
      $party_time = !empty($order_data['cart'][0]['r_time']) ? $order_data['cart'][0]['r_time'] : '';
      $other_reservation = wcportal_custom_check_reserved_dinner_date_time($party_date . ' ' . $party_time);

      if(!$other_reservation) {
        drupal_set_message(t('Add dinner reservation for party "@name" @date @time', array('@date' => $party_date, '@time' => $party_time, '@name' => $party_name)));
        wcportal_custom_progressive_dinner_reservation_save($order);
      } else {
        $other_reservation_order = wcportal_custom_get_order_by_pid($other_reservation['pid']);

        $other_reservation_order_data = unserialize($order['order_data']);
        $party_name = !empty($other_reservation_order_data['cart'][0]['r_name']) ? $other_reservation_order_data['cart'][0]['r_name'] : '';
        $party_date = !empty($other_reservation_order_data['cart'][0]['r_date']) ? $other_reservation_order_data['cart'][0]['r_date'] : '';
        $party_time = !empty($other_reservation_order_data['cart'][0]['r_time']) ? $other_reservation_order_data['cart'][0]['r_time'] : '';
        $tid = !empty($other_reservation_order['tid']) ? $other_reservation_order['tid'] : 0;
        drupal_set_message(t('Error reserving party, because this date/time reserved by other party "@name" @date @time transaction id: @tid',
          array('@date' => $party_date, '@time' => $party_time, '@name' => $party_name, '@tid' => $tid)), 'error');
        //disable change status
        $new_status = $old_status;
      }

    } else if(($old_status == ORDER_STATUS_COMPLETE || $old_status == ORDER_STATUS_IN_PROGRESS || $old_status == ORDER_STATUS_SUCCESS || $old_status == ORDER_STATUS_TEST_SUCCESS)
      &&($new_status == ORDER_STATUS_FAILED || $new_status == ORDER_STATUS_TEST_FAILED) ) {
      //unset reservation for this dinner time
      $order_data = unserialize($order['order_data']);

      $party_name = !empty($order_data['cart'][0]['r_name']) ? $order_data['cart'][0]['r_name'] : '';
      $party_date = !empty($order_data['cart'][0]['r_date']) ? $order_data['cart'][0]['r_date'] : '';
      $party_time = !empty($order_data['cart'][0]['r_time']) ? $order_data['cart'][0]['r_time'] : '';
      drupal_set_message(t('Remove dinner reservation for party "@name" @date @time', array('@date' => $party_date, '@time' => $party_time, '@name' => $party_name)));
      wcportal_custom_delete_dinner_reservation($order['pid']);
    }
  }
}

function  wcportal_custom_get_order_by_pid($pid) {
  $order = db_select('wc_payment_results', 'r')
    ->fields('r')
    ->condition('r.pid', $pid)
    ->execute()
    ->fetchAssoc();
  return $order;
}