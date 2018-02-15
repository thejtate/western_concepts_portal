(function ($) {

  if (typeof Drupal != 'undefined') {
    Drupal.behaviors.wcportalTheme = {
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
    init_uniform();
    init_slides();
    init_combobox();
    init_kwicks();
    init_slider_aboutUs();
    //init_fancybox();
    initModal()
  }

  function initModal(){
    var $wrapper = $('.b-popup'),
      $close = $wrapper.find('.close');

    $close.on('click touch', function(e){
      e.preventDefault();

      $wrapper.removeClass('active');
    });

    setTimeout(function(){ $wrapper.removeClass('active');}, 5000);
  }

  function init_uniform() {
    $("input:checkbox, input:radio").uniform();
  };

  function init_slides() {
    $('.slides-progressive').superslides({
      inherit_width_from: '.outer-slides',
      inherit_height_from: '.outer-slides',
      hashchange: true
    });
  };

  function init_slider_aboutUs() {
    /*$('.outer-slides-about-us').superslides({
      inherit_width_from: '.outer-slides-about-us',
      hashchange: true,
      inherit_height_from: '.outer-slides-about-us'
    });*/

    $('.outer-slides-about-us').viSlider({});
    //$('.outer-descriptions-about-us').viSwitcher({});
  }

  function init_combobox() {
    $('.form-select').combobox({
      btnWidth: 30,
      hoverEnabled: true,
      listMaxHeight: 264,
      forceScroll: true
    });
  };
  function init_kwicks() {
    $('.kwicks').kwicks({
      maxSize: '60%',
      spacing: 0,
      behavior: 'menu'
    });
  };

//  function init_fancybox() {
//    $(".product-full").fancybox({
//      openEffect: 'none',
//      closeEffect: 'none'
//    });
//  }
})(jQuery);

