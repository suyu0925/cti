var net = require('net');

// Host
var HOST = '127.0.0.1';
var PORT = 8123;

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
    });

    // 为这个socket实例添加一个"close"事件处理函数
    socket.on('close', function () {
        console.log('closed: ' + socket.remoteAddress + ' ' + socket.remotePort + ", userid: " + socket.userid);
    });

    socket.on('error', function (data) {
        console.log("web server is down, error: " + JSON.stringify(data) + ", please restart donjin server and restart work server then");
    });
}).listen(PORT, HOST);

console.log('work server listening on ' + HOST + ':' + PORT);
