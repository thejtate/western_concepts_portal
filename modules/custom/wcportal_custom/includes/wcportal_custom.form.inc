<?php
/**
* @file
* Custom page with site settings
*/
function wcportal_custom_site_setings_form() {
  $form = array();
   $form['footer_info'] = array(
    '#type' => 'fieldset',
    '#title' => t('Footer info'),
    '#weight' => 1,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['footer_info']['footer_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => variable_get('footer_title', ''),
    '#size' => 80,
    '#maxlength' => 128,
  );
  $form['footer_info']['footer_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#default_value' => variable_get('footer_address', ''),
    '#size' => 80,
    '#maxlength' => 128,
  );

  $form['wc_top_image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Top image link'),
    '#weight' => 2,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['wc_top_image']['image'] = array(
    '#title' => t('Button image for desctop version'),
    '#type' => 'managed_file',
    '#description' => t('Top button image.'),
    '#default_value' => variable_get('wc_top_image_fid', ''),
    '#upload_location' => 'public://top-image/',
  );

  $form['wc_top_image']['wc_top_image_link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link for desktop version'),
    '#default_value' => variable_get('wc_top_image_link', 'http://www.westernconceptsdining.com/westfest'),
  );


  $form['wc_top_image']['mobile_image'] = array(
    '#title' => t('Button image for mobile version'),
    '#type' => 'managed_file',
    '#description' => t('Top button image.'),
    '#default_value' => variable_get('wc_top_mobile_image_fid', ''),
    '#upload_location' => 'public://top-image/',
  );

  $form['wc_top_image']['map_mobile_image'] = array(
    '#title' => t('Map image for mobile version'),
    '#type' => 'managed_file',
    '#description' => t('Map image.'),
    '#default_value' => variable_get('wc_top_map_mobile_image_fid', ''),
    '#upload_location' => 'public://top-image/',
  );




  $form['#submit'][] = 'wc_save_image';

  return system_settings_form($form);
}

function wc_save_image($form, $form_state) {
  global $user;

  if(!empty($form_state['values']['image'])) {
    $file = file_load($form_state['values']['image']);
    // Change status to permanent.
    $file->status = FILE_STATUS_PERMANENT;
    // Save.
    file_save($file);
    // Record that the module (in this example, user module) is using the file.
    file_usage_add($file, 'user', 'user', $user->uid);
    variable_set('wc_top_image_fid', $file->fid);
  } else {
    variable_set('wc_top_image_fid', 0);
  }


  if(!empty($form_state['values']['mobile_image'])) {
    $file = file_load($form_state['values']['mobile_image']);
    // Change status to permanent.
    $file->status = FILE_STATUS_PERMANENT;
    // Save.
    file_save($file);
    // Record that the module (in this example, user module) is using the file.
    file_usage_add($file, 'user', 'user', $user->uid);
    variable_set('wc_top_mobile_image_fid', $file->fid);
  } else {
    variable_set('wc_top_mobile_image_fid', 0);
  }

  if(!empty($form_state['values']['map_mobile_image'])) {
    $file = file_load($form_state['values']['map_mobile_image']);
    // Change status to permanent.
    $file->status = FILE_STATUS_PERMANENT;
    // Save.
    file_save($file);
    // Record that the module (in this example, user module) is using the file.
    file_usage_add($file, 'user', 'user', $user->uid);
    variable_set('wc_top_map_mobile_image_fid', $file->fid);
  } else {
    variable_set('wc_top_map_mobile_image_fid', 0);
  }
}
