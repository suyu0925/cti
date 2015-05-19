var express = require('express');
var path = require('path');
var favicon = require('serve-favicon');
var logger = require('morgan');
var cookieParser = require('cookie-parser');
var bodyParser = require('body-parser');
var session = require('express-session');
var MongoStore = require('connect-mongo')(session);
var multer = require('multer');

var routes = require('./routes/index');
var login = require('./routes/login');
var signup = require('./routes/signup');
var upload = require('./routes/upload');
var ergodic = require('./routes/ergodic');
var agent_report = require('./routes/agent_report');
var call_report = require('./routes/call_report');

var hash = require('./pass').hash;
var setting = require('./setting');

var debug = require('debug')('kivvitek:server');
var http = require('http');

var app = express();

var port = parseInt(process.env.PORT, 10) || 2345;

/*
 View engine setup
 */
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

// uncomment after placing your favicon in /public
//app.use(favicon(__dirname + '/public/favicon.ico'));
app.use(logger('dev'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({extended: false}));
app.use(multer({dest: './uploads/'}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

/*
 Session
 */
app.use(session({
    secret: setting.cookieSecret,
    key: setting.db,
    cookie: {maxAge: 1000 * 60 * 60 * 24 * 30},
    store: new MongoStore({
        db: setting.db
    }),
    resave: true,
    saveUninitialized: true
}));

/*
 Routes
 */
app.use('/', routes);
app.use('/login', login);
app.use('/signup', signup);
app.use('/upload', upload);
app.use('/ergodic', ergodic);
app.use('/agent_report', agent_report);
app.use('/call_report', call_report);
app.use('/edit_case', require('./routes/edit_case'));
app.use('/log_report', require('./routes/log_report'));
app.use('/team_leader', require('./routes/team_leader'));

app.get('/logout', function (req, res) {
    req.session.destroy(function () {
        res.redirect('/');
    });
});

// catch 404 and forward to error handler
app.use(function (req, res, next) {
    var err = new Error('Not Found');
    err.status = 404;
    next(err);
});

// error handlers

// development error handler
// will print stacktrace
if (app.get('env') === 'development') {
    app.use(function (err, req, res, next) {
        res.status(err.status || 500);
        res.render('error', {
            message: err.message,
            error: err
        });
    });
}

// production error handler
// no stacktraces leaked to user
app.use(function (err, req, res, next) {
    res.status(err.status || 500);
    res.render('error', {
        message: err.message,
        error: {}
    });
});

/**
 * Get port from environment and store in Express.
 */
app.set('port', port);

/**
 * Create HTTP server.
 */

var server = http.createServer(app);

/**
 * Listen on provided port, on all network interfaces.
 */

server.listen(port);
server.on('error', onError);
server.on('listening', onListening);

/**
 * Event listener for HTTP server "error" event.
 */

function onError(error) {
    if (error.syscall !== 'listen') {
        throw error;
    }

    // handle specific listen errors with friendly messages
    switch (error.code) {
        case 'EACCES':
            console.error('Port ' + port + ' requires elevated privileges');
            process.exit(1);
            break;
        case 'EADDRINUSE':
            console.error('Port ' + port + ' is already in use');
            process.exit(1);
            break;
        default:
            throw error;
    }
}

/**
 * Event listener for HTTP server "listening" event.
 */

function onListening() {
    debug('Listening on port ' + server.address().port);
}

// require('./chat')(server);
var bridge = new require('./bridge')(server);

var work = new require('./work')();
work.setBridge(bridge);