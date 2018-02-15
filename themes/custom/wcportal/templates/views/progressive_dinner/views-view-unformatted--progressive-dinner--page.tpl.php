<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php foreach ($rows as $id => $row): ?>
  <?php if(!empty($view->result[$id]->node_type) && $view->result[$id]->node_type == 'progressive_dinner_your_reservat'):?>
    <div id="reservation-form" class="slide-<?php print($id + 1)?> slide-progressive">
  <?php else: ?>
    <div class="slide-<?php print($id + 1)?> slide-progressive">
  <?php endif;?>

    <?php print $row; ?>
  </div>
<?php endforeach; ?>
