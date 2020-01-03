/** Class header */
#include "cube_face.h"

/** Local headers */
#include "enum2Str.hpp"

/** System headers */
#include <iomanip>
#include <iostream>

// ------------------------------------------------------------------------- //
CubeFace::CubeFace() {}

// ------------------------------------------------------------------------- //
CubeFace::CubeFace(FaceOrientation orientation, 
                   std::array<std::array<FaceColor,3>,3> squares)
  : currentOrientation(orientation) 
  , squares(squares) {}
  
// ------------------------------------------------------------------------- //
void CubeFace::printRow(int rowIndex, std::ostream &stringBuf) const
{
  const auto fca = squares.at(rowIndex);
  if (!fca.empty()) 
  {
    auto item = fca.begin();
    stringBuf << EnumUtils::enum2Str::toStr(*item);
    while (fca.cend() != ++item) 
    {
      stringBuf << " " << EnumUtils::enum2Str::toStr(*item);
    }
  }
}

// ------------------------------------------------------------------------- //
void CubeFace::setOrientation(FaceOrientation newOrientation)
{
  currentOrientation = newOrientation;
}

// ------------------------------------------------------------------------- //
void CubeFace::rotateFaceClockwise()
{
  auto size = squares.size();
  for (int x = 0; x < size / 2; x++)
  {
    for (int y = x; y < size - x - 1; y++)
    {
      const auto temp = std::move(squares[x][y]);
      squares[x][y] = squares[size-1-y][x];
      squares[size-1-y][x] = squares[size-1-x][size-1-y];
      squares[size-1-x][size-1-y] = squares[y][size-1-x];
      squares[y][size-1-x] = std::move(temp);
    }
  }
}

// ------------------------------------------------------------------------- //
void CubeFace::rotateFaceAntiClockwise()
{
  auto size = squares.size();
  for (int x = 0; x < size / 2; x++)
  {
    for (int y = x; y < size - x - 1; y++)
    {
      const auto temp = std::move(squares[x][y]);
      squares[x][y] = squares[y][size-1-x];
      squares[y][size-1-x] = squares[size-1-x][size-1-y];
      squares[size-1-x][size-1-y] = squares[size-1-y][x];
      squares[size-1-y][x] = std::move(temp);
    }
  }
}

// ------------------------------------------------------------------------- //
FaceOrientation CubeFace::getOrientation() const
{
  return currentOrientation;
}

// ------------------------------------------------------------------------- //
FaceColor CubeFace::getColorAtIndices(int i, int j) const
{
  return squares.at(i).at(j);
}