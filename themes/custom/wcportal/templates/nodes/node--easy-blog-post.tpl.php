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
<div id="node-<?php print $node->nid; ?>" class="<?php print $classes; ?> "<?php print $attributes; ?>>
  <?php
  $avatar = "";
  $name = (isset($node->name)) ? $node->name : "";

  if (isset($node->picture->uri) && !empty($name)) {
    $image = array(
      'path' => $node->picture->uri,
      'title' => $node->name,
      'alt' => $node->name,
    );
    $avatar = theme("image", $image);
  }
  ?>
  <div class="content-item">
    <div class="title-content">
      <?php print render($title_prefix); ?>
      <h3>
        <?php if ($teaser): ?>
          <a href="<?php print $node_url; ?>"><?php print $title; ?></a>
        <?php else: ?>
          <?php print $title; ?>
        <?php endif; ?>
      </h3>
      <?php print render($title_suffix); ?>

      <div class="user-image">
        <?php print $avatar; ?>
      </div>

      <?php if ($display_submitted): ?>
        <div class="title-bottom">
          <div class="item-left">
            <span class="text"><?php print t('SUBMITTED BY'); ?></span>
          </div>
          <div class="item-name">
            <h4><?php print $name; ?></h4>
          </div>
        </div>
      <?php endif; ?>
    </div>
    <div class="date-post">
      <span class="month"><?php print $date_month; ?></span>
      <span class="day"><?php print $date_day; ?></span>
    </div>
    <div class="text-content">
      <?php if (!empty($content['field_easy_blog_teaser_image'])) : ?>
      <figure class="images image-right">
        <div class="image">
          <?php print render($content['field_easy_blog_teaser_image']); ?>
        </div>
        <figcaption
          class="images-text"><?php print (isset($content['field_easy_blog_teaser_image'][0]['#item']['title'])) ? $content['field_easy_blog_teaser_image'][0]['#item']['title'] : ""; ?></figcaption>
      </figure>
      <?php endif; ?>
      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['comments']);
      hide($content['links']);
      hide($content['social_share']);
      hide($content['social_share_list']);
      hide($content['field_easy_blog_date']);
      hide($content['field_easy_blog_teaser_image']);
      hide($content['field_easy_blog_tags']);
      hide($content['field_easy_blog_tags_list']);
      print render($content);
      ?>
    </div>
    <div class="footer-post">
      <div class="share-wrapper">
        <span class="title-share"><?php print t('SHARE'); ?></span>
        <?php print render($content['social_share_list']); ?>
      </div>
      <div class="tags-wrapper">
        <span class="tag-title"><?php print t('TAGS'); ?></span>
        <?php print render($content['field_easy_blog_tags_list']); ?>
      </div>
    </div>
  </div>
</div>