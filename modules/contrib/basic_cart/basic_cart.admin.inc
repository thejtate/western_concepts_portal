<?php

/**
 * @file
 * Basic cart admin settings forms.
 */

/**
 * Callback for the admin configuration page.
 */
function basic_cart_admin_content_type() {
  module_load_include('inc', 'basic_cart', 'basic_cart.cart');
  $node_types = node_type_get_types();
  if (empty($node_types)) {
    return NULL;
  }
  

  $options = array();
  foreach ($node_types as $node_type => $type) {
    if ($node_type == 'order' && module_exists('basic_cart_order')) {
      continue;
    }
    $options[$node_type] = check_plain($type->name);
  }
  $default_value = array();
  foreach (basic_cart_product_types() as $product_type){
    if (isset($options[$product_type])){
      $default_value[$product_type] = $product_type;
    }
  }

  $form['content_type'] = array(
    '#title' => t('Content type selection'),
    '#type' => 'fieldset',
    '#description' => t('Please select the content types for which you wish to have the "Add to cart" option.'),
  );

  $form['content_type']['basic_cart_content_types'] = array(
    '#title' => t('Content types'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#default_value' => $default_value,
  );

  $form['currency'] = array(
    '#title' => t('Currency and price'),
    '#type' => 'fieldset',
    '#description' => t('Please select the currency in which the prices will be calculated.'),
  );

  $form['currency']['basic_cart_currency'] = array(
    '#title' => t('Currency'),
    '#type' => 'textfield',
    '#description' => t("Please choose the currency."),
    '#default_value' => variable_get('basic_cart_currency'),
  );

  $form['currency']['basic_cart_price_format'] = array(
    '#title' => t('Price format'),
    '#type' => 'select',
    '#options' => _basic_cart_price_format(),
    '#description' => t("Please choose the format in which the price will be shown."),
    '#default_value' => variable_get('basic_cart_price_format'),
  );
  
  $form['vat'] = array(
    '#title' => t('VAT'),
    '#type' => 'fieldset',
  );

  $form['vat']['basic_cart_vat_state'] = array(
    '#title' => t('Check if you want to apply the VAT tax on the total amount in the checkout process.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('basic_cart_vat_state', FALSE),
  );

  $form['vat']['basic_cart_vat_value'] = array(
    '#title' => t('VAT value'),
    '#type' => 'textfield',
    '#description' => t("Please enter VAT value."),
    '#field_suffix' => '%',
    '#size' => 10,
    '#default_value' => variable_get('basic_cart_vat_value', ''),
  );
  
  $form['redirect'] = array(
    '#title' => t('Redirect user after adding an item to the shopping cart'),
    '#type' => 'fieldset',
  );
  
  $form['redirect']['basic_cart_redirect_user_after_add_to_cart'] = array(
    '#title' => t('Add to cart redirect'),
    '#type' => 'textfield',
    '#description' => t("Enter the page you wish to redirect the customer to when an item is added to the cart, or &lt;none&gt; for no redirect."),
    '#default_value' => variable_get('basic_cart_redirect_user_after_add_to_cart'),
    '#field_prefix' => url(NULL, array('absolute' => TRUE)) . (variable_get('clean_url', 0) ? '' : '?q='),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));

  return $form;
}

/**
 * Callback for the admin messages.
 */
function basic_cart_admin_checkout() {
  $form['messages'] = array(
    '#title' => t('Email messages'),
    '#type' => 'fieldset',
    '#description' => t('Here you can customize the mails sent to the site administrator and customer, after an order is placed.'),
  );
  
  $site_mail = variable_get('site_mail');
  $form['messages']['basic_cart_admin_emails'] = array(
    '#title' => t('Administrator emails'),
    '#type' => 'textarea',
    '#description' => t('After each placed order, an email with the order details will be sent to all the addresses from the list above. 
                          Please add one email address per line.'),
    '#default_value' => variable_get('basic_cart_admin_emails', $site_mail),
  );

  $form['messages']['basic_cart_admin_subject'] = array(
    '#title' => t('Subject'),
    '#type' => 'textfield',
    '#description' => t("Subject field for the administrator's email."),
    '#default_value' => variable_get('basic_cart_admin_subject'),
  );

  $form['messages']['basic_cart_admin_message'] = array(
    '#title' => t('Admin email'),
    '#type' => 'textarea',
    '#description' => t('This email will be sent to the site administrator just after an order is placed. 
      Availabale tokes: %CUSTOMER_NAME, %CUSTOMER_EMAIL, %CUSTOMER_PHONE, %CUSTOMER_CITY, %CUSTOMER_ZIPCODE, %CUSTOMER_ADDRESS, %CUSTOMER_MESSAGE, %ORDER_DETAILS.'),
    '#default_value' => variable_get('basic_cart_admin_message'),
  );

  $form['messages']['basic_cart_send_user_message'] = array(
    '#title' => t('Send an email to the customer after an order is placed'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('basic_cart_send_user_message'),
  );

  $form['messages']['basic_cart_user_subject'] = array(
    '#title' => t('Subject'),
    '#type' => 'textfield',
    '#description' => t("Subject field for the user's email."),
    '#default_value' => variable_get('basic_cart_user_subject'),
  );

  $form['messages']['basic_cart_user_message'] = array(
    '#title' => t('User email'),
    '#type' => 'textarea',
    '#description' => t('This email will be sent to the user just after an order is placed. Availabale tokes: %CUSTOMER_NAME, %CUSTOMER_EMAIL, %CUSTOMER_PHONE, %CUSTOMER_ADDRESS, %CUSTOMER_MESSAGE, %ORDER_DETAILS'),
    '#default_value' => variable_get('basic_cart_user_message'),
  );

  $form['thank_you'] = array(
    '#title' => t('Thank you page'),
    '#type' => 'fieldset',
    '#description' => t('Thank you page customization.'),
  );

  $form['thank_you']['basic_cart_thank_you_title'] = array(
    '#title' => t('Title'),
    '#type' => 'textfield',
    '#description' => t('Thank you page title.'),
    '#default_value' => variable_get('basic_cart_thank_you_title'),
  );

  $form['thank_you']['basic_cart_thank_you_message'] = array(
    '#title' => t('Text'),
    '#type' => 'textarea',
    '#description' => t('Thank you page text.'),
    '#default_value' => variable_get('basic_cart_thank_you_message'),
  );

  return system_settings_form($form);
}

/**
 * Callback validation function for the settings page.
 */
function basic_cart_admin_content_type_validate($form, &$form_state) {
  $vat_is_enabled = (int) $form_state['values']['basic_cart_vat_state'];
  if (!empty ($vat_is_enabled) && $vat_is_enabled) {
    $vat_value = (float) $form_state['values']['basic_cart_vat_value'];
    if ($vat_value <= 0) {
      form_set_error('basic_cart_vat_value', t('Please enter a valid figure for the VAT.'));
    }
  }
}

/**
 * Callback submit function for the settings page.
 */
function basic_cart_admin_content_type_submit($form, &$form_state) {
  // Remove internal Form API values.
  unset($form_state['values']['form_id'], $form_state['values']['form_token'], $form_state['values']['form_build_id'], $form_state['values']['op']);

  $product_types = array();
  // Setting up the price field for the selected content types.
  $content_types = $form_state['values']['basic_cart_content_types'];
  // unset to prevent 'double' save
  unset($form_state['values']['basic_cart_content_types']);
  
  if (!empty($content_types) && is_array($content_types)){
    // Check to see if the price field already exists.
    $field = field_info_field('price');
    // If the price field does not exist then create it.
    if (empty($field)) {
      $field = array(
        'field_name' => 'price',
        'type' => 'number_decimal',
        'entity_types' => array('node'),
      );
      field_create_field($field);
    }
    foreach ($content_types as $type => $checked) {
      // If a node type is checked, then create the price field.
      if ($checked) {
        // save content_type as a product
        $product_types[$type] = $type;
        // Foreach checked content type, we must assign the price field to the content type.
        $instance = field_info_instance('node', 'price', $type);
        if (empty($instance)) {
          $instance = array(
            'field_name' => 'price',
            'label' => t('Price'),
            'description' => t('Please enter the price for this item.'),
            'entity_type' => 'node',
            'bundle' => $type,
          );
          // It doesn't exist. Create it.
          field_create_instance($instance);
        }
      }
      // If not, then delete the instance.
      else {
        $instance = field_info_instance('node', 'price', $type);
        if (!empty($instance)) {
          field_delete_instance($instance);
        }
      }
    }
  }

  variable_set('basic_cart_content_types', $product_types);
  
  // Set VAT to nothing if the checkbox is unchecked.
  if (empty($form_state['values']['basic_cart_vat_state'])) {
    $form_state['values']['basic_cart_vat_value'] = '';
    // Check to see if the VAT instance exists and if so, delete it.
    if (module_exists('basic_cart_order')) {
      $instance = field_info_instance('node', 'vat', 'order');
      if (!empty($instance)) {
        field_delete_instance($instance);
      }
    }
  }
  else {
    // If the enable VAT checkbox is checked and if basic_cart_order is enabled,
    // then create the vat field for the Order content type.
    if (module_exists('basic_cart_order')) {
      // Check to see if the vat field already exists.
      $field = field_info_field('vat');
      // If the vat field does not exist then create it.
      if (empty($field)) {
        $field = array(
          'field_name' => 'vat',
          'type' => 'number_decimal',
          'entity_types' => array('node'),
        );
        field_create_field($field);

        // Assign the vat field to the Order content type.
        $instance = field_info_instance('node', 'vat', 'order');
        if (empty($instance)) {
          $instance = array(
            'field_name' => 'vat',
            'label' => t('VAT'),
            'description' => t('The VAT tax.'),
            'entity_type' => 'node',
            'bundle' => 'order',
          );
          // It doesn't exist. Create it.
          field_create_instance($instance);
        }
      }
    }
  }
  
  // Save other variables.
  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }
  
  drupal_set_message(t('The configuration options have been saved.'));
}
