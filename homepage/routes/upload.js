var express = require('express');
var router = express.Router();
var xlsx = require('node-xlsx');

/* GET home page. */
router.get('/', function (req, res) {
    res.render('upload');
});

/* POST home page. */
router.post("/", function (req, res) {
    // 处理文件上传
    var files = req.files.xlsxs;
    console.log("upload files: " + files);
    // console.log(JSON.stringify(files));
    if (!(files instanceof Array)) {
        files = [files];
    }
    var file = files[0].path;
    if (file.match(/(.xls|.XLS)$/)) {
        var child = require('child_process').spawn;
        xlhtml = child('libreoffice', ['--convert-to', 'xlsx', '--outdir', 'uploads', file, '--headless']);
        xlhtml.on('exit', function () {
            file += 'x';
            parseFiles(file, function (err, data) {
                if (err) {
                    res.json({
                        err: 1,
                        data: err.toString()
                    });
                    return;
                }
                console.log("data: " + JSON.stringify(data));
                res.json({
                    err: 0,
                    data: data
                });
            });
        });
    } else {
        parseFiles(file, function (err, data) {
            if (err) {
                res.json({
                    err: 1,
                    data: err.toString()
                });
                return;
            }
            console.log("data: " + JSON.stringify(data));
            res.json({
                err: 0,
                data: data
            });
        });
    }
});

function parseFiles(file, callback) {
    var data = [];
    var err = null;
    try {
        console.log("file: " + file);
        data = xlsx.parse(file);
    } catch (e) {
        err = e;
    }
    callback(err, data);
}

module.exports = router;