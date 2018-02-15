<?php

/**
 * @file custom site theme functions
 */


define('WCPORTAL_VIEWS_CALENDAR_MOBILE_PATH', 'calendar-mobile');
define("REWARDS_FORM_NID", 5350);
define("WCPORTAL_MOBILE_CAREERS_FORM_NID", 157);



define("PROGRESSIVE_DINNER_FIRST_NID", 5178);
define("PROGRESSIVE_DINNER_SLIDE_1_NID", 5179);
define("PROGRESSIVE_DINNER_SLIDE_2_NID", 5180);
define("PROGRESSIVE_DINNER_SLIDE_3_NID", 5181);
define("PROGRESSIVE_DINNER_RESERV_NID", 5182);



/**
 * Implements hook_preprocess_html().
 */
function wcportal_mobile_preprocess_html(&$vars) {
  if (in_array("html__node__" . PROGRESSIVE_DINNER_FIRST_NID, $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = "page-progressive-dinner";
  }
  if (in_array("html__node__" . PROGRESSIVE_DINNER_SLIDE_1_NID, $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = "page-progressive-dinner";
  }
  if (in_array("html__node__" . PROGRESSIVE_DINNER_SLIDE_2_NID, $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = "page-progressive-dinner";
  }
  if (in_array("html__node__" . PROGRESSIVE_DINNER_SLIDE_3_NID, $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = "page-progressive-dinner";
  }
  if (in_array("html__node__" . PROGRESSIVE_DINNER_RESERV_NID, $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = "page-progressive-dinner";
  }
  if (in_array("html__node__" . WCPORTAL_MOBILE_CAREERS_FORM_NID, $vars['theme_hook_suggestions'])) {
    $vars['classes_array'][] = "page-careers-mobile";
  }

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
}


/**
 * Implements hook_preprocess_page().
 */
function wcportal_mobile_preprocess_page(&$vars) {

  $vars['active_title'] = menu_get_active_title();

  // Rewards card member
  if (in_array("page__node__" . REWARDS_FORM_NID, $vars['theme_hook_suggestions'])){
    $vars['title'] = "";
  }

  //Redirect from careers form
//  if(!empty($vars['node']) && $vars['node']->nid == WCPORTAL_MOBILE_CAREERS_FORM_NID) {
//    drupal_goto('<front>');
//  }

  // shop
  if (in_array("page__shop", $vars['theme_hook_suggestions'])) {
    $vars['title'] = "";
  }
  if (in_array("page__wc_shop", $vars['theme_hook_suggestions'])) {
    $vars['title'] = "";
  }
  if (in_array("page__progressive_dinner", $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
  }

  if (in_array("page__about_us_mobile", $vars['theme_hook_suggestions'])) {
      $vars['title'] = '';
  }


  if (in_array("page__node__" . PROGRESSIVE_DINNER_FIRST_NID, $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
    $vars['active_title'] = t("Progressive Dinner");
  }

  if (in_array("page__node__" . PROGRESSIVE_DINNER_SLIDE_1_NID, $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
    $vars['active_title'] = t("Progressive Dinner");
  }
  if (in_array("page__node__" . PROGRESSIVE_DINNER_SLIDE_2_NID, $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
    $vars['active_title'] = t("Progressive Dinner");
  }
  if (in_array("page__node__" . PROGRESSIVE_DINNER_SLIDE_3_NID, $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
    $vars['active_title'] = t("Progressive Dinner");
  }
  if (in_array("page__node__" . PROGRESSIVE_DINNER_RESERV_NID, $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
    $vars['active_title'] = t("Progressive Dinner");
  }
  if (in_array("page__node__" . WCPORTAL_MOBILE_CAREERS_FORM_NID, $vars['theme_hook_suggestions'])) {
    $vars['title'] = '';
  }



  // user login page - for manager
  if (in_array("page__user", $vars['theme_hook_suggestions'])) {
    drupal_set_title(t("Administrator"));
    if (user_is_logged_in()){
      drupal_goto("<front>");
    }
  }

}


function wcportal_mobile_node_view_alter(&$build) {
    if ($build['#entity_view_mode']['bundle'] == 'rewards_card_members') {
        $node = $build['#node'];
        $view_mode = 'mobile';
        $langcode = $build['#language'];

        node_build_content($node, $view_mode, $langcode);
        $build = $node->content;

        $build += array(
           '#theme' => 'node',
            '#node' => $node,
            '#view_mode' => $view_mode,
            '#language' => $langcode,
          );
     }
}


/**
 * Implements hook_preprocess_node().
 */
function wcportal_mobile_preprocess_node(&$vars) {

  switch ($vars['type']) {
    case "restaurant":
      switch ($vars['nid']) {
        case RESTAURANT_SUSHI_NEKO_NID :
          $vars['node']->restaurant_class = "site-sushi-neko";
          break;
        case RESTAURANT_MUSASHI_NID:
          $vars['node']->restaurant_class = "site-musashis";
          break;
        case RESTAURANT_WILL_ROGERS_THEATRE_NID:
          $vars['node']->restaurant_class = "site-will-rogers-theatre";
          break;
        case RESTAURANT_LOBBY_CAFE_BAR_NID:
          $vars['node']->restaurant_class = "site-lobby";
          break;
        case RESTAURANT_TASTING_ROOM_NID:
          $vars['node']->restaurant_class = "site-testing-room";
          break;
        case RESTAURANT_COACH_HOUSE_NID:
          $vars['node']->restaurant_class = "site-coach-house";
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
      $date_delta = 0;
      //if node displays in calendar view. find current calendar date
      if(isset($vars['view']->row_index)
        && $vars['view']->name == 'calendar'
        && isset($vars['view']->result[$vars['view']->row_index]->field_data_field_event_date_time_delta)) {

        $date_delta = $vars['view']->result[$vars['view']->row_index]->field_data_field_event_date_time_delta;
      }
      $date_from = (isset($vars['field_event_date_time'][$date_delta]['value'])) ? new DateTime($vars['field_event_date_time'][$date_delta]['value'], new DateTimeZone($vars['field_event_date_time'][$date_delta]['timezone_db'])) : new DateTime();
      $date_from->setTimezone(new DateTimeZone($vars['field_event_date_time'][$date_delta]['timezone']));

      $vars['event_day'] = $date_from->format("j");
      $vars['event_week'] = $date_from->format("D");
      $vars['event_time'] = $date_from->format("g:iA");
      break;
    case 'progressive_dinner_first':
      $vars['reserv_link'] = 'node/' . PROGRESSIVE_DINNER_RESERV_NID;
      $vars['next_link'] = 'node/' . PROGRESSIVE_DINNER_SLIDE_1_NID;

      $image = $vars['content']['field_pd_first_image'];
      if (isset($image['#items'][0]['uri'])) {
        $image_style = array(
          'style_name' => 'progressive_dinner_first_mobile',
          'path' => $image['#items'][0]['uri'],
          'width' => '',
          'height' => '',
          'alt' => $image['#items'][0]['alt'],
          'title' => $image['#items'][0]['title'],
        );
        $vars['rendered_image'] = theme('image_style', $image_style);
      }


      break;
    case 'progressive_dinner_slide':
      $slide_number = 1;
      $slide_class = "slide-2";
      switch ($vars['nid']) {
        case PROGRESSIVE_DINNER_SLIDE_1_NID:
          $vars['prev_link'] = 'node/' . PROGRESSIVE_DINNER_FIRST_NID;
          $vars['next_link'] = 'node/' . PROGRESSIVE_DINNER_SLIDE_2_NID;
          $slide_number = 1;
          $slide_class = "slide-2";
          break;
        case PROGRESSIVE_DINNER_SLIDE_2_NID:
          $vars['prev_link'] = 'node/' . PROGRESSIVE_DINNER_SLIDE_1_NID;
          $vars['next_link'] = 'node/' . PROGRESSIVE_DINNER_SLIDE_3_NID;
          $slide_number = 2;
          $slide_class = "slide-3";
          break;
        case PROGRESSIVE_DINNER_SLIDE_3_NID:
          $vars['prev_link'] = 'node/' . PROGRESSIVE_DINNER_SLIDE_2_NID;
          $vars['next_link'] = 'node/' . PROGRESSIVE_DINNER_RESERV_NID;
          $slide_number = 3;
          $slide_class = "slide-4";
          break;
      }
      $vars['slide_number'] = $slide_number;
      $vars['slide_class'] = $slide_class;
      $image = $vars['content']['field_pd_slide_image'];
      if (isset($image['#items'][0]['uri'])) {
        $image_style = array(
          'style_name' => 'progressive_dinner_slide_' . $slide_number . '_mobile',
          'path' => $image['#items'][0]['uri'],
          'width' => '',
          'height' => '',
          'alt' => $image['#items'][0]['alt'],
          'title' => $image['#items'][0]['title'],
        );
        $vars['rendered_image'] = theme('image_style', $image_style);
      }

      break;
    case 'progressive_dinner_your_reservat':
      $vars['prev_link'] = 'node/' . PROGRESSIVE_DINNER_SLIDE_3_NID;
      break;
    case 'webform':
      if (!empty($vars['content']['field_webform_image'])){
        hide($vars['content']['field_webform_image']);
      }
      if (!empty($vars['field_product_gift'])) {
        $vars['node']->store_check_balance_link = variable_get('store_check_balance_link', "");
      }
      break;
  }

}



/**
 * Implements template_preprocess_calendar_month().
 * Events Calendar
 */
function wcportal_mobile_preprocess_calendar_month(&$vars) {
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
function wcportal_mobile_preprocess_date_views_pager(&$vars) {

  if (!empty($vars['plugin']->view->name) && $vars['plugin']->view->name == 'calendar') {
    $view = $vars['plugin']->view;
    $date_info = $view->date_info;
    $vars['nav_title'] = date_format_date($date_info->min_date, 'custom', 'F Y');
  }
}


/**
 * Implements template_preprocess_views_view().
 */
function wcportal_mobile_preprocess_views_view(&$vars) {
  //redirect desktop views to mobile version
  if (isset($vars['view']->name)){
    switch($vars['view']->name) {
      case 'progressive_dinner':
        drupal_goto('node/' . PROGRESSIVE_DINNER_FIRST_NID);
        break;
      case 'calendar':
        if(!empty($vars['display_id']) && $vars['display_id'] == 'page_1') {
          drupal_goto(WCPORTAL_VIEWS_CALENDAR_MOBILE_PATH);
        }
        break;
      //redirect views without mobile version to homepage
      case 'easy_blog':
      case 'community':
        drupal_goto('<front>');
        break;
    }
  }

  if (isset($vars['view']->name) && $vars['view']->name == 'about_us') {
    $view = views_embed_view("about_us_mobile");
    $vars['presidents'] = $view;
  }




  if (isset($vars['view']->name) && $vars['view']->name == "calendar" && isset($vars['view']->current_display) && $vars['view']->current_display == "page_1") {
    // calendar page
    $nid = (isset($vars['view']->args[1])) ? $vars['view']->args[1] : NULL;
    if (!empty($nid)) {
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
        drupal_add_js(array("wcportal" => array("calendar_event" => $nid)), "setting");
      }

    }
  }
}


/**
 * Implementation of template_preprocess_calendar_item().
 * Events Calendar
 */
function wcportal_mobile_preprocess_calendar_item(&$vars) {
  if (!empty($vars['view']->name)
    && $vars['view']->name == 'calendar'
    && !empty($vars['view']->current_display)
    && $vars['view']->current_display == 'page_1'
  ) {

    $vars['theme_hook_suggestions'][] = 'calendar_item__calendar__page_1';
    $restaurant_id = (isset($vars['item']->row->field_field_event_restaurant[0]['raw']['target_id'])) ? $vars['item']->row->field_field_event_restaurant[0]['raw']['target_id'] : NULL;
    $calendar_item_type_classes = get_calendar_item_type_classes();
    foreach ($calendar_item_type_classes as $key => $class) {
      if ($restaurant_id == $key) {
        $vars['restaurant_class'] = $class;
      }
    }

  }
}

/**
 * Implements template_preprocess_calendar_datebox().
 * Events Calendar
 */
function wcportal_mobile_preprocess_calendar_datebox(&$vars) {

  if (!empty($vars['view']->name)
    && $vars['view']->name == 'calendar'
    && !empty($vars['view']->current_display)
    && $vars['view']->current_display == 'page_1'
  ) {
    $vars['theme_hook_suggestions'][] = 'calendar_datebox__calendar__page_1';
  }
}


///**
// * Implements hook_form_alter().
// */
function wcportal_mobile_form_alter(&$form, &$form_state, $form_id) {
  //kpr($form_id);
//  kpr($form);

  if (strpos($form_id, "wc_shop_add_to_cart_form_") === 0) {
    //form-field-select form-field
    if (isset($form['price']) && !empty($form['price'])) {
      $form['price']['#prefix'] = '<div class="form-field-select form-field">';
    }
    if (isset($form['color']) && !empty($form['color'])) {
      $form['color']['#prefix'] = '<div class="form-field-select form-field">';
    }
    if (isset($form['size']) && !empty($form['size'])) {
      $form['size']['#prefix'] = '<div class="form-field-select form-field">';
    }

  }




  switch ($form_id) {
    case "wc_shop_checkout_form":
      theme_load_include("inc", "wcportal_mobile", "forms.theme");
      _wcportal_mobile_checkout_form_theme($form);
      break;
    case "wcportal_custom_rewards_card_member_form":
      theme_load_include("inc", "wcportal_mobile", "forms.theme");
      wcportal_mobile_custom_rewards_card_member_form_theme($form);
      break;
    case 'wcportal_custom_progressive_dinner_reservation_form':
      theme_load_include("inc", "wcportal_mobile", "forms.theme");
      wcportal_mobile_custom_progressive_dinner_reservation_form_theme($form);
      break;
    case 'webform_client_form_' . WCPORTAL_MOBILE_CAREERS_FORM_NID:
      // mask careers form
      theme_load_include("inc", "wcportal_mobile", "forms.theme");
      _wcportal_careers_form_theme($form);

      _wcportal_mask_form_element($form['submitted']['personal_information']['social_security_number'], "999-99-9999", "___-__-____");
      _wcportal_mask_form_element($form['submitted']['employment_sought']['date_you_can_start'], "99-99", "MM-DD");
      for ($i = 1; $i < 5; $i++) {
        _wcportal_mask_form_element($form['submitted']['employment_history']['employment_history_' . $i]['employment_history_' . $i . '_from'], "99-9999", "MM-YYYY");
        _wcportal_mask_form_element($form['submitted']['employment_history']['employment_history_' . $i]['employment_history_' . $i . '_to'], "99-9999", "MM-YYYY");
      }
      _wcportal_mask_form_element($form['submitted']['authorization']['date'], "99-99-9999", "MM-DD-YYYY");
      if(!empty($form['captcha'])) {
        $form['submitted']['authorization']['captcha'] = $form['captcha'];
        $form['submitted']['authorization']['#weight'] = 998;
        unset($form['captcha']);
      }
      $form['submitted']['authorization']['submit'] = $form['actions']['submit'];
      $form['submitted']['authorization']['submit']['#weight'] = 999;
      hide($form['actions']['submit']);

      drupal_add_js(
        array(
          'careers_webform' => array(
            'form_id' => $form['#id'],
          )
        ),
        'setting'
      );
      break;
      break;
  }
}

/**
 * Implements phptemplate_webform_mail_headers().
 */
function wcportal_mobile_webform_mail_headers($variables) {
  $headers = array(
    'Content-Type' => 'text/html; charset=UTF-8; format=flowed; delsp=yes',
    'X-Mailer' => 'Drupal Webform (PHP/' . phpversion() . ')',
  );
  return $headers;
}


/**
 * Implements theme_form_element().
 */
function wcportal_mobile_form_element($variables) {
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
 * Impelements hook_css_alter().
 */
function wcportal_mobile_css_alter(&$css) {
  if(isset($css['sites/all/modules/contrib/calendar/css/calendar_multiday.css'])) {
    unset($css['sites/all/modules/contrib/calendar/css/calendar_multiday.css']);
  }
}

/**
 * Implements hook_process_entity().
 */
function wcportal_mobile_process_entity(&$vars) {
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
function wcportal_mobile_preprocess_field(&$vars, $hook) {

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