<?php
/**
 * @file
 * Checkout html template
 */
?>

<div class="content-wrapper">

<div class="content-item">
<div class="title-content">
  <h3><?php print t('Check Out');?></h3>
  <div class="btn-wrapp pull-right">
    <div class="btn-submit">
      <?php print l(t("BACK TO STORE"), "shop");?>
    </div>
  </div>
</div>


<div class="table-product">
  <div class="table-title">
    <h4><?php print t("Your Cart");?></h4>
  </div>
  <?php if (!empty($cart)): ?>
    <?php print $vars['cart'];?>
  <?php endif; ?>

</div>
<div class="form-checkout-wrapper pull-right">
  <div class="form-site-custom">
    <?php print render($vars['checkout_form']);?>
  </div>
</div>
<hr>
</div>



</div>