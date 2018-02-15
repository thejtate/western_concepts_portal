<?php
/**
 * @file
 * Checkout html template
 */
?>



<div class="content-item">

  <div class="content-title">
    <div class="btn-wrapp pull-right">
      <div class="btn-submit">
        <?php print l(t("BACK TO STORE"), "shop"); ?>
      </div>
    </div>
    <h1><?php print t('Check Out'); ?></h1>
  </div>


  <div class="table-product">
    <div class="table-title">
      <h4><?php print t("Your Cart"); ?></h4>
    </div>
    <?php if (!empty($cart)): ?>
      <?php print $vars['cart']; ?>
    <?php endif; ?>

  </div>
  <div class="form-checkout form">
    <?php print render($vars['checkout_form']); ?>
  </div>
  <div class="btn-gift">
    <span class="btn-title"><?php print t('HAVE A GIFT CARD?'); ?></span>
    <?php print l(t("Check Your Balance"), "https://secure.alohaenterprise.com:4430/efMemberLinkLogin.do?companyId=wcs02", array('attributes' => array('target' => '_blank'))); ?>
  </div>


</div>