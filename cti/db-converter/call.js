var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://kivvitek.com:27017/work';

function addDocument(docs, case_id, phone_numbers) {
    if (phone_numbers.length > 0) {
        var doc = {
            case_id: case_id,
            phone_number_count: phone_numbers.length,
            phone_number_cursor: 0,
            flag: 0
        };
        for (var i = 0; i < 11; i++) {
            var n;
            if (i < phone_numbers.length) {
                n = phone_numbers[i];
            } else {
                n = "";
            }
            doc["phone_number_" + i] = n;
        }
        docs.push(doc);
    }
};

function addPhone(phones, phone_number) {
    if (phone_number && phone_number.toString().trim().length != 0) {
        phones.push(phone_number.toString());
    }
}

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
                var phone_numbers = [];
                addPhone(phone_numbers, doc.borrower.phone.mobile);
                addPhone(phone_numbers, doc.borrower.phone.office);
                addPhone(phone_numbers, doc.contacts.spouse.phone.home);
                addPhone(phone_numbers, doc.contacts.spouse.phone.mobile);
                addPhone(phone_numbers, doc.contacts.guarantor.phone.home);
                addPhone(phone_numbers, doc.contacts.guarantor.phone.mobile);
                for (var indexOfContact = 0; indexOfContact < 5; indexOfContact++) {
                    addPhone(phone_numbers, doc.contacts.other[indexOfContact].phone);
                }

                addDocument(insert_docs, doc.id, phone_numbers);
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
