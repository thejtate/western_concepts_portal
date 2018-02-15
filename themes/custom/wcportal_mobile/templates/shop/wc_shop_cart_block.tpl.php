<?php
/**
 * @file
 * Cart shopping cart html template
 */
?>

<?php if (!empty($cart)): ?>
  <div class="table-check_out">
    <table class="table">
      <thead>
      <tr>
        <th></th>
        <th class="item"><?php print t("ITEM"); ?></th>
        <th class="qty"><?php print t("QTY"); ?></th>
        <th class="price"><?php print t("PRICE"); ?></th>
      </tr>
      </thead>
      <tbody>
      <?php foreach ($cart as $key => $row) : ?>
        <tr>
          <td><?php print l("", "wc-shop/cart/remove/" . $key, array("attributes" => array("class" => array("btn-remove")))); ?></td>
          <td class="item">
            <?php print $row['title']; ?>
            <?php if (!empty($row['color']) || !empty($row['size'])) : ?>
              (<?php print $row['color']; ?> <?php print $row['size']; ?>)
            <?php endif; ?>
          </td>
          <td class="qty"><?php print $row['count']; ?></td>
          <td class="price"> $<?php print $row['price']; ?></td>
        </tr>
      <?php endforeach; ?>
      </tbody>
      <tfoot>
      <tr>
        <td colspan="3" class="qty"><?php print t("SUB-TOTAL"); ?></td>
        <td class="price">$<?php print $variables['total']['subtotal']; ?></td>
      </tr>
      </tfoot>
    </table>
    <div class="btn-wrapper">
      <div class="btn-submit">
        <?php print l(t("Check out"), "wc-shop/checkout"); ?>
      </div>
    </div>
  </div>
<?php else: ?>
  <?php print t("Cart is empty"); ?>
<?php endif; ?>
