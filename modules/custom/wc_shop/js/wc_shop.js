/**
 * @file
 * wc_shop.js
 * js behaviors for wc_shop module
 */

(function ($) {

    Drupal.behaviors.wcShop = {
        attach: function (context, settings) {
            var billing = $(".wc-ship-billing", context);
            var shipping = $(".wc-ship-shipping", context);
            var copy_checkbox = $(".shop-copy-information", context);
            // on click by checkbox
            copy_checkbox.change(function () {
                if ($(this).is(":checked")) {
                    billing.find("input").each(function (i, e) {
                        var name = $(e).attr("name").replace(/billing_/g, "");
                        var value = $(e).val();
                        shipping.find("input[name=shipping_" + name + "]").val(value);
                    });
                } else {
                    shipping.find("input").val("");
                }
            });

            // on change content
            billing.find("input").on("input", null, null, function () {
                if (copy_checkbox.is(":checked")) {
                    var name = $(this).attr("name").replace(/billing_/g, "");
                    var value = $(this).val();
                    shipping.find("input[name=shipping_" + name + "]").val(value);
                }
            });


            // checkout form submit

            $('form#wc-shop-checkout-form').submit(function () {
                $(".wc-shop-checkout-overlay", context).remove();
                var message = "Please wait while we are processing your transaction.<br> This may take several minutes...";
                $(".content .content-wrapper", ".page-wc-shop-checkout").append('<div class="wc-shop-checkout-overlay"><div>' + message + '</div></div>')
                return true;
            });
        },

        completedCallback: function () {
            // Do nothing. But it's here in case other modules/themes want to override it.
        }

    }
})(jQuery);