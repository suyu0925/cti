var express = require('express');
var router = express.Router();
var pass = require('../pass');
var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/account';

/* GET home page. */
router.get('/', function(req, res) {
    res.render('login');
});

/* POST home page. */
router.post("/", function (req, res) {
     pass.authenticate(req.body.username, req.body.password, function (err, user) {
        console.log(err);
        if (user) {
            req.session.regenerate(function () {
                req.session.user = user;
                req.session.success = 'Authenticated as ' + user.username + ' click to <a href="/logout">logout</a>. ' + ' You may now access <a href="/restricted">/restricted</a>.';
                res.redirect('/');
            });
        } else {
            req.session.error = 'Authentication failed, please check your ' + ' username and password.';
            res.redirect('/login');
        }
    });
});

module.exports = router;