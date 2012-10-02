<?php

/**
* Implementation of hook_rules_condition_info().
*/
function hc_coupon_rules_condition_info() {
  return array(
    'hc_coupon_coupon_region_is_valid' => array(
      'group' => 'HC Coupons',
      'label' => t('Region is valid'),
      'arguments' => array(
        'commerce_line_item' => array(
          'type' => 'commerce_line_item', 
          'label' => t('line item')
        ),
        'commerce_coupon' => array(
          'type' => 'commerce_coupon',
          'label' => t('coupon'),
        ),
      ),
      'module' => 'hc_coupon',
    ),
  );
}




/**
 *
 */
function hc_coupon_coupon_region_is_valid($commerce_line_item, $commerce_coupon) {

  $fields_line_item = entity_metadata_wrapper('commerce_line_item', $commerce_line_item);
  $fields_coupon = entity_metadata_wrapper('commerce_coupon', $commerce_coupon);
  
  $coupon_region = $fields_coupon->field_course_region->value();  

  $line_item_display_path = $fields_line_item->commerce_display_path->value();
  $line_item_display_path_split = explode('/', $line_item_display_path);
  $nid_display = $line_item_display_path_split[1];
  
  $fields_node = entity_metadata_wrapper('node', $nid_display);
  
  $product_region = $fields_node->field_course_region->value();

  if (in_array($product_region[0], $coupon_region)) {
    return TRUE;
  } else {
    return FALSE;
  }

}