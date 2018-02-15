/**
 * Created by dimateus on 7/18/14.
 */
(function ($) {

    Drupal.behaviors.wcRewardsCardMembers = {
        attach: function (context, settings) {
            var $tastingSettings = $('.group-tasting-room-settings', context);
            var restaurantId = Drupal.settings.wcportal_custom.tasting_restaurant_id;
            var $tastingCheckbox = $('form :input[name="field_event_restaurant[und][' + restaurantId + ']"]', context);

            changeTastingSettingsVisibility($tastingCheckbox);

            $tastingCheckbox.once('tasting-selected').change(function () {
                changeTastingSettingsVisibility($(this));
            });

            function changeTastingSettingsVisibility($checkobox) {

                if ($checkobox.attr("checked")) {
                    $tastingSettings.show();
                }
                else {
                    $tastingSettings.hide();
                }
            }
        }
    }
})(jQuery);