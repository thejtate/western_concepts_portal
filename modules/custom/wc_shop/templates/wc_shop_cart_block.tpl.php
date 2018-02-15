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
        <th><?php print t("ITEM"); ?></th>
        <th><?php print t("QTY"); ?></th>
        <th><?php print t("PRICE"); ?></th>
      </tr>
      </thead>
      <tfoot>
      <tr>
        <td colspan="2"><?php print t("SUB-TOTAL"); ?></td>
        <td>$<?php print number_format((float)$variables['total']['subtotal'], 2, '.', ''); ?></td>
      </tr>
      </tfoot>
      <tbody>
      <?php foreach ($cart as $key => $row) : ?>
        <tr>
          <td>
            <?php print $row['title']; ?>
            <?php if (!empty($row['color']) || !empty($row['size'])) : ?>
              (<?php print $row['color']; ?> <?php print $row['size']; ?>)
            <?php endif; ?>
          </td>
          <td><?php print $row['count']; ?></td>
          <td> $<?php print number_format((float)$row['price'], 2, '.', ''); ?></td>
        </tr>
      <?php endforeach; ?>
      </tbody>
    </table>
    <div class="btn-wrapp">
      <div class="btn-submit">
        <?php print l(t("Check out"), "wc-shop/checkout"); ?>
      </div>
    </div>
  </div>
<?php else: ?>
  <?php print t("Cart is empty"); ?>
<?php endif; ?>
