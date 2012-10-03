<?php

/*
 * @file
 *
 * Nomenclature: MODULE_NAME__WIDGET_NAME__HOOK_NAME
 *
 * e.g. hc_package_types__fixed_dates__menu

/********************************************************
 * SUBHOOKS
 *******************************************************/

/**
 * Subhook for hook_menu
 *
 * This is called from the main module's hook_menu
 * and allows other modules to register additional URLs
 * necessary for business logic
 *
 * URLs should always have a name with following structure:
 * MODULE_NAME/WIDGET_NAME/ACTION_NAME/parameters
 */
function hc_package_types__filled_in_calendar__menu() {

  $items['hc_package_types/filled_in_calendar/get_dates/%'] = array(
    'title' => '',
    'description' => '',
    'page callback' => '_hc_package_types__filled_in_calendar__get_dates',
    'page arguments' => array(3),
    'access arguments' => array('access content'),
  );
  
  return $items;
}

/**
 * Subhook for rendering the default form element for selecting dates
 */
function hc_package_types__filled_in_calendar__default_form_element($product_id) {
  $element['#type'] = 'date_popup';
  $element['#prefix'] = '<div class="filled_in_calendar">';
  $element['#suffix'] = '</div>';
  
  // TODO: REGION-SPECIFIC
  $element['#date_format'] = 'm.d.Y';
  
  return $element;
}


/**
 * Subhook validation function
 */
function hc_package_types__filled_in_calendar__validate(&$form, &$form_state) {

  $values = $form_state['values'];
  $chosen_date = $values['product_package_type'];
  
  $product_id = $values['product_id'];
  $fields = entity_metadata_wrapper('commerce_product', $product_id);

  $package_type = $fields->field_package_type->value();
  $package_dates = $fields->field_package_date->value();

  $flag = FALSE;
  foreach ($package_dates as $item) {
    if (isset($item['value'])) {
      $date_short = substr($item['value'], 0, 10);
      if ($chosen_date === $date_short) {
        $flag = TRUE;
      }
    }
  }
  if (!$flag) {
    form_set_error('product_package_type', t('Please make a valid choice'));
    return FALSE;
  } else {
    // check if the chosen date is in the future
    $chosen_time = strtotime($chosen_date);
  
  	$now = time();
  	
  	// difference between chosen_time and now must be NEGATIVE for future dates
  	if (($now - $chosen_time) > 0) {
  	  form_set_error('product_package_type', t('Please make sure you choose a date in the future.'));
  	  return FALSE;
  	}
  
    return TRUE;
  
  }

}


/**
 * Subhook submit function
 */
function hc_package_types__filled_in_calendar__submit(&$form, &$form_state) {

  $values = $form_state['values'];

  $product_id = $values['product_id'];
  $product_package_type = $values['product_package_type'];    
  
  $fields = entity_metadata_wrapper('commerce_product', $product_id);
  
  $product_type = $fields->type->value();

  $package_type = $fields->field_package_type->value();
  $package_dates = $fields->field_package_date->value();

	if ($product_type == 'team_package') {
	  if (is_array($package_dates)) {
	    foreach ($package_dates as $date) {
	      if ($product_package_type == substr($date['value'], 0, 10)) {
					$line_item_date = $date['value'];		      
	      }
	    } 
	  }	  
    // get line item
    $line_item = entity_metadata_wrapper('commerce_line_item', $form_state['line_item']);
  
  	$line_item->field_course_line_item_date->set($line_item_date);
  	$line_item->save();
  }

}



/********************************************************
 * INTERNAL HELPER FUNCTIONS
 *******************************************************/

/**
 * Page callback for subhook_menu
 *
 * This function takes a product_id as argument
 * and returns the JSONized array with available dates
 * for this "product" (course).
 * This json-output is used in the partially filled in calendar
 */ 
function _hc_package_types__filled_in_calendar__get_dates($product_id) {
  $fields = entity_metadata_wrapper('commerce_product', $product_id);
  $dates = $fields->field_package_date->value();
  
  foreach ($dates as $date) {
    $time = strtotime($date['value']);
      $timezone = $date['timezone'];
      $formatted_date = format_date($time, 'custom', 'n.j.Y', $timezone);
      $available_dates[$formatted_date] = $formatted_date;
  }
  drupal_json_output($available_dates);

}