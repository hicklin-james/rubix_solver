#include "cube_face.h"
#include <iostream>
#include "enum2Str.hpp"
#include <iomanip>

CubeFace::CubeFace() {}

CubeFace::CubeFace(FaceOrientation orientation, std::array<std::array<FaceColor,3>,3> squares)
  : currentOrientation(orientation) 
  , squares(squares) {}

/**
void CubeFace::printFace() const {
  std::cout << EnumUtils::enum2Str::toStr(currentOrientation) << std::endl;
  for(int i = 0; i < squares.size(); i++) {
    printRow(i);
    std::cout << std::endl;
  }
}
**/
  
void CubeFace::printRow(int rowIndex, std::stringstream &stringBuf) const {
  const auto fca = squares.at(rowIndex);
  if (!fca.empty()) {
    auto item = fca.begin();
    stringBuf << EnumUtils::enum2Str::toStr(*item);
    while(fca.cend() != ++item) {
      stringBuf << " " << EnumUtils::enum2Str::toStr(*item);
    }
  }
}

void CubeFace::setOrientation(FaceOrientation newOrientation) {
  currentOrientation = newOrientation;
}

void CubeFace::rotateFaceClockwise() {
  auto size = squares.size();
  for (int x = 0; x < size / 2; x++) {
    for (int y = x; y < size - x - 1; y++) {
      const auto temp = std::move(squares[x][y]);
      squares[x][y] = squares[size-1-y][x];
      squares[size-1-y][x] = squares[size-1-x][size-1-y];
      squares[size-1-x][size-1-y] = squares[y][size-1-x];
      squares[y][size-1-x] = std::move(temp);
    }
  }
}

void CubeFace::rotateFaceAntiClockwise() {
  auto size = squares.size();
  for (int x = 0; x < size / 2; x++) {
    for (int y = x; y < size - x - 1; y++) {
      const auto temp = std::move(squares[x][y]);
      squares[x][y] = squares[y][size-1-x];
      squares[y][size-1-x] = squares[size-1-x][size-1-y];
      squares[size-1-x][size-1-y] = squares[size-1-y][x];
      squares[size-1-y][x] = std::move(temp);
    }
  }
}

FaceOrientation CubeFace::getOrientation() const {
  return currentOrientation;
}

FaceColor CubeFace::getColorAtIndices(int i, int j) const {
  return squares.at(i).at(j);
}