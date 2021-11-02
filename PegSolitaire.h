#pragma once

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
      Cell(int row,char column) : row{row}, column{column}{};
      void setRow(int row);
      void setColumn(int column);
    private:
      int row;
      char column;
      CellState state = EMPTY;
  };

private:
};