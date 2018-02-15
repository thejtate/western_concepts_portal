<?php

/**
 * @file
 * WC blocks
 */


/**
 * Implements hook_block_info().
 */
function wc_blocks_block_info() {
  $blocks = array();

  $blocks['wc_blocks_brochure_block'] = array(
    'info' => t('WC blocks: Brochure link'),
  );


  return $blocks;
}

/**
 * Implements hook_block_configure().
 */
function wc_blocks_block_configure($delta = '') {
  $form = array();

  switch ($delta) {
    case 'wc_blocks_brochure_block':
      $key = 'wc_blocks_brochure_block_';

      $form[$key . 'text'] = array(
        '#type' => 'textfield',
        '#title' => t('Button text'),
        '#default_value' => variable_get($key . 'text', ''),
      );

      $form[$key . 'file'] = array(
        '#name' => 'wc_blocks_brochure_block_file',
        '#type' => 'managed_file',
        '#title' => t('File'),
        '#default_value' => variable_get($key . 'file_fid', ''),
        '#upload_location' => 'public://wc_blocks_brochure_block/',
        '#upload_validators' => array(
          'file_validate_extensions' => array('pdf'),
        ),
      );

      break;
  }

  return $form;
}

/**
 * Implements hook_block_save().
 */
function wc_blocks_block_save($delta = '', $edit = array()) {
  switch ($delta) {
    case 'wc_blocks_brochure_block':
      $key = 'wc_blocks_brochure_block_';
      variable_set($key . 'text', $edit[$key . 'text']);


      // Saving the file, setting it to a permanent state, setting a FID variable
      $file = file_load($edit[$key . 'file']);
      if (!empty($file)) {
        $file->status = FILE_STATUS_PERMANENT;
        file_save($file);
        $block = block_load('wc_blocks', $delta);
        file_usage_add($file, 'wc_blocks', 'block', $block->bid);
        variable_set($key . 'file_fid', $file->fid);
      }
      else {
        variable_set($key . 'file_fid', 0);
      }
      break;
  }
}

/**
 * Implements hook_block_view().
 */
function wc_blocks_block_view($delta = '') {
  $block = array();

  switch ($delta) {
    case 'wc_blocks_brochure_block':
      $block['subject'] = '';
      $block['content'] = _wc_blocks_brochure_content();
      break;
  }

  return $block;
}


/**
 * Get social top block content
 * @return string
 */
function _wc_blocks_brochure_content() {
  $key = 'wc_blocks_brochure_block_';
  $text = variable_get($key . 'text', "");

  $file = file_load(variable_get($key . 'file_fid', ''));
  $file_path = (isset($file->uri)) ? file_create_url($file->uri) : "";

  if (empty($file_path) || empty($text)){
    return;
  }
  $brochure_link = l($text, $file_path, array('html' => TRUE, 'attributes' => array('target' => '_blank', 'class' => array('brochure-bnt', 'link'))));

  return theme("wc_blocks_brochure_block", array('brochure_link' => $brochure_link));
}

