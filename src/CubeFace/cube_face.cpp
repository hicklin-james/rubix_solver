#include "cube_face.h"
#include <iostream>

CubeFace::CubeFace(std::array<std::array<FaceColor,3>,3> squares) : squares(squares) {}

void CubeFace::printFace() {
  for(const auto& fca : squares) {
    for(const auto& fc : fca) {
      std::cout << fc;
    }
  }
  std::cout << std::endl;
}