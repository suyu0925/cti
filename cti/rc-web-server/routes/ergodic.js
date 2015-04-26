/**
 * Created by Administrator on 2015/4/13.
 */
var express = require('express');
var router = express.Router();
var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/work';

/* GET home page. */
router.get('/', function (req, res) {
    MongoClient.connect(mongoUrl, function(err, db) {
        var collection = db.collection('debt');
        collection.find({}, {limit: 20}).toArray(function(err, docs) {
            res.render('ergodic', {data: docs});
            db.close();
        });
    });
});

router.post('/clear', function(req, res) {
    MongoClient.connect(mongoUrl, function(err, db) {
        var collection = db.collection('debt');
        collection.drop(function(err, reply) {
            res.redirect('/ergodic');
            db.close();
        });
    });
});

router.post('/start', function(req, res) {
    // TODO send a "start" message to work server
    res.redirect('/ergodic');
});

router.post('/stop', function(req, res) {
    // TODO send a "stop" message to work server
    res.redirect('/ergodic');
});

module.exports = router;