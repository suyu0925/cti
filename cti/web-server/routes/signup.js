var express = require('express');
var router = express.Router();
var pass = require('../pass');
var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/account';

/*
Function
*/
function userExist(req, res, next) {
    // Use connect method to connect to the Server
    MongoClient.connect(mongoUrl, function(err, db) {
        var collection = db.collection('users');
        collection.find({'username': req.body.username}).toArray(function(err, users) {
            db.close();
            console.log("users: " + JSON.stringify(users));
            if (users && users.length != 0) {
                req.session.error = "User Exist";
                res.redirect("/signup");
            } else {
                next();
            }
        });
    });
}

/* GET home page. */
router.get('/', function(req, res) {
    if (req.session.user) {
        res.redirect("/");
    } else {
        res.render("signup", {
            username_error: '',
            password_error: '',
            password_confirm_error: ''
        });
    }
});

/* POST home page. */
router.post("/", userExist, function (req, res) {
    var username = req.body.username;
    var password = req.body.password;
    var password_confirm = req.body.password_confirm;
    console.log('username: ' + username);
    console.log('password: ' + password);
    console.log('password_confirm: ' + password_confirm);

    if (!username || username == '' ||
        !password || password == '' ||
        !password_confirm || password_confirm == '') {
        res.render("signup", {
            username_error: '不能为空',
            password_error: '',
            password_confirm_error: ''
        });
        return;
    }

    if (password != password_confirm) {
        res.render("signup", {
            username_error: '',
            password_error: '',
            password_confirm_error: '两次密码必须相同'
        });
        return;
    }

    pass.hash(password, function (err, salt, _hash) {
        if (err) throw err;
        MongoClient.connect(mongoUrl, function(err, db) {
            var collection = db.collection('users');
            console.log("salt: " + salt);
            collection.insert({username: username, salt: salt, hash: _hash.toString('base64')}, {w: 1}, function (err, result) {
                db.close();

                if (err) throw err;
                pass.authenticate(username, password, function(err, user) {
                    if (err) throw err;
                    if (user) {
                        req.session.regenerate(function() {
                            req.session.user = user;
                            req.session.success = 'Authenticated as ' + username + ' click to <a href="/logout">logout</a>. ' + ' You may now access <a href="/restricted">/restricted</a>.';
                            res.redirect('/');
                        });
                    }
                });
            });
        });
    });
});

module.exports = router;
