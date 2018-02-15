<?php

/**
 * @file
 * Basic cart shopping cart implementation functions.
 */

/**
 * Callback function for cart listing.
 */
function basic_cart_cart() {
  $cart = basic_cart_get_cart();

  if (empty($cart)) {
    return t('Your cart is empty.');
  }
  return drupal_get_form('basic_cart_cart_form');
}

/**
 * Shopping cart form.
 */
function basic_cart_cart_form() {
  // Getting the shopping cart.
  $cart = basic_cart_get_cart();
  // And now the form.
  $form['cartcontents'] = array(
    // Make the returned array come back in tree form.
    '#tree' => TRUE,
    '#prefix' => '<div class="basic-cart-cart basic-cart-grid">',
    '#suffix' => '</div>',
  );
  // Cart elements.
  foreach ($cart as $nid => $node) {
    $form['cartcontents'][$nid] = array(
      '#type' => 'textfield',
      '#size' => 1,
      '#default_value' => $node->basic_cart_quantity,
      '#theme' => 'basic_cart_render_cart_element',
    );
  }
  // Total price.
  $form['total_price'] = array(
    '#markup' => t('Total price'),
    '#prefix' => '<div class="basic-cart-cart basic-cart-grid">',
    '#suffix' => '</div>',
    '#theme' => 'basic_cart_cart_total_price',
  );
  // Buttons.
  $form['buttons'] = array(
    // Make the returned array come back in tree form.
    '#tree' => TRUE,
    '#prefix' => '<div class="row"><div class="basic-cart-call-to-action cell">',
    '#suffix' => '</div></div>',
  );
  // Update button.
  $form['buttons']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );
  // Checkout button.
  $form['buttons']['checkout'] = array(
    '#type' => 'submit',
    '#value' => t('Checkout'),
  );

  return $form;
}

/**
 * Shopping cart form.
 */
function basic_cart_cart_form_submit($form_id, $form_state) {
  foreach ($form_state['values']['cartcontents'] as $nid => $value) {
    $quantity = (int) $value;
    if ($quantity > 0) {
      $_SESSION['basic_cart']['cart'][$nid]->basic_cart_quantity = $quantity;
    }
    // If the quantity is zero, we just remove the node from the cart.
    elseif ($quantity == 0) {
      unset($_SESSION['basic_cart']['cart'][$nid]);
    }
  }

  if ($form_state['values']['op'] == t('Checkout')) {
    drupal_goto('checkout');
  }
  else {
    drupal_set_message(t('Shopping cart updated.'));
  }
}

/**
 * Callback function for cart/add/.
 *
 * @param int $nid
 *   We are using the node id to store the node in the shopping cart
 */
function basic_cart_add_to_cart($nid = NULL) {
  $nid = (int) $nid;
  if ($nid > 0) {
    // If a node is added more times, just update the quantity.
    $cart = basic_cart_get_cart();
    if (!empty($cart) && in_array($nid, array_keys($cart))) {
      // Clicked 2 times on add to cart button. Increment quantity.
      $_SESSION['basic_cart']['cart'][$nid]->basic_cart_quantity++;
    }
    else {
      $node = node_load($nid);
      $node->basic_cart_quantity = 1;
      // Adding description.
      $body = field_get_items('node', $node, 'body');
      $description = isset($body[0]['value']) ? check_plain(strip_tags($body[0]['value'])) : '';
      $node->basic_cart_node_description = $description;
      // Unit price.
      $unit_price = field_get_items('node', $node, 'price');
      $unit_price = isset($unit_price[0]['value']) ? check_plain(strip_tags($unit_price[0]['value'])) : 0;
      $node->basic_cart_unit_price = $unit_price;
      
      // Storing in session.
      $_SESSION['basic_cart']['cart'][$nid] = $node;
    }
  }
  drupal_set_message(t('Shopping cart updated.'));
  
  $redirect = variable_get('basic_cart_redirect_user_after_add_to_cart', FALSE);
  if (empty($redirect)) {
    drupal_goto('cart');
  }
  elseif ($redirect == '<none>') {
    $referer = $_SERVER["HTTP_REFERER"];
    drupal_goto($referer);
  }
  else {
    drupal_goto($redirect);
  }
}

