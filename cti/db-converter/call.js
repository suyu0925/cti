var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://kivvitek.com:27017/work';

function addPhone(docs, case_id, phone_number) {
    var doc = null;
    if (phone_number && phone_number.toString().trim().length != 0) {
        doc = {
            case_id: case_id,
            phone_number: 
                // getARandomPhone().toString(), 
                phone_number.toString(),
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
        if (!err || !result || result.length > 0) {
            console.log("result.length = " + result.length);
            var insert_docs = [];
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.borrower.phone.mobile);
            }
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.borrower.phone.home);
            }
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.borrower.phone.office);
            }
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.contacts.spouse.phone.home);
            }
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.contacts.spouse.phone.mobile);
            }
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.contacts.guarantor.phone.home);
            }
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.contacts.guarantor.phone.mobile);
            }
            for (var indexOfContact = 0; indexOfContact < 5; indexOfContact++) {
                for (var i = 0; i < result.length; i++) {
                    var doc = result[i];
                    addPhone(insert_docs, doc.id, doc.contacts.other[indexOfContact].phone);
                }
            }
            if (insert_docs.length > 0) {
                console.log("insert_docs.length = " + insert_docs.length);
                var callCollection = db.collection('call');
                // FIXME: insert every peice.
                var end = insert_docs.length > 1000 ? 1000 : insert_docs.length;
                insert_docs = insert_docs.slice(0, end);
                callCollection.insertMany(insert_docs, function (err, result) {
                    console.log("insert error: " + err);
                    db.close();
                    console.log("job done");
                });
            } else {
                db.close();
            }
        } else {
            db.close();
        }
    });
});
