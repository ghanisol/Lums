"use strict"

const fs = require('fs')
const path = require('path')

function copyAll(srcFiles, dest, callback)
{
	console.log('	Entering copyAll')
	let count = srcFiles.length
	// BAD : for (let i=0; i<srcFiles.length; ++i) {
	// OK : for (const filename of srcFiles) {
	srcFiles.forEach(filename => {
		console.log(`	Initiating to read ${filename}`)
		fs.readFile(filename, (readErr, filedata) => {
			console.log('Got called from readFile completion event')
			if (readErr)
			{
				console.log(`	Reading ${filename} ${readErr}`)
				--count || callback()
			}
			else
			{
				console.log(`	${filename} read, initiating write`)
				const destfile = path.join(dest, filename)
				fs.writeFile(destfile, filedata, writeErr => {
					console.log('Got called from writeFile completion event')
					if (writeErr)
					{
						console.log(`	Writing ${destfile} ${writeErr}`)
					}
					else
					{
						console.log(`	${destfile} written, count=${count}`)
					}
					--count || callback()
					console.log('	Return to event loop')
				})
			}
			console.log('	Return to event loop')
		})
	})
	console.log('	Leaving copyAll')
}

console.log('Starting main program')
copyAll(['a.txt', 'b.txt', 'c.txt'], 'test', () => console.log('	All Done'))
console.log('	Ending main program, going in to event loop')