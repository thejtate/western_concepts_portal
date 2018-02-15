<?php

/**
 * @file
 * Cart shopping implementation functions.
 */


function wc_shop_cart_remove($vid = "") {
  $pTitle = wc_shop_cart_get_title_by_key($vid);
  if (!empty($pTitle)) {
    $message = '"' . $pTitle . '" ' . t("removed from your cart.");
    drupal_set_message($message);
  }
  wc_shop_remove_from_cart($vid);
  drupal_goto("wc-shop/checkout");
}


/**
 * Prepare variants for product
 * @param array $variants
 * @return array
 */
function wc_shop_get_variants($node) {
  $vdata = array();
  $variants = (isset($node->field_store_product_variant[LANGUAGE_NONE])) ? $node->field_store_product_variant[LANGUAGE_NONE] : array();
  foreach ($variants as $item) {
    $vid = $item['value'];
    $variant = field_collection_item_load($vid);

    if (isset($variant->field_store_product_size[LANGUAGE_NONE][0]['tid'])) {
      $tid = $variant->field_store_product_size[LANGUAGE_NONE][0]['tid'];
      $term = taxonomy_term_load($tid);
      $size = array(
        'id' => $term->tid,
        'title' => $term->name,
      );
    }
    else {
      $size = array(
        'id' => -1,
        'title' => "",
      );
    }

    if (isset($variant->field_store_product_color[LANGUAGE_NONE][0]['tid'])) {
      $tid = $variant->field_store_product_color[LANGUAGE_NONE][0]['tid'];
      $term = taxonomy_term_load($tid);
      $color = array(
        'id' => $term->tid,
        'title' => $term->name
      );
    }
    else {
      $color = array(
        'id' => -1,
        'title' => "",
      );
    }

    $price = (isset($variant->field_store_product_price[LANGUAGE_NONE][0]['value'])) ? $variant->field_store_product_price[LANGUAGE_NONE][0]['value'] : 0;
    $stock = (isset($variant->field_store_product_stock[LANGUAGE_NONE][0]['value'])) ? $variant->field_store_product_stock[LANGUAGE_NONE][0]['value'] : 0;

    if (!empty($stock)) {
      $vdata['data'][$color['id']][$size['id']][$price] = $variant->item_id;
      $vdata['color'][$color['id']] = $color['title'];
      $vdata['size'][$size['id']] = $size['title'];
    }
  }
  return $vdata;
}


/**
 * Prepare add to cart form
 *
 * @param $form
 * @param $form_state
 * @param $node
 */
