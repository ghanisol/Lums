const socket = io()
let state = {}
let disk = ''
let op_disk = ''
let turn = 0
let yourScore = 0
let opScore = 0
let isDone = 0
let user = ''
let isStart = 0

const login = () => {
	ReactDOM.render(React.createElement('div', null,
		React.createElement('form', {onSubmit : submitHandler},
			React.createElement('p', null, 'Username : '),
			React.createElement('input', {
				type: 'text',
				onChange : ev => user = ev.target.value
			}),
			React.createElement('input', {
				type: 'submit',
				value: 'Start'

			})))
		, document.getElementById('root'))	
}

const submitHandler = event => {
	event.preventDefault()
	socket.emit('userReg', user)
	isStart = 1
	
}

const setState = updates => {
	Object.assign(state, updates)
	ReactDOM.render(React.createElement(Root, state), document.getElementById('root'))	
}

const Root = ({board}) => {
	let i = 0
	return React.createElement('div', {id : 'main'},
		board.map(row => React.createElement('div', {id : 'row'}, row.map(cell => 
			React.createElement('div', {
				id: i++,
				onClick: ev => onClickHandler(ev.target.id),
				onMouseOver: ev => onMouseOverHandler(ev.target.id),
				onMouseOut: ev => setState({})
			}, cell)))),
		React.createElement('p', null, `Your Disk : ${disk}`),
		React.createElement('p', null, turn ? 'Your Turn' : 'Opponent Turn'),
		React.createElement('p', null, isDone ? (yourScore > opScore) ? 'You Won' : 'You Lost' : ''))
}

const onClickHandler = cellno => {
	if (turn)
	{
		let row = Math.floor(cellno/8)
		let col = Math.floor(cellno%8)
		let toFlip = isValid(row, col)
		if (toFlip.length) socket.emit('updateBoard', row, col, disk)
	}
}

const onMouseOverHandler = cellno => {
	
	if (!turn) return
		
	let toFlip = isValid(Math.floor(cellno/8), Math.floor(cellno%8))
	
	if (!toFlip.length) return

	let nBoard = []
	for (let i=0; i<8; i++)
	{
		nBoard[i] = []
		for (let j=0; j<8; j++)
		{
			nBoard[i][j] = state.board[i][j]
		}
	}

	for (let cell of toFlip)
	{
		nBoard[cell[0]][cell[1]] = disk
	} 

	ReactDOM.render(React.createElement(Root, {board : nBoard}), document.getElementById('root'))
}

const isCell = (row, col) => row>=0 && row<=7 && col>=0 && col<=7 

const isValid = (row, col) => {
	
	let deltas = [[-1, -1], [-1, 0], [-1, 1], [0, -1], [0, 1], [1, -1], [1, 0], [1, 1]]
	let toFlip = []

	if (state.board[row][col] !== '-') return toFlip

	state.board[row][col] = disk

	for (let [xd,yd] of deltas)
	{

		let r = row + xd
		let c = col + yd
		
		if (isCell(r, c) && state.board[r][c] === op_disk)
		{
			r += xd
			c += yd

			while (isCell(r,c) && state.board[r][c] === op_disk)
			{
				r += xd
				c += yd
			}

			if (isCell(r,c) && state.board[r][c] === disk)
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

	state.board[row][col] = '-'
	return toFlip
}

const calcScore = () => {

	for (let i=0; i<8; i++)
	{
		for (let j=0; j<8; j++)
		{
			(state.board[i][j] === disk) ? yourScore++ : opScore++
		}
	}
}

const isBoardFilled = () => {

	for (let i=0; i<8; i++)
	{
		for (let j=0; j<8; j++)
		{
			if (state.board[i][j] === '-') return false
		}
	}
	return true
}

const hasValidMoves = () => {

	for (let i=0; i<8; i++)
	{
		for (let j=0; j<8; j++)
		{
			if (isValid(i,j).length > 0) return true
		}
	}

	return false
}



socket.on('playGame', (newBoard) => setState({board: newBoard}))

socket.on('getUser', () => {
	if (isStart)
		socket.emit('userReg', user)
})

socket.on('setDisk', d => {
	disk = d
	op_disk = d === 'X' ? 'O' : 'X'
	turn = d === 'X' ? 1 : 0
})

socket.on('updateBoard', (newBoard, currentPlayer) => {
	turn = disk === currentPlayer ? 0 : 1
	setState({board: newBoard})

	if (turn)
	{
		if (isBoardFilled())
			socket.emit('gameEnd')
		else if (!hasValidMoves())
			socket.emit('noValidMoves', disk)	
	}
	
})

socket.on('noValidMoves', currentPlayer => {
	turn = disk === currentPlayer ? 0 : 1
	setState({})
	if (disk !== currentPlayer)
	{
		if (!hasValidMoves()) socket.emit('gameEnd')
	}
})

socket.on('gameEnd', () => {
	turn = 0;
	isDone = 1;
	calcScore()
	setState({})
})

socket.on('wait', () => {
	ReactDOM.render(React.createElement('p', null, 'Waiting For other Player'), document.getElementById('root'))
})

socket.on('playerLeft', () => {
	ReactDOM.render(React.createElement('p', null, 'Other Player Left' ), document.getElementById('root'))	
})

socket.on('resume', (nBoard) => {
	setState({board: nBoard})
})

login()