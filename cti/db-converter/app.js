var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/work';

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
        if (!err || !result || result.length > 0) {
            var insert_docs = [];
            for (var i = 0; i < result.length; i++) {
                var doc = result[i];
                addPhone(insert_docs, doc.id, doc.borrower.phone.mobile);
                addPhone(insert_docs, doc.id, doc.borrower.phone.home);
                addPhone(insert_docs, doc.id, doc.borrower.phone.office);
                addPhone(insert_docs, doc.id, doc.contacts.spouse.phone.home);
                addPhone(insert_docs, doc.id, doc.contacts.spouse.phone.mobile);
                addPhone(insert_docs, doc.id, doc.contacts.guarantor.phone.home);
                addPhone(insert_docs, doc.id, doc.contacts.guarantor.phone.mobile);
                for (var indexOfContact = 0; indexOfContact < 5; indexOfContact++) {
                    addPhone(insert_docs, doc.id, doc.contacts.other[indexOfContact].phone);
                }
            }
            if (insert_docs.length > 0) {
                var callCollection = db.collection('call');
                callCollection.insertMany(insert_docs, function (err, result) {
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
