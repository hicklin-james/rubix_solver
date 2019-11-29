#pragma once

// System headers
#include <array>
// Local headers
#include "util.h"

class CubeFace
{
  private:
    FaceOrientation currentOrientation;
    std::array<std::array<FaceColor,3>,3> squares;

  public:
  	CubeFace(FaceOrientation orientation, std::array<std::array<FaceColor,3>,3> squares);
    void printFace() const;
    void setOrientation(FaceOrientation newOrientation);
    void rotateFaceClockwise();
    void rotateFaceAntiClockwise();
};