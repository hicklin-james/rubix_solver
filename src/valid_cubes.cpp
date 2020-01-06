#include "valid_cubes.h"

const std::array<std::string, 6> ValidCubes::unparsedCubeA = { 
  "G,G,G,Y,O,B,O,W,W", // front
  "O,W,Y,O,Y,R,W,B,B", // left
  "Y,O,R,O,W,G,R,G,R", // right
  "Y,B,G,Y,G,O,G,G,Y", // bottom
  "W,R,W,R,B,W,O,W,R", // top
  "B,B,B,Y,R,Y,B,R,O"  // back
};


const std::array<std::string, 6> ValidCubes::unparsedCubeB = { 
  "R,G,Y,O,G,B,B,B,G", // front
  "B,G,B,O,Y,W,Y,Y,O", // left
  "O,O,G,R,W,R,R,G,W", // right
  "W,Y,Y,O,R,Y,O,W,G", // bottom
  "W,R,O,R,O,G,Y,W,B", // top
  "W,Y,R,W,B,B,R,B,G"  // back
};

const std::array<std::string, 6> ValidCubes::unparsedCubeC = { 
  "W,G,R,B,O,G,W,R,Y", // front
  "W,G,O,W,W,R,G,Y,G", // left
  "B,O,Y,W,Y,B,B,W,R", // right
  "R,G,O,B,B,O,Y,Y,G", // bottom
  "O,W,R,O,G,Y,B,Y,W", // top
  "B,R,G,O,R,B,Y,R,O"  // back
};

const std::array<std::string, 6> ValidCubes::unparsedCubeD = { 
  "O,B,R,O,O,G,Y,W,Y", // front
  "W,R,Y,G,Y,Y,B,G,R", // left
  "W,W,Y,Y,W,Y,R,R,B", // right
  "G,R,B,O,G,B,R,B,O", // bottom
  "O,W,O,G,B,B,B,Y,G", // top
  "G,O,G,R,R,W,W,O,W"  // back
};

const std::array<std::string, 6> ValidCubes::unparsedCubeE = { 
  "G,W,Y,R,W,Y,R,W,W", // front
  "B,R,W,Y,B,Y,W,O,G", // left
  "O,B,G,B,G,W,B,Y,O", // right
  "Y,O,R,B,O,G,G,R,W", // bottom
  "R,O,Y,B,R,W,R,R,B", // top
  "O,G,Y,G,Y,O,B,G,O"  // back
};