function wc_shop_prepare_add_to_cart_form(&$form, &$form_state, $node) {
  $variants = wc_shop_get_variants($node);
  $variants['data'] = isset($variants['data']) ? $variants['data'] : array();
  $node->variants = $variants;

  $selected_color = (isset($form_state['values']['color'])) ? $form_state['values']['color'] : NULL;
  $selected_size = (isset($form_state['values']['size'])) ? $form_state['values']['size'] : NULL;
  $selected_sites = (isset($form_state['values']['sites'])) ? $form_state['values']['sites'] : NULL;


  $color_options = array();
  foreach ($variants['data'] as $color_id => $value) {
    if ($color_id != -1) {
      $color_options[$color_id] = isset($variants['color'][$color_id]) ? $variants['color'][$color_id] : $color_id;
    }
  }

  if ((!empty($selected_color) && array_key_exists($selected_color, $color_options))) {
    $first_color_id = $selected_color;
  }
  else {
    $color_options_keys = array_keys($color_options);
    $first_color_id = reset($color_options_keys);
  }

//  $first_color_id = (!empty($selected_color) && array_key_exists($selected_color, $color_options)) ? $selected_color : reset(array_keys($color_options));
  $first_color_id = (empty($first_color_id)) ? -1 : $first_color_id;
  $size_options = array();
  if (isset($variants['data'][$first_color_id])) {
    foreach ($variants['data'][$first_color_id] as $size_id => $value) {
      if ($size_id != -1) {
        $size_options[$size_id] = isset($variants['size'][$size_id]) ? $variants['size'][$size_id] : $size_id;
      }
    }
  }
  if (!empty($selected_size) && array_key_exists($selected_size, $size_options)) {
    $first_size_id = $selected_size;
  }
  else {
    $size_options_keys = array_keys($size_options);
    $first_size_id = reset($size_options_keys);
  }
  //$first_size_id = (!empty($selected_size) && array_key_exists($selected_size, $size_options)) ? $selected_size : reset(array_keys($size_options));
  $first_size_id = (empty($first_size_id)) ? -1 : $first_size_id;
  $price_options = array();
  if (isset($variants['data'][$first_color_id][$first_size_id])) {
    foreach ($variants['data'][$first_color_id][$first_size_id] as $price => $vid) {
      $price_options[$price] = $price;
    }
  }


  if (isset($node->field_product_gift[LANGUAGE_NONE][0]['value']) && !empty($node->field_product_gift[LANGUAGE_NONE][0]['value'])) {
    // gift card
    $form['sites'] = array(
      '#type' => 'select',
      '#title' => t('Type'),
      '#options' => _wc_shop_get_sites(),
      '#prefix' => '<div class="gift-type-select-wrapper"><div class="width-form-110 ff-tt-l">',
      '#suffix' => '</div></div>',
      '#weight' => 5,
      '#default_value' => (!empty($selected_sites)) ? array($selected_sites) : array(),
    );
  }


  if (!empty($color_options)) {
    $form['color'] = array(
      '#type' => 'select',
      '#title' => t('Color'),
      '#options' => $color_options,
      '#prefix' => '<div class="width-form-110 ff-tt-l">',
      '#suffix' => '</div>',
      '#weight' => 1,
      '#default_value' => (!empty($selected_color)) ? array($selected_color) : array(),
      '#ajax' => array(
        'event' => 'change',
        'callback' => 'wc_shop_ajax_select_callback',
        'wrapper' => 'replace-add-to-cart-form-' . $node->nid,
        'method' => 'replace',
        'progress' => array(
          'type' => 'throbber',
          'message' => '',
        ),
      ),
    );
  }

  if (!empty($size_options)) {
    $form['size'] = array(
      '#type' => 'select',
      '#title' => t('Size'),
      '#options' => $size_options,
      '#prefix' => '<div class="width-form-110 ff-tt-l">',
      '#suffix' => '</div>',
      '#weight' => 2,
      '#default_value' => (!empty($selected_size)) ? array($selected_size) : array(),
      '#ajax' => array(
        'event' => 'change',
        'callback' => 'wc_shop_ajax_select_callback',
        'wrapper' => 'replace-add-to-cart-form-' . $node->nid,
        'method' => 'replace',
        'progress' => array(
          'type' => 'throbber',
          'message' => '',
        ),
      ),
    );
  }

  $form['submit'] = array('#type' => 'submit', '#value' => t('Add to cart'), '#weight' => 10);
  $form['submit']['#prefix'] = '<div class="btn-wrapp"><div class="btn-submit">';
  $form['submit']['#suffix'] = '</div></div>';

  // price
  if (!empty($price_options) && count($price_options) > 1) {
    $form['price'] = array(
      '#type' => 'select',
      '#title' => t('Select amount'),
      '#options' => $price_options,
      '#prefix' => '<div class="width-form-110 ff-tt-l">',
      '#suffix' => '</div>',
      '#weight' => 3,
    );
  }
  else {
    $price_options_keys = array_keys($price_options);
    $price = reset($price_options_keys);
    $form['price'] = array('#type' => 'hidden', '#value' => $price);
    if (!empty($price)) {
      $form['price_murkup'] = array(
        '#type' => 'markup',
        '#markup' => '<span class="price-product">$' . $price . '</span>',
        '#weight' => -1,
      );

    }
    else {
      $form['price_murkup'] = array(
        '#type' => 'markup',
        '#markup' => '<span class="price-product">' . t('Out of stock') . '</span>',
        '#weight' => -1,
      );
      //hide submit button
      $form['submit']['#access'] = FALSE;
    }

  }
}


/**
 * Add to cart form
 *
 * @param $node
 * @return mixed
 */
function wc_shop_add_to_cart_form($form, &$form_state, $node) {
  $form['pid'] = array('#type' => 'hidden', '#value' => $node->nid);
  $form['p_title'] = array('#type' => 'hidden', '#value' => $node->title);
  $form['#prefix'] = '<div id="replace-add-to-cart-form-' . $node->nid . '">';
  $form['#suffix'] = '</div>';

  wc_shop_prepare_add_to_cart_form($form, $form_state, $node);

  return $form;
}

