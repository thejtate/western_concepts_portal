<?php

/**
 * @file
 * Orders
 */


/**
 * Orders page
 * @return string
 */
function wc_payment_orders() {
  wc_payment_orders_init_modal();

  // Sorting
  if (isset($_GET['sort']) && isset($_GET['order'])) {
    if ($_GET['sort'] == 'asc') {
      $sort = 'ASC';
    }
    else {
      $sort = 'DESC';
    }

    switch ($_GET['order']) {
      case 'Transaction ID':
        $order = 'tid';
        break;
      case 'Total amount':
        $order = 'amount';
        break;
      case 'Date':
        $order = 'transaction_date';
        break;
      case 'Status':
        $order = 'order_status';
        break;
      default:
        $order = 'transaction_date';
    }
  }
  else {
    // Default sort
    $sort = 'DESC';
    $order = ' transaction_date';
  }

  $query = db_select("wc_payment_results", "r");
  $query->fields("r");
  $query->orderBy($order, $sort);
  $query = $query->extend('TableSort')->extend('PagerDefault')->limit(50);
  $result = $query->execute();

  $header = array(
    array(
      "data" => t('Transaction ID'),
      "field" => "tid",
    ),
    array("data" => t('Products')),
    array(
      "data" => t('Total amount'),
      "field" => "amount",
    ),
    'default' => array(
      "data" => t('Date'),
      "field" => "transaction_date",
      "sort" => "desc",
    ),
    array(
      "data" => t('Status'),
      "field" => "order_status",
    )
  );

  $rows = array();
  while ($data = $result->fetchObject()) {
    $titles = wc_payment_orders_get_product_titles($data->order_data);
    $status_form = drupal_get_form("wc_payment_orders_status_ajax_form", $data->order_status, $data->pid);
    $rows[] = array(
      l($data->tid, "wc-payment/order/" . $data->pid . "/ajax", array(
        "attributes" => array(
          "class" => array(
            "ctools-use-modal",
            "ctools-modal-downtown-modal-ajax-style"
          )
        )
      )),
      implode("<br>", $titles),
      $data->amount,
      $data->transaction_date,
      render($status_form)
    );
  }

// Output of table with the paging
  $output = theme_table(
    array(
      "header" => $header,
      "rows" => $rows,
      "attributes" => array("width" => "100%"),
      "sticky" => TRUE, // Table header will be sticky
      "caption" => "",
      "colgroups" => array(),
      "empty" => t("No orders") // The message to be displayed if table is empty
    )
  ) . theme("pager");
  return $output;
}


/**
 * Get product titles from cart
 * @param $order_data
 * @return array
 */
function wc_payment_orders_get_product_titles($order_data) {
  $titles = array();
  $order_data = unserialize($order_data);
  if (isset($order_data['cart']) && is_array($order_data['cart'])) {
    foreach ($order_data['cart'] as $key => $item) {
      $title = (isset($item['node']->title)) ? $item['node']->title : "";
      $color = (isset($item['color']) && !empty($item['color'])) ? $item['color'] : NULL;
      $size = (isset($item['size']) && !empty($item['size'])) ? $item['size'] : NULL;
      $count = (isset($item['count']) && !empty($item['count'])) ? $item['count'] : 0;
      $price = (isset($item['price']) && !empty($item['price'])) ? $item['price'] : 0;
      $discount = (isset($item['discount']) && !empty($item['discount'])) ? $item['discount'] : 0;

      // reservation
      $r_name = (isset($item['r_name']) && !empty($item['r_name'])) ? $item['r_name'] : "";
      $r_date = (isset($item['r_date']) && !empty($item['r_date'])) ? $item['r_date'] : "";
      $r_time = (isset($item['r_time']) && !empty($item['r_time'])) ? $item['r_time'] : "";
      $r_number_of_guests = (isset($item['r_number_of_guests']) && !empty($item['r_number_of_guests'])) ? $item['r_number_of_guests'] : 0;


      if (!empty($title)) {
        $row = $title . " ";
        // store
        if (!empty($color) || !empty($size) || !empty($discount)) {
          $row .= "<span style='color:gray;'>(";
          if (!empty($color)) {
            $row .= $color . " ";
          }
          if (!empty($size)) {
            $row .= $size;
          }
          if (!empty($discount)) {
            $row .= $discount . '% Off';
          }
          $row .= ")</span>";
        }

        // reservations
        if (!empty($r_date) || !empty($r_time) || !empty($r_number_of_guests)) {
          $row .= "<span style='color:gray;'>(";
          if (!empty($r_date)) {
            $row .= $r_date . " ";
          }
          if (!empty($r_time)) {
            $row .= $r_time . " ";
          }
          if (!empty($r_number_of_guests)) {
            $row .= "No.:" . $r_number_of_guests;
          }
          $row .= ")</span>";
        }

        $row .= " <b>$" . $price . "</b>";
        $row .= " (qty:" . $count . ")";
        $titles[] = $row;
      }
    }
  }
  return $titles;
}


/**
 * Change order status
 */
