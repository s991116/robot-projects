#include <gtest/gtest.h>
#include <Position.h>

TEST(Position_Image_Position, Image_Position)
{
  int width = 100;
  int height = 50;
  int x = 50;
  int y = 25;
  
  Position* sut = new Position();
  sut->SetImagePosition(x, y, width, height);
  
  int resultX = sut->GetImageX();
  int resultY = sut->GetImageY();
  
  ASSERT_EQ(x, resultX);
  ASSERT_EQ(y, resultY);
}

TEST(Position_Image_Position, Norm_Position)
{
  int width = 100;
  int height = 50;
  int x = 100;
  int y = 50;
  
  float expectedNormX = 1;
  float expectedNormY = -1;
  
  Position* sut = new Position();
  sut->SetImagePosition(x, y, width, height);
  
  float resultX = sut->GetNormalizedX();
  float resultY = sut->GetNormalizedY();
  
  ASSERT_EQ(expectedNormX, resultX);
  ASSERT_EQ(expectedNormY, resultY);
}

TEST(Position_Norm_Position, Norm_Position)
{
  int width = 100;
  int height = 50;
  float normX = 0.25;
  float normY = -1;

  Position* sut = new Position();
  sut->SetNormalizedPosition(normX, normY, width, height);

  float resultX = sut->GetNormalizedX();
  float resultY = sut->GetNormalizedY();

  ASSERT_EQ(normX, resultX);
  ASSERT_EQ(normY, resultY);
}

TEST(Position_Norm_Position, Image_Position)
{
  int width = 100;
  int height = 50;
  float normX = 0.5;
  float normY = 1;

  int expectedX = 75;
  int expectedY = 0;

  Position* sut = new Position();
  sut->SetNormalizedPosition(normX, normY, width, height);

  int resultX = sut->GetImageX();
  int resultY = sut->GetImageY();

  ASSERT_EQ(expectedX, resultX);
  ASSERT_EQ(expectedY, resultY);
}
