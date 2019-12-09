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
    void rotateCubeClockwise();
    void rotateCubeAntiClockwise();
    void rotateCubeUp();
    void rotateCubeDown();

    // These are the main rotation procedures
    void r();
    void ri();
    void l();
    void li();
    void f();
    void fi();
    void u();
    void ui();
    void d();
    void di();
    void b();
    void bi();

};