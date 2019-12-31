// local headers
#include "cube.h"
#include "cube_face.h"
#include "util.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
// system headers
#include <iostream>
#include <iomanip>
#include <string>  
#include <iostream>
#include <sstream>

Cube::Cube(std::array<CubeFace, 6> faces) : cubeState(faces) {}

std::array<CubeFace, 6>::const_iterator Cube::roBegin() {
  return cubeState.begin();
}

std::array<CubeFace, 6>::const_iterator Cube::roEnd() {
  return cubeState.end();
}

void Cube::printCube() const {
  std::stringstream stringBuf;
  stringBuf << "Current cube state:" << std::endl;
  stringBuf << std::left << std::setw(8) << "";
  cubeState[4].printRow(0, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[4].printRow(1, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[4].printRow(2, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  stringBuf << "- - -" << std::endl;

  cubeState[1].printRow(0, stringBuf);
  stringBuf << " | ";
  cubeState[0].printRow(0, stringBuf);
  stringBuf << " | ";
  cubeState[2].printRow(0, stringBuf);
  stringBuf << " | ";
  cubeState[5].printRow(0, stringBuf);
  stringBuf << std::endl;
  cubeState[1].printRow(1, stringBuf);
  stringBuf << " | ";
  cubeState[0].printRow(1, stringBuf);
  stringBuf << " | ";
  cubeState[2].printRow(1, stringBuf);
  stringBuf << " | ";
  cubeState[5].printRow(1, stringBuf);
  stringBuf << std::endl;
  cubeState[1].printRow(2, stringBuf);
  stringBuf << " | ";
  cubeState[0].printRow(2, stringBuf);
  stringBuf << " | ";
  cubeState[2].printRow(2, stringBuf);
  stringBuf << " | ";
  cubeState[5].printRow(2, stringBuf);
  stringBuf << std::endl;

  stringBuf << std::left << std::setw(8) << "";
  stringBuf << "- - -" << std::endl;
  stringBuf << std::left << std::setw(8) << "";
  cubeState[3].printRow(0, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[3].printRow(1, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[3].printRow(2, stringBuf);
  stringBuf << std::endl;

  spdlog::info(stringBuf.str());
}

void Cube::rotateCubeLeft() {
  const auto tempF = std::move(cubeState[0]);
  const auto tempL = std::move(cubeState[1]);
  const auto tempB = std::move(cubeState[5]);
  const auto tempR = std::move(cubeState[2]);

  cubeState[0] = std::move(tempR);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[1] = std::move(tempF);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[5] = std::move(tempL);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[2] = std::move(tempB);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[4].rotateFaceClockwise();
  cubeState[3].rotateFaceAntiClockwise();
}

void Cube::rotateCubeRight() {
  const auto tempF = std::move(cubeState[0]);
  const auto tempL = std::move(cubeState[1]);
  const auto tempB = std::move(cubeState[5]);
  const auto tempR = std::move(cubeState[2]);

  cubeState[2] = std::move(tempF);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[5] = std::move(tempR);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[1] = std::move(tempB);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[0] = std::move(tempL);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[4].rotateFaceAntiClockwise();
  cubeState[3].rotateFaceClockwise();
}

void Cube::rotateCubeUp() {
  const auto tempF = std::move(cubeState[0]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempD = std::move(cubeState[3]);
  const auto tempB = std::move(cubeState[5]);

  cubeState[4] = std::move(tempF);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[5] = std::move(tempU);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[5].rotateFaceClockwise();
  cubeState[5].rotateFaceClockwise();
  cubeState[3] = std::move(tempB);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[3].rotateFaceClockwise();
  cubeState[3].rotateFaceClockwise();
  cubeState[0] = std::move(tempD);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[1].rotateFaceAntiClockwise();
  cubeState[2].rotateFaceClockwise();
}

void Cube::rotateCubeDown() {
  const auto tempF = std::move(cubeState[0]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempD = std::move(cubeState[3]);
  const auto tempB = std::move(cubeState[5]);

  cubeState[3] = std::move(tempF);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[5] = std::move(tempD);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[5].rotateFaceClockwise();
  cubeState[5].rotateFaceClockwise();
  cubeState[4] = std::move(tempB);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[4].rotateFaceClockwise();
  cubeState[4].rotateFaceClockwise();
  cubeState[0] = std::move(tempU);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[1].rotateFaceClockwise();
  cubeState[2].rotateFaceAntiClockwise();
}

void Cube::rotateCubeClockwise() {
  const auto tempL = std::move(cubeState[1]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempR = std::move(cubeState[2]);
  const auto tempD = std::move(cubeState[3]);

  cubeState[2] = std::move(tempU);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[2].rotateFaceClockwise();
  cubeState[3] = std::move(tempR);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[3].rotateFaceClockwise();
  cubeState[1] = std::move(tempD);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[1].rotateFaceClockwise();
  cubeState[4] = std::move(tempL);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[4].rotateFaceClockwise();

  cubeState[0].rotateFaceClockwise();
  cubeState[5].rotateFaceAntiClockwise();
}

void Cube::rotateCubeAntiClockwise() {
  const auto tempL = std::move(cubeState[1]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempR = std::move(cubeState[2]);
  const auto tempD = std::move(cubeState[3]);

  cubeState[2] = std::move(tempD);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[2].rotateFaceAntiClockwise();
  cubeState[3] = std::move(tempL);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[3].rotateFaceAntiClockwise();
  cubeState[1] = std::move(tempU);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[1].rotateFaceAntiClockwise();
  cubeState[4] = std::move(tempR);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[4].rotateFaceAntiClockwise();

  cubeState[0].rotateFaceAntiClockwise();
  cubeState[5].rotateFaceClockwise();
}

void Cube::f() {
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[2]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[2][2], cubeState[1].squares[1][2], cubeState[1].squares[0][2]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[0]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[2][0], cubeState[2].squares[1][0], cubeState[2].squares[0][0]};

  cubeState[4].squares[2] = std::move(leftRotated);
  cubeState[2].squares[0][0] = topRotated[0];
  cubeState[2].squares[1][0] = topRotated[1];
  cubeState[2].squares[2][0] = topRotated[2];
  cubeState[3].squares[0] = std::move(rightRotated);
  cubeState[1].squares[0][2] = bottomRotated[0];
  cubeState[1].squares[1][2] = bottomRotated[1];
  cubeState[1].squares[2][2] = bottomRotated[2];

  cubeState[0].rotateFaceClockwise();
}

void Cube::fi() {
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[2]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[0][2], cubeState[1].squares[1][2], cubeState[1].squares[2][2]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[0]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[0][0], cubeState[2].squares[1][0], cubeState[2].squares[2][0]};

  cubeState[1].squares[0][2] = topRotated[2];
  cubeState[1].squares[1][2] = topRotated[1];
  cubeState[1].squares[2][2] = topRotated[0];
  cubeState[3].squares[0] = std::move(leftRotated);
  cubeState[2].squares[0][0] = bottomRotated[2];
  cubeState[2].squares[1][0] = bottomRotated[1];
  cubeState[2].squares[2][0] = bottomRotated[0];
  cubeState[4].squares[2] = std::move(rightRotated);

  cubeState[0].rotateFaceAntiClockwise();
}

void Cube::r() {
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][2], cubeState[4].squares[1][2], cubeState[4].squares[2][2]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][0], cubeState[5].squares[1][0], cubeState[5].squares[2][0]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][2], cubeState[3].squares[1][2], cubeState[3].squares[2][2]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][2], cubeState[0].squares[1][2], cubeState[0].squares[2][2]};

  cubeState[5].squares[0][0] = topRotated[2];
  cubeState[5].squares[1][0] = topRotated[1];
  cubeState[5].squares[2][0] = topRotated[0];
  cubeState[3].squares[0][2] = backRotated[2];
  cubeState[3].squares[1][2] = backRotated[1];
  cubeState[3].squares[2][2] = backRotated[0];
  cubeState[0].squares[0][2] = bottomRotated[0];
  cubeState[0].squares[1][2] = bottomRotated[1];
  cubeState[0].squares[2][2] = bottomRotated[2];
  cubeState[4].squares[0][2] = frontRotated[0];
  cubeState[4].squares[1][2] = frontRotated[1];
  cubeState[4].squares[2][2] = frontRotated[2];

  cubeState[2].rotateFaceClockwise();
}

void Cube::ri() {
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][2], cubeState[4].squares[1][2], cubeState[4].squares[2][2]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][0], cubeState[5].squares[1][0], cubeState[5].squares[2][0]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][2], cubeState[3].squares[1][2], cubeState[3].squares[2][2]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][2], cubeState[0].squares[1][2], cubeState[0].squares[2][2]};

  cubeState[0].squares[0][2] = topRotated[0];
  cubeState[0].squares[1][2] = topRotated[1];
  cubeState[0].squares[2][2] = topRotated[2];
  cubeState[3].squares[0][2] = frontRotated[0];
  cubeState[3].squares[1][2] = frontRotated[1];
  cubeState[3].squares[2][2] = frontRotated[2];
  cubeState[5].squares[0][0] = bottomRotated[2];
  cubeState[5].squares[1][0] = bottomRotated[1];
  cubeState[5].squares[2][0] = bottomRotated[0];
  cubeState[4].squares[0][2] = backRotated[2];
  cubeState[4].squares[1][2] = backRotated[1];
  cubeState[4].squares[2][2] = backRotated[0];

  cubeState[2].rotateFaceAntiClockwise();
}

