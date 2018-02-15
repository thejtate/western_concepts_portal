<?php

/**
 * @file
 * Settings forms
 */

/**
 * Create settings form in drupal configuration setings section for module.
 */
function wc_shop_admin_settings() {
  $form['wc_shop_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Store Settings'),
    '#collapsible' => TRUE,
  );

  $form['wc_shop_settings']['wc_shop_settings_shipping_price'] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#title' => t('Shipping price ($)'),
    '#default_value' => variable_get('wc_shop_settings_shipping_price', 0),
  );

  $form['wc_shop_settings']['wc_shop_settings_rewards_card_price'] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#title' => t('Rewards Card Members price ($)'),
    '#default_value' => variable_get('wc_shop_settings_rewards_card_price', 0),
  );

  $form['wc_shop_settings']['wc_shop_settings_progressive_dinner_price'] = array(
    '#type' => 'textfield',
    '#size' => 5,
    '#title' => t('Progressive dinner price per guest ($)'),
    '#default_value' => variable_get('wc_shop_settings_progressive_dinner_price', 0),
  );

  $form['wc_shop_settings']['store_check_balance_link'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('"Check your balance" link'),
    '#default_value' => variable_get('store_check_balance_link', "https://secure.alohaenterprise.com:4430/efMemberLinkLogin.do?companyId=wcs02"),
  );


  $form['wc_shop_email_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email Settings'),
    '#collapsible' => TRUE,
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_all'] = array(
    '#type' => 'textfield',
    '#title' => t('For all of the sites'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_all', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_musashis'] = array(
    '#type' => 'textfield',
    '#title' => t('Musashi’s'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_musashis', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_sushineko'] = array(
    '#type' => 'textfield',
    '#title' => t('Sushineko'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_sushineko', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_wrt'] = array(
    '#type' => 'textfield',
    '#title' => t('Will Rogers Theatre'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_wrt', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_tasting_room'] = array(
    '#type' => 'textfield',
    '#title' => t('Tasting room'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_tasting_room', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_coach_house'] = array(
    '#type' => 'textfield',
    '#title' => t('Coach house'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_coach_house', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_lobby_bar'] = array(
    '#type' => 'textfield',
    '#title' => t('Lobby bar'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_lobby_bar', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  $form['wc_shop_email_settings']['wc_shop_email_settings_hutch'] = array(
    '#type' => 'textfield',
    '#title' => t('The Hutch'),
    '#size' => 180,
    '#maxlength' => 256,
    '#default_value' => variable_get('wc_shop_email_settings_hutch', ''),
    '#description' => t("Example: webmaster@yoursite.com, sales@yoursite.com"),
  );

  return system_settings_form($form, TRUE);
}