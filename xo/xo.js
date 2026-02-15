// game variables
const arrBoardBlock = document.querySelectorAll(".board-block");

function gameData(){
  let gameBoard = {}
  let count = 1;
  while (count<=9){
    gameBoard[count] = {played:false, block:null, contains:null, drawn:null};
    count++;
  }
  let idx = 1;
  arrBoardBlock.forEach((block) => {
    gameBoard[idx].block = block;
    idx++;
  });
  return gameBoard
}
const gameBoard = gameData()
// gameBoard data format = {[bool, blockWithClass, [O or X], place or placed], ...}

let currentPlayer = "naught";
let playTurn  = 0;
let winningRow = null;
let gameOver = false;
// -X-

// game functions
// observations by me 
// not taking any overlapping inputs
// has condition checks if already block occupied or not

function detectClick() {
  arrBoardBlock.forEach((block, idx) => {
    // event listner
    block.addEventListener("click", ()=>{
      gameBoard[idx+1][0] = true;
      if (!(gameBoard[idx+1].contains === "cross" || gameBoard[idx+1].contains === "naught")){
          gameBoard[idx+1].contains = currentPlayer;
          gameBoard[idx+1].todraw = true;
          playTurn = playTurn + 1;
      }
    });
    // event listerner
  });
  // loop end
}

function changePlayer() {
  if(playTurn % 2 === 0){
    currentPlayer = "naught";
  }
  else{
    currentPlayer = "cross";
  }
}

function checkForWinner() {
  if (playTurn<5){return}
  winningRow = getWinningRow();
  if (winningRow == null){return}
  gameOver = true;
}

function getWinningRow() {
  let board = ["", "", ""]
  let position = 0;
  let row = -1; // not zero because of 0 % 3 is zero
  const naughtPattern = "OOO";
  const crossPattern = "XXX";
  for (const key in gameBoard){
    if (position % 3 === 0){
      row = row + 1;
    }
    if (gameBoard[key].contains === "cross"){
      board[row] = board[row] + "X";
    }
    else if (gameBoard[key].contains === "naught"){
      board[row] = board[row] + "O";
    }else {
      board[row] = board[row] + " ";
    }
    position++;
  }
  if (board[0] === crossPattern || board[0] === naughtPattern){
    return [1, 2, 3]
  }
  else if (board[1] === crossPattern || board[1] === naughtPattern){
    return [4, 5, 6]
  }
  else if (board[2] === crossPattern || board[2] === naughtPattern){
    return [7, 8, 9]
  }
  else if (board[0][0]+board[1][0]+board[2][0] === crossPattern || board[0][0]+board[1][0]+board[2][0] === naughtPattern){
    return [1, 4, 7]
  }
  else if (board[0][1]+board[1][1]+board[2][1] === crossPattern || board[0][1]+board[1][1]+board[2][1] === naughtPattern){
    return [2, 5, 8]
  }
  else if (board[0][2]+board[1][2]+board[2][2] === crossPattern || board[0][2]+board[1][2]+board[2][2] === naughtPattern){
    return [3, 6, 9]
  }
  else if (board[0][0]+board[1][1]+board[2][2] === crossPattern || board[0][0]+board[1][1]+board[2][2] === naughtPattern){
    return [1, 5, 9]
  }
  else if (board[0][2]+board[1][1]+board[2][0] === crossPattern || board[0][2]+board[1][1]+board[2][0] === naughtPattern){
    return [3, 5, 7]
  }
  return null
}

function processGame() {
  detectClick();// detects and updates gameBoard obj
  checkForWinner();
  if (!gameOver){
    changePlayer();
  }
}

function renderNaught(blockArea) {
  const naught = document.createElement("div");
  naught.classList.add("naught");
  const outerNaught = document.createElement("div");
  const innerNaught = document.createElement("div");
  
  outerNaught.appendChild(innerNaught);
  naught.appendChild(outerNaught);
  
  blockArea.appendChild(naught);
}

function renderCross(blockArea){
  const lhs = document.createElement("div");
  const rhs = document.createElement("div");

  blockArea.appendChild(lhs);
  blockArea.appendChild(rhs);
  blockArea.classList.add("cross")
}

function exitSequence(){
  winningRow.forEach((coord) => {
    gameBoard[coord].block.classList.remove(`${currentPlayer}`)
    gameBoard[coord].block.classList.add(`win-${currentPlayer}`)
  });
}

function renderGame(){
  for(const dataKey in gameBoard){
    if (gameBoard[dataKey].todraw){
      let blockArea = gameBoard[dataKey].block;
      gameBoard[dataKey].contains === "naught" ? renderNaught(blockArea) : renderCross(blockArea);
      gameBoard[dataKey].todraw = false;
    }
  }
  if (gameOver){exitSequence()}
}

// -X-

// main gameLoop
function gameLoop(){
  processGame();
  renderGame();
  if (gameOver){return}
  
  requestAnimationFrame(gameLoop);
}
requestAnimationFrame(gameLoop);