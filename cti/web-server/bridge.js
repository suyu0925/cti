/**
 * Created by Administrator on 2015/4/15.
 */
function Bridge(srv) {
    // guarder
    if (!(this instanceof Bridge)) return new Bridge(srv);

    this.io = require('socket.io')(srv);

    // userIds which are currently connected to the chat
    this.io.userIds = [];
    this.io.maxUsers = 2; // 只有两个用户：1和2

    this.io.on('connection', function (socket) {
        var server = this.server;
        // TODO: 一个用户连接上来，给他分配一个id
        if (server.userIds.length == server.maxUsers) {
            // 满了
            socket.emit("oops", {message: "用户已满"});
            socket.disconnect();
        } else {
            // 寻找一个空位
            for (var i = 1; i < server.maxUsers + 1; i++) {
                var existed = false;
                for (var j = 0; j < server.userIds.length; j++) {
                    if (server.userIds[j] == i) {
                        existed = true;
                        break;
                    }
                }
                if (!existed) {
                    break;
                }
            }
            // 找到一个userid
            socket.userid = i;
            server.userIds.push(socket.userid);
            socket.emit("userid", {
                userid: socket.userid
            });
        }

        // when the user disconnects.. perform this
        socket.on('disconnect', function () {
            var server = this.server;

            // 从userIds里去掉当前用户
            for (var i = 0; i < server.userIds.length; i++) {
                if (socket.userid == server.userIds[i]) {
                    server.work.emit("not-ready", {userid: server.userIds[i]});
                    server.userIds.splice(i, 1);
                    break;
                }
            }
        });

        socket.on("ready", function () {
            var server = this.server;
            server.work.emit("ready", {userid: socket.userid});
        });

        socket.on("not-ready", function () {
            var server = this.server;
            server.work.emit("not-ready", {userid: socket.userid});
        });

        // for debug
        socket.on("start", function(){
            var server = this.server;
            server.work.emit("start", {userid: socket.userid});
        });
    });
}

Bridge.prototype.setWork = function (work) {
    this.io.work = work;
};

// 从网页后端发送到网页前端
Bridge.prototype.emit = function (message, data) {
    if (!data.userid) {
        this.io.emit(message, data);
    } else {
        var sockets = this.io.sockets.sockets;
        for (var i = 0; i < sockets.length; i++) {
            if (sockets[i].userid === data.userid) {
                sockets[i].emit(message, data);
                break;
            }
        }
    }
};

module.exports = Bridge;