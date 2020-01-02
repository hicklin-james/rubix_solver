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
    /** void printFace() const; **/
    void printRow(int rowIndex, std::ostream &stringBuf) const;
    void setOrientation(FaceOrientation newOrientation);
    FaceOrientation getOrientation() const;
    FaceColor getColorAtIndices(int i, int j) const;
    void rotateFaceClockwise();
    void rotateFaceAntiClockwise();
};