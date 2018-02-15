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
  $fieldsets_array = _wcportal_careers_form_fieldset_array($form);

  //fieldsets
  _wcportal_careers_form_theme_fieldsets($form, "choose_a_restaurant", 1, $fieldsets_array);
  _wcportal_careers_form_theme_fieldsets($form, "personal_information", 2, $fieldsets_array);
  _wcportal_careers_form_theme_fieldsets($form, "employment_sought", 3, $fieldsets_array);
  _wcportal_careers_form_theme_fieldsets($form, "education", 4, $fieldsets_array);
  _wcportal_careers_form_theme_fieldsets($form, "employment_history", 5, $fieldsets_array);
  _wcportal_careers_form_theme_fieldsets($form, "references", 6, $fieldsets_array);
  _wcportal_careers_form_theme_fieldsets($form, "availability", 7, $fieldsets_array);
  _wcportal_careers_form_theme_fieldsets($form, "authorization", 8, $fieldsets_array);

  // choose_a_restaurant
  $form['choose_a_restaurant']['choose_a_restaurant_radios']['#attributes']['class'][] = "radio-group";

  // personal_information
  _wcportal_careers_form_add_wrapper($form['personal_information']['last_name'], array('form-field-text','form-field'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['first_name'], array('form-field-text','form-field'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['social_security_number'], array('form-field-text', 'form-field', 'width-form-180'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['current_address'], array('form-field-text', 'form-field', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['city'], array('form-field-text', 'form-field'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['state'], array('form-field-text','form-field', 'width-form-30'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['zip'], array('form-field-text','form-field', 'width-form-70'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['home_phone_number'], array('form-field-text','form-field', 'width-form-60-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['cell_phone_number'], array('form-field-text','form-field', 'width-form-60-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['email_address'], array('form-field-text','form-field', 'width-form-60-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['emergency_contact'], array('form-field-text','form-field', 'width-form-60-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['relation'], array('form-field-text','form-field', 'width-form-60-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['phone_number'], array('form-field-text','form-field', 'width-form-60-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['personal_information']['referred_by'], array('form-field-text','form-field', 'width-form-60-percentages', 'clear-left'));


  //employment_sought
  $form['employment_sought']['type_of_employment']['#attributes']['class'][] = "form-fieldset rtcenter";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['choose_a_position'], array('width-fieldset-136', 'form-field-select', 'form-field', 'field-type'));
  $form['employment_sought']['times_available']['#attributes']['class'][] = "rtcenter ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['date_you_can_start'], array('form-fieldset', 'form-field-text', 'width-fieldset-110'));
  _wcportal_careers_form_add_wrapper($form['employment_sought']['salary_desired'], array('form-fieldset', 'form-field-text', 'width-fieldset-110'));
  $form['employment_sought']['are_you_currently_employed']['#attributes']['class'][] = "form-item webform-component-radios";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['are_you_currently_employed'], array('clear-left'));

  $form['employment_sought']['if_yes_may_we_contact_your_current_employer']['#attributes']['class'][] = "ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['please_initial'], array('form-fieldset', 'form-field-text', 'width-fieldset-90'));
  $form['employment_sought']['have_you_ever_applied_with_us_before']['#attributes']['class'][] = "ff-tt-l";
  _wcportal_careers_form_add_wrapper($form['employment_sought']['have_you_ever_applied_with_us_before'], array('clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_sought']['if_yes_where'], array('form-fieldset', 'form-field-text', 'width-fieldset-180'));
  _wcportal_careers_form_add_wrapper($form['employment_sought']['when'], array('form-fieldset', 'form-field-text', 'width-fieldset-180'));


  //education
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school_years'], array('width-form-15-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school_graduated'], array('width-form-23-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['grammar_school_subjects_studied'], array('width-form-48-percentages', 'last'));

  _wcportal_careers_form_add_wrapper($form['education']['high_school'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['high_school_years'], array('width-form-15-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['high_school_graduated'], array('width-form-23-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['high_school_subjects_studied'], array('width-form-48-percentages', 'last'));

  _wcportal_careers_form_add_wrapper($form['education']['college'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['college_years'], array('width-form-15-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['college_graduated'], array('width-form-23-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['college_subjects_studied'], array('width-form-48-percentages', 'last'));

  _wcportal_careers_form_add_wrapper($form['education']['trade_or_businnes_school'], array('width-form-350', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['trade_years'], array('width-form-15-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['trade_graduated'], array('width-form-23-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['education']['trade_subjects_studied'], array('width-form-48-percentages', 'last'));


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
  _wcportal_careers_form_add_wrapper($form['authorization']['date'], array('rtleft', 'form-fieldset',' width-fieldset-180', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['authorization']['signed'], array('rtleft', 'form-fieldset', 'width-form-296'));


  //submit
  $vars['actions']['submit']['#value'] = t("Submit application");
  $vars['actions']['submit']['#prefix'] = '<div class="btn-wrapp rtcenter"><div class="btn-submit">';
  $vars['actions']['submit']['#suffix'] = '</div></div>';

}

/**
 * Theme drewards card member form
 * @param $form
 */
function wcportal_mobile_custom_rewards_card_member_form_theme(&$form){
  // form
  _wcportal_careers_form_add_wrapper($form, array("tabs-content", "form"));

  // Personal information
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_first_name'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_last_name'], array("form-field-text", "form-field"), TRUE);

  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_birthday'], array("form-field-text", "form-field", 'birthday-date-select'), FALSE);

  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_company'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_address'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_city'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_state'], array("form-field-text", "form-field", "field-state"), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_zip'], array("form-field-text", "form-field", "field-zip"), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_home_phone'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['personal_information']['personal_information_email'], array("form-field-text", "form-field"), TRUE);

  // Payment information
  _wcportal_careers_form_add_wrapper($form['payment']['card'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['number'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['name'], array("form-field-text", "form-field"), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['exp'], array("form-field-text", "form-field", "field-date"), FALSE);
  _wcportal_careers_form_add_wrapper($form['payment']['code'], array("form-field-text", "form-field", "field-code"), TRUE);

}


function wcportal_mobile_custom_progressive_dinner_reservation_form_theme(&$form) {
//  //add wrappers
//
//  //party
  _wcportal_custom_form_add_wrapper($form['party']['name'], array('form-field-text', 'form-field', 'field-name-party'));
  _wcportal_custom_form_add_wrapper($form['party']['time'], array('form-field-select', 'form-field', 'field-time'), FALSE, 'ajax-replace-time');
  _wcportal_custom_form_add_wrapper($form['party']['date'], array('form-field-text', 'form-field', 'field-date'));
  _wcportal_custom_form_add_wrapper($form['party']['guests'], array('form-field-select', 'form-field', 'field-guests'));
  _wcportal_custom_form_add_wrapper($form['party']['total'], array('form-field-text', 'form-field', 'field-total'), FALSE, 'ajax-replace-total-price');
  _wcportal_custom_form_add_wrapper($form['party']['description'], array('fieldset-description'));
//  // Billing
  _wcportal_custom_form_add_wrapper($form['personal_info']['first_name'], array('form-field-text', 'form-field', 'field-name'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['last_name'], array('form-field-text', 'form-field', 'field-last-name'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['company'], array('form-field-text', 'form-field'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['address'], array('form-field-text', 'form-field'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['city'], array('form-field-text', 'form-field', 'field-city'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['state'], array('form-field-text', 'form-field', 'field-state'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['zip'], array('form-field-text', 'form-field', 'field-zip'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['home_phone'], array('form-field-text', 'form-field', 'field-phone'), TRUE);
  _wcportal_custom_form_add_wrapper($form['personal_info']['email'], array('form-field-text', 'form-field', 'field-email'), TRUE);
//
//  // Payment
  _wcportal_custom_form_add_wrapper($form['payment']['card'], array('form-field-select', 'form-field', 'field-type'));
  _wcportal_custom_form_add_wrapper($form['payment']['exp'], array('form-field-text', 'form-field', 'field-expiration-date'));
  _wcportal_custom_form_add_wrapper($form['payment']['code'], array('form-field-text', 'form-field', 'field-card'), TRUE);
  _wcportal_custom_form_add_wrapper($form['payment']['number'], array('form-field-text', 'form-field', 'clear-left'), TRUE);
  _wcportal_custom_form_add_wrapper($form['payment']['name'], array('form-field-text', 'form-field', 'field-name-card'), TRUE);
  //change element position
  $form['payment']['code']['#weight'] = 49;
  $form['payment']['name']['#weight'] = 50;
  //disable direct date input
  $form['party']['date']['#attributes']['readonly'] = 'true';
}


/**
 * Theme checkout form
 * @param $vars
 */
function _wcportal_mobile_checkout_form_theme(&$vars){
  $form = &$vars;
  // Billing
  $form['billing']['#attributes']['class'][] = "wc-ship-billing";


  _wcportal_careers_form_add_wrapper($form['billing']['billing_first_name'], array('form-field-text', 'form-field', 'field-name'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_last_name'], array('form-field-text', 'form-field', 'field-last-name'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_company'], array('form-field-text', 'form-field', 'field-company'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_address'], array('form-field-text', 'form-field', 'field-address'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_city'], array('form-field-text', 'form-field', 'field-city'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_state'], array('form-field-text', 'form-field', 'field-state'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_zip'], array('form-field-text', 'form-field', 'field-zip'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_home_phone'], array('form-field-text', 'form-field', 'field-phone'), TRUE);
  _wcportal_careers_form_add_wrapper($form['billing']['billing_email'], array('form-field-text', 'form-field', 'field-email'), TRUE);

  // Shipping
  $form['shipping']['same_as_billing']['#attributes']['class'][] = "form-radio";

  $form['shipping']['#attributes']['class'][] = "wc-ship-shipping";
  _wcportal_careers_form_add_wrapper($form['shipping']['same_as_billing'], array('form-field-checkbox', 'form-field', 'field-billing-address'));
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_first_name'], array('form-field-text', 'form-field', 'field-name'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_last_name'], array('form-field-text', 'form-field', 'field-last-name'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_company'], array('form-field-text', 'form-field', 'field-company'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_address'], array('form-field-text', 'form-field', 'field-address'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_city'], array('form-field-text', 'form-field', 'field-city'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_state'], array('form-field-text', 'form-field', 'field-state'), TRUE);
  _wcportal_careers_form_add_wrapper($form['shipping']['shipping_zip'], array('form-field-text', 'form-field', 'field-zip'), TRUE);

  // Payment
  _wcportal_careers_form_add_wrapper($form['payment']['card'], array('form-field-select', 'form-field', 'field-type'));
  _wcportal_careers_form_add_wrapper($form['payment']['exp'], array('form-field-text', 'form-field', 'field-expiration-date'));

  $form['payment']['number']['#weight'] = 1;
  $form['payment']['code']['#weight'] = 2;
  $form['payment']['name']['#weight'] = 3;
  _wcportal_careers_form_add_wrapper($form['payment']['code'], array('form-field-text', 'form-field', 'field-code'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['number'], array('form-field-text', 'form-field', 'field-card'), TRUE);
  _wcportal_careers_form_add_wrapper($form['payment']['name'], array('form-field-text', 'form-field', 'field-name-card'), TRUE);

  $form['submit']['#prefix'] = '<div class="btn-wrapp"><div class="btn-submit pull-right">';
  $form['submit']['#suffix'] = '</div></div>';
}


/**
 * Creates array of fieldset title
 * @param $form
 * @return array
 */
function _wcportal_careers_form_fieldset_array($form){
  $fieldset_array = array();
  $id = 1;
  foreach ($form as $key=> $item) {
    if (!empty($item['#type']) && $item['#type'] == 'fieldset'){
      $fieldset_array['title'][$id++] = $item['#title'];
    }
  }

  return $fieldset_array;
}


/**
 * Theme webform careers fieldsets
 * @param $form
 * @param $field
 * @param int $number
 * @param string $fieldsets
 */
function _wcportal_careers_form_theme_fieldsets(&$form, $field, $number = 1, $fieldsets = ''){

  $previous_step_btn = ($number == 1) ? '' :  '<div class="btn-wrap-previous"><div class="btn-previous"><a href="#">' .  $fieldsets['title'][$number-1] . '</a></div></div>';
  $next_step_btn = ($number == 8) ? '' : '<div class="btn-wrap"><div class="btn-next"><a href="#">STEP ' . ($number+1) . '-' .  $fieldsets['title'][$number+1] . '</a></div></div>';
  $form[$field]['#prefix'] = '<div class="item">' . $previous_step_btn .'<div class="form-fieldset"><span class="legend-title"><span class="number-step">' . $number . '</span><span class="legend-span">' . $form[$field]['#title'] . '</span></span>';
  $form[$field]['#suffix'] = $next_step_btn . '</div></div>';
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


/**
 * Add wrappers for employment_history section
 *
 * @param $form
 * @param int $number
 */
function _wcportal_careers_form_theme_employment_history(&$form, $number = 1){
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_from'], array('width-form-60-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_company'], array('width-form-200', 'ff-tt-l', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_phone'], array('width-form-70-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_to'], array('width-form-50-percentages', 'ff-tt-l', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_address'], array('width-form-70-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_city'], array('width-form-70-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_state'], array('width-form-20-percentages', 'ff-tt-l', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_zip'], array('width-form-30-percentages', 'ff-tt-l'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_salary'], array('rtleft','form-fieldset','width-form-50-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_position'], array('rtleft','form-fieldset','width-form-60-percentages'));
  _wcportal_careers_form_add_wrapper($form['employment_history_' . $number]['employment_history_' . $number . '_reason_for_leaving'], array('rtleft','form-fieldset','width-form-60-percentages'));
}

/**
 * Add wrappers for references section
 *
 * @param $form
 * @param int $number
 */
function _wcportal_careers_form_theme_references(&$form, $number = 1){
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_name'], array('rtleft','form-fieldset','width-form-70-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_address'], array('rtleft','form-fieldset','width-form-90-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_business'], array('rtleft','form-fieldset','width-form-70-percentages', 'clear-left'));
  _wcportal_careers_form_add_wrapper($form['references_' . $number]['references_' . $number . '_phone'], array('rtleft','form-fieldset','width-form-60-percentages', 'clear-left'));
  //legeng-bottom
  _wcportal_careers_form_add_wrapper($form['references_' . $number], array('legeng-bottom'));
}