/**
 * Form ajax callback
 * @param $form
 * @param $form_state
 * @return mixed
 */
function wc_shop_ajax_select_callback($form, $form_state) {
  return $form;
}


function wc_shop_add_to_cart_form_submit($form, &$form_state) {

  $node = (isset($form_state['build_info']['args'][0])) ? $form_state['build_info']['args'][0] : NULL;
  $title = (isset($form_state['values']['p_title'])) ? $form_state['values']['p_title'] : "";
  $nid = (isset($form_state['values']['pid'])) ? $form_state['values']['pid'] : NULL;
  $color = (isset($form_state['values']['color'])) ? $form_state['values']['color'] : -1;
  $size = (isset($form_state['values']['size'])) ? $form_state['values']['size'] : -1;
  $price = (isset($form_state['values']['price'])) ? $form_state['values']['price'] : -1;
  $sites = (isset($form_state['values']['sites'])) ? $form_state['values']['sites'] : -1;


  if (!empty($nid)) {
    wc_shop_add_to_cart($node, $nid, $color, $size, $price, $sites);
  }
  drupal_goto("shop");
}


/**
 * Load cart
 */
function wc_shop_get_cart() {
  $session_cart = & wc_shop_get_session_cart();
  $cart = array();

  foreach ($session_cart as $vid => $count) {
    $variant = field_collection_item_load($vid);
    $node = $variant->hostEntity();

    $color = (isset($variant->field_store_product_color[LANGUAGE_NONE][0]['tid'])) ? $variant->field_store_product_color[LANGUAGE_NONE][0]['tid'] : NULL;
    $size = (isset($variant->field_store_product_size[LANGUAGE_NONE][0]['tid'])) ? $variant->field_store_product_size[LANGUAGE_NONE][0]['tid'] : NULL;
    $price = (isset($variant->field_store_product_price[LANGUAGE_NONE][0]['value'])) ? $variant->field_store_product_price[LANGUAGE_NONE][0]['value'] : 0;
    $discount = wc_shop_get_discount($node);
    $price = wc_shop_get_discount_price($price, $discount);

    $cart[$vid] = array(
      'node' => $node,
      'color' => wc_shop_get_attr_name($color),
      'size' => wc_shop_get_attr_name($size),
      'price' => $price,
      'count' => $count,
      'discount' => $discount,
    );
  }
  return $cart;
}


/**
 * Load term name for product
 * @param $tid
 * @return string
 */
function wc_shop_get_attr_name($tid) {
  $term = taxonomy_term_load($tid);
  return isset($term->name) ? $term->name : "";
}


/**
 * Add to cart
 *
 * @param null $nid
 * @param string $color
 * @param string $size
 */
function wc_shop_add_to_cart($node = NULL, $nid = NULL, $color = '-1', $size = '-1', $price = "-1", $sites = "-1") {
  $variants = (isset($node->variants)) ? $node->variants : array(); // [data][color][size][price] = field_collection_item ID
  if (isset($variants['data'][$color][$size][$price])) {
    $vid = $variants['data'][$color][$size][$price];
    $session_cart = &wc_shop_get_session_cart();
    $count_in_cart = (isset($session_cart[$vid])) ? isset($session_cart[$vid]) : 0;
    $available_in_stock = wc_shop_get_variant_stock($vid);

    if ($available_in_stock >= ($count_in_cart + 1)) {
      $session_cart[$vid] = isset($session_cart[$vid]) ? $session_cart[$vid] + 1 : 1;

      // add sites for gift cart
      if (!empty($sites) && $sites != -1){
        $session_sites = &wc_shop_get_session_cart_sites();
        if (isset($session_sites[$vid][$sites])){
          $session_sites[$vid][$sites] = $session_sites[$vid][$sites] + 1;
        } else {
          $session_sites[$vid][$sites] = 1;
        }
      }

      if (isset($node->title)) {
        drupal_set_message($node->title . " " . t("was added to your cart."));
      }
    }
    else {
      drupal_set_message(t('Available number of ') . '"' . $node->title . '": ' . $available_in_stock, "error");
    }

  }
}

/**
 * Get variant stock number
 * @param $vid
 * @return int
 */
function wc_shop_get_variant_stock($vid) {
  $variant = field_collection_item_load($vid);
  return (isset($variant->field_store_product_stock[LANGUAGE_NONE][0]['value'])) ? $variant->field_store_product_stock[LANGUAGE_NONE][0]['value'] : 0;
}

