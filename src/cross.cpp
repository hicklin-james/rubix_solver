/** Class header */
#include "cross.h"

/** Local headers */
#include "cube_face.h"
#include "enum2Str.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "util.h"

/** System headers */
#include <iostream>

// ------------------------------------------------------------------------- //
Cross::Cross(Cube &cube) : Step(cube) {}

// ------------------------------------------------------------------------- //
void Cross::setupTargetLocations() 
{
  targets.insert({cube.getColorAtFaceAndLocation(FaceOrientation::LE, 1, 1),
                  std::make_pair(1, 0)});
  targets.insert({cube.getColorAtFaceAndLocation(FaceOrientation::BA, 1, 1),
                  std::make_pair(0, 1)});
  targets.insert({cube.getColorAtFaceAndLocation(FaceOrientation::RI, 1, 1),
                  std::make_pair(1, 2)});
  targets.insert({cube.getColorAtFaceAndLocation(FaceOrientation::FR, 1, 1),
                  std::make_pair(2, 1)});
}

// ------------------------------------------------------------------------- //
bool Cross::nextUnsolvedCrossPiece(TargetItem &unsolvedPiece)
{
  for (auto face = cube.roBegin(); face != cube.roEnd(); ++face)
  {
    for (int i = 0; i < face->squares.size(); i++) 
    {
      for (int j = 0; j < face->squares[i].size(); j++) 
      {
        if (face->squares[i][j] == FaceColor::W) 
        {
          if (
              (i == 0 && j == 1) ||
              (i == 1 && j == 0) ||
              (i == 1 && j == 2) ||
              (i == 2 && j == 1)
             ) 
          {
            auto adjColor = cube.getAdjacentFaceColor(face->getOrientation(), 
                                                      i, j);
            auto target = targets.at(adjColor);
            if (i == target.first &&
                j == target.second &&
                face->getOrientation() == FaceOrientation::UP) 
            {
              continue;
            }
            unsolvedPiece.i = i;
            unsolvedPiece.j = j;
            unsolvedPiece.color = adjColor;
            unsolvedPiece.orientation = face->getOrientation();
            unsolvedPiece.targetLocation = target;
            return true;
          }
        }
      }
    }
  }
  return false;
}

// ------------------------------------------------------------------------- //
void Cross::solveCross()
{
  reorientWhiteFaceToTop();
  setupTargetLocations();
  TargetItem unsolvedPiece;
  while (nextUnsolvedCrossPiece(unsolvedPiece))
  {
    repositionWhiteCrossPiece(unsolvedPiece);
  }
}

// ------------------------------------------------------------------------- //
void Cross::repositionTopWhitePiece(int i, int j)
{
  if (i == 0 && j == 1)
  {
    cube.b();
    cube.b();
  }
  else if (i == 1 && j == 0)
  {
    cube.l();
    cube.l();
  }
  else if (i == 1 && j == 2)
  {
    cube.r();
    cube.r();
  }
  else if (i == 2 && j == 1)
  {
    cube.f();
    cube.f();
  }
}

// ------------------------------------------------------------------------- //
void Cross::repositionTopInverseWhitePiece(FaceOrientation orientation)
{
  switch(orientation)
  {
    case FaceOrientation::RI:
    {
      cube.r();
      cube.bi();
      cube.di();
      cube.r();
      break;
    }
    case FaceOrientation::FR:
    {
      cube.f();
      cube.ri();
      cube.di();
      cube.r(); 
      break;
    }
    case FaceOrientation::LE:
    {
      cube.li();
      cube.b();
      cube.di();
      cube.bi();
      break;
    }
    case FaceOrientation::BA:
    {
      cube.b();
      cube.li();
      cube.di();
      cube.l();
      break;
    }
    default:
    {
      return;
    }
  }
}

// ------------------------------------------------------------------------- //
void Cross::repositionMiddleWhitePiece(FaceOrientation orientation, int j)
{
  switch(orientation)
  {
    case FaceOrientation::RI:
    {
      if (j == 0)
      {
        cube.f();
        cube.d();
        cube.fi();
      }
      else
      {
        cube.bi();
        cube.d();
        cube.b();
      }
      break;
    }
    case FaceOrientation::FR:
    {
      if (j == 0)
      {
        cube.l();
        cube.d();
        cube.li();
      }
      else
      {
        cube.ri();
        cube.d();
        cube.r();
      }
      break;
    }
    case FaceOrientation::LE:
    {
      if (j == 0)
      {
        cube.b();
        cube.d();
        cube.bi();
      }
      else
      {
        cube.fi();
        cube.d();
        cube.f();
      }
      break;
    }
    case FaceOrientation::BA:
    {
      if (j == 0)
      {
        cube.r();
        cube.d();
        cube.ri();
      }
      else
      {
        cube.li();
        cube.d();
        cube.l();
      }
      break;
    }
    default:
    {
      return;
    }
  }
}

