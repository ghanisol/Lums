"use strict"

const fs = require('fs');

function grep(str, srcFiles, callback)
{
	let count = srcFiles.length;
	srcFiles.forEach(filename => {
		fs.readFile(filename, 'utf8', (err, data) => {	// utf8 reads file as string, no need for toString() func.
			if (err)
				return console.log(`Error while reading ${filename}`);
			let lines = data.split('\n');
			console.log(lines.filter(l => l.search(str) >= 0));
			
			--count || callback();
		});
	});
}

grep(process.argv[2], process.argv.slice(3), () => console.log('All Done'));

