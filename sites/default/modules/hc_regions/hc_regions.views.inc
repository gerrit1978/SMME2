<?php

function hc_regions_views_query_alter(&$view, &$query) {
  if ($view->name == 'course_packages') {
  
    $user_location = $_SESSION['user_location'];
    $continent_code = $user_location['continent_code'];
 
    // Currently disabled: the view was altered and the region is a contextual filter now

//    $query->add_where($group = '0', $field = 'field_data_field_course_region.field_course_region_value', $value = $continent_code , $operator = '=');
//    $view->query->set_group_operator('OR');
  }
}