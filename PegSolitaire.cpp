#include "PegSolitaire.h"

using BoardRow = std::vector<PegSolitaire::Cell>;


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
  
}