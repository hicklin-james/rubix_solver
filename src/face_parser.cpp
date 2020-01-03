/** Class header */
#include "face_parser.h"

/** Local headers */
#include "cube_face.h"
#include "util.h"

/** System headers */
#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// ------------------------------------------------------------------------- //
CubeFace FaceParser::parseFaceFromString(std::string inputStr,
                                         FaceOrientation orientation) 
{
  std::stringstream ss(inputStr);

  std::array<std::array<FaceColor,3>,3> faceArr;
  std::vector<FaceColor> vec;
  int rowNum = 0;
  while (ss.good())
  {
    std::string substr;
    getline(ss, substr, ',');
    FaceColor col = Util::str2FaceColor.at(substr);
    vec.push_back(col);
    if (vec.size() == 3)
    {
      std::copy_n(vec.begin(), vec.size(), faceArr.at(rowNum).begin());
      vec.clear();
      rowNum++;
    }
  }
  
  CubeFace face(orientation, faceArr);
  return face;
}