void Cube::l() {
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][0], cubeState[4].squares[1][0], cubeState[4].squares[2][0]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][2], cubeState[5].squares[1][2], cubeState[5].squares[2][2]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][0], cubeState[3].squares[1][0], cubeState[3].squares[2][0]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][0], cubeState[0].squares[1][0], cubeState[0].squares[2][0]};

  cubeState[0].squares[0][0] = topRotated[0];
  cubeState[0].squares[1][0] = topRotated[1];
  cubeState[0].squares[2][0] = topRotated[2];
  cubeState[3].squares[0][0] = frontRotated[0];
  cubeState[3].squares[1][0] = frontRotated[1];
  cubeState[3].squares[2][0] = frontRotated[2];
  cubeState[5].squares[0][2] = bottomRotated[2];
  cubeState[5].squares[1][2] = bottomRotated[1];
  cubeState[5].squares[2][2] = bottomRotated[0];
  cubeState[4].squares[0][0] = backRotated[2];
  cubeState[4].squares[1][0] = backRotated[1];
  cubeState[4].squares[2][0] = backRotated[0];

  cubeState[1].rotateFaceClockwise();
}

void Cube::li() {
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][0], cubeState[4].squares[1][0], cubeState[4].squares[2][0]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][2], cubeState[5].squares[1][2], cubeState[5].squares[2][2]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][0], cubeState[3].squares[1][0], cubeState[3].squares[2][0]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][0], cubeState[0].squares[1][0], cubeState[0].squares[2][0]};  

  cubeState[4].squares[0][0] = frontRotated[0];
  cubeState[4].squares[1][0] = frontRotated[1];
  cubeState[4].squares[2][0] = frontRotated[2];
  cubeState[5].squares[0][2] = topRotated[2];
  cubeState[5].squares[1][2] = topRotated[1];
  cubeState[5].squares[2][2] = topRotated[0];
  cubeState[3].squares[0][0] = backRotated[2];
  cubeState[3].squares[1][0] = backRotated[1];
  cubeState[3].squares[2][0] = backRotated[0];
  cubeState[0].squares[0][0] = bottomRotated[0];
  cubeState[0].squares[1][0] = bottomRotated[1];
  cubeState[0].squares[2][0] = bottomRotated[2];

  cubeState[1].rotateFaceAntiClockwise();
}

