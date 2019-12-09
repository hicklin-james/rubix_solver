#pragma once

#include <map>
#include <string>

typedef enum {FR = 0, DO = 1, LE = 2, RI = 3, UP = 4, BA = 5} FaceOrientation;
typedef enum {W = 0, O = 1, G = 2, B = 3, R = 4, Y = 5} FaceColor;

class Util {
  public:
    typedef std::map<std::string, FaceColor> ColMap;
    static ColMap str2FaceColor;
};