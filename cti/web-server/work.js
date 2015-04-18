/**
 * Created by Administrator on 2015/4/15.
 */
function Work(srv) {
    // guarder
    if (!(this instanceof Work)) return new Work(srv);

    var net = require('net');
    var HOST = '127.0.0.1';
    var PORT = 8123;

    // client是用来跟外呼后台通信的
    this.client = new net.Socket();
    this.client.connect(PORT, HOST, function () {
        console.log('connect to: ' + HOST + ':' + PORT);
    });
    this.client.work = this;

    // 从外呼后台收到的消息，通过bridge转给网页前端
    this.client.on('data', function (data) {
        data = data + "";
        data = data.trim();
        console.log('rec from work: ' + data);

        var result = data.match(/notify ([0-9]+) on-hook/);
        if (result) {
            var userid = parseInt(result[1]);
            this.work.bridge.emit("on-hook", {userid: userid});
            return;
        }

        var result = data.match(/notify ([0-9]+) off-hook/);
        if (result) {
            var userid = parseInt(result[1]);
            this.work.bridge.emit("off-hook", {userid: userid});
            return;
        }

        var result = data.match(/call ([0-9]+) ([0-9]+) ([A-Za-z0-9]+)/);
        if (result) {
            var userid = parseInt(result[1]);
            var phone_number = result[2];
            var case_id = result[3];
            this.work.bridge.emit("call", {
                userid: userid,
                case_id: case_id,
                phone_number: phone_number
            });
            return;
        }

        var result = data.match(/call ([0-9]+) connect/);
        if (result) {
            var userid = parseInt(result[1]);
            this.work.bridge.emit("talk", {
                userid: userid
            });
            return;
        }

        var result = data.match(/call ([0-9]+) end (\-*[0-9]+)/);
        if (result) {
            var userid = parseInt(result[1]);
            var error_code = parseInt(result[2]);
            this.work.bridge.emit("end", {
                userid: userid,
                error_code: error_code
            });
            return;
        }
    });

    this.client.on('close', function () {
        console.log('connect closed');
    });

    this.client.on('error', function (data) {
        console.log("work server is down, error: " + JSON.stringify(data) + ", please restart work server and restart web server then");
        process.exit(-1);
    });
}

Work.prototype.setBridge = function (bridge) {
    this.bridge = bridge;
    bridge.setWork(this);
};

Work.prototype.sendToWorkServer = function (data) {
    console.log("send to work: " + data);
    data = data + '\n';
    this.client.write(data);
}

Work.prototype.emit = function (message, data) {
    if (message === "ready") {
        this.sendToWorkServer("notify " + data.userid + " ready");
    } else if (message === "not-ready") {
        this.sendToWorkServer("notify " + data.userid + " not-ready");
    } else if (message === "start") {
        this.sendToWorkServer("notify job start");
    } else if (message === "stop") {
        this.sendToWorkServer("notify job stop");
    }
};

module.exports = Work;