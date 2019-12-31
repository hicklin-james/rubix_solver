#include "cross.h"
#include "util.h"
#include "cube_face.h"
#include "enum2Str.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

Cross::Cross(Cube &cube) : Step(cube) {}

bool Cross::reachedGoal() {
  return false;
}

FaceColor Cross::getAdjacentFaceColor(FaceOrientation orientation, int i, int j) {
  switch(orientation) {
    case FaceOrientation::FR:
      if (i == 0 && j == 1) {
        return 
      }
      break;
    case FaceOrientation::LE:
      break;
    case FaceOrientation::RI: 
      break;
    case FaceOrientation::BA:
      break;
    case FaceOrientation::DO:
      break;
    case FaceOrientation::UP:
      break; 
  }
}

void Cross::repositionWhiteCrossMidPiece(const CubeFace &face, int sj) {
  switch(face.getOrientation()) {
    case FaceOrientation::FR:
      if (sj == 0) {
        cube.l();
      } else {
        cube.ri();
      }

      break;
    case FaceOrientation::LE:
      break;
    case FaceOrientation::RI: 
      break;
    case FaceOrientation::BA:
      break;
    case FaceOrientation::DO:
      break;
    case FaceOrientation::UP:
      break;
  }
}

void Cross::repositionWhiteCrossPiece(const CubeFace &face, int si, int sj) {
  switch(si) {
    case 0:

      break;
    case 1:
      repositionWhiteCrossMidPiece(si, sj);
      break;

    case 2:

      break;
  }
}

void Cross::reorientWhiteFaceToTop() {
  auto whiteFaceOrientation = findWhiteCenter();
  spdlog::info("White center is on face <" + EnumUtils::enum2Str::toStr(whiteFaceOrientation) + ">.");
  switch(whiteFaceOrientation) {
    case FaceOrientation::FR:
      cube.rotateCubeUp();
      break;
    case FaceOrientation::LE:
      cube.rotateCubeClockwise();
      break;
    case FaceOrientation::RI: 
      cube.rotateCubeAntiClockwise();
      break;
    case FaceOrientation::BA:
      cube.rotateCubeDown();
      break;
    case FaceOrientation::DO:
      cube.rotateCubeClockwise();
      cube.rotateCubeClockwise();
      break; 
  }
}

FaceOrientation Cross::findWhiteCenter() {
  for (auto face = cube.roBegin(); face != cube.roEnd(); ++face) {
    if (face->getColorAtIndices(1, 1) == FaceColor::W) {
      return face->getOrientation();
    }
  }
}