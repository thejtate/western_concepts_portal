<?php
/**
 * @file
 * Wc Payment Order html template
 */
?>

<div class="order-print-btn"><?php print t('Print'); ?></div>
<div class="wc-payment-order-content">
  <div class="wc-payment-order-table">
    <?php if (!empty($order)): ?>
      <?php
      $cart = (isset($order['order_data']['cart'])) ? $order['order_data']['cart'] : array();
      $total = (isset($order['order_data']['total'])) ? $order['order_data']['total'] : array(
        'subtotal' => 0,
        'total' => 0,
        'shipping' => 0
      );
      $status = (isset($order['order_status'])) ? $order['order_status'] : "";
      ?>

      <h2><?php print t('Status') . ": " . $status; ?></h2>
      <?php if(!empty($order['error'])): ?>
          <h3 style="color:red;"><?php print t('Payment Error message: @message', array('@message' => $order['error'])); ?></h3>
      <?php endif; ?>
      <table class="order-table" width="100%" border="1">
        <thead>
        <tr>
          <th><?php print t('Product') ?></th>
          <th><?php print t('QTY') ?></th>
          <th><?php print t('Price') ?></th>
          <th><?php print t('Subtotal') ?></th>
        </tr>
        </thead>
        <tbody>
        <?php foreach ($cart as $vid => $item) : ?>
          <?php
          $title = (isset($item['node']->title)) ? $item['node']->title : "";

          // store
          $color = (isset($item['color'])) ? $item['color'] : "";
          $size = (isset($item['size'])) ? $item['size'] : "";
          $discount = (isset($item['discount'])) ? $item['discount'] : "";
          $sites = (isset($item['sites'])) ? $item['sites'] : "";

          // reservation
          $r_name = (isset($item['r_name'])) ? $item['r_name'] : "";
          $r_date = (isset($item['r_date'])) ? $item['r_date'] : "";
          $r_time = (isset($item['r_time'])) ? $item['r_time'] : "";
          $r_number_of_guests = (isset($item['r_number_of_guests'])) ? $item['r_number_of_guests'] : 0;

          $count = (isset($item['count'])) ? $item['count'] : 0;
          $price = (isset($item['price'])) ? $item['price'] : 0;
          $subtotal = $price * $count;
          ?>

          <tr class="order-item">
            <td>
              <div class="order-item-title"><?php print $title; ?></div>

              <?php if (!empty($color)) : ?>
                <div class="order-item-color"><?php print t("Color") . ": " . $color; ?></div>
              <?php endif; ?>
              <?php if (!empty($size)) : ?>
                <div class="order-item-size"><?php print t("Size") . ": " . $size; ?></div>
              <?php endif; ?>
              <?php if (!empty($sites)) : ?>
                <div class="order-item-sites"><?php print $sites; ?></div>
              <?php endif; ?>
              <?php if (!empty($discount)) : ?>
                <div class="order-item-discount"><?php print t("Discount") . ": " . $discount . '% Off'; ?></div>
              <?php endif; ?>

              <?php if (!empty($r_name)) : ?>
                <div class="order-item-r-name"><?php print t("Name of party") . ": " . $r_name; ?></div>
              <?php endif; ?>
              <?php if (!empty($r_date)) : ?>
                <div class="order-item-r-date"><?php print t("Date") . ": " . $r_date; ?></div>
              <?php endif; ?>
              <?php if (!empty($r_time)) : ?>
                <div class="order-item-r-time"><?php print t("Time") . ": " . $r_time; ?></div>
              <?php endif; ?>
              <?php if (!empty($r_number_of_guests)) : ?>
                <div class="order-item-r-number-of-guests"><?php print t("No. of guests") . ": " . $r_number_of_guests; ?></div>
              <?php endif; ?>

            </td>
            <td><?php print $count; ?></td>
            <td>$<?php print $price; ?></td>
            <td>$<?php print $subtotal; ?></td>
          </tr>
        <?php endforeach; ?>
        <tr class="order-total">
          <td colspan="4"><?php print t('Subtotal') ?>: $<?php print $total['subtotal'] ?></td>
        </tr>
        <tr class="order-total">
          <td colspan="4"><?php print t('Shipping') ?>: $<?php print $total['shipping'] ?></td>
        </tr>
        <tr class="order-total">
          <td colspan="4"><?php print t('Total') ?>: $<?php print $total['total'] ?></td>
        </tr>
        </tbody>
      </table>

      <?php $billing = isset($order['billing_data']) ? $order['billing_data'] : array(); ?>
      <div class="order-billing">
        <h2><?php print t('Billing Info'); ?></h2>
        <?php foreach ($billing as $title => $value) : ?>
          <div class="order-billing-item">
            <span class="order-billing-item-title"><?php print $title; ?>:</span>
            <span class="order-billing-item-value"><?php print $value; ?></span>
          </div>
        <?php endforeach; ?>
      </div>

      <?php $shipping = isset($order['shipping_data']) ? $order['shipping_data'] : array(); ?>
      <div class="order-shipping">
        <h2><?php print t('Shipping Info'); ?></h2>

        <?php foreach ($shipping as $title => $value) : ?>
          <div class="order-shipping-item">
            <span class="order-shipping-item-title"><?php print $title; ?>:</span>
            <span class="order-shipping-item-value"><?php print $value; ?></span>
          </div>
        <?php endforeach; ?>
      </div>
    <?php else: ?>
      <?php print t("Nonexistent order"); ?>
    <?php endif; ?>
  </div>
</div>