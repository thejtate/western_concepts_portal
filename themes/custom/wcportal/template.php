<?php

/**
 * @file custom site theme functions
 */


define("WCPORTAL_VIEWS_ABOUT_US_PATH", 'about-us');
define("WCPORTAL_VIEWS_CALENDAR_PATH", 'calendar');
define("CAREERS_FORM_NID", 157);

define("WCPORTAL_TASTINGROOM_URL", 'http://thetastingroomokc.com/');


/**
 * Implements hook_preprocess_html().
 */
function wcportal_preprocess_html(&$vars) {

  //attach conditional js
  $html5 = array(
    '#tag' => 'script',
    '#attributes' => array(
      'src' => drupal_get_path('theme', 'wcportal') . '/js/lib/html5.js',
    ),
    '#prefix' => '<!--[if (lt IE 9) & (!IEMobile)]>',
    '#suffix' => '</script><![endif]-->',
  );
  drupal_add_html_head($html5, 'wcportal_html5');

  $ie8lte = array(
    '#tag' => 'script',
    '#attributes' => array(
      'src' => drupal_get_path('theme', 'wcportal') . '/js/ie8lte.js',
    ),
    '#prefix' => '<!--[if (lt IE 9) & (!IEMobile)]>',
    '#suffix' => '</script><![endif]-->',
  );

  drupal_add_html_head($ie8lte, 'wcportal_ie8lte');

  $vars['so6ix_digital_pixel'] = "<!-- So6ix Digital Pixel-->
  <script type=\"text/javascript\">var ssaUrl = ('https:' == document.location.protocol ? 'https://' : 'http://') +
  'centro.pixel.ad/iap/d058d451a76921aa';new Image().src = ssaUrl;</script>
  <script>
  !function(f,b,e,v,n,t,s){if(f.fbq)return;n=f.fbq=function(){n.callMethod?
  n.callMethod.apply(n,arguments):n.queue.push(arguments)};if(!f._fbq)f._fbq=n;
  n.push=n;n.loaded=!0;n.version='2.0';n.queue=[];t=b.createElement(e);t.async=!0;
  t.src=v;s=b.getElementsByTagName(e)[0];s.parentNode.insertBefore(t,s)}(window,
  document,'script','https://connect.facebook.net/en_US/fbevents.js');
  fbq('init', '355326344839575', {
  });
  fbq('track', 'PageView');
  </script>
  <noscript><img height=\"1\" width=\"1\" style=\"display:none\"
  src=\"https://www.facebook.com/tr?id=355326344839575&ev=PageView&noscript=1\"
  /></noscript>";

  if (!empty($_SESSION['clickserv_pixel'])) {
    $vars['so6ix_digital_pixel'] .= "<script type=\"text/javascript\"> new Image().src = '//clickserv.pixel.ad/conv/eed587dcfaadd873'; </script>";
    $_SESSION['clickserv_pixel'] =  FALSE;
  }

  if ($node = menu_get_object()) {
    switch ($node->type) {
      case 'construction_page':
        $vars['classes_array'][] = 'page-con';
        break;
    }
  }
}


/**
 * Implements hook_preprocess_page().
 */
