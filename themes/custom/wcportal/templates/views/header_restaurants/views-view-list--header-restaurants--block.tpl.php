<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */
?>
<?php print $wrapper_prefix; ?>
  <?php if (!empty($title)) : ?>
    <h3><?php print $title; ?></h3>
  <?php endif; ?>
  <?php print $list_type_prefix; ?>
    <?php foreach ($rows as $id => $row): ?>
      <li class="<?php print $classes_array[$id]; ?> navigation-item"><?php print $row; ?></li>
      <?php if($id == 2):?>
        <li class="logo_top navigation-item">
          <a href="<?php print url('<front>');?>" class="header-link">
            <span class="logo"><img src="<?php print base_path() . drupal_get_path('theme', 'wcportal')?>/images/nav_icon/logo_nav.png" alt="<?php print t('Logo'); ?>"></span>
            <?php /*
            <span class="text-item"><?php print t('Our family of award-winning restaurants'); ?></span>
            */?>
          </a></li>
      <?php endif;?>
    <?php endforeach; ?>
  <?php print $list_type_suffix; ?>
<?php print $wrapper_suffix; ?>
