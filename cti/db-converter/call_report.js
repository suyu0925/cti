var MongoClient = require('mongodb').MongoClient;

// Connection URL
var mongoUrl = 'mongodb://localhost:27017/report';

var insert_docs = [
	{
		date: "2015-05-15",
		loss_count: "31",
		connect_count: "803",
		call_count: "2512",
		case_count: "1318",
	}
];
	
MongoClient.connect(mongoUrl, function (err, db) {
    var collection = db.collection('call');
    collection.insertMany(insert_docs, function (err, result) {
        db.close();
        console.log("job done");
    });
});