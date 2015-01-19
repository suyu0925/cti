var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var mongoose = require('mongoose');
var session = require('express-session');
var MongoStore = require('connect-mongo')(session);

var routes = require('./routes/index');
var login = require('./routes/login');
var signup = require('./routes/signup');
var users = require('./routes/users');
var userlist = require('./routes/userlist');
var newuser = require('./routes/newuser');

var hash = require('./pass').hash;
var setting = require('./setting');

// mongodb
var mongo = require('mongodb');
var monk = require('monk');
var db = monk('localhost:27017/kivvitek');

var app = express();

/*
Database and Models
*/
global.db = {};
global.db.connect = mongoose.connect("mongodb://localhost/kivvitek");
var UserSchema = new mongoose.Schema({
    username: String,
    password: String,
    salt: String,
    hash: String
});

global.db.User = mongoose.model('users', UserSchema);

/*
View engine setup
*/
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

/*
Session
*/
app.use(session({
    secret: setting.cookieSecret,  
    store: new MongoStore({
        db : setting.db
    })
}));

/*
Routes
*/
app.use('/', routes);
app.use('/login', login);
app.use('/signup', signup);

app.use('/users', users);

app.use('/userlist', userlist);
app.get('/userlist', userlist.userlist(db));

app.use('/newuser', newuser);
app.post('/adduser', newuser.adduser(db));

// catch 404 and forward to error handler
app.use(function(req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function(err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function(err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});


module.exports = app;
