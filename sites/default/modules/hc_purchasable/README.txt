This module alters the "Add to cart form", in that "products" without dates (i.e. course packages with the field_can_purchase is set to value 0) cannot be added to a cart, but instead lead to another form in which users can propose dates (instead of selecting a date and purchasing the course directly for that date).

This module also hides the price fields for non-purchasable course packages by using preprocess functions.
