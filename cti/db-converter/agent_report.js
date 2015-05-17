var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://kivvitek.com:27017/report';

var insert_docs = [
	{
		user_name: "马春花",
		user_id: "1",
		user_ext_number: "803",
		login_duration: "537",
		phone_count: "83",
		phone_duration: "462"
	}
];
	
MongoClient.connect(mongoUrl, function (err, db) {
    var collection = db.collection('agent');
    collection.insertMany(insert_docs, function (err, result) {
        db.close();
        console.log("job done");
    });
});