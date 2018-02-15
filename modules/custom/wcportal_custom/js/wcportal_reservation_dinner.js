(function ($) {
    Drupal.behaviors.dinnerReservation = {
        attach: function (context) {
            for (var id in Drupal.settings.datePopup) {
                if(typeof Drupal.settings.datePopup[id].settings.dinnerReservationDateRange != 'undefined') {
                    Drupal.settings.datePopup[id].settings.beforeShowDay = dinnerReservationDateRange;
                }
            }



            // checkout form submit
            $('form.dinner-reservation-form').submit(function () {
                $(".wc-progressive-dinner-reservation-checkout-overlay", context).remove();
                var message = "Please wait while we are processing your transaction.<br> This may take several minutes...";
                $(".content-form", ".page-progressive-dinner").append('<div class="wc-progressive-dinner-reservation-checkout-overlay bg_transparent"><div>' + message + '</div></div>')
                return true;
            });


        }
    };

    function dinnerReservationDateRange(date) {

        var day = date.getDay();
        //allow only Tuesday, Wednesday or Thursday
        if (day == 0 || day == 1 || day == 5 || day == 6) {
            return [false, ""]
        } else {
            //check if this date not already sold
            var monthDay = date.getDate();
            var year = date.getFullYear();
            var month = date.getMonth() +1;
            var day_string = year + '-' + month + '-' + monthDay;
            if(typeof Drupal.settings.wcportal_custom != 'undefined' &&
                typeof Drupal.settings.wcportal_custom.dinner_reserved_days != 'undefined' &&
                !($.inArray(day_string, Drupal.settings.wcportal_custom.dinner_reserved_days) > -1)) {
                return [true, ""]
            } else {
                return [false, ""]
            }

        }
    }

})(jQuery);