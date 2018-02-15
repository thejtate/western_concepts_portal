window.$ = jQuery;
function manager_access_settings_form(){
  // fix fieldset "all" height
  $("fieldset.anonymous").each(function(i, e){
    var h = $(e).height() - 13;
    $("fieldset.all:eq(" + i + ")").find(".fieldset-wrapper").css({'height': h + 'px'});
  });

  // Collapse all volcano fiedsets
  $(".collapsible .fieldset-title").click(function() {
    var clickId = $(this).parent().parent().parent().attr('id');
    if ($("fieldset#"+clickId).hasClass('collapsed')) {
      $("fieldset#"+clickId).each(function() {
        $("fieldset#"+clickId).removeClass('collapsed');
      });
    }
    else {
      $("fieldset#"+clickId).each(function() {
        $("fieldset#"+clickId).addClass('collapsed');
      });
    }
  });
  // Checks all volcano chekboxes per line
  $('.all .form-checkbox').change(function() {
    var parentclickId =  $(this).parent().parent().parent().attr('id');
    var checkboxId =  $(this).attr('id');
    $("fieldset#"+parentclickId+" .form-checkbox#"+checkboxId).attr('checked', $('.all .form-checkbox#'+checkboxId).is(':checked'));
  });
  $('.users').live('change', function() {
    var checkboxId =  $(this).attr('id');
    $('.users').length == $('.users:checked').length ? $('.allcheckboxes#' + checkboxId).attr('checked', 'checked').next(): $('.allcheckboxes#' + checkboxId).attr('checked', '').next();
  });

}
