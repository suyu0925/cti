/**
 * Created by Administrator on 2015/4/15.
 */
function Work(srv) {
    // guarder
    if (!(this instanceof Work)) return new Work(srv);

    var net = require('net');
    //var HOST = '193.168.0.88';
    var HOST = 'localhost';
    var PORT = 8123;

    var MongoClient = require('mongodb').MongoClient;
    var mongoUrl = 'mongodb://kivvitek.com:27017/work';

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

        // call user_id on_hook...
        var result = data.match(/call ([0-9]+) on_hook.../);
        if (result) {
            var user_id = parseInt(result[1]);
            this.work.bridge.emit("on-hook", {user_id: user_id});
            return;
        }

        // call user_id case_id phone_number line_conn...
        var result = data.match(/call ([0-9]+) ([A-Za-z0-9\-_]+) ([\+]*[\s0-9]+) line_conn.../);
        if (result) {
            var user_id = parseInt(result[1]);
            var case_id = result[2];
            var phone_number = result[3];
            // query database to get debt info
            var bridge = this.work.bridge;
            MongoClient.connect(mongoUrl, function (err, db) {
                if (err) {
                    db.close();
                    bridge.emit("call", {
                        user_id: user_id,
                        case_id: case_id,
                        phone_number: phone_number,
                        debt: null
                    });
                } else {
                    var collection = db.collection('debt');
                    collection.find({id: case_id}).toArray(function (err, result) {
                        db.close();
                        var debt;
                        if (err || result.length == 0) {
                            debt = null;
                        } else {
                            debt = result[0];
                        }
                        bridge.emit("call", {
                            user_id: user_id,
                            case_id: case_id,
                            phone_number: phone_number,
                            debt: debt
                        });
                    });
                }
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
        this.sendToWorkServer("notify " + data.user_id + " ready");
    } else if (message === "not-ready") {
        this.sendToWorkServer("notify " + data.user_id + " not-ready");
    } else if (message === "start") {
        this.sendToWorkServer("notify 0 ready");
    } else if (message === "stop") {
        this.sendToWorkServer("notify 0 not-ready");
    } else if (message == "done") {
        this.sendToWorkServer("notify " + data.case_id + " done");
    }
};

module.exports = Work;