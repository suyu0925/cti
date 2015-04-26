// check out https://github.com/visionmedia/node-pwd

/**
 * Module dependencies.
 */

var crypto = require('crypto');
var MongoClient = require('mongodb').MongoClient;

/**
 * Bytesize.
 */

var len = 128;

/**
 * Iterations. ~300ms
 */

var iterations = 12000;

// Connection URL
// var HOST = "localhost";
var HOST = "115.28.1.58";
var mongoUrl = 'mongodb://' + HOST + ':27017/account';

/**
 * Hashes a password with optional `salt`, otherwise
 * generate a salt for `pass` and invoke `fn(err, salt, hash)`.
 *
 * @param {String} password to hash
 * @param {String} optional salt
 * @param {Function} callback
 * @api public
 */

var hash = function (pwd, salt, fn) {
    console.log("hash: " + pwd + ", " + salt + ", " + fn);
    if (3 == arguments.length) {
        crypto.pbkdf2(pwd, salt, iterations, len, fn);
    } else {
        fn = salt;
        crypto.randomBytes(len, function (err, salt) {
            if (err) return fn(err);
            salt = salt.toString('base64');
            console.log('generate salt: ' + salt);
            crypto.pbkdf2(pwd, salt, iterations, len, function (err, _hash) {
                if (err) return fn(err);
                fn(null, salt, _hash);
            });
        });
    }
};

exports.hash = hash;

exports.authenticate = function (name, pass, fn) {
    console.log('authenticating %s:%s', name, pass);

    // Use connect method to connect to the Server
    MongoClient.connect(mongoUrl, function (err, db) {
        var collection = db.collection('users');
        collection.find({'username': name}).toArray(function (err, users) {
            db.close();
            if (users && users.length > 0) {
                var user = users[0];
                if (err) {
                    console.log('can not find user. err: ' + err);
                    return fn(new Error('can not find user. err: ' + err));
                } else {
                    console.log("user: " + JSON.stringify(user));
                    hash(pass, user.salt, function (err, _hash) {
                        _hash = _hash.toString('base64');
                        console.log("err: " + err + ", _hash: " + _hash);
                        console.log("user.hash: " + user.hash);
                        if (err)
                            return fn(err);
                        if (_hash == user.hash) {
                            console.log('authenticate ok.');
                            return fn(null, user);
                        } else {
                            return fn(new Error('authenticate failed.'));
                        }
                    });
                }
            } else {
                console.log('can not find user');
                return fn(new Error('can not find user'));
            }
        });
    });
};