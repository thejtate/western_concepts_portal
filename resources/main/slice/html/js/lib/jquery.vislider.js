(function($) {

    var plugin = 'viSlider';

    function ClassViSlider(node, options) {
        options = $.extend({
            animationSpeed    : 600,
            pagination        : true,
            containerSelector : '.slides-container',
            pagerClass        : 'slides-pagination',
            offset            : 0.2,
            minSlideWidth     : 820,
            maxSlideWidth     : 9999
        }, options);

        var self       = this,
            $node      = $(node),
            $container = $node.find(options.containerSelector),
            $pager     = $('<div class="' + options.pagerClass + '"/>'),
            $slides    = $container.find('.slide'),
            nodeWidth  = null,
            slideWidth = null,
            numOfSlides= $slides.length,
            curSlide   = null,
            prefix     = getPrefix();

        function initialize() {
            $node.css({
                position: 'relative',
                overflow: 'hidden'
            });
            $container.css({
                position: 'absolute',
                height: '100%'
            });
            $container.css(prefix + 'transition', 'left ' + options.animationSpeed + 'ms ease-out');
            $slides.css({
                position: 'absolute'
            });

            for(var i = 0; i < numOfSlides; i++) {
              $slides.eq(i).data('id', i);
              $pager.append('<a href="#' + i + '">' + i + '</a>');
            }

            if(options.pagination === true) {
                $node.append($pager);
                $pager = $pager.find('a');
            } else {
                $pager = null;
            }

            onResize();
            onHashChange();

            $(window).on('hashchange.ClassViSlider', onHashChange);
            $(window).on('resize.ClassViSlider',     onResize);
            $slides.find('.image').on('click.ClassViSlider', onSlideClick);
            $(document).on('keyup', function(e) {
              if(e.keyCode == 39) {
                goToSlide(curSlide + 1);
              } else if(e.keyCode == 37) {
                goToSlide(curSlide - 1);
              }
            });
        };

        function onResize() {
            nodeWidth = $node.outerWidth();
            slideWidth = nodeWidth - (nodeWidth * (options.offset * 2));
            slideWidth = slideWidth >= options.minSlideWidth ? slideWidth : options.minSlideWidth;
            slideWidth = slideWidth <= options.maxSlideWidth ? slideWidth : options.maxSlideWidth;

            $container.width(slideWidth * numOfSlides);

            $slides.each(function(i, el) {
              el.style.width = slideWidth + 'px';
              el.style.left  = slideWidth * i + 'px';
            });

            curSlide && goToSlide(curSlide);
        };

        function goToSlide(index) {
            index = index < 0 ? 0 : index;
            index = index > (numOfSlides - 1) ? (numOfSlides - 1) : index;

            var left = (-index * slideWidth) + (nodeWidth * options.offset);


            if(Modernizr.csstransitions == true) {
              $container.css('left', left);
            } else {
              $container.animate({
                left: left
              }, {
                duration: options.animationSpeed
              });
            }



            $slides.removeClass('current').eq(index).addClass('current');
            if($pager) {
              $pager.removeClass('current').eq(index).addClass('current');
            }

            curSlide = parseInt(index);
            location.hash = curSlide;
        };

        function onHashChange() {
            var hash = location.hash.replace('#', '');
            //hash = $.isNumeric(hash) ? parseInt(hash) : 0;

            if($.isNumeric(hash)) {
              hash = parseInt(hash);
            } else {
              hash = curSlide ? curSlide : 0;
            }

            goToSlide(hash);
        };

        function onSlideClick(e) {
          var id = $(this).parents('.slide').data('id');
          goToSlide(id);
        };

        initialize();
        return this;
    };

    $.fn[plugin] = function(options) {
      this.each(function() {
          new ClassViSlider(this, options);
      });
    };

    function getPrefix() {
      var prefix = '';
      if($.browser.webkit) {
        prefix = '-webkit-'
      } else if($.browser.mozilla) {
        prefix = '-moz-'
      } else if($.browser.msie) {
        prefix = '-ms-'
      } else if($.browser.presto) {
        prefix = '-o-'
      }

      return prefix;
    }
})(jQuery);
