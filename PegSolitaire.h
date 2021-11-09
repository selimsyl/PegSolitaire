#pragma once
#include <vector>
#include <string>
#include <unordered_map>

class PegSolitaire
{
public:
  class Cell
  {
    public:
      enum CellState
      {
        EMPTY,
        PEG,
        NOTCELL,
      };

      Cell() =  default;
      Cell(int row,char column,CellState state) 
        : row{row}, column{column}, state{state}{};
      void setRow(int);
      void setColumn(char);
      void setState(CellState);
      int getRow();
      char getColumn();
      CellState getState();
    private:
      int row;
      char column;
      CellState state = PEG;
  };

  // PegSolitaire() = default;
  PegSolitaire(int boardType);
  PegSolitaire(int row,int column);
  PegSolitaire(std::string boardImage);

  int getRowSize();
  int getColumnSize();
  int getNumberOfPegs();
  int getNumberOfEmptyCells();
  int getNumberOfPegsTakenOut();
  void displayBoard();
  std::string converBoardToString();
  std::string getBoardImage(int boardType);
private:
  void initBoardMap();
  auto getBoardFromString(const std::string& boardImage);
  void createBoard(int boardType = 0);
  void adjustBoardSizeIfNeeded();

  static constexpr int minRowSize = 6;
  static constexpr int minColumnSize = minRowSize;
  std::vector<std::vector<Cell>> board;
  std::unordered_map<int,std::string> mapBoard;

  int rowSize = 0;
  int columnSize = 0;
  int numberOfPegs = 0;
  // int numberOfEmptyCells = rowSize*columnSize-numberOfPegs;
};