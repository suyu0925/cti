$(function () {
    var FADE_TIME = 150; // ms

    // Initialize variables
    var $messages = $('.messages'); // Messages area

    var ready = false;
    var connect = false;

    // Adds a message element to the messages and scrolls to the bottom
    // el - The element to add as a message
    // options.fade - If the element should fade-in (default = true)
    // options.prepend - If the element should prepend
    //   all other messages (default = true)
    function addMessageElement(el, options) {
        var $el = $(el);

        // Setup default options
        if (!options) {
            options = {};
        }
        if (typeof options.fade === 'undefined') {
            options.fade = true;
        }
        if (typeof options.prepend === 'undefined') {
            options.prepend = true;
        }

        // Apply options
        if (options.fade) {
            $el.hide().fadeIn(FADE_TIME);
        }
        if (options.prepend) {
            $messages.prepend($el);
        } else {
            $messages.append($el);
        }
        $messages[0].scrollTop = $messages[0].scrollHeight;
    }

    // Log a message
    function log(message, options) {
        var $el = $('<li>').addClass('log').text(message);
        addMessageElement($el, options);
    }

    var socket = io();
    socket.on('connect', function (data) {
        log("已连接至服务器");
        $('.ready').text('当前状态：准备就绪');
        $('.ready-button').text('离开');
        connect = true;
        ready = true;
        socket.emit('ready');
    });

    socket.on('disconnect', function () {
        log("已从服务器断开");
        $('.ready').text('当前状态：未连接服务器');
        $('.ready-button').text('未连接');
        ready = false;
        connect = false;
    });

    socket.on("oops", function (data) {
        log(data.message);
    });

    socket.on("userid", function (data) {
        log("分配到的userid为" + data.userid);
    });

    socket.on("on-hook", function () {
        log("您已挂机");
    });

    socket.on("off-hook", function () {
        log("您已摘机");
    });

    $('#ready-button')[0].onclick = function () {
        if (connect) {
            if (ready) {
                log('用户切换状态：离开');
                ready = false;
                $('.ready-button').text('就绪');
                $('.ready').text('当前状态：离开');
                socket.emit('not-ready');
            } else {
                log('用户切换状态：就绪');
                ready = true;
                $('.ready-button').text('离开');
                $('.ready').text('当前状态：准备就绪');
                socket.emit('ready');
            }
        } else {
            log("未连接服务器");
        }
    };
});
