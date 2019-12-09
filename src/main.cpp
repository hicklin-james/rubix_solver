#include "util.h"
#include "cube.h"
#include "face_parser.h"
#include <array>
#include <iostream>
#include <string>
#include <array>

int main()
{
  std::array<std::string, 6> unparsedCube{ 
    "W,W,W,W,W,W,W,W,W", // front
    "W,W,W,W,W,W,W,W,W", // left
    "W,W,W,W,W,W,W,W,W", // right
    "W,W,W,W,W,W,W,W,W", // bottom
    "W,W,W,W,W,W,W,W,W", // top
    "O,W,W,W,W,W,W,W,W"  // back
  };

  CubeFace front;
  FaceParser::parseFaceFromString(front, unparsedCube.at(0), FaceOrientation::FR);

  CubeFace left;
  FaceParser::parseFaceFromString(left, unparsedCube.at(1), FaceOrientation::LE);

  CubeFace right;
  FaceParser::parseFaceFromString(right, unparsedCube.at(2), FaceOrientation::RI);

  CubeFace bottom;
  FaceParser::parseFaceFromString(bottom, unparsedCube.at(3), FaceOrientation::DO);

  CubeFace top;
  FaceParser::parseFaceFromString(top, unparsedCube.at(4), FaceOrientation::UP);

  CubeFace back;
  FaceParser::parseFaceFromString(back, unparsedCube.at(5), FaceOrientation::BA);

  Cube cube(std::array<CubeFace, 6>{front, left, right, bottom, top, back});
  cube.printCube();
  std::cout << std::endl;
  cube.ui();
  cube.printCube();

  return 0;
}