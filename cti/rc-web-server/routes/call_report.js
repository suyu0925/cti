var express = require('express');
var router = express.Router();
var MongoClient = require('mongodb').MongoClient;
var fs = require('fs');
var xlsx = require('node-xlsx');

// Connection URL
var mongoUrl = 'mongodb://kivvitek.com:27017/report';

/* GET home page. */
router.get('/', function (req, res) {
    MongoClient.connect(mongoUrl, function (err, db) {
        var collection = db.collection('call');
        collection.find({}, {limit: 20}).toArray(function (err, docs) {
            res.render('call_report', {data: docs});
            db.close();
        });
    });
});

function output(data) {
    console.log('data:', data);
    var obj = [{name: "呼叫报表", data: data}];
    var file = xlsx.build(obj);
    fs.writeFileSync('./public/call_report.xlsx', file, 'binary');
}

router.post('/', function (req, res) {
    MongoClient.connect(mongoUrl, function (err, db) {
        var collection = db.collection('call');
        collection.find({}, {limit: 20}).toArray(function (err, docs) {
            var data = [["日期", "呼损数", "接通数","呼叫电话总数","呼叫总案件数"]];
            for (var i = 0; i < docs.length; i++) {
                var row = [];
                row.push(docs[i].date);
                row.push(docs[i].loss_count);
                row.push(docs[i].connect_count);
                row.push(docs[i].call_count);
                row.push(docs[i].case_count);
                data.push(row);
            }
            output(data);
            res.redirect('/call_report.xlsx');
            db.close();
        });
    });
});

module.exports = router;