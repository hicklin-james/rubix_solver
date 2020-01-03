#include "util.h"
#include "cube.h"
#include "face_parser.h"
#include "cross.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include <array>
#include <iostream>
#include <string>
#include <array>

int main()
{
  spdlog::info("Welcome to the rubix solver!");

  std::array<std::string, 6> unparsedCube{ 
    "G,O,Y,R,R,Y,R,G,G", // front
    "B,R,R,O,G,G,W,O,Y", // left
    "O,B,R,B,B,B,O,Y,Y", // right
    "B,W,W,Y,Y,R,B,B,G", // bottom
    "O,G,G,W,W,O,Y,G,B", // top
    "W,Y,W,R,O,W,O,W,R"  // back
  };

  CubeFace front;
  CubeFace left;
  CubeFace right;
  CubeFace bottom;
  CubeFace top;
  CubeFace back;

  try {
    front = FaceParser::parseFaceFromString(unparsedCube.at(0), FaceOrientation::FR);
    left = FaceParser::parseFaceFromString(unparsedCube.at(1), FaceOrientation::LE);
    right = FaceParser::parseFaceFromString(unparsedCube.at(2), FaceOrientation::RI);
    bottom = FaceParser::parseFaceFromString(unparsedCube.at(3), FaceOrientation::DO);
    top = FaceParser::parseFaceFromString(unparsedCube.at(4), FaceOrientation::UP);
    back = FaceParser::parseFaceFromString(unparsedCube.at(5), FaceOrientation::BA);
  }
  catch (const std::out_of_range& oor) {
    // TODO show error
    return -1;
  }

  Cube cube(std::array<CubeFace, 6>{front, left, right, bottom, top, back});

  cube.printCube();


  Cross crossSolver(cube);

  //cube.rotateCubeAntiClockwise();
  //cube.printCube();
  crossSolver.solveCross();

  cube.printCube();

  cube.printMoveHistory();
  //cube.printCube();


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

  // cube.printCube();

  return 0;
}