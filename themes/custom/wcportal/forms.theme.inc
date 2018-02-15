<?php

/**
 * @file webform theme functions
 */


/**
 * Theme careers form
 * @param $vars
 */
function _wcportal_careers_form_theme(&$vars){
  //$form = &$vars['content']['webform']['#form']['submitted'];
  $form = &$vars['submitted'];
  $imagedata = isset($vars['#node']->content['field_webform_image'][0]['#item']) ? $vars['#node']->content['field_webform_image'][0]['#item'] : NULL;

  $image = "";
  if (!empty($imagedata)) {
    $imagedata['style_name'] = "careers_form";
    $imagedata['path'] =  $imagedata['uri'];
    $image = theme("image_style", $imagedata);
  }

  //fieldsets
  _wcportal_careers_form_theme_fieldsets_with_image($form, "choose_a_restaurant", $image, 1);
  _wcportal_careers_form_theme_fieldsets($form, "personal_information", 2);
  _wcportal_careers_form_theme_fieldsets($form, "employment_sought", 3);
  _wcportal_careers_form_theme_fieldsets($form, "education", 4);
  _wcportal_careers_form_theme_fieldsets($form, "employment_history", 5);
  _wcportal_careers_form_theme_fieldsets($form, "references", 6);
  _wcportal_careers_form_theme_fieldsets($form, "availability", 7);
  _wcportal_careers_form_theme_fieldsets($form, "authorization", 8);

  // choose_a_restaurant
  $form['choose_a_restaurant']['choose_a_restaurant_radios']['#attributes']['class'][] = "radio-group";

  // personal_information
  _wcportal_careers_form_add_wrapper($form['personal_information']['last_name'], array('form-type-text','width-form-310', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['first_name'], array('form-type-text','width-form-310', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['social_security_number'], array('form-type-text','width-form-240', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['current_address'], array('form-type-text','width-form-310', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['city'], array('form-type-text','width-form-310', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['state'], array('form-type-text','width-form-110', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['zip'], array('form-type-text','width-form-110', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['home_phone_number'], array('form-type-text','width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['cell_phone_number'], array('form-type-text','width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['email_address'], array('form-type-text','width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['emergency_contact'], array('form-type-text','width-form-200', 'ff-tt-l', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['relation'], array('form-type-text','width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['phone_number'], array('form-type-text','width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['referred_by'], array('form-type-text','width-form-240', 'ff-tt-l'));


  //employment_sought
  $form['employment_sought']['type_of_employment']['#attributes']['class'][] = "ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['choose_a_position'], array('form-type-select', 'pull-right'));
  $form['employment_sought']['times_available']['#attributes']['class'][] = "ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['date_you_can_start'], array('form-type-text', 'width-form-200'));
  _wcportal_careers_form_add_wrapper($form['employment_sought']['salary_desired'], array('form-type-text', 'width-form-110'));
  $form['employment_sought']['are_you_currently_employed']['#attributes']['class'][] = "ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['are_you_currently_employed'], array('clear-left'));

  $form['employment_sought']['if_yes_may_we_contact_your_current_employer']['#attributes']['class'][] = "ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['please_initial'], array('form-type-text', 'width-form-110'));
  $form['employment_sought']['have_you_ever_applied_with_us_before']['#attributes']['class'][] = "ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['have_you_ever_applied_with_us_before'], array('clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_sought']['if_yes_where'], array('form-type-text', 'width-form-240'));
  _wcportal_careers_form_add_wrapper($form['employment_sought']['when'], array('form-type-text', 'width-form-240'));


  //education
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school_years'], array('width-form-62', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school_graduated'], array('width-form-146', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school_subjects_studied'], array('width-form-282', 'ff-tt-l'));

  _wcportal_careers_form_add_wrapper($form['education']['high_school'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['high_school_years'], array('width-form-62', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['high_school_graduated'], array('width-form-146', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['high_school_subjects_studied'], array('width-form-282', 'ff-tt-l'));

  _wcportal_careers_form_add_wrapper($form['education']['college'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['college_years'], array('width-form-62', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['college_graduated'], array('width-form-146', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['college_subjects_studied'], array('width-form-282', 'ff-tt-l'));

  _wcportal_careers_form_add_wrapper($form['education']['trade_or_businnes_school'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['trade_years'], array('width-form-62', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['trade_graduated'], array('width-form-146', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['trade_subjects_studied'], array('width-form-282', 'ff-tt-l'));


  //employment_history
  _wcportal_careers_form_theme_employment_history($form['employment_history'], 1);
  _wcportal_careers_form_theme_employment_history($form['employment_history'], 2);
  _wcportal_careers_form_theme_employment_history($form['employment_history'], 3);
  _wcportal_careers_form_theme_employment_history($form['employment_history'], 4);


  //references
  _wcportal_careers_form_theme_references($form['references'], 1);
  _wcportal_careers_form_theme_references($form['references'], 2);
  _wcportal_careers_form_theme_references($form['references'], 3);
  _wcportal_careers_form_theme_references($form['references'], 4);


  //availability
  foreach (element_children($form['availability']) as $key) {
    _wcportal_careers_form_add_wrapper($form['availability'][$key], array('form-type-text','width-form-110', 'ff-tt-l'));
  }



  //authorization
  _wcportal_careers_form_add_wrapper($form['authorization']['description'], array('fieldset-description'));
  _wcportal_careers_form_add_wrapper($form['authorization']['date'], array('width-form-194', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['authorization']['signed'], array('width-form-296'));


  //submit
  $vars['actions']['submit']['#value'] = t("Submit application");
  $vars['actions']['submit']['#prefix'] = '<div class="btn-wrapp"><div class="btn-submit">';
  $vars['actions']['submit']['#suffix'] = '</div></div>';

}


/**
 * Theme checkout form
 * @param $vars
 */
function _wcportal_checkout_form_theme(&$vars){
  $form = &$vars;
  // Billing
  $form['billing']['#attributes']['class'][] = "wc-ship-billing";
  _wcportal_careers_form_add_wrapper($form['billing']['billing_first_name'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_last_name'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_company'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_address'], array('width-form-534'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_city'], array('width-form-261'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_state'], array('width-form-158'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_zip'], array('width-form-91'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_home_phone'], array('width-form-261'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_email'], array('width-form-261'), TRUE);

  // Shipping
  $form['shipping']['same_as_billing']['#attributes']['class'][] = "checker";
  $form['shipping']['#attributes']['class'][] = "wc-ship-shipping";
  _wcportal_careers_form_add_wrapper($form['shipping']['same_as_billing'], array('ff-tt-l', 'clearfix'));
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_first_name'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_last_name'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_company'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_address'], array('width-form-534'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_city'], array('width-form-261'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_state'], array('width-form-158'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_zip'], array('width-form-91'), TRUE);

  // Payment
  _wcportal_careers_form_add_wrapper($form['payment']['card'], array('width-form-138', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['payment']['exp'], array('width-form-166', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['payment']['code'], array('width-form-100', 'not-label'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['number'], array('width-form-261', 'clear-left'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['name'], array('width-form-261'), TRUE);
}


/**
 * Add wrappers for employment_history section
 *
 * @param $form
 * @param int $number
 */
function _wcportal_careers_form_theme_employment_history(&$form, $number = 1){
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_from'], array('width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_company'], array('width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_phone'], array('width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_to'], array('width-form-200', 'ff-tt-l', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_address'], array('width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_city'], array('width-form-200', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_state'], array('width-form-110', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_zip'], array('width-form-110', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_salary'], array('width-form-200', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_position'], array('width-form-200'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_reason_for_leaving'], array('width-form-460'));
}

/**
 * Add wrappers for references section
 *
 * @param $form
 * @param int $number
 */
function _wcportal_careers_form_theme_references(&$form, $number = 1){
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_name'], array('width-form-194'));
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_address'], array('width-form-296'));
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_business'], array('width-form-192'));
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_phone'], array('width-form-158'));
  //legeng-bottom
  _wcportal_careers_form_add_wrapper($form['references_' . $number], array('legeng-bottom'));
}

/**
 * Theme dinner reservation form
 * @param $form
 */
function _wcportal_dinner_reservation_form_theme(&$form){
  //party
  _wcportal_careers_form_add_wrapper($form['party']['name'], array('width-form-230'));
  _wcportal_careers_form_add_wrapper($form['party']['time'], array('width-form-110'));
  _wcportal_careers_form_add_wrapper($form['party']['date'], array('width-form-110'));
  _wcportal_careers_form_add_wrapper($form['party']['guests'], array('width-form-110', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['party']['total'], array('width-form-80', 'bg-dark-input'));
  _wcportal_careers_form_add_wrapper($form['party']['description'], array('fieldset-description'));
  // Billing
  _wcportal_careers_form_add_wrapper($form['personal_info']['first_name'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['last_name'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['company'], array('width-form-170'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['address'], array('width-form-534'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['city'], array('width-form-261'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['state'], array('width-form-158'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['zip'], array('width-form-91'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['home_phone'], array('width-form-261'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_info']['email'], array('width-form-261'), TRUE);

  // Payment
  _wcportal_careers_form_add_wrapper($form['payment']['card'], array('width-form-138', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['payment']['exp'], array('width-form-166', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['payment']['code'], array('width-form-100', 'not-label'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['number'], array('width-form-261', 'clear-left'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['name'], array('width-form-261'), TRUE);

}


/**
 * Theme drewards card member form
 * @param $form
 */
function wcportal_custom_rewards_card_member_form_theme(&$form){
  // form
  _wcportal_careers_form_add_wrapper($form, array("form-site-custom"));

  // Personal information
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_first_name'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_last_name'], array('width-form-298'), TRUE);

  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_birthday'], array('width-form-298', 'birthday-date-select'), FALSE);

  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_company'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_address'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_city'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_state'], array('width-form-182'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_zip'], array('width-form-106'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_home_phone'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_email'], array('width-form-298'), TRUE);

  // Payment information
  _wcportal_careers_form_add_wrapper($form['payment']['card'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['number'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['name'], array('width-form-298'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['exp'], array('width-form-166', 'ff-tt-l'), FALSE);
  _wcportal_careers_form_add_wrapper($form['payment']['code'], array('width-form-106', 'not-label'), TRUE);

}


function wcportal_custom_progressive_dinner_reservation_form_theme(&$form) {
  //add wrappers

  //party
  _wcportal_custom_form_add_wrapper($form['party']['name'], array('width-form-230'));
  _wcportal_custom_form_add_wrapper($form['party']['time'], array('width-form-110'), FALSE, 'ajax-replace-time');
  _wcportal_custom_form_add_wrapper($form['party']['date'], array('width-form-110'));
  _wcportal_custom_form_add_wrapper($form['party']['guests'], array('width-form-110', 'clear-left'));
  _wcportal_custom_form_add_wrapper($form['party']['total'], array(
    'width-form-80',
    'bg-dark-input'
  ), FALSE, 'ajax-replace-total-price');
  _wcportal_custom_form_add_wrapper($form['party']['description'], array('fieldset-description'));
  // Billing
  _wcportal_custom_form_add_wrapper($form['personal_info']['first_name'], array('width-form-170'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['last_name'], array('width-form-170'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['company'], array('width-form-170'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['address'], array('width-form-534'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['city'], array('width-form-261'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['state'], array('width-form-158'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['zip'], array('width-form-91'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['home_phone'], array('width-form-261'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['email'], array('width-form-261'), TRUE);

  // Payment
  _wcportal_custom_form_add_wrapper($form['payment']['card'], array('width-form-138', 'ff-tt-l'));
  _wcportal_custom_form_add_wrapper($form['payment']['exp'], array('width-form-166', 'ff-tt-l'));
  _wcportal_custom_form_add_wrapper($form['payment']['code'], array('width-form-100', 'not-label'), TRUE);
  _wcportal_custom_form_add_wrapper($form['payment']['number'], array('width-form-261', 'clear-left'), TRUE);
  _wcportal_custom_form_add_wrapper($form['payment']['name'], array('width-form-261'), TRUE);
}







/**
 * Theme webform careers fieldsets
 * @param $form
 * @param $field
 * @param int $number
 */
function _wcportal_careers_form_theme_fieldsets(&$form, $field, $number = 1){
  $form[$field]['#attributes']['class'][] = "form-fieldset";
  $form[$field]['#prefix'] = '<div class="form-fieldset-wrapper"><span class="legend-title"><span class="number-step">' . $number . '</span><span class="legend-span">' . $form[$field]['#title'] . '</span></span>';
  $form[$field]['#suffix'] = '</div>';
  $form[$field]['#title'] = "";
}


/**
 * Theme webform careers fieldsets with image
 * @param $form
 * @param $field
 * @param int $number
 */
function _wcportal_careers_form_theme_fieldsets_with_image(&$form, $field, $image, $number = 1){
  $form[$field]['#attributes']['class'][] = "form-fieldset";
  $form[$field]['#prefix'] = '<div class="form-fieldset-wrapper"><span class="legend-title"><span class="number-step">' . $number . '</span><span class="legend-span">' . $form[$field]['#title'] . '</span></span>';
  $form[$field]['#prefix'] .= '<figure class="images"><div class="image">' . $image . '</div></figure>';
  $form[$field]['#suffix'] = '</div>';
  $form[$field]['#title'] = "";
}



/**
 * Add wrappers with classes to form items
 * @param $form
 * @param $field
 * @param array $classes
 */
function _wcportal_careers_form_add_wrapper(&$element, $classes = array(), $removeTitle = FALSE){
  if ($removeTitle) {
    $classes[] = "hide-title";
  }

  $element['#prefix'] = '<div class="' . implode(" ", $classes) . '">';
  $element['#suffix'] = '</div>';
}


/**
 * Add mask to form element
 * @param $form
 * @param $mask
 * @param string $placeholder
 */
function _wcportal_mask_form_element(&$form, $mask, $placeholder = ""){
  $form['#type'] = "masked_input";
  $form['#mask'] = $mask;
  if (!empty($placeholder)) {
    $form['#attributes']['placeholder'] = $placeholder;
  }
}