var net = require('net');
var events = require('events');

var HOST = "127.0.0.1";
var PORT = 4567;

var event = new events.EventEmitter();

var calls = [];
var users = [];

// 初始化座席
var maxUsers = 3;
for (var i = 0; i < maxUsers; i++) {
    users.push({
        user_id: i + 1,
        on_hook: true,
        state: "idle",
        duration: 0
    });
}

// 模拟硬件与客户反应
var maxLines = 5;
var line = maxLines;
setInterval(function () {
    for (var i = 0; i < calls.length; i++) {
        var call = calls[i];
        if (call.duration <= 0) {
            if (call.state == "start" && line > 0) {
                event.emit("write", "call " + call.call_handle + " start");
                line--;
                // 有一成概率是空号，一成概率是忙线，八成概率响铃
                var r = Math.random() * 10;
                if (r < 1) {
                    // 空号
                    event.emit("write", "call " + call.call_handle + " end 4");
                    call.state = "end";
                    line++;
                } else if (r < 2) {
                    // 忙线
                    event.emit("write", "call " + call.call_handle + " end 2");
                    call.state = "end";
                    line++;
                } else {
                    // 300毫秒后响铃
                    call.state = "ring";
                    call.duration = 300;
                }
            } else if (call.state == "ring") {
                event.emit("write", "call " + call.call_handle + " ring");
                // 有两成概率用户看到来电号码就拒接，一成概率无人接听，七成概率接起
                var r = Math.random() * 10;
                if (r < 2) {
                    // 犹豫1-10秒后拒接
                    call.state = "refuse";
                    call.duration = (Math.random() * 9 + 1) * 1000;
                } else if (r < 3) {
                    // 等待15秒后，无人接听
                    call.state = "no answer";
                    call.duration = 15 * 1000;
                } else {
                    // 犹豫1-15秒后接通
                    call.state = "connect";
                    call.duration = (Math.random() * 14 + 1) * 1000;
                }
            } else if (call.state == "no answer") {
                event.emit("write", "call " + call.call_handle + " end 3");
                call.state = "end";
                line++;
            } else if (call.state == "refuse") {
                event.emit("write", "call " + call.call_handle + " end 1");
                call.state = "end";
                line++;
            } else if (call.state == "connect") {
                // 用户接通后，2-15秒后会挂断，如果座席不接的话
                event.emit("write", "call " + call.call_handle + " connect");
                call.state = "hang up";
                call.duration = (Math.random() * 13 + 2) * 1000;
            } else if (call.state == "hang up") {
                if (call.user && call.user.state == "talking") {
                    event.emit("write", "call " + call.call_handle + " end 0");
                } else {
                    event.emit("write", "call " + call.call_handle + " end 5");
                }
                call.state = "end";
                line++;
            } else if (call.state == "talking") {
                // 接通座席，15-30秒后挂机
                call.state = "hang up";
                call.duration = (Math.random() * 15 + 15) * 1000;
            }
        } else {
            call.duration -= 100;
        }
    }

    // TODO: 从数组中去掉完成的通话
}, 100);

// 模拟座席反应
setInterval(function () {
    for (var i = 0; i < users.length; i++) {
        var user = users[i];
        if (user.duration <= 0 && user.state != "idle") {
            if (user.state == "ring") {
                // 听到响铃后，座席有一成机率不接，九城机率在1-5秒内接通
                var r = Math.random() * 10;
                if (r < 1) {
                    user.state = "no answer";
                    user.duration = 5 * 1000;
                } else {
                    // 在1-5秒内接通
                    user.state = "talking";
                    user.duration = (Math.random() * 4 + 1) * 1000;
                }
            } else if (user.state == "talking") {
                // 座席摘机
                event.emit("write", "notify " + user.user_id + " off-hook");
                // 接通完成
                event.emit("write", "join " + user.join_handle + " 0");
                // 接上话后，座席大概能讲20-30秒
                user.state = "hang up";
                user.duration = (Math.random() * 20 + 10) * 1000;
            } else if (user.state == "no answer") {
                user.state = "idle";
                event.emit("write", "join " + user.join_handle + " -1");
            } else if (user.state == "hang up") {
                // 座席挂机
                event.emit("write", "notify " + user.user_id + " on-hook");
                // 恢复待机状态
                user.state = "idle";
            }
        } else {
            user.duration -= 100;
        }
    }
}, 100);

event.on("write", function (data) {
    console.log("send: " + data);
    server.socket.write(data + "\n");
});

event.on("make call", function (data) {
    // add a call
    var call = {
        call_handle: data.call_handle,
        phone_number: data.phone_number,
        case_id: data.case_id,
        state: "start",
        duration: 0
    };
    calls.push(call);
});

event.on("join", function (data) {
    var user = null;
    // 首先查看座席状态是否为挂机
    for (var i = 0; i < users.length; i++) {
        if (users[i].user_id == data.user_id) {
            user = users[i];
            break;
        }
    }
    if (user == null) {
        // 无此座席
        event.emit("write", "join " + data.join_handle + " -4");
        return;
    }
    if (!user.on_hook) {
        // 座席已摘机
        event.emit("write", "join " + data.join_handle + " -2");
        return;
    }

    var call = null;
    // 首先查找call_handle
    for (var i = 0; i < calls.length; i++) {
        if (calls[i].call_handle == data.call_handle) {
            call = calls[i];
            break;
        }
    }
    if (call == null) {
        // 无此通话
        event.emit("write", "join " + data.join_handle + " -3");
        return;
    }
    if (call.state == "connect" || call.state == "hang up") {
        event.emit("write", "notify " + user.user_id + " ring");
        user.state = "ring";
        user.join_handle = data.join_handle;
        user.call = call;
        call.user = user;
        return;
    } else if (call.state == "end") {
        // 对方已挂机
        event.emit("write", "join " + data.join_handle + " -1");
    } else {
        // 通话状态异常
        event.emit("write", "join " + data.join_handle + " -5");
        return;
    }
});

var server = net.createServer(function (socket) {
    // 我们获得一个连接 - 该连接自动关联一个socket对象
    console.log('connected: ' + socket.remoteAddress + ':' + socket.remotePort);

    // 只允许有一个连接，外呼后台只有一个
    if (this.socket) {
        console.log("only support one single socket.");
        process.exit(-1);
    } else {
        this.socket = socket;
    }

    socket.on("data", function (data) {
        // convert buffer to string
        data = data + "";
        data = data.trim();
        console.log("rec: " + data);
        datas = data.split("\n");

        for (var i = 0; i < datas.length; i++) {
            // call call_handle phone_number case_id
            data = datas[i];
            var matched = data.match(/call ([0-9]+) ([0-9]+) ([0-9A-Za-z]+)/);
            if (matched) {
                var emitData = {
                    call_handle: matched[1],
                    phone_number: matched[2],
                    case_id: matched[3]
                };
                event.emit("make call", emitData);
                continue;
            }

            // join join_handle call_handle user_id
            matched = data.match(/join ([0-9]+) ([0-9])+ ([0-9]+)/);
            if (matched) {
                var emitData = {
                    join_handle: matched[1],
                    call_handle: matched[2],
                    user_id: matched[3]
                };
                event.emit("join", emitData);
                continue;
            }
        }
    });

    socket.on("close", function (data) {
        console.log("lose connection of work server.");
    });

    socket.on("error", function (data) {
        console.log("donjin server error: " + JSON.stringify(data));
    });
});

server.listen(PORT, HOST);

console.log("server is listening on " + HOST + ":" + PORT);