/**
 * Callback function for cart/remove/.
 *
 * @param int $nid
 *   We are using the node id to remove the node in the shopping cart
 */
function basic_cart_remove_from_cart($nid = NULL) {
  $nid = (int) $nid;
  if ($nid > 0) {
    unset($_SESSION['basic_cart']['cart'][$nid]);
  }
  drupal_set_message(t('Shopping cart updated.'));
  drupal_goto('cart');
}

/**
 * Function for shopping cart retrieval.
 *
 * @param int $nid
 *   We are using the node id to store the node in the shopping cart
 *
 * @return mixed
 *   Returning the shopping cart contents.
 *   An empty array if there is nothing in the cart
 */
function basic_cart_get_cart($nid = NULL) {
  if (isset($nid)) {
    return $_SESSION['basic_cart']['cart'][$nid];
  }
  if (isset($_SESSION['basic_cart']['cart'])) {
    return $_SESSION['basic_cart']['cart'];
  }
  // Empty cart.
  return array();
}

/**
 * Returns the final price for the shopping cart.
 *
 * @return mixed $total_price
 *   The total price for the shopping cart. 
 */
function basic_cart_get_total_price() {
  // Building the return array.
  $return = array(
    'price' => 0,
    'vat' => 0,
    'total' => 0,
  );
  $cart = basic_cart_get_cart();
  if (empty($cart)) {
    return (object) $return;
  }
  
  $total_price = 0;
  foreach ($cart as $nid => $node) {
    if (isset($node->basic_cart_quantity) && isset($node->basic_cart_unit_price)) {
      $total_price += $node->basic_cart_quantity * $node->basic_cart_unit_price;
    }
  }
  
  $return['price'] = $total_price;
  
  // Checking whether to apply the VAT or not.
  $vat_is_enabled = (int) variable_get('basic_cart_vat_state');
  if (!empty ($vat_is_enabled) && $vat_is_enabled) {
    $vat_value = (float) variable_get('basic_cart_vat_value');
    $vat_value = ($total_price * $vat_value) / 100;
    $total_price += $vat_value;
    // Adding VAT and total price to the return array.
    $return['vat'] = $vat_value;
  }
  
  $return['total'] = $total_price;
  return (object) $return;
}

/**
 * Shopping cart reset.
 */
function basic_cart_empty_cart() {
  unset($_SESSION['basic_cart']['cart']);
}

/**
 * Formats the input $price in the desired format.
 *
 * @param float $price
 *   The price in the raw format.
 * @return $price
 *   The price in the custom format.
 */
function basic_cart_price_format($price) {
  $format = variable_get('basic_cart_price_format');
  $currency = check_plain(variable_get('basic_cart_currency'));
  $price = (float) $price;
  switch ($format) {
    case 0:
      $price = number_format($price, 2, ',', ' ') . ' ' . $currency;
      break;
    
    case 1:
      $price = number_format($price, 2, '.', ' ') . ' ' . $currency;
      break;
    
    case 2:
      $price = number_format($price, 2, '.', ',') . ' ' . $currency;
      break;
    
    case 3:
      $price = number_format($price, 2, ',', '.') . ' ' . $currency;
      break;
    
    case 4:
      $price = $currency . ' ' . number_format($price, 2, ',', ' ');
      break;
    
    case 5:
      $price = $currency . ' ' . number_format($price, 2, '.', ' ');
      break;
    
    case 6:
      $price = $currency . ' ' . number_format($price, 2, '.', ',');
      break;
    
    case 7:
      $price = $currency . ' ' . number_format($price, 2, ',', '.');
      break;
    
    default:
      $price = number_format($price, 2, ',', ' ') . ' ' . $currency;
      break;
  }
  return $price;
}

/**
 * Returns the available price formats.
 *
 * @return $formats
 *   A list with the available price formats.
 */
function _basic_cart_price_format() {
  $currency = variable_get('basic_cart_currency');
  return array(
    0 => t('1 234,00 @currency', array('@currency' => $currency)),
    1 => t('1 234.00 @currency', array('@currency' => $currency)),
    2 => t('1,234.00 @currency', array('@currency' => $currency)),
    3 => t('1.234,00 @currency', array('@currency' => $currency)),
    
    4 => t('@currency 1 234,00', array('@currency' => $currency)),
    5 => t('@currency 1 234.00', array('@currency' => $currency)),
    6 => t('@currency 1,234.00', array('@currency' => $currency)),
    7 => t('@currency 1.234,00', array('@currency' => $currency)),
  );
}

