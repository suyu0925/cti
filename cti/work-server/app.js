var net = require('net');
var events = require("events");
var MongoClient = require('mongodb').MongoClient;
var event = new events.EventEmitter();

// Host
var HOST = '127.0.0.1';
var PORT = 8123;
// Connection URL
var mongoUrl = 'mongodb://localhost:27017/account';
// call state
var CALL_STATE_CALLING = 1;
var CALL_STATE_WAITING = 2;
var CALL_STATE_COMMUNICATING = 3;
// work state
var running = false;

var jobs = [];
var job_point = 0;
var users = [];
var calls = [];

var call_handle = 0;
var join_handle = 0;

// test database, if database is not connected, exit process
MongoClient.connect(mongoUrl, function (err, db) {
    if (err) {
        console.log("database is not connected, please start mongodb first");
        process.exit(1);
    } else {
        db.close();
    }
});

event.on("make call", function () {
    // 获取可用的席座数
    var n = 0;
    for (var i = 0; i < users.length; i++) {
        if (users[i].ready) {
            n++;
        }
    }

    // 获取正在拨话的个数
    var state = {
        calling: 0,
        waiting: 0,
        communicating: 0
    };
    for (var i = 0; i < calls.length; i++) {
        if (calls[i].state == CALL_STATE_CALLING) {
            state.calling++;
        } else if (calls[i].state == CALL_STATE_COMMUNICATING) {
            state.communicating++;
        } else if (calls[i].state == CALL_STATE_WAITING) {
            state.waiting++;
        }
    }

    var nMakeCall = 0;
    nMakeCall = (n - state.waiting) * 3 - state.calling;
    makeCall(nMakeCall);
});

function makeCall(n) {
    if (jobs.length - job_point < n) {
        n = jobs.length - job_point;
    }

    for (var i = job_point; i < n; i++) {
        var phone_number = jobs[i].phone_number;
        var case_id = jobs[i].case_id;
        call_handle++;
        event.emit("write to donjin", "call " + call_handle + " " + phone_number + " " + case_id);
    }

    if (n == 0) {
        console.log("job done");
    }
}

// read case from database
function getJobs() {
    for (var i = 0; i < 100; i++) {
        jobs.push({
            name: i + 1,
            phone_number: i + 1,
            case_id: "BS" + i
        });
    }
}

event.on("job start", function () {
    // read cases from database and start calling
    if (running) {
        console.log("job is running");
    } else {
        // get jobs
        getJobs();

        event.emit("make call");
    }
});

event.on("job stop", function () {
    // stop job
    console.log("job stop");
});

event.on("ready", function (data) {
    console.log("user " + data.userid + " ready");

    var user = null;
    for (var i = 0; i < users.length; i++) {
        if (users[i].userid == data.userid) {
            user = users[i];
            user.ready = true;
            break;
        }
    }

    if (user == null) {
        user = {};
        user.userid = data.userid;
        user.ready = true;
        users.push(user);
    }
});

event.on("not-ready", function (data) {
    console.log("user " + data.userid + " not-ready");

    var user = null;
    for (var i = 0; i < users.length; i++) {
        if (users[i].userid == data.userid) {
            user = users[i];
            user.ready = false;
            break;
        }
    }

    if (user == null) {
        user = {};
        user.userid = data.userid;
        user.ready = false;
        users.push(user);
    }
});

event.on("write to web", function (data) {
    server.socket.write(data + '\n');
});

event.on("write to donjin", function (data){
    client.write(data + '\n');
});

// 开一个TCP服务器给网页后端
var server = net.createServer(function (socket) {
    // 我们获得一个连接 - 该连接自动关联一个socket对象
    console.log('connected: ' +
        socket.remoteAddress + ':' + socket.remotePort);

    this.socket = socket;

    // 为这个socket实例添加一个"data"事件处理函数
    socket.on('data', function (data) {
        // convert buff to string
        data = data + "";
        data = data.trim();
        console.log('data from ' + socket.remoteAddress + ': ' + data);

        var matched = data.match(/notify job start/);
        if (matched) {
            event.emit("job start");
        }

        matched = data.match(/notify job end/);
        if (matched) {
            event.emit("job stop");
        }

        matched = data.match(/notify ([0-9]+) ready/);
        if (matched) {
            var userid = matched[1];
            socket.userid = userid;
            event.emit("ready", {userid: userid});
        }

        matched = data.match(/notify ([0-9]+) not-ready/);
        if (matched) {
            var userid = matched[1];
            socket.userid = userid;
            event.emit("not-ready", {userid: userid});
        }
    });

    // 为这个socket实例添加一个"close"事件处理函数
    socket.on('close', function () {
        console.log('closed: ' + socket.remoteAddress + ' ' + socket.remotePort + ", userid: " + socket.userid);
    });
}).listen(PORT, HOST);

console.log('work server listening on ' + HOST + ':' + PORT);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// donjin client
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
var HOST_DONJIN = "127.0.0.1";
var PORT_DONJIN = 4567;

var client = new net.Socket();
client.setNoDelay(true);
client.connect(PORT_DONJIN, HOST_DONJIN, function () {
    console.log('connect to donjin server: ' + HOST_DONJIN + ':' + PORT_DONJIN);
});

client.on("data", function(data){
    data = data + '';
    data = data.trim();


});

client.on("error", function(data){
    console.log("donjin server is down, error: " + JSON.stringify(data) + ", please restart donjin server and restart work server then");
    process.exit(-1);
});