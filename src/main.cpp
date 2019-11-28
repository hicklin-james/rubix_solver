#include "Util/util.h"
#include "CubeFace/cube_face.h"
#include <array>

int main()
{
  std::array<std::array<FaceColor,3>,3> squares{ std::array<FaceColor, 3>{FaceColor::white,FaceColor::green,FaceColor::blue},
                                                 std::array<FaceColor, 3>{FaceColor::white,FaceColor::green,FaceColor::yellow},
                                                 std::array<FaceColor, 3>{FaceColor::white,FaceColor::green,FaceColor::yellow} };
  CubeFace cf(squares);
  cf.printFace();
  return 0;
}