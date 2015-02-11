$(function () {
    $('#toggle-ready').bootstrapToggle();
    $('#toggle-ready').change(function () {
        console.log('Toggle: ' + $(this).prop('checked'));
    });
    //$('#username').html('<i class="icon-user icon-large"></i> haha <span class="caret"></span>');

	var socket = io.connect('http://localhost:3000');
	socket.on('connect', function(){
		console.log('connect');
	    $('#toggle-ready').bootstrapToggle('on');
	});
	socket.on('event', function(data){
		console.log('event: ' + data);
	});
	socket.on('disconnect', function(){
		console.log('disconnect');
	    $('#toggle-ready').bootstrapToggle('off');
	});
});

$(window).unload(function () { 
	alert('获取到了页面要关闭的事件了!'); 
});

window.onbeforeunload=function (e){
	alert('获取到了页面要关闭的事件了!'); 
};