var fs = require("fs")

function copyAll(srcFiles, dest, callback)
{
	count = srcFiles.length;
	srcFiles.forEach(filename => {
		fs.readFile(filename, (err, data) => {
			fs.writeFile(dest+'/'+filename, data, () => {
				--count || callback();	// || will only see the second arg when count is 0
			});
		});
	});
}

copyAll(['a.txt', 'b.txt', 'c.txt'], 'test', ()=>console.log('All Done!'));