var express = require('express');
var router = express.Router();
var MongoClient = require('mongodb').MongoClient;
var xlsx = require('node-xlsx');

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/work';

// 错误号码与描述
var error_single_file = 1;
var error_not_supported_file = 2;
var error_empty_case_id = 3;
var error_reduplicated_case_id = 4;
var error_db_insert = 5;
var error_db_find = 6;
var error_empty_name = 7;
var error_repeated_case_id = 8;
var error_empty_file = 9;
var errors = [
    {code: error_single_file, content: "只允许选择一个文件"},
    {code: error_not_supported_file, content: "不支持的文件"},
    {code: error_empty_case_id, content: "空白的个案序列号"},
    {code: error_reduplicated_case_id, content: "重复的个案序列号"},
    {code: error_db_insert, content: "数据库插入错误"},
    {code: error_db_find, content: "数据库查询错误"},
    {code: error_empty_name, content: "借款人的姓名为空"},
    {code: error_repeated_case_id, content: "导入的数据中存在重复的个案序列号"},
    {code: error_empty_file, content: "导入数据为空"}
];

var profile = {
    start: 0,
    end: 0,
    tag: null,
    rbi: function (tag) {
        var now = (new Date()).getTime();
        if (this.tag != null) {
            var dt = now - this.start;
            console.log(this.tag + " spend " + dt + " ms.");
            this.start = now;
            if (this.tag != tag) {
                this.tag = null;
                this.end = 0;
            }
        } else {
            this.tag = tag;
            this.start = now;
        }
    }
};

/* GET home page. */
router.get('/', function (req, res) {
    res.render('upload');
});

/* POST home page. */
router.post("/", function (req, res) {
    // 处理文件上传
    var files = req.files.xlsxs;
    // console.log(JSON.stringify(files));
    if (!(files instanceof Array)) {
        files = [files];
    }
    parseFiles(files, function (err) {
        var out = {
            error: err || 0,
            content: "导入成功"
        };
        if (err) {
            for (var i = 0; i < errors.length; i++) {
                if (err === errors[i].code) {
                    out.content = errors[i].content;
                    break;
                }
            }
        }
        res.send(JSON.stringify(out));
    });
});

function parseFiles(files, next) {
    var err = 0;
    var docs = [];

    // 暂时只允许选择一个文件
    if (files.length > 1) {
        err = error_single_file;
    }

    profile.rbi("xlsx");
    if (!err) {
        for (var fileIndex = 0; fileIndex < files.length; fileIndex++) {
            try {
                var worksheets = xlsx.parse(files[fileIndex].path);
                // 取得第一个工作表的数据
                var data = worksheets[0].data;
                // console.log(JSON.stringify(data));

                // skip the first line
                for (var i = 1; i < data.length; i++) {
                    var line = data[i];
                    var doc = {};
                    // id
                    doc.id = line[0];
                    // order
                    doc.order = {};
                    doc.order.name = line[2];
                    doc.order.datetime = line[3];
                    doc.order.amount = line[4];
                    // loan
                    doc.loan = {};
                    doc.loan.contract = line[1];
                    doc.loan.datetime = line[5];
                    doc.loan.amount = line[6];
                    doc.loan.terms = line[7];
                    doc.loan.principal = "";
                    doc.loan.interest = "";
                    doc.loan.monthly = line[16];
                    doc.loan.account = {};
                    doc.loan.account.name = line[18];
                    doc.loan.account.id = line[19];
                    doc.loan.account.bank = line[17];
                    // overdue
                    doc.overdue = {};
                    doc.overdue.days = line[10];
                    doc.overdue.terms = line[9];
                    doc.overdue.amount = line[11];
                    doc.overdue.principal = line[12];
                    doc.overdue.interest = line[13];
                    doc.overdue.default = line[14];
                    doc.overdue.expenses = line[15];
                    doc.overdue.datetime = line[8];
                    // borrower
                    doc.borrower = {};
                    doc.borrower.name = {};
                    doc.borrower.name.personal = line[20];
                    doc.borrower.name.office = line[28];
                    doc.borrower.gender = line[21];
                    doc.borrower.phone = {};
                    doc.borrower.phone.mobile = line[24];
                    doc.borrower.phone.home = line[25];
                    doc.borrower.phone.office = line[27];
                    doc.borrower.address = {};
                    doc.borrower.address.home = line[26];
                    doc.borrower.address.office = line[29];
                    doc.borrower.address.huji = line[30];
                    doc.borrower.id = {};
                    doc.borrower.id.personal = line[22];
                    doc.borrower.id.company = line[23];
                    // contacts
                    doc.contacts = {};
                    doc.contacts.spouse = {};
                    doc.contacts.spouse.name = {};
                    doc.contacts.spouse.name.personal = line[31];
                    doc.contacts.spouse.name.office = line[33];
                    doc.contacts.spouse.phone = {};
                    doc.contacts.spouse.phone.home = line[35];
                    doc.contacts.spouse.phone.mobile = line[36];
                    doc.contacts.spouse.id = {};
                    doc.contacts.spouse.id.personal = line[32];
                    doc.contacts.spouse.id.company = "";
                    doc.contacts.spouse.address = {};
                    doc.contacts.spouse.address.home = line[34];
                    doc.contacts.spouse.address.company = "";
                    doc.contacts.guarantor = {};
                    doc.contacts.guarantor.name = line[37];
                    doc.contacts.guarantor.id = line[38];
                    doc.contacts.guarantor.phone = {};
                    doc.contacts.guarantor.phone.home = line[39];
                    doc.contacts.guarantor.phone.mobile = line[40];
                    doc.contacts.guarantor.address = line[41];
                    doc.contacts.other = [];
                    for (var indexOfContact = 0; indexOfContact < 5; indexOfContact++) {
                        var contact = {};
                        contact.name = line[42 + indexOfContact * 3];
                        contact.relationship = line[43 + indexOfContact * 3];
                        contact.phone = line[44 + indexOfContact * 3];
                        doc.contacts.other.push(contact);
                    }

                    docs.push(doc);
                }
            } catch (e) {
                console.log(e);
                err = error_not_supported_file;
            } finally {
            }
        }
    }
    profile.rbi();

    if (!err) {
        check(docs, next);
    } else {
        next(err);
    }
}

