#pragma once

/** Local headers */
#include "cube_face.h"

/** System headers */
#include <string>

class FaceParser
{
  public:

    /**
    * Main FaceParser constructor
    *
    * @param inputStr std::string string representing cube face
    * @param orientation FaceOrientation the orientation to use for the face
    */
    static CubeFace parseFaceFromString(std::string inputStr, 
                                        FaceOrientation orientation);
};