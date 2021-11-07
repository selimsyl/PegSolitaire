#include "PegSolitaire.h"
#include <iostream>
#include <sstream>

using BoardRow = std::vector<PegSolitaire::Cell>;
using CellState = PegSolitaire::Cell::CellState;

char PegSolitaire::Cell::getColumn()
{
  return column;
}

int PegSolitaire::Cell::getRow()
{
  return row;
}

CellState PegSolitaire::Cell::getState()
{
  return state;
}

void PegSolitaire::Cell::setRow(int row)
{
  this->row = row;
}

void PegSolitaire::Cell::setColumn(char column)
{
  this->column = column;
}

void PegSolitaire::Cell::setState(CellState state)
{
  this->state = state;
}

PegSolitaire::PegSolitaire(int boardType)
{
  initBoardMap();
  createBoard(boardType);
}

PegSolitaire::PegSolitaire(int row,int column)
: rowSize{row}, columnSize{column}
{
  initBoardMap();
  createBoard();
}

auto PegSolitaire::getBoardFromString(const std::string& boardImage)
{
  decltype(board) tempBoard(1);
  int row = 0;
  char column = 'a';
  for(auto&& ch : boardImage) {
    Cell::CellState cellState{};
    switch (ch)
    {
    case '\n':
      tempBoard.push_back(std::vector<Cell>{});
      row++;
      column = 'a';
      continue;
      break;
    case '0':
    case ' ':
      cellState = Cell::EMPTY;
      break;
    case '1':
    case '*':
      cellState = Cell::PEG;
      break;
    default:
      break;
    }
    tempBoard.at(row).push_back(Cell{row,column++,cellState});
  }
  return tempBoard;
}

std::string PegSolitaire::converBoardToString()
{
  std::ostringstream boardString{};
  for (auto&& rowVec : board)
  {
    for (auto&& cell : rowVec)
    {
      switch (cell.getState())
      {
      case CellState::EMPTY :
      case CellState::NOTCELL :
        boardString << ' ';
        break;
      case CellState::PEG :
        boardString << '*';
        break;
      default:
        break;
      }
    }
    boardString << '\n';
  }
  auto retString = boardString.str();
  retString.pop_back();
  return retString;
}

void PegSolitaire::createBoard(int boardType)
{
  if (!boardType) {
    adjustBoardSizeIfNeeded();
    board = decltype(board) (rowSize,BoardRow(columnSize));
    board.at(rowSize / 2).at(columnSize / 2).setState(Cell::EMPTY);
  } else {
    auto boardImage = mapBoard.at(boardType);
    board = getBoardFromString(boardImage);
  }
  numberOfPegs = rowSize*columnSize-1;
}

int PegSolitaire::getRowSize()
{
  return rowSize;
}

int PegSolitaire::getColumnSize()
{
  return columnSize;
}

int PegSolitaire::getNumberOfPegs()
{
  return numberOfPegs;
}

int PegSolitaire::getNumberOfEmptyCells()
{
  return rowSize*columnSize - numberOfPegs;
}

int PegSolitaire::getNumberOfPegsTakenOut()
{
  return getNumberOfEmptyCells()-1;
}

void PegSolitaire::displayBoard()
{
  //print x axis bar
  std::cout << "  ";
  for (int i = 0; i < board.at(0).size(); ++i)
  {
    std::cout << static_cast<char>('a'+ i);
  }
  std::cout << "\n";

  int row = 1;
  for (auto&& rowVec : board)
  {
    std::cout << row++ << ' ';
    for (auto&& cell : rowVec)
    {
      std::cout << (cell.getState() == Cell::PEG ? '*' : ' ');      
    }
    std::cout << '\n';
  }
}

void PegSolitaire::adjustBoardSizeIfNeeded()
{
  rowSize = rowSize < minRowSize ? minRowSize : rowSize;
  columnSize = columnSize < minColumnSize ? minColumnSize : columnSize;
}

void PegSolitaire::initBoardMap()
{
  std::string boardOne {"  ***  \n ***** \n*** ***\n*******\n*******\n ***** \n  ***  \n"};
  std::string boardTwo {"   ***   \n   ***   \n   ***   \n*********\n**** ****\n*********\n   ***   \n   ***   \n   ***   \n"};
  std::string boardThree {"  ***   \n  ***   \n  ***   \n********\n*** ****\n********\n  ***   \n  ***   \n  ***   \n"};
  std::string boardFour {"  ***  \n  ***  \n*******\n*** ***\n*******\n  ***  \n  ***  \n"};
  std::string boardFive {"    *    \n   ***   \n  *****  \n ******* \n**** ****\n ******* \n  *****  \n   ***   \n    *    \n"};
  mapBoard.insert({1,boardOne});
  mapBoard.insert({2,boardTwo});
  mapBoard.insert({3,boardThree});
  mapBoard.insert({4,boardFour});
  mapBoard.insert({5,boardFive});
}