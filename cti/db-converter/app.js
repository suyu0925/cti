var MongoClient = require('mongodb').MongoClient;

// Host
var HOST = '127.0.0.1';
var PORT = 8123;

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/account';

function addPhone(docs, case_id, phone_number) {
    var doc = null;
    if (phone_number && phone_number.toString().trim().length != 0) {
        doc = {
            case_id: case_id,
            phone_number: getARandomPhone().toString(), //phone_number.toString(),
            flag: 0
        };
        docs.push(doc);
    }
};

// debug hardcore
function getARandomPhone() {
    var phone = 805; // 805 - 808
    phone += parseInt(Math.floor(Math.random() * 4));
    return phone;
}

MongoClient.connect(mongoUrl, function (err, db) {
    var collection = db.collection('debt');
    collection.find().toArray(function (err, result) {
        if (!err || !result || result.length == 0) {
            var insert_docs = [];
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.borrower.phone.mobile);
                addPhone(insert_docs, doc.id, doc.borrower.phone.home);
                addPhone(insert_docs, doc.id, doc.borrower.phone.office);
                addPhone(insert_docs, doc.id, doc.contacts.spouse.phone.home);
                addPhone(insert_docs, doc.id, doc.contacts.spouse.phone.home);
                addPhone(insert_docs, doc.id, doc.doc.contacts.spouse.phone.home);
                for (var indexOfContact = 0; indexOfContact < 5; indexOfContact++) {
                    addPhone(insert_docs, doc.id, doc.contacts.other[indexOfContact].phone);
                }
            }
            collection.insertMany(insert_docs, function (err, result) {
                db.close();
            });
        } else {
            db.close();
        }
    });
});
