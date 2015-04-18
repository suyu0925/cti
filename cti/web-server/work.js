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
        console.log('data: ' + data);

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

        var result = data.match(/notify ([0-9]+) ring/);
        if (result) {
            var userid = parseInt(result[1]);
            this.work.bridge.emit("ring", {
                userid: userid
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

Work.prototype.emit = function (message, data) {
    if (message === "ready") {
        this.client.write("notify " + data.userid + " ready");
    } else if (message === "not-ready") {
        this.client.write("notify " + data.userid + " not-ready");
    }
};

module.exports = Work;