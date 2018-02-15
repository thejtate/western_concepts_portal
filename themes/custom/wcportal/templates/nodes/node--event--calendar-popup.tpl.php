<?php

/**
 * @file
 * Default theme implementation to display a node.
 *
 * Available variables:
 * - $title: the (sanitized) title of the node.
 * - $content: An array of node items. Use render($content) to print them all,
 *   or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $user_picture: The node author's picture from user-picture.tpl.php.
 * - $date: Formatted creation date. Preprocess functions can reformat it by
 *   calling format_date() with the desired parameters on the $created variable.
 * - $name: Themed username of node author output from theme_username().
 * - $node_url: Direct URL of the current node.
 * - $display_submitted: Whether submission information should be displayed.
 * - $submitted: Submission information created from $name and $date during
 *   template_preprocess_node().
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. The default values can be one or more of the
 *   following:
 *   - node: The current template type; for example, "theming hook".
 *   - node-[type]: The current node type. For example, if the node is a
 *     "Blog entry" it would result in "node-blog". Note that the machine
 *     name will often be in a short form of the human readable label.
 *   - node-teaser: Nodes in teaser form.
 *   - node-preview: Nodes in preview mode.
 *   The following are controlled through the node publishing options.
 *   - node-promoted: Nodes promoted to the front page.
 *   - node-sticky: Nodes ordered above other non-sticky nodes in teaser
 *     listings.
 *   - node-unpublished: Unpublished nodes visible only to administrators.
 * - $title_prefix (array): An array containing additional output populated by
 *   modules, intended to be displayed in front of the main title tag that
 *   appears in the template.
 * - $title_suffix (array): An array containing additional output populated by
 *   modules, intended to be displayed after the main title tag that appears in
 *   the template.
 *
 * Other variables:
 * - $node: Full node object. Contains data that may not be safe.
 * - $type: Node type; for example, story, page, blog, etc.
 * - $comment_count: Number of comments attached to the node.
 * - $uid: User ID of the node author.
 * - $created: Time the node was published formatted in Unix timestamp.
 * - $classes_array: Array of html class attribute values. It is flattened
 *   into a string within the variable $classes.
 * - $zebra: Outputs either "even" or "odd". Useful for zebra striping in
 *   teaser listings.
 * - $id: Position of the node. Increments each time it's output.
 *
 * Node status variables:
 * - $view_mode: View mode; for example, "full", "teaser".
 * - $teaser: Flag for the teaser state (shortcut for $view_mode == 'teaser').
 * - $page: Flag for the full page state.
 * - $promote: Flag for front page promotion state.
 * - $sticky: Flags for sticky post setting.
 * - $status: Flag for published status.
 * - $comment: State of comment settings for the node.
 * - $readmore: Flags true if the teaser content of the node cannot hold the
 *   main body content.
 * - $is_front: Flags true when presented in the front page.
 * - $logged_in: Flags true when the current user is a logged-in member.
 * - $is_admin: Flags true when the current user is an administrator.
 *
 * Field variables: for each field instance attached to the node a corresponding
 * variable is defined; for example, $node->body becomes $body. When needing to
 * access a field's raw values, developers/themers are strongly encouraged to
 * use these variables. Otherwise they will have to explicitly specify the
 * desired field language; for example, $node->body['en'], thus overriding any
 * language negotiation rule that was previously applied.
 *
 * @see template_preprocess()
 * @see template_preprocess_node()
 * @see template_process()
 *
 * @ingroup themeable
 */
?>

<?php
$date_from = (isset($content['field_event_date_time']['#items'][0]['value'])) ? new DateTime($content['field_event_date_time']['#items'][0]['value'], new DateTimeZone($content['field_event_date_time']['#items'][0]['timezone_db'])) : new DateTime();
$date_from->setTimezone(new DateTimeZone($content['field_event_date_time']['#items'][0]['timezone']));
$date_to = (isset($content['field_event_date_time']['#items'][0]['value2'])) ? new DateTime($content['field_event_date_time']['#items'][0]['value2'], new DateTimeZone($content['field_event_date_time']['#items'][0]['timezone_db'])) : new DateTime();;
$date_to->setTimezone(new DateTimeZone($content['field_event_date_time']['#items'][0]['timezone']));

$time_from = $date_from->getTimestamp();
$time_to = $date_to->getTimestamp();

if ($time_to != $time_from) {
  $ftime_to = $date_to->format("g:iA");
}

//Get date from pupup link not from node field. Use only time from node fields.
$year = $node->display_popup_date->format("Y");
$month_digits = $node->display_popup_date->format("m");
$month = $node->display_popup_date->format("F");
$day = $node->display_popup_date->format("d");

$ftime = $date_from->format("g:iA");

$class = (isset($variables['restaurant_popup_class'])) ? $variables['restaurant_popup_class'] : "";

$url = url("calendar/" . $year . "-" . $month_digits . "/" . $nid .  "/" . $day  , array("absolute" => TRUE));
$facebook = "http://facebook.com/sharer.php?u=" . urlencode($url);
$twitter = "http://twitter.com/intent/tweet?url=" . urlencode($url);
$mailto = "mailto:?subject=I wanted you to see this event&body=" . $url;

if (isset ($field_event_restaurant) && isset ($restaurant_popup_class_id) && !empty ($restaurant_popup_class_id)) {
  foreach ($field_event_restaurant as $key => $value) {
    if ($restaurant_popup_class_id == $value['target_id']) {
      $event_restaurant = isset ($content['field_event_restaurant'][$key]['#markup']) ? $content['field_event_restaurant'][$key]['#markup'] : render($content['field_event_restaurant']);
    }
  }
} else {
  $event_restaurant = render($content['field_event_restaurant']);
}

?>
<div class="popup_calendar <?php print $class; ?>">
  <div class="date-popup">
    <span class="day"><?php print $month; ?></span>
    <span class="month"><?php print $day; ?></span>
  </div>
  <div class="content-popup">
    <div class="title-header-popup">
      <h3><?php print $event_restaurant; ?></h3>
    </div>
    <div class="text-popup-wrapper">
      <div class="title-text-popup">
        <h3><?php print $title; ?></h3>
      </div>
      <div class="time-popup">
          <span class="time">
            <?php print $ftime; ?>
            <?php if (isset($ftime_to)) : ?>
              – <?php print $ftime_to; ?>
            <?php endif; ?>
          </span>
      </div>
      <div class="text-popup">
        <?php print render($content['field_event_description']); ?>
        <?php print render($content['field_event_email']); ?>
        <?php if ($restaurant_popup_class_id == 5) : ?>
          <?php print isset($content['field_event_type']) ? render($content['field_event_type']) : ''; ?>
        <?php endif; ?>

        <?php print render($content['reserve_btn']); ?>
      </div>

      <div class="share-wrapper share-popup">
        <div class="item-list">
          <ul class="list-share">
            <li
              class="item-facebook"><?php print l(t("facebook"), $facebook, array('attributes' => array('target' => '_blank'))); ?></li>
            <li
              class="item-twitter"><?php print l(t("twitter"), $twitter, array('attributes' => array('target' => '_blank'))); ?></li>
            <li class="item-mail"><?php print l(t("mail"), $mailto); ?></li>
          </ul>
        </div>
      </div>
      <div class="btn-wrapper">
        <a class="btn-close calendar-popup-close"
           href="javascript:parent.jQuery.fancybox.close();"><?php print t("CLOSE") ?></a>
      </div>
    </div>
  </div>
</div>
