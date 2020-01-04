#pragma once

/** Local headers */
#include "cube.h"

class Step {
  public:

    /**
    * Main Step constructor
    *
    * @param &cube Cube the cube 
    */
    Step(Cube &cube);

  protected:

    Cube &cube; // the cube - protected to give child access
};