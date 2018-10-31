"use strict"

const fs = require('fs')
const path = require('path')

const readFile = file => new Promise( (resolve, reject) => 
	fs.readFile(file, (err, data) => err ? reject(err) : resolve(data)))

const writeFile = (file, data) => new Promise((resolve, reject) =>
	fs.writeFile(file, data, err => err ? reject(err) : resolve()))

const copyAll_promises = (srcFiles, dest) =>	// catch and ignore errors
	Promise.all(srcFiles.map(filename =>
		readFile(filename).then(filedata => {
			console.log(`${filename} read, initiating write`)
			return writeFile(path.join(dest, filename), filedata)
		}).then(() => console.log(`${filename} written`)
		).catch(err => console.log(`Reading/Writing ${filename} ${err}`))))

const copyAll_await = (srcFiles, dest) =>	// rejected promises become exceptions
	Promise.all(srcFiles.map(async filename => {
		try 
		{
			const filedata = await readFile(filename)
			console.log(`${filename} read, initiating write`)
			await writeFile(path.join(dest, filename), filedata)
			console.log(`${filename} written`)
		}
		catch (err)
		{
			console.log(`Reading/writing ${filename} ${err}`)
		}
	}))

const copyAll_nochk = (srcFiles, dest) =>	// Promise.all rejected at the first error
	Promise.all(srcFiles.map(async filename =>
		writeFile(path.join(dest, filename), await readFile(filename))))

copyAll_nochk(['a.txt', 'b.txt', 'c.txt'], 'test')
.then(() => console.log('All Done'))
.catch(err => console.log(err))
