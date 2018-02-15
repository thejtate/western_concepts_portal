(function ($) {
  
   Drupal.behaviors.wcPaymentPrint = {
        attach: function (context, settings) {
            $(".order-print-btn").click(function(){
                $(".wc-payment-order-content").printElement({
                    printMode:'popup',
                    //leaveOpen:true,
                    pageTitle: settings.wc_payment_order.title,
                    overrideElementCSS: [settings.wc_payment_order.order_css_link]
                });
            });

        },

        completedCallback: function () {
            // Do nothing. But it's here in case other modules/themes want to override it.
        }
    }


})(jQuery);

