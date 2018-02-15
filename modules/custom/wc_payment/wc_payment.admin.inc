<?php

/**
 * @file
 * Settings forms
 */

/**
 * Create settings form in drupal configuration setings section for module.
 */
function wc_payment_admin_settings() {
  $form['wc_payment_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Payment Settings'),
    '#collapsible' => TRUE,
  );


  $form['wc_payment_settings']['wc_payment_testing'] = array(
    '#type' => 'checkbox',
    '#title' => t('Test mode'),
    '#default_value' => variable_get('wc_payment_testing', 0),
  );

  $form['wc_payment_settings']['wc_payment_payjunction_api_version'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#title' => t('Api version'),
    '#default_value' => variable_get('wc_payment_payjunction_api_version', 'old_quick'),
    '#options' => array('old_quick' => t('Old payjunction quick api'), 'new' => t('New payjunction api')),
  );

  // Live
  $form['wc_payment_settings']['wc_payment_url'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment url'),
    '#default_value' => variable_get('wc_payment_url', "https://www.payjunction.com/quick_link"),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_payjunction_api_version"]' => array('value' => 'old_quick'),
        ':input[name="wc_payment_testing"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_new_api_url'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment url (New API)'),
    '#default_value' => variable_get('wc_payment_new_api_url', "https://api.payjunction.com"),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_payjunction_api_version"]' => array('value' => 'new'),
        ':input[name="wc_payment_testing"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_login'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment login'),
    '#default_value' => variable_get('wc_payment_login', ""),
    '#states' => array(
      'invisible' => array(
        ':input[name="wc_payment_testing"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_password'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment password'),
    '#default_value' => variable_get('wc_payment_password', ""),
    '#states' => array(
      'invisible' => array(
        ':input[name="wc_payment_testing"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_payjunction_app_key'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Application key'),
    '#description' => t('Unique Identifier for an Application.'),
    '#default_value' => variable_get('wc_payment_payjunction_app_key', ""),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_payjunction_api_version"]' => array('value' => 'new'),
        ':input[name="wc_payment_testing"]' => array('checked' => FALSE),
      ),
    ),
  );


  // Test
  $form['wc_payment_settings']['wc_payment_test_url'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment test url'),
    '#default_value' => variable_get('wc_payment_test_url', "https://www.payjunctionlabs.com/quick_link"),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_testing"]' => array('checked' => TRUE),
        ':input[name="wc_payment_payjunction_api_version"]' => array('value' => 'old_quick'),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_test_new_api_url'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment test url (New API)'),
    '#default_value' => variable_get('wc_payment_test_new_api_url', "https://api.payjunctionlabs.com"),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_testing"]' => array('checked' => TRUE),
        ':input[name="wc_payment_payjunction_api_version"]' => array('value' => 'new'),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_test_login'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment test login'),
    '#default_value' => variable_get('wc_payment_test_login', "pj-ql-01"),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_testing"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_test_password'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Payment test password'),
    '#default_value' => variable_get('wc_payment_test_password', "pj-ql-01p"),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_testing"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['wc_payment_settings']['wc_payment_payjunction_test_app_key'] = array(
    '#type' => 'textfield',
    '#size' => 120,
    '#title' => t('Application test key'),
    '#description' => t('Unique Identifier for an Application.'),
    '#default_value' => variable_get('wc_payment_payjunction_test_app_key', "70ef7234-c45d-472b-92b8-e8f494901a84"),
    '#states' => array(
      'visible' => array(
        ':input[name="wc_payment_payjunction_api_version"]' => array('value' => 'new'),
        ':input[name="wc_payment_testing"]' => array('checked' => TRUE),
      ),
    ),
  );



  return system_settings_form($form, TRUE);
}
