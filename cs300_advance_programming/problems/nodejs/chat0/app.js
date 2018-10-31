const nodeStatic = require('node-static')
const http = require('http')
const socketIO = require('socket.io')

const file = new nodeStatic.Server( './', {	// ./ -> folder containing all our html files e.t.c
	cache:0,	// don't cache
	gzip:true	// gzip our assets
})

const server = http.createServer( (request, response) => { 
	request.addListener( 'end', () =>
		file.serve(request, response))
	request.resume()
}).listen(4000)

const sio = socketIO()
sio.serveClient(true)	// the server will serve the client js file
sio.attach(server)

// listen for a connection
sio.on( 'connection', socket => {
	console.log(`User ${socket.id} connected`)
	socket.emit('greetings', 'Hello from the server!', socket.id)

	// listen for the message event
	socket.on('message', msg => {
		console.log(`User ${socket.id} sent a message : ${msg}`)
	})

	// sending message to everyone in a namespace
	socket.on('tellEveryone', msg => {
		sio.emit('heyEveryone', msg, socket.id)

		// Following 3 calls all do the same thing
/*		sio.emit('heyEveryone', msg, socket.id)
		sio.socket.emit('heyEveryone', msg, socket.id)	// sio.sockets is a reference to the main "/" namespace
		sio.of('/').emit('heyEveryone', msg, socket.id)	// of( '/' ) is how we reference a namespace, in this case the main "/" one*/
	})

	// work around for users on one namespace sending messages to another namespace
	socket.on('tellNamespace', (msg, namespaceName) => {
		sio.of(namespaceName).emit('heyEveryone', msg, socket.id );	// NOTE: namespace will be created if it doesn't exist
	})

	// sending message to everyone in a room
	// you don't need to be a member of a room to send a message to a room.
	socket.on('tellRoom', (msg, roomName) => {
		// could use 'in' instead of 'to'
		socket.to(roomName).emit('heyThere', msg, socket.id)	// NOTE: room will be created if it doesn't exist
	})

	// sending message to multiple rooms
	socket.on('tellRooms', (msg, room1Name, room2Name) => {
		socket.to(room1Name).to(room2Name).emit('heyThere', msg, socket.id)
	})

	// sending message to everyone except yourself
	// use socket.to(roomName <- passed as a parameter).broadcast.emit(...) to send the message to a room
	socket.on('broadcastMsg', msg => {
		socket.broadcast.emit('broadcastFrom', msg, socket.id)
	})

	// sending message to another user
	socket.on('sendToUser', (msg, userID) => {
		const otherSocket = sio.sockets.connected[userID]
		if (otherSocket)
			otherSocket.emit('messageFromUser', msg, userID)
	})
	// The first thing a connected user does is to join a room with the same name as it's id
	// so, the following could also be done to send a message to another user.
	/*socket.on('sendToUser', (msg, userID) => {
		socket.to(userID).emit('messageFromUser', msg, userID)
	})*/

	// getting id's of connected users
	const sidsInNamespace = keys(sio.sockets.connected)	// users in a particular namespace, socket = default '/' namespace
	const socketsInRoom = sio.sockets.adapter.rooms[roomName]
	const sidsInRoom = (socketsInRoom) ? keys(socketsInRoom) : []

	// could maintain a dictionary of usernames along with the socket ids



});



// custom namespace
var nsp = sio.of('/news')
nsp.on('connection', socket => {
	console.log('someone connected')
})
nsp.emit('hi', 'everyone')

// joining room
io.on('connection', socket => {
	socket.join('some room')
})
// sending msg to that room
io.to('some room').emit('some event')