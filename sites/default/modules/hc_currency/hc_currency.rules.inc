<?php

/**
* Implementation of hook_rules_condition_info().
*/
function hc_currency_rules_condition_info() {
  return array(
    'hc_currency_euro_prices' => array(
      'group' => 'HC Currency',
      'label' => t('User surfs from Europe'),
      'module' => 'hc_currency',
    ),
    'hc_currency_dollar_prices' => array(
      'group' => 'HC Currency',
      'label' => t('User surfs from America/Asia'),
      'module' => 'hc_currency',
    ),
    
  );
}




/**
 *
 */
function hc_currency_euro_prices() {
  
  // get user location
  $user_location = $_SESSION['user_location'];
  
  // if not defined --> return false so the default currency (USD) is shown
  if (!is_array($user_location)) {
    return FALSE;
  } else {
    if (isset($user_location['continent_code']) && $user_location['continent_code'] == 'EU') {
      return TRUE;
    } else {
      return FALSE;
    }
  }
}



function hc_currency_dollar_prices() {
  return TRUE;
}