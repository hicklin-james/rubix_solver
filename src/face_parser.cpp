#include "face_parser.h"
#include "util.h"
#include "cube_face.h"
#include <string>
#include <sstream>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

int FaceParser::parseFaceFromString(CubeFace &face, std::string inputStr, FaceOrientation orientation) {
  std::stringstream ss(inputStr);

  std::array<std::array<FaceColor,3>,3> faceArr;
  std::vector<FaceColor> vec;
  int rowNum = 0;
  while( ss.good() ) {
    std::string substr;
    getline( ss, substr, ',' );
    try {
      FaceColor col = Util::str2FaceColor.at(substr);
      vec.push_back(col);
      if (vec.size() == 3) {
        std::copy_n(vec.begin(), vec.size(), faceArr.at(rowNum).begin());
        vec.clear();
        rowNum++;
      }
    }
    catch (const std::out_of_range& oor) {
      return -1;
    }
  }
  
  face.squares = faceArr;
  face.setOrientation(orientation);
  return 1;
}