<?php
/**
 * @file
 * Cart shopping cart html template
 */
?>


<?php if (!empty($cart)): ?>
  <table class="table">
    <thead>
    <tr>
      <th><?php print t("ITEM"); ?></th>
      <th><?php print t("QTY"); ?></th>
      <th><?php print t("PRICE"); ?></th>
    </tr>
    </thead>
    <tfoot>
    <tr>
      <td colspan="2"><?php print t("SUB-TOTAL"); ?></td>
      <td><span>$<?php print number_format((float)$variables['total']['subtotal'], 2, '.', ''); ?></span></td>
    </tr>
    <tr>
      <td colspan="2"><?php print t("SHIPPING"); ?></td>
      <td><span>$<?php print number_format((float)$variables['total']['shipping'], 2, '.', ''); ?></span></td>
    </tr>
    <tr>
      <td colspan="2"><strong><?php print t("TOTAL"); ?></strong></td>
      <td><strong>$<?php print number_format((float)$variables['total']['total'], 2, '.', ''); ?></strong></td>
    </tr>
    </tfoot>
    <tbody>
    <?php foreach ($cart as $key => $row) : ?>
      <tr>
        <td>
          <div class="image"><?php print $row['image']; ?></div>
          <div class="text-product checkout-page-cart">
            <?php print $row['title']; ?><br/>

            <div class="data-product">
              <?php if (isset($row['color']) && !empty($row['color'])) : ?>
                <span><?php print t("Color:"); ?> <?php print $row['color']; ?></span>
              <?php endif; ?>
              <?php if (isset($row['size']) && !empty($row['size'])) : ?>
                <span><?php print t("Size:"); ?>  <?php print $row['size']; ?></span>
              <?php endif; ?>
              <?php if (isset($row['sites']) && !empty($row['sites'])) : ?>
                <span><?php print $row['sites']; ?></span>
              <?php endif; ?>
              <?php if (isset($row['discount']) && !empty($row['discount'])) : ?>
                <span><?php print t("Discount:"); ?> <?php print $row['discount'] . '% Off'; ?></span>
              <?php endif; ?>
            </div>

          </div>
          <div class="btn-remove">
            <?php print l(t("Remove"), "wc-shop/cart/remove/" . $key, array("attributes" => array("class" => array("remove")))); ?>
          </div>
        </td>
        <td><?php print $row['count']; ?></td>
        <td>$<?php print number_format((float)$row['price'], 2, '.', ''); ?></td>
      </tr>
    <?php endforeach; ?>
    </tbody>
  </table>

<?php else: ?>
  <?php print t("Cart is empty"); ?>
<?php endif; ?>
