if (false) {
	var xlsx = require('node-xlsx');

	try {
		var worksheets = xlsx.parse('./debt.xlsx');
		// console.log(JSON.stringify(worksheets));
		//第一个工作表的数据
		var data = worksheets[0].data;
		// console.log(JSON.stringify(data));

		for (var i = 0; i < data.length; i++) {
			console.log("line " + i + ": ");
			var line = data[i];
			// for (var j = 0; j < line.length; j++) {
			// 	console.log(line[j] + ", ");
			// }
			console.log(JSON.stringify(line, null, 4));
		}

		var i = parseFloat("2000.51");
		console.log("number: " + i);
		i = parseFloat("a2000.51fb");
		if (isNaN(i)) {
			console.log("not a number");
		}
		console.log("number: " + i);
	}
	catch (exception) {
		console.log(exception);
	}
}

if (true) {
	var child = require('child_process').spawn;
	var fs = require('fs');
  	var xml = "";

  	var file = "test.xls";

	fs.exists(file, function(exists){
	    if (!exists) {
	    	throw new Error('file does not exist');
	    }
	    
	    xlhtml = child('soffice', ['--convert-to', 'xlsx', file, '--headless']);

	    xlhtml.stdout.on('data', function(data) {
	        xml += data;
	    });

	    xlhtml.on('exit', function() {
	        	var data = require('node-xlsx').parse('test.xlsx');
				console.log(JSON.stringify(data, null, 4));
	    });
	});
}