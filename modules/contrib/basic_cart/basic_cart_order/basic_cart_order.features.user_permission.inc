<?php
/**
 * @file
 * basic_cart_order.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function basic_cart_order_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer basic cart.
  $permissions['administer basic cart'] = array(
    'name' => 'administer basic cart',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'basic_cart',
  );

  // Exported permission: use basic cart.
  $permissions['use basic cart'] = array(
    'name' => 'use basic cart',
    'roles' => array(
      0 => 'administrator',
      1 => 'anonymous user',
    ),
    'module' => 'basic_cart',
  );

  // Exported permission: view basic cart orders.
  $permissions['view basic cart orders'] = array(
    'name' => 'view basic cart orders',
    'roles' => array(
      0 => 'administrator',
      1 => 'authenticated user',
    ),
    'module' => 'basic_cart',
  );

  return $permissions;
}
