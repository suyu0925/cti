var net = require('net');

var HOST = "127.0.0.1";
var PORT = 4567;

var client = new net.Socket();
client.setNoDelay(true);
client.connect(PORT, HOST, function () {
    console.log('connect to: ' + HOST + ':' + PORT);

    // 直接拨打10个号码
    for (var i = 0; i < 10; i++) {
        client.write("call " + i + " 138160" + i + " case_id_" + i + "\n");
    }
});

client.on('data', function (data) {
    data = data + '';
    console.log(data.trim());
});

client.on('error', function (data) {
    console.log("donjin server is down, error: " + JSON.stringify(data) + ", please restart donjin server and restart test then");
    process.exit(-1);
});