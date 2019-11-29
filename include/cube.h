#pragma once

// Local headers
#include "cube_face.h"
// System headers
#include <array>

class Cube
{
  private:
    std::array<CubeFace, 6> cubeState;

  public:
    Cube(std::array<CubeFace, 6> faces);

    void printCube() const;

    // These functions rotate the entire cube, which means the
    // F, R, L, U, D, and B faces change
    void rotateClockwise(); // [] <--
    void rotateAntiClockwise(); // [] -->
    void rotateOver() // [] ^
    void rotateUnder() // [] v
};