#pragma once
#include <vector>

enum CellState
{
  EMPTY,
  PEG
};

class PegSolitaire
{
public:
  class Cell
  {
    public:
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
      CellState state = EMPTY;
  };

  // PegSolitaire() = default;
  PegSolitaire(int boardType);
  PegSolitaire(int row,int column);

  int getRowSize();
  int getColumnSize();
  int getNumberOfPegs();
  int getNumberOfEmptyCells();
private:
  std::vector<std::vector<Cell>> board;
  int rowSize = 0;
  int columnSize = 0;
  int numberOfPegs = rowSize*columnSize-1;
  int numberOfEmptyCells = rowSize*columnSize-numberOfPegs;
};