void Cube::u() {
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[0]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[0]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[0]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[0]);

  cubeState[1].squares[0] = std::move(frontRotated);
  cubeState[5].squares[0] = std::move(leftRotated);
  cubeState[2].squares[0] = std::move(backRotated);
  cubeState[0].squares[0] = std::move(rightRotated);

  cubeState[4].rotateFaceClockwise();
}

void Cube::ui() {
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[0]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[0]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[0]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[0]);

  cubeState[1].squares[0] = std::move(backRotated);
  cubeState[5].squares[0] = std::move(rightRotated);
  cubeState[2].squares[0] = std::move(frontRotated);
  cubeState[0].squares[0] = std::move(leftRotated);

  cubeState[4].rotateFaceAntiClockwise();
}

void Cube::d() {
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[2]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[2]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[2]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[2]);

  cubeState[2].squares[2] = std::move(frontRotated);
  cubeState[5].squares[2] = std::move(rightRotated);
  cubeState[1].squares[2] = std::move(backRotated);
  cubeState[0].squares[2] = std::move(leftRotated);

  cubeState[3].rotateFaceClockwise();
}

void Cube::di() {
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[2]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[2]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[2]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[2]);

  cubeState[2].squares[2] = std::move(backRotated);
  cubeState[5].squares[2] = std::move(leftRotated);
  cubeState[1].squares[2] = std::move(frontRotated);
  cubeState[0].squares[2] = std::move(rightRotated);

  cubeState[3].rotateFaceAntiClockwise();
}

void Cube::b() {
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[0]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[0][0], cubeState[1].squares[1][0], cubeState[1].squares[2][0]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[2]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[0][2], cubeState[2].squares[1][2], cubeState[2].squares[2][2]};

  cubeState[4].squares[0] = std::move(rightRotated);
  cubeState[1].squares[0][0] = topRotated[2];
  cubeState[1].squares[1][0] = topRotated[1];
  cubeState[1].squares[2][0] = topRotated[0];
  cubeState[3].squares[2] = std::move(leftRotated);
  cubeState[2].squares[0][2] = bottomRotated[2];
  cubeState[2].squares[1][2] = bottomRotated[1];
  cubeState[2].squares[2][2] = bottomRotated[0];

  cubeState[5].rotateFaceClockwise();
}

void Cube::bi() {
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[0]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[0][0], cubeState[1].squares[1][0], cubeState[1].squares[2][0]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[2]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[0][2], cubeState[2].squares[1][2], cubeState[2].squares[2][2]};

  cubeState[4].squares[0][0] = leftRotated[2];
  cubeState[4].squares[0][1] = leftRotated[1];
  cubeState[4].squares[0][2] = leftRotated[0];
  cubeState[1].squares[0][0] = bottomRotated[0];
  cubeState[1].squares[1][0] = bottomRotated[1];
  cubeState[1].squares[2][0] = bottomRotated[2];
  cubeState[3].squares[2][0] = rightRotated[2];
  cubeState[3].squares[2][1] = rightRotated[1];
  cubeState[3].squares[2][2] = rightRotated[0];
  cubeState[2].squares[0][2] = topRotated[0];
  cubeState[2].squares[1][2] = topRotated[1];
  cubeState[2].squares[2][2] = topRotated[2];

  cubeState[5].rotateFaceAntiClockwise();
}