/** Class header */
#include "white_cross.h"

/** Local headers */
#include "cube_face.h"
#include "enum2Str.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "util.h"

/** System headers */
#include <iostream>
#include <functional>

// ------------------------------------------------------------------------- //
WhiteCross::WhiteCross(Cube &cube) : Step(cube) {}

// ------------------------------------------------------------------------- //
void WhiteCross::setupTargetLocations() 
{
  targets.push_back({
    std::make_pair(1,0),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::LE, 1, 1),
                     FaceOrientation::LE)
    }
  });

  targets.push_back({
    std::make_pair(0,1),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::BA, 1, 1),
                     FaceOrientation::BA)
    }
  });

  targets.push_back({
    std::make_pair(1,2),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::RI, 1, 1),
                     FaceOrientation::RI)
    }
  });

  targets.push_back({
    std::make_pair(2,1),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::FR, 1, 1),
                     FaceOrientation::FR)
    }
  });
}

// ------------------------------------------------------------------------- //
bool WhiteCross::nextUnsolvedCrossPiece(SolveStep &unsolvedPiece)
{
  auto retryTarg = findTargetThatNeedsRetry();

  for (auto face = cube.roBegin(); face != cube.roEnd(); ++face)
  {
    for (int i = 0; i < face->squares.size(); i++) 
    {
      for (int j = 0; j < face->squares[i].size(); j++) 
      {
        if (face->squares[i][j] == FaceColor::W) 
        {
          if ((i == 0 && j == 1) ||
              (i == 1 && j == 0) ||
              (i == 1 && j == 2) ||
              (i == 2 && j == 1)) 
          {
            auto adjColor = cube.getAdjacentFaceColor(face->getOrientation(), 
                                                      i, j);
            // find target with matching adjacent color
            auto target = std::find_if(
              targets.begin(),
              targets.end(),
              [&] (const auto& targ) 
              {
                return targ.adjacentColors.at(0).first == adjColor;
              }
            );

            if (target != targets.end())
            {
              auto completed = i == target->position.first &&
                               j == target->position.second &&
                               face->getOrientation() == target->face;
              auto retrySet = retryTarg != targets.end() && 
                              target->position != retryTarg->position &&
                              target->face == retryTarg->face;

              if (completed || retrySet)
              {
                continue;
              }

              unsolvedPiece.startLocation = std::make_pair(i, j);
              unsolvedPiece.orientation = face->getOrientation();
              unsolvedPiece.targetLocation = *target;
              return true;
            }
          }
        }
      }
    }
  }
  return false;
}

// ------------------------------------------------------------------------- //
void WhiteCross::solveStep()
{
  spdlog::info("Starting to solve white cross.");
  reorientWhiteFaceToTop();
  setupTargetLocations();
  SolveStep unsolvedPiece;
  while (nextUnsolvedCrossPiece(unsolvedPiece))
  {
    repositionWhiteCrossPiece(unsolvedPiece);
  }
  spdlog::info("White cross solved!");
}

// ------------------------------------------------------------------------- //
void WhiteCross::repositionTopWhitePiece(int i, int j)
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
void WhiteCross::repositionTopInverseWhitePiece(FaceOrientation orientation)
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
void WhiteCross::repositionMiddleWhitePiece(FaceOrientation orientation, int j)
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

// ------------------------------------------------------------------------- //
void WhiteCross::repositionBottomInverseWhitePiece(FaceOrientation orientation)
{
  switch(orientation)
  {
    case FaceOrientation::RI:
    {
      cube.r();
      cube.f();
      cube.d();
      cube.fi();
      break;
    }
    case FaceOrientation::FR:
    {
      cube.f();
      cube.l();
      cube.d();
      cube.li();
      break;
    }
    case FaceOrientation::LE:
    {
      cube.li();
      cube.fi();
      cube.di();
      cube.f();
      break;
    }
    case FaceOrientation::BA:
    {
      cube.b();
      cube.r();
      cube.d();
      cube.ri();
      break;
    }
    default:
    {
      return;
    }
  }
}