function check(docs, next) {
    var err = 0;

    if (docs.length == 0) {
        err = error_empty_file;
    }

    profile.rbi("check");
    var hash = {};
    for (var i = 0; i < docs.length; i++) {
        // 个案序列号非空检查
        var id = docs[i].id || "";
        id = id.replace(/(^\s*)|(\s*$)/g, "");
        if (id.length == 0) {
            err = error_empty_case_id;
            break;
        }

        // 姓名的非空检查
        var name = docs[i].borrower.name.personal || "";
        name = name.replace(/(^\s*)|(\s*$)/g, "");
        if (name.length == 0) {
            err = error_empty_name;
            break;
        }

        // 重复的个案序列号检查
        if (hash[id]) {
            err = error_repeated_case_id;
            break;
        }
        hash[id] = true;
    }
    profile.rbi();

    if (!err) {
        add(docs, next);
    } else {
        next(err);
    }
}

function add(docs, next) {
    MongoClient.connect(mongoUrl, function (err, db) {
        db.ensureIndex('debt', {id: 1}, {unique: true});
        var collection = db.collection('debt');
        var case_ids = [];
        for (var i = 0; i < docs.length; i++) {
            case_ids.push(docs[i].id);
        }
        profile.rbi("find");
        collection.find({id: {"$in": case_ids}}).toArray(function (err, result) {
            profile.rbi();
            if (err) {
                db.close();
                next(error_db_find);
            } else {
                if (result && result.length != 0) {
                    db.close();
                    next(error_reduplicated_case_id);
                } else {
                    _add(db, 0, docs, next);
                }
            }
        });
    });
}

function _add(db, start, docs, next) {
    if (start == docs.length) {
        db.close();
        next();
        return;
    }

    profile.rbi("add");
    var insert_docs;
    if (docs.length - start > 1000) {
        insert_docs = docs.slice(start, start + 1000);
        start += 1000;
    } else {
        insert_docs = docs.slice(start, docs.length);
        start = docs.length;
    }

    var collection = db.collection('debt');
    collection.insertMany(insert_docs, function (err, result) {
        profile.rbi();
        if (err) {
            console.log(err);
            db.close();
            next(error_db_insert);
        } else {
            _add(db, start, docs, next);
        }
    });
}

module.exports = router;