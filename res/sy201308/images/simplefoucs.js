$(function () {
    var sWidth = $("#focus_slide").width();
    var len = $("#focus_slide ul li").length;
    var index = 0;
    var picTimer;
    var btn = "<div class='btnBg'></div><div class='btn'>";
    for (var i = 0; i < len; i++) {
        btn += "<span></span>";
    }
    btn += "</div><div class='preNext pre'></div><div class='preNext next'></div>";
    $("#focus_slide").append(btn);
    $("#focus_slide .btnBg").css("opacity", 0);
    $("#focus_slide .btn span").css("opacity", 0.4).mouseenter(function () {
        index = $("#focus_slide .btn span").index(this);
        showPics(index);
    }).eq(0).trigger("mouseenter");
    $("#focus_slide .preNext").css("opacity", 0.4).hover(function () {
        $(this).stop(true, false).animate({ "opacity": "0.8" }, 300);
    }, function () {
        $(this).stop(true, false).animate({ "opacity": "0.4" }, 300);
    });
    $("#focus_slide .pre").click(function () {
        index -= 1;
        if (index == -1) { index = len - 1; }
        showPics(index);
    });
    $("#focus_slide .next").click(function () {
        index += 1;
        if (index == len) { index = 0; }
        showPics(index);
    });
    $("#focus_slide ul").css("width", sWidth * (len));
    $("#focus_slide").hover(function () {
        clearInterval(picTimer);
    }, function () {
        picTimer = setInterval(function () {
            showPics(index);
            index++;
            if (index == len) { index = 0; }
        }, 5000);
    }).trigger("mouseleave");
    function showPics(index) {
        var nowLeft = -index * sWidth;
        $("#focus_slide ul").stop(true, false).animate({ "left": nowLeft }, 300);
        $("#focus_slide .btn span").stop(true, false).animate({ "opacity": "0.4" }, 300).eq(index).stop(true, false).animate({ "opacity": "1" }, 300);
    }
});