// ------------------------------------------------------------------------- //
std::function<void(Cube&)> WhiteCross::getRotationForFinalPosition(
  FaceOrientation endFace
)
{
  std::function<void(Cube&)> rot;
  switch (endFace)
  {
    case FaceOrientation::FR:
    {
      rot = &Cube::f;
      break;
    }
    case FaceOrientation::RI:
    {
      rot = &Cube::r;
      break;
    }
    case FaceOrientation::BA:
    {
      rot = &Cube::b;
      break;
    }
    case FaceOrientation::LE:
    {
      rot = &Cube::l;
      break;
    }
    default:
    {
      break;
    }
  }
  return rot;
}

// ------------------------------------------------------------------------- //
int WhiteCross::getNumRotationsBetweenFaces(FaceOrientation startFace,
                                            FaceOrientation endFace)
{
  std::unordered_map<int, int> mapping{
    {FaceOrientation::FR, 0},
    {FaceOrientation::RI, 1},
    {FaceOrientation::BA, 2},
    {FaceOrientation::LE, 3}
  };

  auto start = mapping.at(startFace);
  auto end = mapping.at(endFace);
  
  if (start == end)
  {
    return 0;
  }
  else if (start < end)
  {
    return abs(start-end);
  }
  else
  {
    return (4-abs(start-end));
  }
}

// ------------------------------------------------------------------------- //
void WhiteCross::repositionBottomWhitePiece(int i, 
                                            int j,
                                            FaceOrientation endFace)
{
  auto rot = getRotationForFinalPosition(endFace);
  int numRotations = 0;

  if (i == 0 && j == 1) 
  {
    numRotations = getNumRotationsBetweenFaces(FaceOrientation::FR, endFace);
  }
  else if (i == 1 && j == 0)
  {
    numRotations = getNumRotationsBetweenFaces(FaceOrientation::LE, endFace);
  }
  else if (i == 1 && j == 2)
  {
    numRotations = getNumRotationsBetweenFaces(FaceOrientation::RI, endFace);
  }
  else if (i == 2 && j == 1)
  {
    numRotations = getNumRotationsBetweenFaces(FaceOrientation::BA, endFace);
  }

  int counter = 0;
  while (counter < numRotations)
  {
    cube.d();
    counter++;
  }
  rot(cube);
  rot(cube);
}

// ------------------------------------------------------------------------- //
void WhiteCross::repositionWhiteCrossPiece(const SolveStep target) 
{
  // Different rotations needed depending on whether top, middle, or bottom row
  switch(target.orientation)
  {
    case FaceOrientation::UP:
    {
      repositionTopWhitePiece(target.startLocation.first, 
                              target.startLocation.second);
      retryTarget(target.targetLocation.face, 
                  target.targetLocation.position.first, 
                  target.targetLocation.position.second);
      break;
    }
    case FaceOrientation::RI:
    case FaceOrientation::FR:
    case FaceOrientation::LE:
    case FaceOrientation::BA:
    {
      if (target.startLocation.first == 0)
      {
        // top row
        repositionTopInverseWhitePiece(target.orientation);
      }
      else if (target.startLocation.first == 1)
      {
        // middle row
        repositionMiddleWhitePiece(target.orientation, 
                                   target.startLocation.second);
      }
      else
      {
        // bottom row
        repositionBottomInverseWhitePiece(target.orientation);
      }

      retryTarget(target.targetLocation.face, 
                  target.targetLocation.position.first, 
                  target.targetLocation.position.second);
      break;
    }
    case FaceOrientation::DO:
    {
      auto adjacentTargetFace = target
                                .targetLocation
                                .adjacentColors
                                .at(0)
                                .second;

      repositionBottomWhitePiece(target.startLocation.first, 
                                 target.startLocation.second, 
                                 adjacentTargetFace);
      break;
    }
    default:
    {
      break;
    }
  }
}

// ------------------------------------------------------------------------- //
void WhiteCross::reorientWhiteFaceToTop()
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
FaceOrientation WhiteCross::findWhiteCenter() {
  for (auto face = cube.roBegin(); face != cube.roEnd(); ++face)
  {
    if (face->getColorAtIndices(1, 1) == FaceColor::W)
    {
      return face->getOrientation();
    }
  }
  return FaceOrientation::FO_ERR;
}