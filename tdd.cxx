#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "PegSolitaire.h"
#include <random>
#include <stdexcept>

using namespace testing;
using CellState = PegSolitaire::Cell::CellState;

TEST(pegCell,defaultCtor)
{
  PegSolitaire::Cell cell{};
  EXPECT_FALSE(cell.getRow());
  EXPECT_FALSE(cell.getColumn());
  EXPECT_EQ(cell.getState(),CellState::PEG);
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
  cell.setState(CellState::EMPTY);
  EXPECT_EQ(cell.getState(),CellState::EMPTY);
}

class PegSolitaireTest : public ::testing::Test
{
protected:
  PegSolitaireTest()
  {
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<uint_least32_t> distribute(0,20);
    auto val = distribute(generator);
    board = std::make_unique<PegSolitaire>(val,val);
  }
  void SetUp() override
  {
    boardArea = board->getColumnSize()*board->getRowSize();
  }

  void TearDown() override 
  {

  }

  std::unique_ptr<PegSolitaire> board;
  int boardArea = 0;
};

TEST(PegSolitaire,adjustBoardSizeIfNeeded)
{
  PegSolitaire board{0,0};
  ASSERT_TRUE(board.getColumnSize() > 5) << "Board row size should bigger than 5";
  ASSERT_TRUE(board.getRowSize() > 5) << "Board column size should bigger than 5";
}

TEST_F(PegSolitaireTest,numberOfPegs)
{
  EXPECT_FALSE(board->getNumberOfPegs() == boardArea);
  EXPECT_FALSE(board->getNumberOfPegs() == boardArea-5);
  EXPECT_EQ(board->getNumberOfPegs(),boardArea-1);
}

TEST_F(PegSolitaireTest,numberOfEmptyCells)
{
  EXPECT_FALSE(board->getNumberOfEmptyCells() == 0);
  EXPECT_FALSE(board->getNumberOfEmptyCells() == boardArea);
  EXPECT_FALSE(board->getNumberOfEmptyCells() == boardArea-1);
  ASSERT_EQ(board->getNumberOfEmptyCells(),1) << board->getNumberOfEmptyCells() << "Board 1 tane empty cell ile baslamali";
}

TEST(PegSolitaire,boardTypeCtor)
{
  std::string boardOne {"  ***  \n ***** \n*** ***\n*******\n*******\n ***** \n  ***  \n"};
  std::string boardTwo {"   ***   \n   ***   \n   ***   \n*********\n**** ****\n*********\n   ***   \n   ***   \n   ***   \n"};
  std::string boardThree {"  ***   \n  ***   \n  ***   \n********\n*** ****\n********\n  ***   \n  ***   \n  ***   \n"};
  std::string boardFour {"  ***  \n  ***  \n*******\n*** ***\n*******\n  ***  \n  ***  \n"};
  std::string boardFive {"    *    \n   ***   \n  *****  \n ******* \n**** ****\n ******* \n  *****  \n   ***   \n    *    \n"};
  PegSolitaire board{1};
}

TEST_F(PegSolitaireTest,boardSizeCtor)
{
  ASSERT_EQ(board->getColumnSize(),board->getRowSize());
  EXPECT_TRUE(board->getColumnSize() > 0);
  EXPECT_TRUE(board->getRowSize() > 0);
  EXPECT_TRUE(board->getColumnSize() < 20);
  EXPECT_TRUE(board->getRowSize() < 20);
}

TEST_F(PegSolitaireTest,numberOfPegsTakenOut)
{
  EXPECT_EQ(board->getNumberOfPegsTakenOut(),0);
}

TEST_F(PegSolitaireTest,display)
{
  ASSERT_NO_THROW(board->displayBoard());
}

TEST(PegSolitaire,BoardFromString)
{
  PegSolitaire board{2};
  std::string boardTwo {"   ***   \n   ***   \n   ***   \n*********\n**** ****\n*********\n   ***   \n   ***   \n   ***   \n"};
  ASSERT_EQ(boardTwo,board.converBoardToString());
}