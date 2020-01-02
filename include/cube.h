#pragma once

// Local headers
#include "cube_face.h"
#include "util.h"

// System headers
#include <array>
#include <vector>
#include <string>

class Cube
{
  private:
    std::array<CubeFace, 6> cubeState;
    std::vector<std::string> moveHistory;

  public:
    Cube(std::array<CubeFace, 6> faces);

    void printCube() const;
    void printMoveHistory() const;
    std::array<CubeFace, 6>::const_iterator roBegin();
    std::array<CubeFace, 6>::const_iterator roEnd();

    FaceColor getColorAtFaceAndLocation(FaceOrientation orientation, int i, int j);
    const CubeFace getFaceAtOrientation(FaceOrientation orientation);

    // These functions rotate the entire cube, which means the
    // F, R, L, U, D, and B faces change
    void rotateCubeClockwise();
    void rotateCubeAntiClockwise();
    void rotateCubeUp();
    void rotateCubeDown();
    void rotateCubeLeft();
    void rotateCubeRight();

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