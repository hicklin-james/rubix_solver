// local headers
#include "cube.h"
#include "cube_face.h"
#include "util.h"
// system headers
#include <iostream>
#include <iomanip>

Cube::Cube(std::array<CubeFace, 6> faces) : cubeState(faces) {}

void Cube::printCube() const {
  std::cout << std::left << std::setw(8) << "";
  cubeState[4].printRow(0);
  std::cout << std::endl << std::left << std::setw(8) << "";
  cubeState[4].printRow(1);
  std::cout << std::endl << std::left << std::setw(8) << "";
  cubeState[4].printRow(2);
  std::cout << std::endl << std::left << std::setw(8) << "";
  std::cout << "- - -" << std::endl;

  cubeState[1].printRow(0);
  std::cout << " | ";
  cubeState[0].printRow(0);
  std::cout << " | ";
  cubeState[2].printRow(0);
  std::cout << " | ";
  cubeState[5].printRow(0);
  std::cout << std::endl;
  cubeState[1].printRow(1);
  std::cout << " | ";
  cubeState[0].printRow(1);
  std::cout << " | ";
  cubeState[2].printRow(1);
  std::cout << " | ";
  cubeState[5].printRow(1);
  std::cout << std::endl;
  cubeState[1].printRow(2);
  std::cout << " | ";
  cubeState[0].printRow(2);
  std::cout << " | ";
  cubeState[2].printRow(2);
  std::cout << " | ";
  cubeState[5].printRow(2);
  std::cout << std::endl;

  std::cout << std::left << std::setw(8) << "";
  std::cout << "- - -" << std::endl;
  std::cout << std::left << std::setw(8) << "";
  cubeState[3].printRow(0);
  std::cout << std::endl << std::left << std::setw(8) << "";
  cubeState[3].printRow(1);
  std::cout << std::endl << std::left << std::setw(8) << "";
  cubeState[3].printRow(2);
  std::cout << std::endl;
}

void Cube::rotateCubeClockwise() {
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

void Cube::rotateCubeAntiClockwise() {
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