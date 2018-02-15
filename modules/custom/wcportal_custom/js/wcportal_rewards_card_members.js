/**
 * @file
 * wc_shop.js
 * js behaviors for wc_shop module
 */

(function ($) {

    Drupal.behaviors.wcRewardsCardMembers = {
        attach: function (context, settings) {
            // checkout form submit
            $('form#wcportal-custom-rewards-card-member-form').submit(function () {
                $(".wc-rewards-card-members-checkout-overlay", context).remove();
                var message = "Please wait while we are processing your transaction.<br> This may take several minutes...";
                $("#block-wcportal-custom-wcportal-custom-rcm .content", ".page-rewards-card-members").append('<div class="wc-rewards-card-members-checkout-overlay bg_transparent"><div>' + message + '</div></div>')
                return true;
            });
        },

        completedCallback: function () {
            // Do nothing. But it's here in case other modules/themes want to override it.
        }

    }
})(jQuery);