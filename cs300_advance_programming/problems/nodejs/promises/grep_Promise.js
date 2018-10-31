"use strict"

const fs = require('fs');

const readFile = file => new Promise( (resolve, reject) =>
	fs.readFile(file, 'utf8', (err, data) => err ? reject(err) : resolve(data)))

const grep_promises = (str, srcFiles) =>
	Promise.all(srcFiles.map(filename =>
		readFile(filename).then(filedata => {
			let lines = filedata.split('\n')
			console.log(lines.filter(l => l.search(str) >= 0))
		}).catch(err => console.log(`Reading ${filename} ${err}`))))

const grep_await = (str, srcFiles) =>
	Promise.all(srcFiles.map(async filename => {
		try
		{
			const filedata = await readFile(filename)
			let lines = filedata.split('\n')
			console.log(lines.filter(l => l.search(str) >= 0))
		}
		catch (err)
		{
			console.log(`Reading ${filename} ${err}`)
		}
	}))

grep_promises(process.argv[2], process.argv.slice(3)).then(() => console.log('All Done'));

