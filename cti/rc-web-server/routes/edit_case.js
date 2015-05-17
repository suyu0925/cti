var express = require('express');
var router = express.Router();
var MongoClient = require('mongodb').MongoClient;
var url = require('url');

// Connection URL
var mongoUrl = 'mongodb://kivvitek.com:27017/work';

/* GET home page. */
router.get('/', function (req, res) {
    var case_id = url.parse(req.url, true).query.case_id;

    MongoClient.connect(mongoUrl, function (err, db) {
        var collection = db.collection('debt');
        collection.find({"id": case_id}).toArray(function (err, docs) {
            if (err || !docs || docs.length == 0) {
                res.status(404).send("not found");
            } else {
                res.render('edit_case', {data: docs[0]});
            }
            db.close();
        });
    });
});

router.post('/', function (req, res) {
    var case_id = url.parse(req.url, true).query.case_id;
    var log = {
        user_id: -1,
        text: req.body.log_textarea,
        action: req.body.log_action,
        datetime: new Date().getTime()
    };

    MongoClient.connect(mongoUrl, function (err, db) {
        db.collection("debt").updateOne({"id": case_id}, {$push: {"logs": log}}, function (err, results) {
            db.collection("debt").find({"id": case_id}).toArray(function (err, docs) {
                if (err || !docs || docs.length == 0) {
                    res.status(404).send("not found");
                } else {
                    res.render('edit_case', {data: docs[0]});
                }
                db.close();
            });
        });
    });
});

module.exports = router;