void Cross::repositionBottomInverseWhitePiece(FaceOrientation orientation)
{
  switch(orientation)
  {
    case FaceOrientation::RI:
      cube.r();
      cube.f();
      cube.d();
      cube.fi();
      break;
    case FaceOrientation::FR:
      cube.f();
      cube.l();
      cube.d();
      cube.li();
      break;
    case FaceOrientation::LE:
      cube.li();
      cube.fi();
      cube.di();
      cube.f();
      break;
    case FaceOrientation::BA:
      cube.b();
      cube.r();
      cube.d();
      cube.ri();
      break;
    default:
      return;
  }
}

// ------------------------------------------------------------------------- //
void Cross::repositionBottomWhitePiece(int i, int j, FaceColor targetFaceColor)
{
  while (cube.getColorAtFaceAndLocation(FaceOrientation::FR, 1, 1) != targetFaceColor) 
  {
    cube.rotateCubeRight();

    // targets need to be updated with whole face rotation
    auto tempG = targets.at(FaceColor::G);
    auto tempO = targets.at(FaceColor::O);
    auto tempB = targets.at(FaceColor::B);
    auto tempR = targets.at(FaceColor::R);

    targets[FaceColor::O] = tempG;
    targets[FaceColor::B] = tempO;
    targets[FaceColor::R] = tempB;
    targets[FaceColor::G] = tempR;
  }

  while (cube.getColorAtFaceAndLocation(FaceOrientation::FR, 2, 1) != targetFaceColor ||
         cube.getColorAtFaceAndLocation(FaceOrientation::DO, 0, 1) != FaceColor::W)
  {
    cube.d();
  }

  cube.f();
  cube.f();
}

// ------------------------------------------------------------------------- //
void Cross::repositionWhiteCrossPiece(const TargetItem target) {
  // Different rotations needed depending on whether top, middle, or bottom row
  switch(target.orientation)
  {
    case FaceOrientation::UP:
    {
      repositionTopWhitePiece(target.i, target.j);
      break;
    }
    case FaceOrientation::RI:
    case FaceOrientation::FR:
    case FaceOrientation::LE:
    case FaceOrientation::BA:
    {
      if (target.i == 0)
      {
        // top row
        repositionTopInverseWhitePiece(target.orientation);
      }
      else if (target.i == 1)
      {
        // middle row
        repositionMiddleWhitePiece(target.orientation, target.j);
      }
      else
      {
        // bottom row
        repositionBottomInverseWhitePiece(target.orientation);
      }
      break;
    }
    case FaceOrientation::DO:
    {
      repositionBottomWhitePiece(target.i, target.j, target.color);
      break;
    }
    default:
    {
      break;
    }
  }
}

// ------------------------------------------------------------------------- //
void Cross::reorientWhiteFaceToTop()
{
  auto whiteFaceOrientation = findWhiteCenter();
  switch(whiteFaceOrientation)
  {
    case FaceOrientation::FR:
    {
      cube.rotateCubeUp();
      break;
    }
    case FaceOrientation::LE:
    {
      cube.rotateCubeClockwise();
      break;
    }
    case FaceOrientation::RI:
    {
      cube.rotateCubeAntiClockwise();
      break;
    }
    case FaceOrientation::BA:
    {
      cube.rotateCubeDown();
      break;
    }
    case FaceOrientation::DO:
    {
      cube.rotateCubeClockwise();
      cube.rotateCubeClockwise();
      break;
    }
    default:
    {
      break;
    }
  }
}

// ------------------------------------------------------------------------- //
FaceOrientation Cross::findWhiteCenter() {
  for (auto face = cube.roBegin(); face != cube.roEnd(); ++face)
  {
    if (face->getColorAtIndices(1, 1) == FaceColor::W)
    {
      return face->getOrientation();
    }
  }
  return FaceOrientation::FO_ERR;
}