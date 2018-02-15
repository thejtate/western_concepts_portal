<?php

/**
 * @file
 * Settings forms
 */

/**
 * Create settings form in drupal configuration setings section for module
 */
function manager_access_links_admin_settings() {
  $node_types = node_type_get_types();
  $view_types = views_get_all_views();

  foreach ($view_types as $view_type) {
    $options_views[$view_type->name] = $view_type->human_name ? $view_type->human_name : $view_type->name;
  }

  foreach ($node_types as $node_type) {
    $options_nodes[$node_type->type] = $node_type->name;
  }

  $form['manager_links_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Add manager links to this content types'),
    '#options' => $options_nodes,
    '#default_value' => variable_get('manager_links_node_types', array('page')),
    '#desctioption' => t('A options wheel will be available on these content types to make author-specific notes.'),
  );
  $form['manager_links_view_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Add manager links to this views'),
    '#options' => $options_views,
    '#default_value' => variable_get('manager_links_view_types', array('page')),
    '#desctioption' => t('A options wheel will be available on these content types to make author-specific notes.'),
  );
  return system_settings_form($form, TRUE);
}

/**
 * manager access administration page
 */
function manager_access_admin_page_form($form, &$form_state) {
  $manager_access_settings = variable_get('manager_accesssettings', array());
  $node_base_fields = array(
    'author' => 'Authoring information',
    'revision_information' => 'Revision information',
    'options' => 'Publishing options');
  drupal_add_js('jQuery(document).ready(function () { manager_access_settings_form(); });', array('type' => 'inline'));
  $user_roles = user_roles();
  ksort($user_roles);
  $types = node_type_get_types();


  $query = db_select('field_config_instance', 't');
  $query->fields('t', array('field_name', 'bundle'));
  $query->where('entity_type = :type', array(':type' => 'node'));
  $query->orderBy('bundle');
  $result = $query->execute();
  $fields = $result->fetchAll();
  $fields_tmp = array();

  // Restructure fields array.
  foreach ($fields as $field) {
    $fields_tmp[$field->bundle][] = $field->field_name;
  }
  $fields = $fields_tmp;
  $user_roles[0] = 'all';
  // Fields.
  $form = array();
  $form['#attached']['css'][] = array(
    'data' => drupal_get_path('module', 'manager_access') . '/css/manager_access.css',
    'type' => 'file');
  $form['#attached']['js'][] = array(
    'data' => drupal_get_path('module', 'manager_access') . '/js/manager_access.js',
    'type' => 'file');

  foreach ($user_roles as $role_id => $role) {
    foreach ($types as $type) {
      if (isset($fields[$type->type])) {
        if ($role_id != 0) {
          $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type] = array(
            '#type' => 'fieldset',
            '#attributes' => array(
              'class' => array($role, 'fieldset' . $type->type)),
            '#id' => 'fieldset' . $type->type,
            '#title' => check_plain($type->name),
            '#collapsible' => TRUE,
          );
          foreach ($fields[$type->type] as $field) {
            $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type][MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $type->type . "__" . MANAGER_ACCESS_FIELD_KEY . $field] = array(
              '#type' => 'checkbox',
              '#attributes' => array('class' => array('users')),
              '#title' => check_plain($field),
              '#id' => $field,
              '#default_value' => (isset($manager_access_settings[$role_id][$type->type][$field])) ? $manager_access_settings[$role_id][$type->type][$field] : 0,
            );
          }
          // Node base.
          foreach ($node_base_fields as $key => $name) {
            $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type][MANAGER_ACCESS_ROLE_KEY . $role_id . '__' . MANAGER_ACCESS_TYPE_KEY . $type->type . "__" . MANAGER_ACCESS_NODE_BASE_KEY . $key] = array(
              '#type' => 'checkbox',
              '#title' => check_plain($name),
              '#id' => $key,
              '#default_value' => (isset($manager_access_settings[$role_id][$type->type][$key])) ? $manager_access_settings[$role_id][$type->type][$key] : 0,
            );
          }
        }
        else {
          $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type] = array(
            '#type' => 'fieldset',
            '#attributes' => array(
              'class' => array($role, 'fieldset' . $type->type)),
            '#id' => 'fieldset' . $type->type,
            '#title' => '_',
            '#collapsible' => TRUE,
          );
          foreach ($fields[$type->type] as $field) {
            $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type][MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $type->type . "__" . MANAGER_ACCESS_FIELD_KEY . $field] = array(
              '#type' => 'checkbox',
              '#attributes' => array('class' => array('allcheckboxes')),
              '#id' => $field,
              '#default_value' => (isset($manager_access_settings[$role_id][$type->type][$field])) ? $manager_access_settings[$role_id][$type->type][$field] : 0,
            );
          }
          // Node base.
          foreach ($node_base_fields as $key => $name) {
            $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type][MANAGER_ACCESS_ROLE_KEY . $role_id . '__' . MANAGER_ACCESS_TYPE_KEY . $type->type . "__" . MANAGER_ACCESS_NODE_BASE_KEY . $key] = array(
              '#type' => 'checkbox',
              '#id' => $key,
              '#default_value' => (isset($manager_access_settings[$role_id][$type->type][$key])) ? $manager_access_settings[$role_id][$type->type][$key] : 0,
            );
          }
        }
      }
    }
  }

  // Other modules.
  $module_info = system_get_info('module');
  $modules = array();
  foreach (module_implements('form_node_form_alter') as $module) {
    if (module_hook($module, 'form_node_form_alter')) {
      switch ($module) {
        case 'pathauto':
          $module_form = array('path' => array(), 'node' => NULL);
          break;

        case 'nodesinblock':
          $module_form = array('nodesinblock' => array());
          break;

        case 'forum':
          // $module_form = array('taxonomy_forums' => array());
          break;

        default:
          $module_form = array();
          break;
      }
      $form_state = array('method' => NULL, 'rebuild' => NULL, 'cache' => NULL);
      if ($module == 'pathauto') {
        $module_form = array('path' => NULL);
      }
      elseif ($module == 'forum') {
        // $module_form = array('taxonomy_forums' => null);
      }
      else {
        @call_user_func_array($module . '_' . 'form_node_form_alter', array(&$module_form, $form_state));
      }
      $MANAGER_ACCESS_MODULE_KEY = array_keys($module_form);
      $MANAGER_ACCESS_MODULE_KEY = (isset($MANAGER_ACCESS_MODULE_KEY[0])) ? $MANAGER_ACCESS_MODULE_KEY[0] : NULL;

      if (!empty($MANAGER_ACCESS_MODULE_KEY)) {
          $modules[$MANAGER_ACCESS_MODULE_KEY] = $module_info[$module]['name'];
      }
    }
  }
  asort($modules);

  foreach ($user_roles as $role_id => $role) {
    if ($role_id != 0) {
      foreach ($types as $type) {
        foreach ($modules as $module => $display_name) {
          $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type][MANAGER_ACCESS_ROLE_KEY . $role_id . '__' . MANAGER_ACCESS_TYPE_KEY . $type->type . "__" . MANAGER_ACCESS_MODULE_KEY . $module] = array(
            '#type' => 'checkbox',
            '#title' => check_plain($display_name),
            '#attributes' => array('class' => array('users')),
            '#id' => $module,
            '#default_value' => (isset($manager_access_settings[$role_id][$type->type][$module])) ? $manager_access_settings[$role_id][$type->type][$module] : 0,
          );
        }
        $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type][MANAGER_ACCESS_ROLE_KEY . $role_id . '__' . MANAGER_ACCESS_TYPE_KEY . $type->type . "__" . 'textarea'] = array(
          '#type' => 'textarea',
          '#title' => 'Custom fields:',
          '#rows' => 1,
          '#resizable' => FALSE,
          '#attributes' => array('class' => array('manager_access-customarea')),
          '#default_value' => (isset($manager_access_settings[$role_id][$type->type]['textarea'])) ? $manager_access_settings[$role_id][$type->type]['textarea'] : '',
        );
      }
    }
    else {
      foreach ($types as $type) {
        foreach ($modules as $module => $display_name) {
          $form[MANAGER_ACCESS_ROLE_KEY . $role_id][MANAGER_ACCESS_TYPE_KEY . $type->type][MANAGER_ACCESS_ROLE_KEY . $role_id . '__' . MANAGER_ACCESS_TYPE_KEY . $type->type . "__" . MANAGER_ACCESS_MODULE_KEY . $module] = array(
            '#type' => 'checkbox',
            '#attributes' => array('class' => array('allcheckboxes')),
            '#id' => $module,
            '#default_value' => (isset($manager_access_settings[$role_id][$type->type][$module])) ? $manager_access_settings[$role_id][$type->type][$module] : 0,
          );
        }
      }
    }
  }
  $form['submit'] = array('#type' => 'submit', '#value' => t('Save configuration'));
  $form['#submit'][] = 'manager_access_admin_page_submit';
  return $form;
}

