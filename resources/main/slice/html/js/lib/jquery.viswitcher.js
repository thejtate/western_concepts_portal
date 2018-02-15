(function($) {

    var plugin = 'viSwitcher';

    function ClassViSwitch(node, options) {
        options = $.extend({
            itemsSelector       : '.switch-item',
            swithDuration       : 600,
            activeItemClassName : 'active'
        }, options);

        var self       = this,
            $node      = $(node),
            $items     = $node.find(options.itemsSelector),
            curItem    = 0;

        function initialize() {
          $items.hide();
          onHashChange();
          $(window).on('hashchange.ClassViSwitch', onHashChange);
        };

        function onHashChange() {
            var hash = location.hash.replace('#', '');

            if($.isNumeric(hash)) {
              $items.eq(curItem).fadeOut(options.swithDuration/2, function() {
                $items.eq(hash).fadeIn(options.swithDuration/2);
                curItem = parseInt(hash);
              });
            }
        };


        initialize();
        return this;
    };

    $.fn[plugin] = function(options) {
      this.each(function() {
          new ClassViSwitch(this, options);
      });
    };
})(jQuery);
