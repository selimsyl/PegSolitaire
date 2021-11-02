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
  PegSolitaire() = default;
  PegSolitaire(int);

private:
  std::vector<std::vector<Cell>> board;
};