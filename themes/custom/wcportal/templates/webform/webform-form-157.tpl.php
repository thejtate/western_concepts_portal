<?php

/**
 * @file
 * Customize the display of a complete webform.
 *
 * This file may be renamed "webform-form-[nid].tpl.php" to target a specific
 * webform on your site. Or you can leave it "webform-form.tpl.php" to affect
 * all webforms on your site.
 *
 * Available variables:
 * - $form: The complete form array.
 * - $nid: The node ID of the Webform.
 *
 * The $form array contains two main pieces:
 * - $form['submitted']: The main content of the user-created form.
 * - $form['details']: Internal information stored by Webform.
 */
?>

<?php $title = (isset($form['#node']->title)) ? $form['#node']->title : ""; ?>

<div class="content-item form-careers">
  <div class="title-form">
    <h1><?php print $title; ?></h1>
  </div>
  <div class="form-site-custom">
    <?php
    // Print out the main part of the form.
    // Feel free to break this up and move the pieces within the array.
    print drupal_render($form['submitted']);

    // Always print out the entire $form. This renders the remaining pieces of the
    // form that haven't yet been rendered above.
    print drupal_render_children($form);

    ?>
  </div>
</div>