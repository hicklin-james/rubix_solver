// local headers
#include "cube.h"
#include "cube_face.h"
#include "util.h"

Cube::Cube(std::array<CubeFace, 6> faces) : cubeState(faces) {}

void Cube::printCube() const {
  for(const auto& face : cubeState) {
    face.printFace();
  }
}

void Cube::rotateClockwise() {
  const auto tempF = std::move(cubeState[0]);
  const auto tempL = std::move(cubeState[1]);
  const auto tempB = std::move(cubeState[5]);
  const auto tempR = std::move(cubeState[2]);

  // move right to front
  cubeState[0] = std::move(tempR);
  cubeState[0].setOrientation(FaceOrientation::FR);
  // move front to left
  cubeState[1] = std::move(tempF);
  cubeState[1].setOrientation(FaceOrientation::LE);
  // move left to back
  cubeState[5] = std::move(tempL);
  cubeState[5].setOrientation(FaceOrientation::BA);
  // move back to right
  cubeState[2] = std::move(tempB);
  cubeState[2].setOrientation(FaceOrientation::RI);

  // top rotated 90 degrees clockwise
  cubeState[4].rotateFaceClockwise();

  // bottom rotated 90 degrees anticlockwise
  cubeState[3].rotateFaceAntiClockwise();
}

void Cube::rotateAntiClockwise() {
  const auto tempF = std::move(cubeState[0]);
  const auto tempL = std::move(cubeState[1]);
  const auto tempB = std::move(cubeState[5]);
  const auto tempR = std::move(cubeState[2]);

  // move front to right
  cubeState[2] = std::move(tempF);
  cubeState[2].setOrientation(FaceOrientation::RI);
  // move right to back
  cubeState[5] = std::move(tempR);
  cubeState[5].setOrientation(FaceOrientation::BA);
  // move back to left
  cubeState[1] = std::move(tempB);
  cubeState[1].setOrientation(FaceOrientation::LE);
  // move left to front
  cubeState[0] = std::move(tempL);
  cubeState[0].setOrientation(FaceOrientation::FR);

  // top rotated 90 degrees anticlockwise
  cubeState[4].rotateFaceAntiClockwise();

  // bottom rotated 90 degrees clockwise
  cubeState[3].rotateFaceClockwise();
}