/**
 * remove from cart
 *
 * @param null $nid
 * @param string $color
 * @param string $size
 */
function wc_shop_remove_from_cart($vid) {
  $session_cart = & wc_shop_get_session_cart();
  if (isset($session_cart[$vid])) {
    if ($session_cart[$vid] > 1) {
      $session_cart[$vid]--;
    }
    else {
      unset($session_cart[$vid]);
    }
  }

  // remove gift cart element
  $session_cart_sites = & wc_shop_get_session_cart_sites();
  if (isset($session_cart_sites[$vid])) {
    $last_element = array_keys($session_cart_sites[$vid]);
    $last_key = end($last_element);
    $last = &$session_cart_sites[$vid][$last_key];
    if ($last > 1){
      $last--;
    } else {
      unset($session_cart_sites[$vid][$last_key]);
      if (empty($session_cart_sites[$vid])){
        unset($session_cart_sites[$vid]);
      }
    }
  }
}

/**
 * Clear cart
 */
function wc_shop_clear_cart() {
  $session_cart = & wc_shop_get_session_cart();
  $session_cart = array();

  $session_cart_sites = & wc_shop_get_session_cart_sites();
  $session_cart_sites = array();
}


/**
 * Calculate cart total price
 * @param array $cart
 * @return array
 */
function wc_shop_get_cart_total($cart = array()) {
  $total = array('subtotal' => 0, 'total' => 0);
  $shipping = variable_get('wc_shop_settings_shipping_price', 0);

  foreach ($cart as $row) {
    $count = (isset($row['count'])) ? $row['count'] : 1;
    $total['subtotal'] += $row['price'] * $count;
  }

  $total['shipping'] = $shipping;
  $total['total'] = $total['subtotal'] + $shipping;

  return $total;
}


/**
 * Get product title by cart key
 * @param $vid
 * @return string
 */
function wc_shop_cart_get_title_by_key($vid) {
  $session_cart = & wc_shop_get_session_cart();
  if (isset($session_cart[$vid])) {
    $variant = field_collection_item_load($vid);
    $node = $variant->hostEntity();
    return (isset($node->title)) ? $node->title : "";
  }
  return "";
}

/**
 * Get Session cart identifier
 *
 * @return mixed
 */
function &wc_shop_get_session_cart() {
  if (!isset($_SESSION['wc_shop']['cart'])) {
    $_SESSION['wc_shop']['cart'] = array();
  }
  return $_SESSION['wc_shop']['cart'];
}


/**
 * Get Session cart identifier
 *
 * @return mixed
 */
function &wc_shop_get_session_cart_sites() {
  if (!isset($_SESSION['wc_shop']['sites'])) {
    $_SESSION['wc_shop']['sites'] = array();
  }
  return $_SESSION['wc_shop']['sites'];
}

/**
 * Get discount.
 *
 * @param $node
 * @return int
 */
function wc_shop_get_discount($node) {
  $discount = (isset($node->field_store_product_discount) &&
    isset($node->field_store_product_discount[LANGUAGE_NONE][0]['value'])) ?
    $node->field_store_product_discount[LANGUAGE_NONE][0]['value'] : 0;

  $discount_period = (isset($node->field_store_product_discount_dat) &&
    isset($node->field_store_product_discount_dat[LANGUAGE_NONE][0])) ?
    $node->field_store_product_discount_dat[LANGUAGE_NONE][0] : '';

  $timezone = isset($discount_period['timezone']) ? $discount_period['timezone'] : 'America/Chicago';
  $timezone = new DateTimeZone($timezone);
  $start = isset($discount_period['value']) ? new DateTime($discount_period['value'], $timezone) : '';
  $end = isset($discount_period['value2']) ? new DateTime($discount_period['value2'], $timezone) : '';
  $now = new DateTime('now', $timezone);

  if (($start <= $now) && ($now < $end)) {
    return $discount;
  }
  else {
    return;
  }
}

/**
 * Get discount price.
 *
 * @param $price
 * @param $discount
 * @return float
 */
function wc_shop_get_discount_price($price, $discount) {
  if (empty($discount)) {
    return $price;
  }
  else {
    return round($price - ($price * ($discount / 100)), 2);
  }
}