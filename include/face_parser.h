#pragma once

// Local headers
#include "cube_face.h"
// System headers
#include <string>

class FaceParser
{
  public:
    static int parseFaceFromString(CubeFace &face, std::string inputStr, FaceOrientation orientation);

};