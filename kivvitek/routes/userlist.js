var express = require('express');
var router = express.Router();

router.userlist = function(db) {
    return function(req, res) {
        var collection = db.get('usercollection');
        collection.find({}, {}, function(e, docs) {
            res.render('userlist', {
                "userlist" : docs
            });
        });
    };
};

module.exports = router;
