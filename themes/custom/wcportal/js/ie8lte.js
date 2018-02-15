(function ($) {
  $(function() {
    init_css3_selector();
  });

  function init_css3_selector(){
    $(".item-twitter:last-child").addClass("css3_last-child");
    $(".structs-content .template-section:nth-child(odd)").addClass("css3_nth-child-odd");
  };
})(jQuery);