function wc_payment_orders_status_ajax_form($form, &$form_state, $status, $pid) {
  $order_statuses = array(
    ORDER_STATUS_FAILED => ORDER_STATUS_FAILED,
    ORDER_STATUS_SUCCESS => ORDER_STATUS_SUCCESS,
    ORDER_STATUS_IN_PROGRESS => ORDER_STATUS_IN_PROGRESS,
    ORDER_STATUS_COMPLETE => ORDER_STATUS_COMPLETE,
    ORDER_STATUS_TEST_FAILED => ORDER_STATUS_TEST_FAILED,
    ORDER_STATUS_TEST_SUCCESS => ORDER_STATUS_TEST_SUCCESS,
  );

  $form['order_status'] = array(
    '#type' => 'select',
    '#title' => t('Status'),
    '#options' => $order_statuses,
    '#weight' => 1,
    '#default_value' => array($status),
    '#prefix' => '<div id="wc_payment_orders_status_wrapper_' . $pid . '">',
    '#suffix' => '</div>',
    '#ajax' => array(
      'callback' => 'wc_payment_orders_status_ajax_form_callback',
      'wrapper' => 'wc_payment_orders_status_wrapper_' . $pid,
    ),
  );
  return $form;
}


/**
 * Order update status AJAX callback
 * @param $form
 * @param $form_state
 * @return mixed
 */
function wc_payment_orders_status_ajax_form_callback($form, $form_state) {
  $element = $form['order_status'];
  $pid = (isset($form_state['build_info']['args'][1])) ? $form_state['build_info']['args'][1] : NULL;
  $status = (isset($form_state['values']['order_status'])) ? $form_state['values']['order_status'] : "";
  if (!empty($pid) && is_numeric($pid)) {
    $new_status = wc_payment_orders_status_update_status($pid, $status);
    $element['#value'] = $new_status;
  }
  return $element;
}

/**
 * Update order status
 * @param $pid
 * @param $status
 */
function wc_payment_orders_status_update_status($pid, $status) {
  drupal_alter('wc_payment_orders_status_update', $pid, $status);
  $result = db_update('wc_payment_results') // Table name no longer needs {}
    ->fields(array('order_status' => $status,))
    ->condition('pid', $pid, '=')
    ->execute();
  if ($result) {
    drupal_set_message('Status has been set to "' . $status . '".');
  }
  return $status;
}


/**
 * Init modal form
 */
function wc_payment_orders_init_modal() {
  // Modal
  ctools_include('modal');
  ctools_modal_add_js();
  $sample_style = array(
    'ctools-sample-style' => array(
      'modalSize' => array(
        'type' => 'fixed',
        'width' => 500,
        'height' => 300,
        'addWidth' => 20,
        'addHeight' => 15,
      ),
      'modalOptions' => array(
        'opacity' => .5,
        'background-color' => '#000',
      ),
      'animation' => 'fadeIn',
      'modalTheme' => 'CToolsSampleModal',
      'throbber' => theme('image', array(
        'path' => ctools_image_path('ajax-loader.gif', 'ctools_ajax_sample'),
        'alt' => t('Loading...'),
        'title' => t('Loading')
      )),
    ),
  );

  drupal_add_js($sample_style, 'setting');
  ctools_add_js('ctools-ajax-sample', 'ctools_ajax_sample');
  ctools_add_css('ctools-ajax-sample', 'ctools_ajax_sample');
}


function wc_payment_orders_init_print($title = "") {
  global $base_url;
  drupal_add_js(drupal_get_path("module", "wc_payment") . "/js/jquery.printElement.min.js");
  drupal_add_js(drupal_get_path("module", "wc_payment") . "/js/wc_payment_print.js");
  $settings = array(
    "wc_payment_order" =>
    array(
      'order_css_link' => $base_url . base_path() . drupal_get_path("module", "wc_payment") . "/css/wc_payment_order.css",
      'title' => $title,
    )
  );
  drupal_add_js($settings, "setting");

}

/**
 * Order full page
 * @param $pid
 * @param $js
 * @param bool $force_page_reload
 * @return string
 */
function wc_payment_order_view($pid, $js, $force_page_reload = FALSE) {
  drupal_add_css(drupal_get_path("module", "wc_payment") . "/css/wc_payment_order.css");
  $order = wc_payment_order_load($pid);
  $title = t("Order") . " #" . $pid;
  wc_payment_orders_init_print("wc_order_" . $pid);
  $output = theme("wc_payment_order", array('order' => $order));
  if ($js) {
    ctools_include('ajax');
    $commands = array();
    $commands[] = ajax_command_html('#modal-title', $title);
    $commands[] = ajax_command_html('#modal-content', $output);
    print ajax_render($commands);
    exit;
  }
  else {
    return $output;
  }
}


function wc_payment_order_load($pid) {
  $query = db_select("wc_payment_results", "r");
  $query->fields("r");
  $query->condition('pid', $pid, '=');
  $order = $query->execute()->fetchAssoc();
  $order['order_data'] = unserialize($order['order_data']);
  return $order;
}