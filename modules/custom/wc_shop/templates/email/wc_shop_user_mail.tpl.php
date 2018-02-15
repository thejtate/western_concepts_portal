<?php
/**
 * @file
 * Shop user email html template
 */

$fname = (isset($data['first_name'])) ? $data['first_name'] : "";
$lname = (isset($data['last_name'])) ? $data['last_name'] : "";
$birthday = (isset($data['birthday'])) ? $data['birthday'] : "";

$address = (isset($data['address'])) ? $data['address'] : "";
$city = (isset($data['city'])) ? $data['city'] : "";
$state = (isset($data['state'])) ? $data['state'] : "";
$zip = (isset($data['zip'])) ? $data['zip'] : "";
$phone = (isset($data['phone'])) ? $data['phone'] : "";
$company = (isset($data['company'])) ? $data['company'] : "";

$shipping_first_name = (isset($data['shipping_first_name'])) ? $data['shipping_first_name'] : "";
$shipping_last_name = (isset($data['shipping_last_name'])) ? $data['shipping_last_name'] : "";
$shipping_address = (isset($data['shipping_address'])) ? $data['shipping_address'] : "";
$shipping_city = (isset($data['shipping_city'])) ? $data['shipping_city'] : "";
$shipping_state = (isset($data['shipping_state'])) ? $data['shipping_state'] : "";
$shipping_zip = (isset($data['shipping_zip'])) ? $data['shipping_zip'] : "";
$shipping_company = (isset($data['shipping_company'])) ? $data['shipping_company'] : "";

$amount  = (isset($data['amount '])) ? $data['amount '] : "";

$order_data = (isset($data['order_data'])) ? unserialize($data['order_data']) : array();

$subtotal = (isset($order_data['total']['subtotal'])) ? $order_data['total']['subtotal'] : 0;
$shipping = (isset($order_data['total']['shipping'])) ? $order_data['total']['shipping'] : 0;
$total = (isset($order_data['total']['total'])) ? $order_data['total']['total'] : 0;
$cart = (isset($order_data['cart'])) ? $order_data['cart'] : array();

$transaction_id = (isset($data['transaction_id'])) ? $data['transaction_id'] : "";
$transaction_date = (isset($data['transaction_date'])) ? $data['transaction_date'] : "";
$pid = (isset($data['pid'])) ? $data['pid'] : "";


$key = (isset($data['key'])) ? $data['key'] : 'store';


switch ($key) {
  case "progressive_dinner" :
    $thanks_text = t('Congratulations on purchasing one of our unique and delicious progressive dinner packages');
    break;
  default:
    $thanks_text = t("Thank you for shopping with !site_name! The payment receipt is given below and we will email you separately when your product ships.", array("!site_name" => l("Western Concepts Dining", $GLOBALS['base_url'])));
    break;
}

?>



<h2><?php print t("Dear %first_name %last_name!", array("%first_name" => $fname, "%last_name" => $lname)); ?></h2>

<div><?php print $thanks_text; ?></div>

<h3><?php print t('Product Information:'); ?></h3>

<div><b><?php print t("Receipt #@payment_id as of @transaction_date.", array(
      "@payment_id" => $pid,
      "@transaction_date" => $transaction_date
    )); ?></b></div>

<div><b><?php print t('Payjunction transaction id'); ?>:</b> #<?php print $transaction_id; ?></div>


