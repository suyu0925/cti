var express = require('express');
var router = express.Router();
var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/report';

/* GET home page. */
router.get('/', function (req, res) {
    MongoClient.connect(mongoUrl, function(err, db) {
        var collection = db.collection('call');
        collection.find({}, {limit: 20}).toArray(function(err, docs) {
            res.render('call_report', {data: docs});
            db.close();
        });
    });
});

module.exports = router;