/**
 * Submit admin form.
 */
function manager_access_admin_page_submit($form, &$form_state) {
  
  $manager_access_settings = array();
  foreach ($form as $key => $value) {
    if (strpos($key, MANAGER_ACCESS_ROLE_KEY) === 0) {
      $role_id = substr($key, strlen(MANAGER_ACCESS_ROLE_KEY), strlen($key) - strlen(MANAGER_ACCESS_ROLE_KEY));
      foreach ($value as $k => $v) {
        if (strpos($k, MANAGER_ACCESS_TYPE_KEY) === 0) {
          $content_type = substr($k, strlen(MANAGER_ACCESS_TYPE_KEY), strlen($k) - strlen(MANAGER_ACCESS_TYPE_KEY));
          if (is_array($v)) {
            foreach ($v as $kk => $vv) {
              if (strpos($kk, MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_FIELD_KEY) === 0) {
                $content_field = substr($kk, strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_FIELD_KEY), strlen($kk) - strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_FIELD_KEY));
                $manager_access_settings[$role_id][$content_type][$content_field] = $vv['#value'];
              }
              elseif (strpos($kk, MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_NODE_BASE_KEY) === 0) {
                $content_field = substr($kk, strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_NODE_BASE_KEY), strlen($kk) - strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_NODE_BASE_KEY));
                $manager_access_settings[$role_id][$content_type][$content_field] = $vv['#value'];
              }
              elseif (strpos($kk, MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_MODULE_KEY) === 0) {
                $module_field = substr($kk, strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_MODULE_KEY), strlen($kk) - strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . MANAGER_ACCESS_MODULE_KEY));
                $manager_access_settings[$role_id][$content_type][$module_field] = $vv['#value'];
              }
              elseif (strpos($kk, MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . 'textarea') === 0) {
                $textarea_field = substr($kk, strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__textarea"), strlen($kk) - strlen(MANAGER_ACCESS_ROLE_KEY . $role_id . "__" . MANAGER_ACCESS_TYPE_KEY . $content_type . "__" . 'textarea'));
                $manager_access_settings[$role_id][$content_type]['textarea'] = $vv['#value'];
              }
            } // Endforeach $value.
          }
        }
      }
    }
  }// Endfireach $form.
  variable_set('manager_accesssettings', $manager_access_settings);
  drupal_set_message(t('Changes have been saved.'));
}

/**
 * Implementation of theme_form
 *
 * @param array $variables
 *   theme vars
 *
 * @return form
 *   string
 */
function theme_manager_access_admin_page_form($variables) {
  $form = $variables['form'];
  $user_roles = user_roles();
  $user_roles[0] = 'all';
  ksort($user_roles);
  $header = array();
  $rows = array();
  foreach ($user_roles as $role_id => $role) {
    $header[] = $role;
    $row[] = drupal_render($form[MANAGER_ACCESS_ROLE_KEY . $role_id]);
  }
  $rows[] = $row;

  $output = theme('table', array('header' => $header, 'rows' => $rows));
  $output .= drupal_render_children($form);
  return $output;
}
