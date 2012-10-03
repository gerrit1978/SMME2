<?php

//exit('Widget Blank calendar ingeladen');


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
function hc_package_types__blank_calendar__menu() {
  return array();
}


/**
 * Subhook for rendering the default form element for selecting dates
 */
function hc_package_types__blank_calendar__default_form_element($product_id) {
  $element = array();

  $element['#weight'] = '20';

  $element['#type'] = 'date_popup';
  
  // TODO: REGION-SPECIFIC!
  $element['#date_format'] = 'm.d.Y';
  
  return $element;
}


/**
 * Subhook validation function
 */
function hc_package_types__blank_calendar__validate(&$form, &$form_state) {

  // check if the chosen date is in the future
  $values = $form_state['values'];
  $chosen_date = $values['product_package_type'];
  
  $chosen_time = strtotime($chosen_date);

	$now = time();
	
	// difference between chosen_time and now must be NEGATIVE for future dates
	if (($now - $chosen_time) > 0) {
	  form_set_error('product_package_type', t('Please make sure you choose a date in the future.'));
	  return FALSE;
	}

  return TRUE;
}


/**
 * Subhook submit function
 */
function hc_package_types__blank_calendar__submit(&$form, &$form_state) {

  $values = $form_state['values'];

  $product_id = $values['product_id'];
  $product_package_type = $values['product_package_type'];    
  
  $fields = entity_metadata_wrapper('commerce_product', $product_id);
  
  $product_type = $fields->type->value();

  $package_type = $fields->field_package_type->value();
  $package_dates = $fields->field_package_date->value();

	if ($product_type == 'team_package') {

    $line_item_date = $product_package_type . " 00:00:00"; 

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
 * Helper function for rendering the form element
 *
 * e.g. with fixed dates: a select list
 * e.g. with blank calendar: a date_popup element
 */