<table style="width: 600px; border: 1px solid gray;">
  <thead style="background-color: #808080; color: white;">
  <th><?php print t("Title"); ?></th>
  <th><?php print t("Price"); ?></th>
  <th><?php print t("Qty"); ?></th>
  </thead>
  <tbody>
  <?php foreach ($cart as $k => $item): ?>
    <?php
    $title = (isset($item['node']->title)) ? $item['node']->title : "";
    $attributes = array();

    // store
    if ((isset($item['color']) && !empty($item['color']))) {
      $attributes[] = t("Color") . ": " . $item['color'];
    }
    if ((isset($item['size']) && !empty($item['size']))) {
      $attributes[] = t("Size") . ": " . $item['size'];
    }

    // gift card type
    if (isset($item['gift_type']) && is_array($item['gift_type'])){
      foreach($item['gift_type'] as $gift_type_data){
        $attributes[] = $gift_type_data['title'] . ": " . $gift_type_data['count'];
      }
    }

    // reservation
    if ((isset($item['r_name']) && !empty($item['r_name']))) {
      $attributes[] = t("Party name") . ": " . $item['r_name'];
    }
    if ((isset($item['r_date']) && !empty($item['r_date']))) {
      $attributes[] = t("Date") . ": " . $item['r_date'];
    }
    if ((isset($item['r_time']) && !empty($item['r_time']))) {
      $attributes[] = t("Time") . ": " . $item['r_time'];
    }
    if ((isset($item['r_number_of_guests']) && !empty($item['r_number_of_guests']))) {
      $attributes[] = t("No. of guests") . ": " . $item['r_number_of_guests'];
    }


    if (!empty($attributes)) {
      $title .= "<span style='color:gray;'> (" . implode(", ", $attributes) . ")</span>";
    }

    $price = (isset($item['price'])) ? $item['price'] : 0;
    $qty = (isset($item['count'])) ? $item['count'] : 0;
    ?>

    <tr>
      <td style="border-bottom: 1px solid gray;"><?php print $title; ?></td>
      <td style="border-bottom: 1px solid gray; text-align: center">$<?php print $price; ?></td>
      <td style="border-bottom: 1px solid gray; text-align: center"><?php print $qty; ?></td>
    </tr>
  <?php endforeach; ?>

  <tr>
    <td colspan="3" style="text-align: right; margin-right: 10px;">
      <b><?php print t('Price'); ?>:</b> $<?php print $subtotal; ?>
    </td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: right; margin-right: 10px;">
      <b><?php print t('Shipping'); ?>:</b> $<?php print $shipping; ?>
    </td>
  </tr>
  <tr>
    <td colspan="3" style="text-align: right; margin-right: 10px;">
      <b><?php print t('Total'); ?>:</b> $<?php print $total; ?>
    </td>
  </tr>
  </tbody>
</table>

<p>&nbsp;</p>

<h3><?php print t('Billing Address:'); ?></h3>
<div><b><?php print t('Name'); ?>:</b> <?php print $fname; ?> <?php print $lname; ?></div>
<?php if (isset($birthday)):?>
  <div><b><?php print t('Birthday'); ?>:</b> <?php print $birthday; ?></div>
<?php endif; ?>


<div><b><?php print t('Address'); ?>:</b> <?php print $address; ?></div>
<div><?php print $city; ?> <?php print $state; ?>, <?php print $zip; ?></div>
<div><b><?php print t('Phone'); ?>:</b> <?php print $phone; ?></div>
<div><b><?php print t('Company'); ?>:</b> <?php print $company; ?></div>

<p>&nbsp;</p>


<?php if (!empty($shipping_first_name) || !empty($shipping_last_name) || !empty($shipping_address) || !empty($shipping_city) || !empty($shipping_company)) : ?>
  <h3><?php print t('Shipping Address:'); ?></h3>
  <?php if (!empty($shipping_first_name) || !empty($shipping_last_name)) : ?>
    <div><b><?php print t('Name'); ?>:</b> <?php print $shipping_first_name; ?> <?php print $shipping_last_name; ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($shipping_address) || !empty($shipping_city) || !empty($shipping_state) || !empty($shipping_zip)) : ?>
    <div><b><?php print t('Address'); ?>:</b> <?php print $shipping_address; ?> </div>
    <div><?php print $shipping_city; ?> <?php print $shipping_state; ?>, <?php print $shipping_zip; ?></div>
  <?php endif; ?>

  <?php if (!empty($shipping_company)) : ?>
    <div><b><?php print t('Company'); ?>:</b> <?php print $shipping_company; ?></div>
  <?php endif; ?>

  <p>&nbsp;</p>
<?php endif; ?>


<div><?php print t('Please keep this receipt for your records.');?></div>
<div><?php print t('Thank you!'); ?>,</div>
<div><?php print l("Western Concepts Dining", $GLOBALS['base_url']); ?></div>