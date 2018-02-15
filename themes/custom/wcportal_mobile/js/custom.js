(function ($) {
    $(document).ready(function(){

        if (!Drupal.settings.form_submitted) {
            //javascript to hide navigation bar
            hideAddressBar();
            function hideAddressBar() {
                window.scrollTo(0, 1);
            }

        }

    });
})(jQuery);
