var xlsx = require('node-xlsx');

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
	console.log(JSON.stringify(line));
}

var i = parseFloat("2000.51");
console.log("number: " + i);
i = parseFloat("a2000.51fb");
if (isNaN(i)) {
	console.log("not a number");
}
console.log("number: " + i);