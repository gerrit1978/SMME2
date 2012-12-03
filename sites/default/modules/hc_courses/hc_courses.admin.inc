<?php


/**
 * Callback function for settings
 */
function hc_courses_settings_form($form, &$form_state) {

  $vocabularies =  taxonomy_get_vocabularies();
  
  $options = array();

	foreach ($vocabularies as $vid => $vocabulary) {
	  $options[$vid] = $vocabulary->name;
	}

  $form = array();
  
  $form['hc_courses_domain_vocabulary'] = array(
    '#title' => t('Taxonomy Vocabulary for training domains'),
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => variable_get('hc_courses_domain_vocabulary', 1),
  );
  
  return system_settings_form($form);
}