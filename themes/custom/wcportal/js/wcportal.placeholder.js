
/**
 * @file
 * wcportal.placeholder.js
 * js behaviors for custom placeholders
 */

(function ($) {

    Drupal.behaviors.wcportalPlaceholder = {
        attach: function (context, settings) {
            $('input, textarea').placeholder();
        },

        completedCallback: function () {
            // Do nothing. But it's here in case other modules/themes want to override it.
        }

    }
})(jQuery);