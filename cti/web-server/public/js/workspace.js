$(function () {
    $('#toggle-ready').bootstrapToggle();
    $('#toggle-ready').bootstrapToggle('on');
    $('#toggle-ready').change(function () {
        console.log('Toggle: ' + $(this).prop('checked'));
    });
    //$('#username').html('<i class="icon-user icon-large"></i> haha <span class="caret"></span>');
});

$(window).unload(function () { 
	alert('获取到了页面要关闭的事件了!'); 
});

window.onbeforeunload=function (e){
	alert('获取到了页面要关闭的事件了!'); 
};