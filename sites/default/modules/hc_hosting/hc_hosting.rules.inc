<?php

/**
* Implementation of hook_rules_condition_info().
*/
function hc_hosting_rules_condition_info() {
  return array(
    'hc_hosting_fee' => array(
      'group' => 'HC Hosting',
      'label' => t('Product has hosting fee'),
      'arguments' => array(
        'commerce_line_item' => array(
          'type' => 'commerce_line_item', 
          'label' => t('line item')
        ),
      ),
      'module' => 'hc_hosting',
    ),
  );
}




/**
 *
 */
function hc_hosting_fee($commerce_line_item) {

	$commerce_product_field = field_get_items('commerce_line_item', $commerce_line_item, 'commerce_product');

	if (isset($commerce_product_field[0]['product_id'])) {
	  $product_wrapper = entity_metadata_wrapper('commerce_product', $commerce_product_field[0]['product_id']);
	  $hosting_fee = $product_wrapper->field_hosting_fee->value();
		
		if ($hosting_fee) {
		  return TRUE;
		}
	}

	return FALSE;
}