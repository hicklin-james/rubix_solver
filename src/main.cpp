#include "util.h"
#include "cube.h"
#include "face_parser.h"
#include "white_cross.h"
#include "white_corners.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "valid_cubes.h"
#include <array>
#include <iostream>
#include <string>
#include <array>

int main()
{
  spdlog::info("Welcome to the rubix solver!");

  auto unparsedCube = ValidCubes::unparsedCubeB;

  CubeFace front, left, right, bottom, top, back;
  std::array<CubeFace, 6> faces{front, left, right, bottom, top, back};
  std::array<FaceOrientation, 6> faceOrientations{
    FaceOrientation::FR,
    FaceOrientation::LE,
    FaceOrientation::RI,
    FaceOrientation::DO,
    FaceOrientation::UP,
    FaceOrientation::BA
  };

  try {
    for (int i = 0; i < faces.size(); i++)
    {
      faces[i] = FaceParser::parseFaceFromString(unparsedCube.at(i), faceOrientations.at(i));
    }
  }
  catch (const std::out_of_range& oor) {
    // TODO show error
    return -1;
  }

  Cube cube(faces);

  //spdlog::info("Initial cube state:");
  cube.printCube("Initial cube state:");


  WhiteCross crossSolver(cube);

  //cube.rotateCubeAntiClockwise();
  //cube.printCube();
  crossSolver.solveStep();

  cube.printCube();

  WhiteCorners cornersSolver(cube);
  cornersSolver.solveStep();

  cube.printCube();

  cube.printMoveHistory();


  /** This is a valid solve for the cube! **/

  // std::array<std::string, 6> unparsedCube{ 
  //   "O,W,O,B,W,W,G,Y,B", // front
  //   "Y,G,W,G,G,O,W,W,R", // left
  //   "W,O,B,R,B,R,O,Y,G", // right
  //   "W,R,Y,B,R,G,B,B,Y", // bottom
  //   "G,Y,Y,R,O,G,G,O,B", // top
  //   "R,O,O,B,Y,W,R,Y,R"  // back
  // };

  // cube.f();
  // cube.f();
  // cube.r();
  // cube.r();
  // cube.ui();
  // cube.d();
  // cube.r();
  // cube.r();
  // cube.l();
  // cube.f();
  // cube.f();
  // cube.b();
  // cube.d();
  // cube.f();
  // cube.b();
  // cube.b();
  // cube.l();
  // cube.d();
  // cube.b();
  // cube.b();
  // cube.r();
  // cube.r();
  // cube.l();
  // cube.l();
  // cube.u();
  // cube.u();
  // cube.r();
  // cube.r();
  // cube.u();
  // cube.l();
  // cube.l();

  return 0;
}