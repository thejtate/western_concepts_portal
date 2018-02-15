(function ($) {

  if (typeof Drupal != 'undefined') {
    Drupal.behaviors.wcportalMobileTheme = {
      attach: function (context, settings) {
        init();

      },

      completedCallback: function () {
        // Do nothing. But it's here in case other modules/themes want to override it.
      }
    }
  }

  $(function () {
    if (typeof Drupal == 'undefined') {
      init();
    }
  });

  function init() {
    setTimeout(function() {
      initCombobox();
    }, 50);

    $('.btn-dd').once('btn-dd', function(){
      $(this).dropDown();
    });
    initUniform();
    initTabs();
  }

  function initTabs() {
    var $body = $('body');

    if ($body.hasClass('slickSliderQuotesActive')) return;
    $body.addClass('slickSliderQuotesActive');

    var $wrapper = $('.page-careers-mobile .form-careers');
    if (!$wrapper.length) return;

    var $nav = $wrapper.find('.tabs-nav li');
    var $content = $wrapper.find('.tabs-content .item');
    var current;

    $nav.find('a').on('click touchend', function (e) {
      e.preventDefault();

      setActive($(this).parent().index());
    });

    $content.find('.btn-next a').on('click touchend', function (e) {
      e.preventDefault();

      var $next = $(this).closest('.item').index() + 1;
      if ($next < 0 || $next > $content.length + 1) return;

      setActive($next);
    });

    $content.find('.btn-previous a').on('click touchend', function (e) {
      e.preventDefault();

      var $previous = $(this).closest('.item').index() - 1;
      if ($previous < 0 || $previous > $content.length + 1) return;

      setActive($previous);
    });


    setActive(0);

    function setActive(index) {
      current = index;

      $nav.removeClass('active').eq(current).addClass('active');
      $content.removeClass('active').eq(current).addClass('active');
    }
  }

  $.fn.dropDown = function() {
    return this.each(function() {
      var $btn = $(this),
        $wrapper = $btn.parents('.wrapper-drop-down'),
        $boxDD = $wrapper.find('.box-drop-down'),
        flag = 0;

      $btn.on('click', function(e) {
        e.preventDefault();
        if(flag == 0) {
          flag = 1;
          if($wrapper.hasClass('collapsed')) {
            $boxDD.slideDown('normal', function() {
              flag = 0;
              $wrapper.removeClass('collapsed');
            });
          } else {
            $boxDD.slideUp('normal', function() {
              flag = 0;
              $wrapper.addClass('collapsed');
            });
          }
        }
      });

      $(document).on('click', function(e) {
        if($(e.target).closest($wrapper).length) return;
        $boxDD.slideUp('normal');
        $wrapper.addClass('collapsed');
        e.stopPropagation();
      });
    });
  }

  function initCombobox() {
    $('.field-type .form-select').combobox({
      btnWidth: 24,
      height: 26,
      hoverEnabled: true,
      width: 130,
      listMaxHeight: 264,
      forceScroll: true
    });

    $('.form-select').combobox({
      btnWidth: 24,
      height: 26,
      hoverEnabled: true,
      listMaxHeight: 264,
      forceScroll: true
    });
  }

  function initUniform() {
    $('.field-billing-address .form-radio').uniform();
  }

})(jQuery);

