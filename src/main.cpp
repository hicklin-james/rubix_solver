#include "util.h"
#include "cube.h"
#include <array>
#include <iostream>

int main()
{
  std::array<std::array<FaceColor,3>,3> frontFace{ 
    std::array<FaceColor, 3>{FaceColor::R,FaceColor::G,FaceColor::G},
    std::array<FaceColor, 3>{FaceColor::Y,FaceColor::G,FaceColor::O},
    std::array<FaceColor, 3>{FaceColor::Y,FaceColor::W,FaceColor::R} 
  };
  std::array<std::array<FaceColor,3>,3> leftFace{ 
    std::array<FaceColor, 3>{FaceColor::O,FaceColor::G,FaceColor::W},
    std::array<FaceColor, 3>{FaceColor::R,FaceColor::O,FaceColor::O},
    std::array<FaceColor, 3>{FaceColor::B,FaceColor::R,FaceColor::B} 
  };
  std::array<std::array<FaceColor,3>,3> rightFace{ 
    std::array<FaceColor, 3>{FaceColor::R,FaceColor::R,FaceColor::G},
    std::array<FaceColor, 3>{FaceColor::B,FaceColor::R,FaceColor::R},
    std::array<FaceColor, 3>{FaceColor::Y,FaceColor::Y,FaceColor::O} 
  };
  std::array<std::array<FaceColor,3>,3> bottomFace{ 
    std::array<FaceColor, 3>{FaceColor::R,FaceColor::O,FaceColor::G},
    std::array<FaceColor, 3>{FaceColor::Y,FaceColor::Y,FaceColor::G},
    std::array<FaceColor, 3>{FaceColor::O,FaceColor::B,FaceColor::W} 
  };
  std::array<std::array<FaceColor,3>,3> topFace{
    std::array<FaceColor, 3>{FaceColor::G,FaceColor::B,FaceColor::Y},
    std::array<FaceColor, 3>{FaceColor::W,FaceColor::W,FaceColor::B},
    std::array<FaceColor, 3>{FaceColor::B,FaceColor::O,FaceColor::W} 
  };
  std::array<std::array<FaceColor,3>,3> backFace{ 
    std::array<FaceColor, 3>{FaceColor::O,FaceColor::Y,FaceColor::W},
    std::array<FaceColor, 3>{FaceColor::W,FaceColor::B,FaceColor::G},
    std::array<FaceColor, 3>{FaceColor::B,FaceColor::W,FaceColor::Y} 
  };

  CubeFace front(FaceOrientation::FR, frontFace);
  CubeFace left(FaceOrientation::LE, leftFace);
  CubeFace right(FaceOrientation::RI, rightFace);
  CubeFace bottom(FaceOrientation::DO, bottomFace);
  CubeFace top(FaceOrientation::UP, topFace);
  CubeFace back(FaceOrientation::BA, backFace);

  Cube cube(std::array<CubeFace, 6>{front, left, right, bottom, top, back});
  cube.printCube();
  cube.rotateClockwise();
  cube.rotateClockwise();
  cube.rotateClockwise();
  cube.rotateClockwise();

  std::cout << std::endl;
  cube.printCube();

  return 0;
}