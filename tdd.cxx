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
  PegSolitaireTest() {}

  void SetUp() override
  {
    auto val = getRandom(0,20);
    randomBoard = std::make_unique<PegSolitaire>(val,val);
    boardArea = randomBoard->getColumnSize()*randomBoard->getRowSize();
    typedBoard = std::make_unique<PegSolitaire>(boardType = getRandom(1,5));
  }

  void TearDown() override 
  {
  }

  int getRandom(int min,int max)
  {
    std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<uint_least32_t> distribute(min,max);
    return distribute(generator);
  }

  std::unique_ptr<PegSolitaire> randomBoard;
  std::unique_ptr<PegSolitaire> typedBoard;
  int boardArea = 0;
  int boardType;
};

class PegSolitaireBoardTypeTest : public ::testing::Test
{
protected:
  PegSolitaireBoardTypeTest(int boardType) : boardType{boardType} {}
  
  void SetUp() override
  {
    board = std::make_unique<PegSolitaire>(boardType);
  }

  std::unique_ptr<PegSolitaire> board;
  int boardType;
};

TEST(PegSolitaire,adjustBoardSizeIfNeeded)
{
  PegSolitaire board{0,0};
  ASSERT_TRUE(board.getColumnSize() > 5) << "Board row size should bigger than 5";
  ASSERT_TRUE(board.getRowSize() > 5) << "Board column size should bigger than 5";
}

TEST_F(PegSolitaireTest,numberOfPegs)
{
  EXPECT_FALSE(randomBoard->getNumberOfPegs() == boardArea);
  EXPECT_FALSE(randomBoard->getNumberOfPegs() == boardArea-5);
  EXPECT_EQ(randomBoard->getNumberOfPegs(),boardArea-1);
}

TEST_F(PegSolitaireTest,numberOfEmptyCells)
{
  EXPECT_FALSE(randomBoard->getNumberOfEmptyCells() == 0);
  EXPECT_FALSE(randomBoard->getNumberOfEmptyCells() == boardArea);
  EXPECT_FALSE(randomBoard->getNumberOfEmptyCells() == boardArea-1);
  ASSERT_EQ(randomBoard->getNumberOfEmptyCells(),1) << randomBoard->getNumberOfEmptyCells() << "Board 1 tane empty cell ile baslamali";
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
  ASSERT_EQ(randomBoard->getColumnSize(),randomBoard->getRowSize());
  EXPECT_TRUE(randomBoard->getColumnSize() > 0);
  EXPECT_TRUE(randomBoard->getRowSize() > 0);
  EXPECT_TRUE(randomBoard->getColumnSize() < 20);
  EXPECT_TRUE(randomBoard->getRowSize() < 20);
}

TEST_F(PegSolitaireTest,numberOfPegsTakenOut)
{
  EXPECT_EQ(randomBoard->getNumberOfPegsTakenOut(),0);
}

TEST_F(PegSolitaireTest,display)
{
  ASSERT_NO_THROW(randomBoard->displayBoard());
}

TEST_F(PegSolitaireTest,boardImageToString)
{
  ASSERT_EQ(typedBoard->converBoardToString(),typedBoard->getBoardImage(boardType));
}