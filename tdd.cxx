#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "PegSolitaire.h"

using namespace testing;

TEST(pegCell,defaultCtor)
{
  PegSolitaire::Cell cell{};
  EXPECT_FALSE(cell.getRow());
  EXPECT_FALSE(cell.getColumn());
  EXPECT_EQ(cell.getState(),EMPTY);
}

TEST(pegCell,setRow)
{
  PegSolitaire::Cell cell{};
  cell.setRow(1);
  EXPECT_EQ(cell.getRow(),1);
}

TEST(pegCell,setColumn)
{
  PegSolitaire::Cell cell{};
  cell.setColumn('b');
  EXPECT_EQ(cell.getColumn(),'b');
}

TEST(pegCell,setState)
{
  PegSolitaire::Cell cell{};
  cell.setState(PEG);
  EXPECT_EQ(cell.getState(),PEG);
}

TEST(PegSolitaire,boardCtor)
{
  PegSolitaire board{1};
}