<?php

// $Id$
/**
* @file
* HTML for courses page per course domain
*
* Available variables:
* - $term: Taxonomy term referring to course domain
* - $description: term ("course domain") description
* - $individual packages: the individual course packages for this term (view "Courses" - block_1 display)
* - $team packages: the team course packages for this term (view "Courses" - block_2 display)
*
*/

?>

<div class="domain-description">
<?php print render($description); ?>
</div>

<div class="individual-packages packages">
<h2>Individual Packages</h2>
<?php print render($individual_packages); ?>
</div>

<div class="team-packages packages">
<h2>Team Packages</h2>
<?php print render($team_packages); ?>
</div>