var express = require('express');
var router = express.Router();
var MongoClient = require('mongodb').MongoClient;
var fs = require('fs');
var xlsx = require('node-xlsx');

// Connection URL
var mongoUrl = 'mongodb://kivvitek.com:27017/work';

function getFixTime(time) {
    if (time < 10) {
        return "0" + time.toString();
    } else {
        return time.toString();
    }
}

function getDateString(date) {
    var str = "";
    var year = date.getFullYear();
    var month = getFixTime(date.getMonth() + 1);
    var day = getFixTime(date.getDate());
    var hours = getFixTime(date.getHours());
    var min = getFixTime(date.getMinutes());
    str = year + "-" + month + "-" + day + " " + hours + ":" + min;
    return str;
}

/* GET home page. */
router.get('/', function (req, res) {
    MongoClient.connect(mongoUrl, function (err, db) {
        var collection = db.collection('debt');
        collection.find({}, {limit: 20}).toArray(function (err, docs) {
            var logs = [];
            if (docs) {
                for (var i = 0; i < docs.length; i++) {
                    if (docs[i].logs) {
                        for (var j = 0; j < docs[i].logs.length; j++) {
                            docs[i].logs[j]["case_id"] = docs[i].id;
                            var date = new Date(parseInt(docs[i].logs[j].datetime));
                            docs[i].logs[j]["date"] = getDateString(date);
                            logs.push(docs[i].logs[j]);
                        }
                    }
                }
            }
            res.render('log_report', {data: logs});
            db.close();
        });
    });
});

function output(data) {
    console.log('data:', data);
    var obj = [{name: "日志报表", data: data}];
    var file = xlsx.build(obj);
    fs.writeFileSync('./public/log_report.xlsx', file, 'binary');
}

router.post('/', function (req, res) {
    MongoClient.connect(mongoUrl, function (err, db) {
        var collection = db.collection('debt');
        collection.find({}, {limit: 20}).toArray(function (err, docs) {
            var logs = [];
            var data = [["案件号", "备注时间", "动作代码","备注内容","创建人"]];
            if (docs) {
                for (var i = 0; i < docs.length; i++) {
                    if (docs[i].logs) {
                        for (var j = 0; j < docs[i].logs.length; j++) {
                            docs[i].logs[j]["case_id"] = docs[i].id;
                            var date = new Date(parseInt(docs[i].logs[j].datetime));
                            docs[i].logs[j]["date"] = getDateString(date);
                            logs.push(docs[i].logs[j]);
                        }
                    }
                }
            }
            for (var i = 0; i < logs.length; i++) {
                var row = [];
                row.push(logs[i].case_id);
                row.push(logs[i].date);
                row.push(logs[i].action);
                row.push(logs[i].text);
                row.push(logs[i].user_id);
                data.push(row);
            }
            output(data);
            res.redirect('/log_report.xlsx');
            db.close();
        });
    });
});

module.exports = router;