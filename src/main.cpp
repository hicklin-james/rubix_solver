#include "util.h"
#include "cube_face.h"
#include <array>

int main()
{
  std::array<std::array<FaceColor,3>,3> squares{ std::array<FaceColor, 3>{FaceColor::W,FaceColor::G,FaceColor::B},
                                                 std::array<FaceColor, 3>{FaceColor::W,FaceColor::G,FaceColor::Y},
                                                 std::array<FaceColor, 3>{FaceColor::W,FaceColor::G,FaceColor::Y} };
  CubeFace cf(squares);
  cf.printFace();
  return 0;
}