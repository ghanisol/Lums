const fs = require('fs'),
	http = require('http'),
	socketio = require('socket.io'),
	mongo = require('mongodb').MongoClient

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

let players = {}
let boards = {}
let waiting = null
let gameId = 0 

let url = 'mongodb://localhost:27017/reversi'
mongo.connect(url, (err, db) => {

	let collection = db.collection('players')
	collection.find().toArray((err, data) => {
		for (let player of data)
		{
			Object.assign(players, player.content)	
		}
		
	})

	collection = db.collection('boards')
	collection.find().toArray((err, data) => {
		for (let board of data)
		{
			Object.assign(boards, board.content)	
		}
	})
	
	collection = db.collection('gameInfo')
	collection.find().toArray((err, data) => {
		let info = {waiting : null, gameId : 0}
		for (let d of data)
		{
			Object.assign(info, d.content)	
		}
		waiting = info.waiting
		gameId = info.gameId


	})

	db.close();


});

const io = socketio(server)

const isCell = (row, col) => row>=0 && row<=7 && col>=0 && col<=7 

const isValid = (row, col, board, disk, op_disk) => {
	
	let deltas = [[-1, -1], [-1, 0], [-1, 1], [0, -1], [0, 1], [1, -1], [1, 0], [1, 1]]
	let toFlip = []

	if (board[row][col] !== '-') return toFlip

	board[row][col] = disk

	for (let [xd,yd] of deltas)
	{

		let r = row + xd
		let c = col + yd
		
		if (isCell(r, c) && board[r][c] === op_disk)
		{
			r += xd
			c += yd

			while (isCell(r,c) && board[r][c] === op_disk)
			{
				r += xd
				c += yd
			}

			if (isCell(r,c) && board[r][c] === disk)
			{
				while (r !== row || c !== col)
				{
					r -= xd
					c -= yd
					toFlip.push([r,c])
				}
			}
		}
	}

	board[row][col] = '-'
	return toFlip
}

const makeBoard = () => {
	let board = []
	for (let i=0; i<8; i++)
	{
		board[i] = []
		for (let j=0; j<8; j++)
		{
			board[i][j] = '-'
		}
	}
	board[3][3] = 'O'
	board[3][4] = 'X'
	board[4][3] = 'X'
	board[4][4] = 'O'
	return board
}

io.sockets.on('connection', socket => {


	socket.emit('getUser')

	socket.on('userReg', user => {
		socket.user = user
		if (players[socket.user] === undefined)
		{
			players[socket.user] = gameId
			let temp = {}
			temp[user] = players[socket.user]
			insertData(temp, 'players')
			socket.join(players[socket.user])
			
			if (!waiting)
			{
				waiting = socket
				insertData({waiting : waiting}, 'gameInfo')
				socket.emit('setDisk', 'X')	
				socket.emit('wait')
			}
			else
			{
				socket.emit('setDisk', 'O')
				boards[players[socket.user]] = makeBoard()
				let temp = {}
				temp[players[socket.user]] = boards[players[socket.user]]
				insertData(temp, 'boards')
				io.to(players[socket.user]).emit('playGame', boards[players[socket.user]])
				waiting = null
				gameId++
				insertData({gameId : gameId, waiting : null}, 'gameInfo')
			}

		}
		else
		{
			socket.join(players[socket.user])
			io.to(players[socket.user]).emit('resume', boards[players[socket.user]])
		}
		
	})

	
	socket.on('disconnect', () => {
		if (waiting === socket)
		{
			waiting = null
			insertData({waiting : null}, 'gameInfo')
				
		} 
		io.sockets.in(players[socket.user]).emit('playerLeft')

		let temp = {}
		temp[socket.user] = players[socket.user]
		removeData(temp, 'players')
		temp = {}
		temp[players[socket.user]] = boards[players[socket.user]]

		removeData(temp, 'boards')
		delete boards[players[socket.user]]
		delete players[socket.user]

	})

	socket.on('updateBoard', (row, col, currentPlayer) => {
		let toFlip = isValid(row, col, boards[players[socket.user]], currentPlayer, (currentPlayer === 'X') ? 'O' : 'X')
		if (toFlip.length)
		{
			for (let cell of toFlip)
			{
				boards[players[socket.user]][cell[0]][cell[1]] = currentPlayer
			} 	
			io.sockets.in(players[socket.user]).emit('updateBoard', boards[players[socket.user]], currentPlayer)
			let temp = {}
			temp[players[socket.user]] = boards[players[socket.user]]
			insertData(temp, 'boards')
		}
		
	})

	socket.on('noValidMoves', currentPlayer => 
		io.sockets.in(players[socket.user]).emit('noValidMoves', currentPlayer))

	socket.on('gameEnd', () => 
		io.sockets.in(players[socket.user]).emit('gameEnd'))
})

server.listen(4444)

const insertData = (data, table) => {

	mongo.connect(url, (err, db) => {

		let collection = db.collection(table)
		collection.insert({content : data})

		db.close();
	});
}

const removeData = (data, table) => {

	mongo.connect(url, (err, db) => {

		let collection = db.collection(table)
		collection.remove({content : data})
	
		db.close();
	});
}
