/**
 * Created by Administrator on 2015/4/15.
 */
function Bridge(srv) {
    // guarder
    if (!(this instanceof Bridge)) return new Bridge(srv);

    var MongoClient = require('mongodb').MongoClient;
    var mongoUrl = 'mongodb://kivvitek.com:27017/work';

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
            // 找到一个user_id
            socket.user_id = i;
            server.userIds.push(socket.user_id);
            socket.emit("user_id", {
                user_id: socket.user_id
            });
        }

        // when the user disconnects.. perform this
        socket.on('disconnect', function () {
            console.log("user " + socket.user_id + " disconnect");
            var server = this.server;

            // 从userIds里去掉当前用户
            for (var i = 0; i < server.userIds.length; i++) {
                if (socket.user_id == server.userIds[i]) {
                    server.work.emit("not-ready", {user_id: server.userIds[i]});
                    server.userIds.splice(i, 1);
                    break;
                }
            }
        });

        socket.on("ready", function () {
            var server = this.server;
            server.work.emit("ready", {user_id: socket.user_id});
        });

        socket.on("not-ready", function () {
            var server = this.server;
            server.work.emit("not-ready", {user_id: socket.user_id});
        });

        socket.on("log", function (data) {
            console.log("rec from bridge: " + "log " + JSON.stringify(data, null, 4));

            var case_done = false;
            var match = data.action.match(/([0-9]+)/);
            // action 1为承诺还款
            if (match && match[0] == "1") {
                console.log("客户承诺还款，修改数据库并通知外呼后台");
                case_done = true;
            }

            if (case_done) {
                var server = this.server;
                server.work.emit("done", {
                    user_id: socket.user_id,
                    case_id: data.case_id
                });
            }

            // 上传log到数据库
            MongoClient.connect(mongoUrl, function (err, db) {
                if (err) {
                    db.close();
                } else {
                    var log = {
                        user_id: socket.user_id,
                        text: data.text,
                        action: data.action,
                        datetime: new Date().getTime()
                    };
                    var action4 = {enable: false};
                    if (log.action.match(/4./)) {
                        action4 = {
                            enable: true,
                            user_id: log.user_id,
                            datetime: log.datetime
                        };
                    }
                    db.collection("debt").updateOne({id: data.case_id}, {
                        $push: {"logs": log},
                        $set: {action4: action4}
                    }, function (err, results) {
                        if (case_done) {
                            // update call collection
                            db.collection("call").updateOne({case_id: data.case_id}, {$set: {"flag": 1}}, function (err, result) {
                                db.close();
                            });
                        } else {
                            db.close();
                        }
                    });
                }
            });
        });

        // for debug
        socket.on("start", function () {
            var server = this.server;
            server.work.emit("start", {user_id: socket.user_id});
        });
    });
}

Bridge.prototype.setWork = function (work) {
    this.io.work = work;
};

// 从网页后端发送到网页前端
Bridge.prototype.emit = function (message, data) {
    if (!data.user_id) {
        this.io.emit(message, data);
    } else {
        var sockets = this.io.sockets.sockets;
        for (var i = 0; i < sockets.length; i++) {
            if (sockets[i].user_id === data.user_id) {
                sockets[i].emit(message, data);
                break;
            }
        }
    }
};

module.exports = Bridge;