const fs = require('fs'),
	http = require('http'),
	socketio = require('socket.io')

const readFile = file => new Promise((resolve, reject) => 
	fs.readFile(file, (err, data) => err ? reject(err) : resolve(data)))

const server = http.createServer(async (request, response) => {
	try
	{
		response.end(await readFile(request.url.substr(1)))
	}
	catch (err)
	{
		response.end()
	}
})

let clients = []

const io = socketio(server)

io.sockets.on('connection', socket => {
	clients = [...clients, socket]
	socket.on('disconnect', () => clients = clients.filter(s => s !== socket))
	socket.on('to_server', data => clients.forEach(s => s.emit('to_client', data)))
})

server.listen(8000)