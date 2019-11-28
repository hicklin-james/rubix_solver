#include "cube_face.h"
#include <iostream>
#include "enum2Str.hpp"
#include <iomanip>


CubeFace::CubeFace(std::array<std::array<FaceColor,3>,3> squares) : squares(squares) {}

void CubeFace::printFace() {
  for(const auto& fca : squares) {
    if (!fca.empty()) {
      auto item = fca.begin();
      std::cout << EnumUtils::enum2Str::toStr(*item);
      while(fca.cend() != ++item) {
        std::cout << " " << EnumUtils::enum2Str::toStr(*item);
      }
    }
    std::cout << std::endl;
  }
}