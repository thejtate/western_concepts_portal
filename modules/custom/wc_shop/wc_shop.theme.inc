<?php

/**
 * @file
 * Theming
 */


/**
 * Implements hook_theme().
 */
function wc_shop_theme() {
  $path = drupal_get_path('module', 'wc_shop');
  return array(
    'wc_shop_cart_block' => array(
      'variables' => array('cart' => NULL),
      'path' => $path . '/templates',
      'template' => 'wc_shop_cart_block',
    ),
    'wc_shop_cart_checkout' => array(
      'variables' => array('cart' => NULL),
      'path' => $path . '/templates',
      'template' => 'wc_shop_cart_checkout',
    ),
    'wc_shop_checkout' => array(
      'variables' => array('cart' => NULL, 'vars' => NULL),
      'path' => $path . '/templates',
      'template' => 'wc_shop_checkout',
    ),


    'wc_shop_user_mail' => array(
      'variables' => array('data' => NULL),
      'path' => $path . '/templates/email',
      'template' => 'wc_shop_user_mail',
    ),
    'wc_shop_admin_mail' => array(
      'variables' => array('data' => NULL),
      'path' => $path . '/templates/email',
      'template' => 'wc_shop_admin_mail',
    ),

  );
}


/**
 * Implements hook_preprocess_theme().
 */
function wc_shop_preprocess_wc_shop_cart_block(&$variables) {

  if (isset($variables['cart']) && !empty($variables['cart'])) {
    $variables['total'] = wc_shop_get_cart_total($variables['cart']);
    foreach ($variables['cart'] as $key => $row) {
      $variables['cart'][$key]['title'] = (isset($row['node']->title)) ? $row['node']->title : "";
    }
  }
}

/**
 * Implements hook_preprocess_theme().
 */
function wc_shop_preprocess_wc_shop_cart_checkout(&$variables) {
  if (isset($variables['cart']) && !empty($variables['cart'])) {
    $variables['total'] = wc_shop_get_cart_total($variables['cart']);

    $session_sites = &wc_shop_get_session_cart_sites();
    $sites = _wc_shop_get_sites();

    foreach ($variables['cart'] as $key => $row) {
      $imagedata = (isset($row['node']->field_store_product_image[LANGUAGE_NONE][0])) ? $row['node']->field_store_product_image[LANGUAGE_NONE][0] : NULL;
      if (isset($imagedata['uri'])) {
        $image_style_data = array(
          'style_name' => 'product_checkout',
          'path' => $imagedata['uri'],
          'width' => '',
          'height' => '',
          'alt' => $imagedata['alt'],
          'title' => $imagedata['title'],
        );
        $image = theme('image_style', $image_style_data);
      }
      else {
        $image = "";
      }

      $variables['cart'][$key]['title'] = (isset($row['node']->title)) ? $row['node']->title : "";
      $variables['cart'][$key]['image'] = $image;

      if (isset($session_sites[$key]) && !empty($session_sites[$key])){
        $variables['cart'][$key]['sites'] = '';

        foreach ($session_sites[$key] as $site => $cart_amount) {
          $variables['cart'][$key]['sites'] .= $sites[$site] . ': ' . $cart_amount . '<br/>';
        }
      }
    }
  }
}



