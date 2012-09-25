<?php

/**
 * Rendering the system settings form
 */
function hc_packages_settings_form() {

  $form = array();
  
  $product_types = node_type_get_types();
  $options = array();
  foreach ($product_types as $key => $type) {
    $options[$key] = $type->name;
  }
  
  $form['hc_packages_team_package_node_type'] = array(
    '#title' => 'Product types',
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => array(variable_get('hc_packages_team_package_node_type', '')),
    '#attributes' => array(),
  );
  
  return system_settings_form($form);
}