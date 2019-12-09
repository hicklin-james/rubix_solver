#pragma once

// System headers
#include <array>
// Local headers
#include "util.h"

class CubeFace
{
  private:
    FaceOrientation currentOrientation;

  public:
    std::array<std::array<FaceColor,3>,3> squares;
    
    CubeFace();
    CubeFace(FaceOrientation orientation, std::array<std::array<FaceColor,3>,3> squares);
    void printFace() const;
    void printRow(int rowIndex) const;
    void setOrientation(FaceOrientation newOrientation);
    void rotateFaceClockwise();
    void rotateFaceAntiClockwise();
};