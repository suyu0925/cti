var net = require('net');
var events = require("events");
var MongoClient = require('mongodb').MongoClient;
var event = new events.EventEmitter();

// Host
var HOST = '127.0.0.1';
var PORT = 8123;
// Connection URL
var mongoUrl = 'mongodb://localhost:27017/work';
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
        var user = users[i];
        if (user.ready && user.state == "idle") {
            n++;
        }
    }

    // 获取正在拨话的个数
    var state = {
        calling: 0,
        waiting: 0
    };
    for (var i = 0; i < calls.length; i++) {
        if (calls[i].state == "waiting") {
            state.waiting++;
        } else if (calls[i].state != "end") {
            state.calling++;
        }
    }

    var nMakeCall = 0;
    nMakeCall = (n - state.waiting) * 3 - state.calling;
    makeCall(nMakeCall);
});

function newCallHandle() {
    return call_handle++;
}

function makeCall(n) {
    if (n < 0)
        return;

    if (jobs.length - job_point < n) {
        n = jobs.length - job_point;
    }

    for (var i = job_point; i < job_point + n; i++) {
        var job = jobs[i];
        var call = {
            phone_number: job.phone_number,
            case_id: job.case_id,
            call_handle: newCallHandle()
        };
        calls.push(call);
        event.emit("write to donjin", "call " + call.call_handle + " " + call.phone_number + " " + call.case_id);
    }
    job_point += n;

    if (n == 0) {
        // console.log("waitting");
    }
}

function assignCall(call) {
    // find a user to get the call
    var user = getAvailableUser();

    if (user) {
        // emit to web
        event.emit("write to web", "call " + user.userid + " " + call.phone_number + " " + call.case_id);

        // emit to donjin
        var join_handle = newJoinHandle();
        event.emit("write to donjin", "join " + join_handle + " " + call.call_handle + " " + user.userid);

        call.state = "connect";
        call.user = user;

        user.state = "join";
        user.call = call;
        user.ready = false;
        user.join_handle = join_handle;
    }
}

// 每100毫秒检查下有没有需要拨打新的电话
setInterval(function () {
    if (!running)
        return;

    // 检查有没有正在等待的客户
    for (var i = 0; i < calls.length; i++) {
        var call = calls[i];
        if (call.state == "waiting") {
            assignCall(call);
        }
    }

    event.emit("make call");
}, 100);

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

        console.log("job start");
        running = true;
    }
});

event.on("job stop", function () {
    // stop job
    console.log("job stop");

    running = false;
});

event.on("ready", function (data) {
    console.log("user " + data.userid + " ready");

    var user = null;
    for (var i = 0; i < users.length; i++) {
        if (users[i].userid == data.userid) {
            user = users[i];
            user.ready = true;
            user.state = "idle";
            break;
        }
    }

    if (user == null) {
        user = {};
        user.userid = data.userid;
        user.ready = true;
        user.state = "idle";
        user.on_hook = true;
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
        console.log("error: a user init with not-ready");
        user = {};
        user.userid = data.userid;
        user.ready = false;
        user.state = "idle";
        user.on_hook = true;
        users.push(user);
    }
});

event.on("write to web", function (data) {
    console.log("send to web: " + data);
    server.socket.write(data + '\n');
});

event.on("write to donjin", function (data) {
    console.log("send to donjin: " + data);
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

    socket.on('error', function (data) {
        console.log("web server is down, error: " + JSON.stringify(data) + ", please restart donjin server and restart work server then");
        process.exit(-1);
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

function findCallWithHandle(call_handle) {
    for (var i = 0; i < calls.length; i++) {
        if (calls[i].call_handle == call_handle) {
            return calls[i];
        }
    }
    return null;
}

function findUserWithId(userid) {
    for (var i = 0; i < users.length; i++) {
        if (users[i].userid == userid) {
            return users[i];
        }
    }
    return null;
}

function findUserWithCall(call) {
    for (var i = 0; i < users.length; i++) {
        if (users[i].call == call) {
            return users[i];
        }
    }
    return null;
}

function findUserWithJoinHandle(join_handle) {
    for (var i = 0; i < users.length; i++) {
        if (users[i].join_handle == join_handle) {
            return users[i];
        }
    }
    return null;
}

function getAvailableUser() {
    // get the first user with state "idle"
    for (var i = 0; i < users.length; i++) {
        var user = users[i];
        if (user.ready && user.state == "idle") {
            return user;
        }
    }
    return null;
}

function newJoinHandle() {
    return join_handle++;
}

client.on("data", function (data) {
    data = data + '';
    data = data.trim();

    console.log("rec from donjin: " + data);

    var matched = data.match(/call ([0-9]+) start/);
    if (matched) {
        var call = findCallWithHandle(matched[1]);
        call.state = "start";
        return;
    }

    var matched = data.match(/call ([0-9]+) end (\-*[0-9]+)/);
    if (matched) {
        var call = findCallWithHandle(matched[1]);
        call.state = "end";

        var user = findUserWithCall(call);
        if (user) {
            user.state = "log";
            event.emit("write to web", "call " + user.userid + " end " + matched[2]);
        }

        return;
    }

    var matched = data.match(/call ([0-9]+) ring/);
    if (matched) {
        var call = findCallWithHandle(matched[1]);
        call.state = "ring";
        return;
    }

    var matched = data.match(/call ([0-9]+) connect/);
    if (matched) {
        var call_handle = matched[1];
        var call = findCallWithHandle(call_handle);
        call.state = "waiting";

        assignCall(call);

        return;
    }

    var matched = data.match(/join ([0-9]+) (\-*[0-9]+)/);
    if (matched) {
        var join_handle = matched[1];
        var error_code = matched[2];
        var user = findUserWithJoinHandle(join_handle);
        if (error_code == 0) {
            user.state = "taling";
            user.join_handle = null;
            user.ready = false;
            event.emit("write to web", "call " + user.userid + " connect");
        } else {
            if (error_code == -1) {
                // 无人接听
                user.state = "afk";
            }
            event.emit("write to web", "call " + user.userid + " end " + error_code);
        }
    }

    var matched = data.match(/notify ([0-9]+) on-hook/);
    if (matched) {
        var user = findUserWithId(matched[1]);
        user.on_hook = true;
        event.emit("write to web", "notify " + user.userid + " on-hook");
    }

    var matched = data.match(/notify ([0-9]+) off-hook/);
    if (matched) {
        var user = findUserWithId(matched[1]);
        user.on_hook = false;
        event.emit("write to web", "notify " + user.userid + " off-hook");
    }
});

client.on("error", function (data) {
    console.log("donjin server is down, error: " + JSON.stringify(data) + ", please restart donjin server and restart work server then");
    process.exit(-1);
});