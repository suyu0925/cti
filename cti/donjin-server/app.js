var net = require('net');
var events = require('events');

var HOST = "127.0.0.1";
var PORT = 4567;

var event = new events.EventEmitter();

var calls = [];
var users = [];

// ��ʼ����ϯ
var maxUsers = 3;
for (var i = 0; i < maxUsers; i++) {
    users.push({
        user_id: i + 1,
        on_hook: true,
        state: "idle",
        duration: 0
    });
}

// ģ��Ӳ����ͻ���Ӧ
var maxLines = 5;
var line = maxLines;
setInterval(function () {
    for (var i = 0; i < calls.length; i++) {
        var call = calls[i];
        if (call.duration <= 0) {
            if (call.state == "start" && line > 0) {
                event.emit("write", "call " + call.call_handle + " start");
                line--;
                // ��һ�ɸ����ǿպţ�һ�ɸ�����æ�ߣ��˳ɸ�������
                var r = Math.random() * 10;
                if (r < 1) {
                    // �պ�
                    event.emit("write", "call " + call.call_handle + " end 4");
                    call.state = "end";
                    line++;
                } else if (r < 2) {
                    // æ��
                    event.emit("write", "call " + call.call_handle + " end 2");
                    call.state = "end";
                    line++;
                } else {
                    // 300���������
                    call.state = "ring";
                    call.duration = 300;
                }
            } else if (call.state == "ring") {
                event.emit("write", "call " + call.call_handle + " ring");
                // �����ɸ����û������������;ܽӣ�һ�ɸ������˽������߳ɸ��ʽ���
                var r = Math.random() * 10;
                if (r < 2) {
                    // ��ԥ1-10���ܽ�
                    call.state = "refuse";
                    call.duration = (Math.random() * 9 + 1) * 1000;
                } else if (r < 3) {
                    // �ȴ�15������˽���
                    call.state = "no answer";
                    call.duration = 15 * 1000;
                } else {
                    // ��ԥ1-15����ͨ
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
                // �û���ͨ��2-15����Ҷϣ������ϯ���ӵĻ�
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
                // ��ͨ��ϯ��15-30���һ�
                call.state = "hang up";
                call.duration = (Math.random() * 15 + 15) * 1000;
            }
        } else {
            call.duration -= 100;
        }
    }

    // TODO: ��������ȥ����ɵ�ͨ��
}, 100);

// ģ����ϯ��Ӧ
setInterval(function () {
    for (var i = 0; i < users.length; i++) {
        var user = users[i];
        if (user.duration <= 0 && user.state != "idle") {
            if (user.state == "ring") {
                // �����������ϯ��һ�ɻ��ʲ��ӣ��ųǻ�����1-5���ڽ�ͨ
                var r = Math.random() * 10;
                if (r < 1) {
                    user.state = "no answer";
                    user.duration = 5 * 1000;
                } else {
                    // ��1-5���ڽ�ͨ
                    user.state = "talking";
                    user.duration = (Math.random() * 4 + 1) * 1000;
                }
            } else if (user.state == "talking") {
                // ��ϯժ��
                event.emit("write", "notify " + user.user_id + " off-hook");
                // ��ͨ���
                event.emit("write", "join " + user.join_handle + " 0");
                // ���ϻ�����ϯ����ܽ�20-30��
                user.state = "hang up";
                user.duration = (Math.random() * 20 + 10) * 1000;
            } else if (user.state == "no answer") {
                user.state = "idle";
                event.emit("write", "join " + user.join_handle + " -1");
            } else if (user.state == "hang up") {
                // ��ϯ�һ�
                event.emit("write", "notify " + user.user_id + " on-hook");
                // �ָ�����״̬
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
    // ���Ȳ鿴��ϯ״̬�Ƿ�Ϊ�һ�
    for (var i = 0; i < users.length; i++) {
        if (users[i].user_id == data.user_id) {
            user = users[i];
            break;
        }
    }
    if (user == null) {
        // �޴���ϯ
        event.emit("write", "join " + data.join_handle + " -4");
        return;
    }
    if (!user.on_hook) {
        // ��ϯ��ժ��
        event.emit("write", "join " + data.join_handle + " -2");
        return;
    }

    var call = null;
    // ���Ȳ���call_handle
    for (var i = 0; i < calls.length; i++) {
        if (calls[i].call_handle == data.call_handle) {
            call = calls[i];
            break;
        }
    }
    if (call == null) {
        // �޴�ͨ��
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
        // �Է��ѹһ�
        event.emit("write", "join " + data.join_handle + " -1");
    } else {
        // ͨ��״̬�쳣
        event.emit("write", "join " + data.join_handle + " -5");
        return;
    }
});

var server = net.createServer(function (socket) {
    // ���ǻ��һ������ - �������Զ�����һ��socket����
    console.log('connected: ' + socket.remoteAddress + ':' + socket.remotePort);

    // ֻ������һ�����ӣ������ֻ̨��һ��
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