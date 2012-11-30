<?php

function hc_calendar_views_query_alter(&$view, &$query) {
  if ($view->name == 'calendar') {
  
    $user_location = $_SESSION['user_location'];
    $continent_code = $user_location['continent_code'];

 
    $query->add_where($group = '1', $field = 'field_data_field_course_region.field_course_region_value', $value = $continent_code , $operator = '=');
//    $view->query->set_group_operator('OR');


  }
}