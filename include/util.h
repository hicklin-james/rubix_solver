#pragma once

/** System headers */
#include <map>
#include <string>
#include <utility>
#include <vector>

// Enum representation face orientations
typedef enum {FR = 0, 
              DO = 1, 
              LE = 2, 
              RI = 3, 
              UP = 4, 
              BA = 5, 
              FO_ERR = -1} FaceOrientation;

// Enum representing cell colors
typedef enum {W = 0, 
              O = 1, 
              G = 2, 
              B = 3, 
              R = 4, 
              Y = 5, 
              FC_ERR = -1} FaceColor;

// Struct to hold info related to a targetLocation
struct TargetLocation {
  std::pair<int, int> position;
  FaceOrientation face;
  FaceColor faceColor;
  std::vector<std::pair<FaceColor, FaceOrientation>> adjacentColors;
  bool retryTarget = false;
};

// Struct to hold info related to a solve step
struct SolveStep {
  std::pair<int, int> startLocation;
  FaceOrientation orientation;
  TargetLocation targetLocation;
};

class Util {
  public:
    
    typedef std::map<std::string, FaceColor> ColMap;
    static ColMap str2FaceColor; // colormap string to enum

    /**
    * Function to compare contents of two vectors for equal elements
    * 
    * Note:
    * Declared inline due to template
    */
    template<typename T>
    static bool compare(std::vector<T>& v1, std::vector<T>& v2)
    {
      std::sort(v1.begin(), v1.end());
      std::sort(v2.begin(), v2.end());
      return v1 == v2;
    }
};