<?php
/**
 * @file Wc ShushiNeko admin custom functionality
 */


function wc_events_site_setings_form($form, &$form_state) {

  $type = array('client' => t('Client'), 'host' => t('Host'));
  $node_types = node_type_get_types();
  $options_nodes = array();
  foreach ($node_types as $node_type) {
    $options_nodes[$node_type->type] = $node_type->name;
  }

  $form['wc_events'] = array(
    '#type' => 'fieldset',
    '#title' => t('Events'),
    '#weight' => 1,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );

  $form['wc_events']['wc_events_type'] = array(
    '#type' => 'radios',
    '#title' => t('Type'),
    '#default_value' => variable_get('wc_events_type', 'client'),
    '#options' => $type,
  );


  $form['wc_events']['client'] = array(
    '#type' => 'fieldset',
    '#title' => t('Client'),
    '#weight' => 1,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        'input[name="wc_events_type"]' => array('value' => 'client'),
      ),
    ),
  );

  $form['wc_events']['client']['client_wc_events_host'] = array(
    '#type' => 'textfield',
    '#title' => t('Host url'),
    '#default_value' => variable_get('client_wc_events_host', ''),
    '#size' => 120,
  );

  $form['wc_events']['client']['client_wc_events_type'] = array(
    '#type' => 'textfield',
    '#title' => t('Type of events (number)'),
    '#default_value' => variable_get('client_wc_events_type', 1),
    '#size' => 10,
  );

  $form['wc_events']['client']['client_wc_events_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of events'),
    '#default_value' => variable_get('client_wc_events_count', 2),
    '#size' => 10,
  );

  $form['wc_events']['client']['client_wc_events_trim'] = array(
    '#type' => 'textfield',
    '#title' => t('Trim event\'s description. (Number of chars)'),
    '#description' => t('0 - Not trim'),
    '#default_value' => variable_get('client_wc_events_trim', 0),
    '#size' => 10,
  );


  $form['wc_events']['host'] = array(
    '#type' => 'fieldset',
    '#title' => t('Host'),
    '#weight' => 1,
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#states' => array(
      'visible' => array(
        'input[name="wc_events_type"]' => array('value' => 'host'),
      ),
    ),
  );

  $form['wc_events']['host']['wc_events_host_node_type'] = array(
    '#type' => 'select',
    '#title' => t('Select Events content type for sync.'),
    '#default_value' => variable_get('wc_events_host_node_type', ''),
    '#options' => $options_nodes,
  );

  return system_settings_form($form);
}