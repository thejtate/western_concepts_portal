(function ($) {

    if (typeof Drupal != 'undefined') {
        Drupal.behaviors.wcportalCalendar = {
            attach: function (context, settings) {

                $(".restaurant-fancybox a").click(function(e){
                    var $this = $(this);
                    var id = $this.parents(".restaurant-fancybox").attr("id");
                    var date = $this.parents("td.single-day").data('date');
                    var restoran_class_array = $this.parents(".restaurant-fancybox").attr("class");
                    restoran_class_array = restoran_class_array.split('split');
                    id = id.replace("restaurant-fancybox-","");
                    var url = "/calendar-event/" + id + "/" + date +'?class=' + restoran_class_array[1];
                    calendar_popup(url, id);
                    e.preventDefault();
                    return false;
                });

            },

            completedCallback: function () {
                // Do nothing. But it's here in case other modules/themes want to override it.
            }
        }
    }

    $(function () {
        // preload from url
        if (typeof(Drupal.settings.wcportal) !=='undefined'
            && typeof(Drupal.settings.wcportal.calendar_event) !=='undefined'
            && typeof(Drupal.settings.wcportal.calendar_date) !=='undefined'){
            var nid = Drupal.settings.wcportal.calendar_event;
            var date = Drupal.settings.wcportal.calendar_date;
            var url = "/calendar-event/" + nid + '/'+date;
            calendar_popup(url, "");
            var path = location.pathname;
            list = path.split("/");
            if (typeof(list[3] !== 'undefined') && typeof(list[4] !== 'undefined') && window.history.pushState){
                window.history.pushState({}, window.document.title, "/" + list[1] + "/" + list[2]);
            }


        }
    });




    function removeHash () {
        history.pushState("", document.title, window.location.pathname
            + window.location.search);
    }


    function calendar_popup(url, id){
        $.fancybox({
            "href": url,
            "type": "ajax",
            "scrolling": "no",
            "closeBtn": false,
            beforeLoad: function () {
                if (id !== "") {
                    //window.location.hash = id;
                }
            },
            afterClose: function () {
                removeHash();
            },
            helpers : {
                overlay : {
                    css : {
                        'background' : 'rgba(00, 00, 00, 0.5)'
                    }
                }
            }
        });
    }



})(jQuery);

