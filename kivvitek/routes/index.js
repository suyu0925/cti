var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
    if (req.session.user) {
        res.render("index");
    } else {
        res.redirect("/login");
    }
});

module.exports = router;
