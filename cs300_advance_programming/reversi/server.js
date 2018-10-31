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

let players = {}
let boards = {}
let waiting = null
let gameId = 0 

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
	
	players[socket.id] = gameId
	socket.join(players[socket.id])
	
	if (!waiting)
	{
		waiting = socket
		socket.emit('setDisk', 'X')	
		socket.emit('wait')
	}
	else
	{
		socket.emit('setDisk', 'O')
		boards[players[socket.id]] = makeBoard()
		io.to(players[socket.id]).emit('playGame')
		waiting = null
		gameId++
	}

	socket.on('disconnect', () => {
		if (waiting === socket) waiting = null
		io.sockets.in(players[socket.id]).emit('playerLeft')
		delete players[socket.id]
	})

	socket.on('updateBoard', (row, col, currentPlayer) => {
		let toFlip = isValid(row, col, boards[players[socket.id]], currentPlayer, (currentPlayer === 'X') ? 'O' : 'X')
		if (toFlip.length)
		{
			for (let cell of toFlip)
			{
				boards[players[socket.id]][cell[0]][cell[1]] = currentPlayer
			} 	
			io.sockets.in(players[socket.id]).emit('updateBoard', boards[players[socket.id]], currentPlayer)
		}
		
	})

	socket.on('noValidMoves', currentPlayer => 
		io.sockets.in(players[socket.id]).emit('noValidMoves', currentPlayer))

	socket.on('gameEnd', () => 
		io.sockets.in(players[socket.id]).emit('gameEnd'))
})

server.listen(4444)