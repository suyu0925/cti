var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function (req, res) {
    console.log("get/ req.session.user: " + JSON.stringify(req.session.user));
    if (req.session.user) {
        res.render('workspace');
    } else {
        res.redirect('/login');
    }
});

module.exports = router;