function wcportal_preprocess_page(&$vars) {
  $vars['inner_wrapper_class'] = 'inner-wrapper';
  $vars['footer_title'] = variable_get('footer_title', '');
  $vars['footer_address'] = variable_get('footer_address', '');
  if (isset($vars['node']->type)) {
    switch ($vars['node']->type) {
      case "easy_blog_post":
        $vars['title'] = "";
        break;
      case "webform":
        $vars['title'] = "";
        break;
      case "rewards_card_members":
        $vars['title'] = "";
        break;
      case 'construction_page':
        $vars['title'] = "";
        break;
    }
  }


  // shop
  if (in_array("page__shop", $vars['theme_hook_suggestions'])) {
    $vars['title'] = "";
  }
  if (in_array("page__wc_shop", $vars['theme_hook_suggestions'])) {
    $vars['title'] = "";
  }
  if (in_array("page__progressive_dinner", $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
    $vars['inner_wrapper_class'] = '';
  }
  else {
    if (in_array("page__about_us", $vars['theme_hook_suggestions'])) {
      $vars['title'] = '';
      $vars['inner_wrapper_class'] = '';
    }
  }


  // user login page - for manager
  if (in_array("page__user", $vars['theme_hook_suggestions'])) {
    drupal_set_title(t("Administrator"));
    if (user_is_logged_in()) {
      drupal_goto("<front>");
    }
  }
}

/**
 * Implements hook_preprocess_node().
 */
function wcportal_preprocess_node(&$vars) {
  switch ($vars['type']) {
    case "easy_blog_post":
      $date = isset($vars['field_easy_blog_date'][0]['value']) ? $vars['field_easy_blog_date'][0]['value'] : NULL;
      if ($date) {
        $vars['date_day'] = format_date(strtotime($date), 'custom', 'd');
        $vars['date_month'] = format_date(strtotime($date), 'custom', 'F');
      }
      else {
        $vars['date_day'] = "";
        $vars['date_month'] = "";
      }

      // social share
      $vars['content']['social_share_list'] = array(
        '#theme' => 'item_list',
        '#type' => 'ul',
        '#attributes' => array('class' => 'list-share'),
        '#items' => array(
          array(
            'data' => render($vars['content']['social_share'][0]),
            'class' => array('item-facebook')
          ),
          array(
            'data' => render($vars['content']['social_share'][1]),
            'class' => array('item-twitter')
          ),
          array(
            'data' => render($vars['content']['social_share'][2]),
            'class' => array('item-mail')
          ),
        ),
      );

      $tags_items = array();
      if (!empty($vars['content']['field_easy_blog_tags']['#items'])) {
        foreach ($vars['content']['field_easy_blog_tags']['#items'] as $item) {
          $tags_items[] = l($item['taxonomy_term']->name, "blog/" . $item['taxonomy_term']->tid, array("attributes" => array("class" => array("tag-item"))));
        }
      }


      $vars['content']['field_easy_blog_tags_list'] = array(
        '#theme' => 'item_list',
        '#type' => 'ul',
        '#attributes' => array('class' => 'tag-list'),
        '#items' => $tags_items,
      );
      break;
    case "webform":
      switch ($vars['nid']) {
        case CAREERS_FORM_NID;
          $vars['theme_hook_suggestions'][] = "node__webform__careers";
          break;
      }
      break;
    case "store_product":
      if (isset($vars['field_product_gift'][LANGUAGE_NONE][0]['value']) && !empty($vars['field_product_gift'][LANGUAGE_NONE][0]['value'])) {
        $vars['node']->store_check_balance_link = variable_get('store_check_balance_link', "");
      }

      $discount_period = (isset($vars['node']->field_store_product_discount_dat) &&
        isset($vars['node']->field_store_product_discount_dat[LANGUAGE_NONE][0])) ?
        $vars['node']->field_store_product_discount_dat[LANGUAGE_NONE][0] : '';

      $timezone = isset($discount_period['timezone']) ? $discount_period['timezone'] : 'America/Chicago';
      $timezone = new DateTimeZone($timezone);
      $start = isset($discount_period['value']) ? new DateTime($discount_period['value'], $timezone) : '';
      $end = isset($discount_period['value2']) ? new DateTime($discount_period['value2'], $timezone) : '';
      $now = new DateTime('now', $timezone);

      if ((($start > $now) || ($now > $end)) && isset($vars['content']['field_store_product_discount_des'])) {
        $vars['content']['field_store_product_discount_des']['#access'] = FALSE;
      }
      break;
    case "event":
      $calendar_item_type_classes = get_calendar_item_type_classes("popup");
      $restaurant_id = (isset($vars['field_event_restaurant'][0]['target_id'])) ? $vars['field_event_restaurant'][0]['target_id'] : NULL;
      if (isset ($_GET['class'])) {
        $vars['restaurant_popup_class'] = $_GET['class'];
        foreach ($calendar_item_type_classes as $key => $class) {
          if ($_GET['class'] == $class) {
            $vars['restaurant_popup_class_id'] = $key;
          }
        }
      }
      else {
        foreach ($calendar_item_type_classes as $key => $class) {
          if ($restaurant_id == $key) {
            $vars['restaurant_popup_class'] = $class;
          }
        }
      }

      wcportal_make_reservation_button($vars);

      break;
  }
}


/**
 * Make reservations button.
 * @param $vars
 */
function wcportal_make_reservation_button(&$vars) {
  $node = $vars['node'];
  $reservation = "";
  $price = (isset($node->field_event_price[LANGUAGE_NONE][0]['value'])) ? $node->field_event_price[LANGUAGE_NONE][0]['value'] : NULL;
  $status = (isset($node->field_event_reservation_status[LANGUAGE_NONE][0]['value'])) ? $node->field_event_reservation_status[LANGUAGE_NONE][0]['value'] : NULL;

  if (!empty($status) && !empty($price)) {
    $date = (isset($node->field_event_date_time[LANGUAGE_NONE][0]['value'])) ? $node->field_event_date_time[LANGUAGE_NONE][0]['value'] : NULL;
    if (!empty($date)) {
      $date_unix = strtotime($date);
      $today_date_full = date('Y-m-d');
      $date_full = date('Y-m-d', $date_unix);
      $date_full_calendar = date('Y-m', $date_unix);


      if ($status == 'Private Event'){
        $reservation = '<div class="private-event-wrapper">' . t('Private Event.') . '</div>';
      } elseif ($date_full < $today_date_full || ($status == 'closed')) {
        $reservation = '<div>' . t('Reservations for this event are currently closed.') . '</div>';
      }
      else {
        //http://wc-tasting.local/events/2015-05/reserve/5519/2015-05-13
        $url = WCPORTAL_TASTINGROOM_URL . 'events/' . $date_full_calendar . '/reserve/' . $node->nid . '/' . $date_full;

        $reservation = '<div class="btn-reserv-wrapper">' . l(t('Make reservations'), $url, array(
            'external' => TRUE,
            'absolute' => TRUE,
            'attributes' => array(
              'target' => '_blank',
              'class' => array(
                'btn-reservation',
                'use-ajax'
              ),
              'id' => 'reserve-btn'
            )
          )) . '</div>';
      }
    }
  }
  $vars['content']['reserve_btn'] = array(
    '#type' => 'markup',
    '#markup' => $reservation
  );
}


/**
 * Implements template_preprocess_calendar_month().
 * Events Calendar
 */
function wcportal_preprocess_calendar_month(&$vars) {
  if (!empty($vars['view']->name) && $vars['view']->name == 'calendar') {
    $vars['day_names'][0]['data'] = t('Sunday');
    $vars['day_names'][1]['data'] = t('Monday');
    $vars['day_names'][2]['data'] = t('Tuesday');
    $vars['day_names'][3]['data'] = t('Wednesday');
    $vars['day_names'][4]['data'] = t('Thursday');
    $vars['day_names'][5]['data'] = t('Friday');
    $vars['day_names'][6]['data'] = t('Saturday');
  }
}

/**
 * Implements template_preprocess_date_views_pager().
 * Events Calendar
 */
function wcportal_preprocess_date_views_pager(&$vars) {

  if (!empty($vars['plugin']->view->name) && $vars['plugin']->view->name == 'calendar') {
    $view = $vars['plugin']->view;
    $date_info = $view->date_info;
    $vars['nav_title'] = date_format_date($date_info->min_date, 'custom', 'F, Y');
  }
}


/**
 * Implements template_preprocess_views_view().
 */
function wcportal_preprocess_views_view(&$vars) {
  //redirect mobile views to desktop version
  if (isset($vars['view']->name)) {
    switch ($vars['view']->name) {
      case 'about_us_mobile':
        drupal_goto(WCPORTAL_VIEWS_ABOUT_US_PATH);
        break;
      case 'calendar':
        if (!empty($vars['display_id']) && $vars['display_id'] == 'page_4') {
          drupal_goto(WCPORTAL_VIEWS_CALENDAR_PATH);
        }
        break;
    }
  }

  if (isset($vars['view']->name) && $vars['view']->name == 'about_us') {
    $node_right = node_load(ABOUT_US_RIGHT_PRESIDENT_NID);
    $node_right_view = node_view($node_right, 'teaser');
    $node_right_render = render($node_right_view);
    $vars['footer_right_node'] = $node_right_render;
    $node_left = node_load(ABOUT_US_LEFT_PRESIDENT_NID);
    $node_left_view = node_view($node_left, 'teaser');
    $vars['footer_left_node'] = render($node_left_view);
  }


  if (isset($vars['view']->name) && $vars['view']->name == "calendar" && isset($vars['view']->current_display) && $vars['view']->current_display == "page_1") {
    // calendar page
    $nid = (isset($vars['view']->args[1])) ? $vars['view']->args[1] : NULL;
    $day = (isset($vars['view']->args[2])) ? $vars['view']->args[2] : NULL;
    $year_month = (isset($vars['view']->args[0])) ? $vars['view']->args[0] : NULL;
    if (!empty($nid) && !empty($day)) {
      $node = node_load($nid);
      if ($node) {
        $og_title = array(
          '#type' => 'html_tag',
          '#tag' => 'meta',
          '#attributes' => array(
            'property' => 'og:title',
            'content' => $node->title,
          ),
        );
        drupal_add_html_head($og_title, 'og_title');
        $desc = (isset($node->field_event_description[LANGUAGE_NONE][0]['value'])) ? $node->field_event_description[LANGUAGE_NONE][0]['value'] : "";
        $og_description = array(
          '#type' => 'html_tag',
          '#tag' => 'meta',
          '#attributes' => array(
            'property' => 'og:description',
            'content' => $desc,
          ),
        );
        drupal_add_html_head($og_description, 'og_description');

        $restaurant_nid = (isset($node->field_event_restaurant[LANGUAGE_NONE][0]['target_id'])) ? $node->field_event_restaurant[LANGUAGE_NONE][0]['target_id'] : NULL;
        $restaurant_node = node_load($restaurant_nid);
        if ($restaurant_node) {
          $img_uri = (isset($restaurant_node->field_restaurant_header_image[LANGUAGE_NONE][0]['uri'])) ? $restaurant_node->field_restaurant_header_image[LANGUAGE_NONE][0]['uri'] : "";
          $img_link = image_style_url("medium", $img_uri);
          $og_img = array(
            '#type' => 'html_tag',
            '#tag' => 'meta',
            '#attributes' => array(
              'property' => 'og:image',
              'content' => $img_link,
            ),
          );
          drupal_add_html_head($og_img, 'og_img');
        }
        drupal_add_js(array(
          "wcportal" => array(
            "calendar_event" => $nid,
            'calendar_date' => $year_month . '-' . $day
          )
        ), "setting");
      }

    }
  }
}


/**
 * Implementation of template_preprocess_calendar_item().
 * Events Calendar
 */
function wcportal_preprocess_calendar_item(&$vars) {
  if (!empty($vars['view']->name)
    && $vars['view']->name == 'calendar'
    && !empty($vars['view']->current_display)
    && $vars['view']->current_display == 'page_1'
  ) {

    $vars['theme_hook_suggestions'][] = 'calendar_item__calendar__page_1';
    $restaurant_id = (isset($vars['item']->row->field_field_event_restaurant[0]['raw']['target_id'])) ? $vars['item']->row->field_field_event_restaurant[0]['raw']['target_id'] : NULL;
    $calendar_item_type_classes = get_calendar_item_type_classes();
    $calendar_item_type_classes_popup = get_calendar_item_type_classes('popup');
    foreach ($calendar_item_type_classes as $key => $class) {
      if ($restaurant_id == $key) {
        $vars['restaurant_class'] = $class . ' split' . $calendar_item_type_classes_popup[$key] . 'split';
      }
    }

  }
}

/**
 * Implements template_preprocess_calendar_datebox().
 * Events Calendar
 */
function wcportal_preprocess_calendar_datebox(&$vars) {

  if (!empty($vars['view']->name)
    && $vars['view']->name == 'calendar'
    && !empty($vars['view']->current_display)
    && $vars['view']->current_display == 'page_1'
  ) {
    $vars['theme_hook_suggestions'][] = 'calendar_datebox__calendar__page_1';
  }
}


/**
 * Implements hook_form_alter().
 */
function wcportal_form_alter(&$form, &$form_state, $form_id) {
  switch ($form_id) {
    case "webform_client_form_" . CAREERS_FORM_NID:
      // mask careers form
      theme_load_include("inc", "wcportal", "forms.theme");
      _wcportal_careers_form_theme($form);

      _wcportal_mask_form_element($form['submitted']['personal_information']['social_security_number'], "999-99-9999", "___-__-____");
      _wcportal_mask_form_element($form['submitted']['employment_sought']['date_you_can_start'], "99-99", "MM-DD");
      for ($i = 1; $i < 5; $i++) {
        _wcportal_mask_form_element($form['submitted']['employment_history']['employment_history_' . $i]['employment_history_' . $i . '_from'], "99-9999", "MM-YYYY");
        _wcportal_mask_form_element($form['submitted']['employment_history']['employment_history_' . $i]['employment_history_' . $i . '_to'], "99-9999", "MM-YYYY");
      }
      _wcportal_mask_form_element($form['submitted']['authorization']['date'], "99-99-9999", "MM-DD-YYYY");

      drupal_add_js(
        array(
          'careers_webform' => array(
            'form_id' => $form['#id'],
          )
        ),
        'setting'
      );
      break;
    case "wc_shop_checkout_form":
      theme_load_include("inc", "wcportal", "forms.theme");
      _wcportal_checkout_form_theme($form);
      break;
    case "wcportal_custom_rewards_card_member_form":
      theme_load_include("inc", "wcportal", "forms.theme");
      wcportal_custom_rewards_card_member_form_theme($form);
      break;
    case 'wcportal_custom_progressive_dinner_reservation_form':
      theme_load_include("inc", "wcportal", "forms.theme");
      wcportal_custom_progressive_dinner_reservation_form_theme($form);
      $form['#action'] = $form['#action'] . '#reservation-form';
      break;
  }
}

/**
 * Implements phptemplate_webform_mail_headers().
 */
function wcportal_webform_mail_headers($variables) {
  $headers = array(
    'Content-Type' => 'text/html; charset=UTF-8; format=flowed; delsp=yes',
    'X-Mailer' => 'Drupal Webform (PHP/' . phpversion() . ')',
  );
  return $headers;
}


/**
 * Implements theme_form_element().
 */
function wcportal_form_element($variables) {
  // theme calendar exposed filters
  $original = theme_form_element($variables);

  $calendar_item_type_classes = get_calendar_item_type_classes();
  if (isset($variables['element']['#id'])) {
    foreach ($calendar_item_type_classes as $key => $class) {
      if ($variables['element']['#id'] == "edit-restaurant-" . $key) {
        $original = '<div class="form-item ' . $class . '">' . $original . '</div>';
      }
    }
  }

  return $original;
}

/**
 * Calendar item classes (key == node nid)
 * @return array
 */
function get_calendar_item_type_classes($type = "") {
  if ($type == "popup") {
    return array(
      1 => "popup_sushi_neko",
      2 => "popup_musashis",
      3 => "popup_will_rogers_theatre",
      4 => "popup_lobby_cafe_bar",
      5 => "popup_tasting_room",
      6 => "popup_coach_house",
    );
  }
  else {
    return array(
      1 => "restaurant-sushi_neko",
      2 => "restaurant-musashis",
      3 => "restaurant-will_rogers_theatre",
      4 => "restaurant-lobby_cafe_bar",
      5 => "restaurant-tasting_room",
      6 => "restaurant-coach_house",
    );
  }
}


//function wcportal_preprocess_field(&$variables, $hook){
//  dsm($variables['element']['#title']);
//}


//function wcportal_url_outbound_alter(&$path, &$options, $original_path) {
//  $options['absolute'] = TRUE;
//  $options['rel'] = 'group';
//}

/**
 * Loads a theme include file.
 */
function theme_load_include($type, $theme, $name = NULL) {
  if (empty($name)) {
    $name = $theme;
  }

  $file = './' . drupal_get_path('theme', $theme) . "/$name.$type";

  if (is_file($file)) {
    require_once $file;
  }
  else {
    return FALSE;
  }
}

/**
 * Implements hook_process_entity().
 */
function wcportal_process_entity(&$vars) {
  if ($vars['entity_type'] == 'bean') {
    switch ($vars['bean']->type) {
      case 'popup':
        if (!empty($vars['content']['field_popup_timer'])) {
          $timer = $vars['content']['field_popup_timer']['#items'][0]['value'];
          $vars['content']['field_popup_timer']['#access'] = FALSE;

          drupal_add_js(
            array(
              'wcportal_popup' => array(
                'timer' => $timer,
              )
            ),
            'setting'
          );
        }

        if ($vars['bean']->delta == 'gift-card-popup') {
          $vars['theme_hook_suggestions'][] = 'bean__gift_card_popup';
        }
        break;
    }
  }
}

/**
 * Implements hook_preprocess_field
 */
function wcportal_preprocess_field(&$vars, $hook) {

  $element = $vars['element'];
  if(!empty($element['#field_name'])) {
    switch($element['#field_name']) {
      case 'field_popup_link':
        if (!empty($vars['items']) && !empty($vars['items'][0]['#element']['title'])) {
          $vars['items'][0]['#element']['title'] = '<span>' . $vars['items'][0]['#element']['title'] . '</span>';
        }
        break;
    }
  }
}