/**
 * Checkout.
 */

/**
 * Checkout form implementation.
 */
function basic_cart_checkout() {
  $shopping_cart = basic_cart_get_cart();
  // Price.
  $price = basic_cart_get_total_price();
  $total = basic_cart_price_format($price->total);
  
  $options = array(
    'cart' => $shopping_cart,
    'price' => $total,
  );
  
  // Checking the VAT.
  $vat_is_enabled = (int) variable_get('basic_cart_vat_state');
  if (!empty ($vat_is_enabled) && $vat_is_enabled) {
    $options['vat'] = basic_cart_price_format($price->vat);
  }
  
  // The flat cart (just the listing part).
  $cart = theme('basic_cart_cart_flat', $options);
  
  // If the cart is empty, we don't want to show the checkout form.
  if (empty($shopping_cart)) {
    return $cart;
  }
  
  $form = drupal_get_form('basic_cart_checkout_form');
  $form = drupal_render($form);
  return $cart . $form;
}

/**
 * Checkout form.
 */
function basic_cart_checkout_form() {
  $form['basic_cart_checkout_name'] = array(
    '#title' => t('Name'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => t('Please enter your name.'),
  );

  $form['basic_cart_checkout_email'] = array(
    '#title' => t('Email'),
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => t('Please enter your email.'),
  );

  $form['basic_cart_checkout_phone'] = array(
    '#title' => t('Phone'),
    '#type' => 'textfield',
    '#description' => t('Please enter your phone.'),
  );

  $form['basic_cart_checkout_address'] = array(
    '#title' => t('Address'),
    '#type' => 'textfield',
    '#description' => t('Please enter your address.'),
  );

  $form['basic_cart_checkout_city'] = array(
    '#title' => t('City'),
    '#type' => 'textfield',
    '#size' => 40,
    '#description' => t('Please enter your city.'),
  );
  
  $form['basic_cart_checkout_zipcode'] = array(
    '#title' => t('Zip code'),
    '#type' => 'textfield',
    '#size' => 16,
    '#description' => t('Please enter your zipcode.'),
  );
  
  $form['basic_cart_checkout_message'] = array(
    '#title' => t('Message'),
    '#type' => 'textarea',
    '#description' => t('If you wish to add a comment, please use this message area.'),
  );

  $form['basic_cart_checkout_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit order'),
  );

  return $form;
}

/**
 * Checkout form validation.
 */
function basic_cart_checkout_form_validate($form, &$form_state) {
  if (!valid_email_address($form_state['values']['basic_cart_checkout_email'])) {
    form_set_error('basic_cart_checkout_email', t('Please enter a valid email address.'));
  }
}

/**
 * Checkout form submit proccess.
 * Register order and send emails.
 */
