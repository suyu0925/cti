var express = require('express');
var router = express.Router();
var MongoClient = require('mongodb').MongoClient;

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
        collection.find({"action4.enable": true}, {limit: 20}).toArray(function (err, docs) {
            var data = [];
            if (docs) {
                for (var i = 0; i < docs.length; i++) {
                    var log = docs[i].logs[docs[i].logs.length - 1];
                    docs[i].href = "<a href=\"/edit_case?case_id=" + docs[i].id + "\">" + docs[i].id + "</a>";
                    docs[i].user_id =log.user_id;
                    docs[i].datetime = getDateString(new Date(parseInt(log.datetime)));
                    data.push(docs[i]);
                }
            }
            res.render('team_leader', {data: data});
            db.close();
        });
    });
});

module.exports = router;