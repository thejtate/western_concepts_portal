(function ($) {

  if (typeof Drupal != 'undefined') {
    Drupal.behaviors.wcportalTheme = {
      attach: function (context, settings) {
        init(settings);
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


  function init(settings) {
      initPopup();
    init_uniform();
    init_slides();
    init_combobox();
    init_kwicks();
    init_slider_aboutUs();
    //init_fancybox();
    initModal(settings);
    initCareersForm(settings);
    initTimeField();
  }

  function initModal(settings){
    var $wrapper = $('.b-popup'),
      $close = $wrapper.find('.close'),
      timer = ((typeof settings !== 'undefined') && (typeof settings.wcportal_popup !== 'undefined') &&
      (typeof settings.wcportal_popup.timer !== 'undefined')) ?
        parseInt(settings.wcportal_popup.timer) : 5;

    timer = timer * 1000;

    $close.on('click touch', function(e){
      e.preventDefault();

      $wrapper.removeClass('active');
    });

    setTimeout(function(){ $wrapper.removeClass('active');}, timer);
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

  function initPopup() {
    var $wrapper = $('.b-popup'),
        $close = $wrapper.find('.close');

    $close.on('click touch', function (e) {
        e.preventDefault();

        $wrapper.removeClass('active');
    })
  }

  function initCareersForm(settings) {
    if (settings.careers_webform) {
      var $form = $('#' + settings.careers_webform.form_id),
        $submit = $form.find('.form-submit');

      $submit.on('click touch', function (e) {
        if ($form.valid()) {
          $(this).parent().addClass('element-invisible');
        }
      });
    }
  }

  function initTimeField() {
    var $elements = $("input[name^='submitted[availability]']");

    $elements.inputmask(
      "hh:mm", {
        placeholder: "HH:MM",
        insertMode: false,
        showMaskOnHover: false,
        hourFormat: 12,
        onKeyDown: function(e, buffer, caretPos, opts) {
          var $input = $(this),
          key = String.fromCharCode(e.which);

          if ((caretPos < buffer.length) && (caretPos != 2) && $.isNumeric(key)) {
            buffer[caretPos] = key;

            if ((buffer[0] == '0') && (buffer[1] == '0')) {
              e.preventDefault();
              buffer[0] = '1';
              buffer[1] = '2';
              var arrj = buffer.join('');
              $input.val(arrj);
              $input.trigger("setvalue");
            }
          }
        }
      }
    );

    $elements.focusout(function() {
      var value = $(this).val();
      if (!/^\d{2}:\d{2}$/.test(value)) {
        $(this).val('');
      }
    });
  }

    //  function init_fancybox() {
//    $(".product-full").fancybox({
//      openEffect: 'none',
//      closeEffect: 'none'
//    });
//  }
})(jQuery);

