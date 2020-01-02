#pragma once

#include <map>
#include <string>
#include <utility>

typedef enum {FR = 0, DO = 1, LE = 2, RI = 3, UP = 4, BA = 5, FO_ERR = -1} FaceOrientation;
typedef enum {W = 0, O = 1, G = 2, B = 3, R = 4, Y = 5, FC_ERR = -1} FaceColor;

struct TargetItem {
  int i;
  int j;
  FaceColor color;
  FaceOrientation orientation;
  std::pair<int, int> targetLocation;
};

class Util {
  public:
    typedef std::map<std::string, FaceColor> ColMap;
    static ColMap str2FaceColor;
};