function basic_cart_checkout_form_submit($form, &$form_state) {
  // %ORDER_DETAILS% placeholder.
  $order_details = '';
  $cart = basic_cart_get_cart();
  $price = basic_cart_get_total_price();
  $total_price = basic_cart_price_format($price->total);
  
  $vat_is_enabled = (int) variable_get('basic_cart_vat_state');
  if (!empty ($vat_is_enabled) && $vat_is_enabled) {
    $vat = basic_cart_price_format($price->vat);
  }
  
  // Registering the new order to the database.
  if (module_exists('basic_cart_order')) {
    $name = $form_state['values']['basic_cart_checkout_name'];
    $email = $form_state['values']['basic_cart_checkout_email'];
    $order_details_ = array(
      'phone' => $form_state['values']['basic_cart_checkout_phone'],
      'city' => $form_state['values']['basic_cart_checkout_city'],
      'zipcode' => $form_state['values']['basic_cart_checkout_zipcode'],
      'address' => $form_state['values']['basic_cart_checkout_address'],
      'message' => $form_state['values']['basic_cart_checkout_message'],
    );
    $order = basic_cart_order_register_order($name, $email, $order_details_);
    
    // Order successfully placed. Custom hook for other modules.
    foreach (module_implements('basic_cart_order') as $module) {
      $function = $module . '_basic_cart_order';
      // Will call all modules implementing hook_basic_cart_order() with the order node as argument.
      $function($order);
    }
  }
  
  // Building the order details.
  $i = 0;
  foreach ($cart as $nid => $node) {
    $unit_price = basic_cart_price_format($node->basic_cart_unit_price);
    $order_details .= ++$i . '. ' . $node->title . "\t" .
                      $node->basic_cart_quantity . ' x ' . $unit_price . "\n";
  }
  $order_details .= "\n";
  $order_details .= "Total price: " . $total_price;
  $vat_is_enabled = (int) variable_get('basic_cart_vat_state');
  if ($vat_is_enabled) {
    $order_details .= "\n";
    $order_details .= "Total VAT: " . $vat;
  }
  // Pleaceholder replacement.
  $search = array(
    '%CUSTOMER_NAME', '%CUSTOMER_EMAIL', '%CUSTOMER_PHONE', '%CUSTOMER_CITY',
    '%CUSTOMER_ZIPCODE', '%CUSTOMER_ADDRESS', '%CUSTOMER_MESSAGE', '%ORDER_DETAILS',
  );
  $replace = array(
    $form_state['values']['basic_cart_checkout_name'], $form_state['values']['basic_cart_checkout_email'],
    $form_state['values']['basic_cart_checkout_phone'], $form_state['values']['basic_cart_checkout_city'],
    $form_state['values']['basic_cart_checkout_zipcode'], $form_state['values']['basic_cart_checkout_address'],
    $form_state['values']['basic_cart_checkout_message'], $order_details,
  );
  // Admin message.
  $message_html = variable_get('basic_cart_admin_message');
  $message_html = str_replace($search, $replace, $message_html);
  
  // Admin mail.
  $params['admin_message'] = $message_html;
  $site_mail = variable_get('site_mail');
  
  $admin_emails = variable_get('basic_cart_admin_emails');
  if (empty ($admin_emails)) {
    // Sending mail to admin.
    $message = drupal_mail('basic_cart', 'admin_mail', $site_mail, language_default(), $params);

    $mails_sent = 0;
    if ($message['result']) {
      $mails_sent++;
    }
  }
  else {
    $admin_emails = explode("\n", $admin_emails);
    if (is_array($admin_emails) && !empty($admin_emails)) {
      $ok = FALSE;
      foreach ($admin_emails as $admin_email) {
        // Sending mail to each admin.
        $message = drupal_mail('basic_cart', 'admin_mail', $admin_email, language_default(), $params);
        
        // Verifing that the mail was sent for at least one email address.
        if ($message['result']) {
          $ok = TRUE;
        }
      }
      
      $mails_sent = 0;
      if ($ok) {
        $mails_sent++;
      }
    }
  }

  
  // User email.
  $send_user_mail = variable_get('basic_cart_send_user_message');
  if ($send_user_mail) {
    $message_html = variable_get('basic_cart_user_message');
    $message_html = str_replace($search, $replace, $message_html);
    $params['user_message'] = $message_html;
    
    // Sending mail.
    $message = drupal_mail('basic_cart', 'user_mail', $form_state['values']['basic_cart_checkout_email'], language_default(), $params);

    if ($message['result']) {
      $mails_sent++;
    }
  }
  
  if ($mails_sent >= 1) {
    basic_cart_empty_cart();
    drupal_goto('checkout/thank-you');
  }
  else {
    drupal_set_message(t('There was a problem in submitting your order. Please try again later.'), 'error');
  }
}


/**
 * Implements hook_mail().
 */
function basic_cart_mail($key, &$message, $params) {
  switch ($key) {
    case 'admin_mail':
      $message['subject'] = check_plain(variable_get('basic_cart_admin_subject'));
      $message['body'][] = filter_xss($params['admin_message']);
      break;

    case 'user_mail':
      $message['subject'] = check_plain(variable_get('basic_cart_user_subject'));
      $message['body'][] = filter_xss($params['user_message']);
      break;
  }
}

/**
 * Callback for thank you page.
 */
function basic_cart_checkout_thank_you() {
  $title = variable_get('basic_cart_thank_you_title');
  drupal_set_title($title);
  $message = variable_get('basic_cart_thank_you_message');
  return filter_xss($message);
}

