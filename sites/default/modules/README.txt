This directory contains the custom modules.

- HC_PACKAGE_TYPES provides functionality for "bronze, silver and golden" packages, i.e. based on team size (other type of date selection depending on package type)
- HC_PURCHASABLE provides functionality for "non-purchasable products", i.e. courses in Europe & Asia (Dubai) without fixed dates where customers can suggest a date
- HC_REGIONS provides functionality for showing/hiding content based on the current region of the site visitor
- HC_HOSTING provides functionality to allow users to indicate if they want SMME to host the course, or to host it theirselves.
- HC_COUPON provides coupon-related functionality (e.g. custom rules condition for checking for region when validating a coupon).
- HC_CURRENCY provides functionality for handling multi-currencies, in addition to commerce_multicurrency. Based on $_SESSION['user_location'], it shows EURO or USD prices as provided with commerce_multicurrency module
- HC_CALENDAR provides calendar-related functionality, i.e. the calendar pages for the different regions and course types.