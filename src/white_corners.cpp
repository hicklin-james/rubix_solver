/** Class header */
#include "white_corners.h"

/** Local headers */
#include "enum2Str.hpp"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "util.h"

/** System headers */
#include <iostream>
#include <unistd.h>

// ------------------------------------------------------------------------- //
WhiteCorners::WhiteCorners(Cube &cube) : Step(cube) {}

// ------------------------------------------------------------------------- //
void WhiteCorners::setupTargetLocations() 
{
  targets.push_back({
    std::make_pair(0,0),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::BA, 1, 1),
                     FaceOrientation::BA),
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::LE, 1, 1),
                     FaceOrientation::LE)
    }
  });

  targets.push_back({
    std::make_pair(0,2),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::BA, 1, 1),
                     FaceOrientation::BA),
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::RI, 1, 1),
                     FaceOrientation::RI)
    }
  });

  targets.push_back({
    std::make_pair(2,0),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::FR, 1, 1),
                     FaceOrientation::BA),
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::LE, 1, 1),
                     FaceOrientation::RI)
    }
  });

  targets.push_back({
    std::make_pair(2,2),
    FaceOrientation::UP,
    FaceColor::W,
    std::vector<std::pair<FaceColor, FaceOrientation>>{
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::FR, 1, 1),
                     FaceOrientation::BA),
      std::make_pair(cube.colorAtFaceAndLoc(FaceOrientation::RI, 1, 1),
                     FaceOrientation::RI)
    }
  });
}

// ------------------------------------------------------------------------- //
void WhiteCorners::repositionTopToBottom(FaceOrientation orientation,
                                         int iUp,
                                         SolveStep &step)
{
  retryTarget(step.targetLocation.face, 
              step.targetLocation.position.first, 
              step.targetLocation.position.second);

  if (orientation == FaceOrientation::RI)
  {
    if (iUp == 0)
    {
      cube.r();
      cube.d();
      cube.ri();
    }
    else if (iUp == 2)
    {
      cube.ri();
      cube.d();
      cube.r();
    }
  }
  else if (orientation == FaceOrientation::LE)
  {
    if (iUp == 0)
    {
      cube.li();
      cube.d();
      cube.l();
    }
    else if (iUp == 2)
    {
      cube.l();
      cube.d();
      cube.li();
    }
  }
}

// ------------------------------------------------------------------------- //
std::vector<FaceColor> WhiteCorners::getBrAdjacentFaceColors()
{
  std::pair<FaceColor, FaceColor> brAdjacentColors;
  if (cube.colorAtFaceAndLoc(FaceOrientation::FR, 2, 2) == FaceColor::W)
  {
    brAdjacentColors = cube.getAdjacentColors(FaceOrientation::FR, 2, 2);
  }
  else if (cube.colorAtFaceAndLoc(FaceOrientation::RI, 2, 0) == FaceColor::W)
  {
    brAdjacentColors = cube.getAdjacentColors(FaceOrientation::RI, 2, 0);
  }
  else if (cube.colorAtFaceAndLoc(FaceOrientation::DO, 0, 2) == FaceColor::W)
  {
    brAdjacentColors = cube.getAdjacentColors(FaceOrientation::DO, 0, 2);
  }
  else {
    brAdjacentColors = std::make_pair(FaceColor::FC_ERR, FaceColor::FC_ERR);
  }

  return std::vector<FaceColor>{brAdjacentColors.first, 
                                brAdjacentColors.second};
}

// ------------------------------------------------------------------------- //
std::pair<int, int> WhiteCorners::getNewPositionAfterRightRotation(int i, 
                                                                   int j)
{
  if (i == 0 && j == 0)
  {
    return std::make_pair(2, 0);
  }
  else if (i == 0 && j == 2)
  {
    return std::make_pair(0, 0);
  }
  else if (i == 2 && j == 0)
  {
    return std::make_pair(2, 2);
  }
  else if (i == 2 && j == 2)
  {
    return std::make_pair(0, 2);
  }
  return std::make_pair(-1, -1);
}

// ------------------------------------------------------------------------- //
void WhiteCorners::repositionDownCornerDo()
{
  cube.ri();
  cube.di();
  cube.di();
  cube.r();
  cube.d();
  cube.ri();
  cube.di();
  cube.r();
}

// ------------------------------------------------------------------------- //
void WhiteCorners::repositionDownCornerRi()
{
  cube.ri();
  cube.di();
  cube.r();
}

// ------------------------------------------------------------------------- //
void WhiteCorners::repositionDownCornerFr()
{
  cube.di();
  cube.ri();
  cube.d();
  cube.r();
}

// ------------------------------------------------------------------------- //
void WhiteCorners::doActualCubeRotations()
{
  if (cube.colorAtFaceAndLoc(FaceOrientation::FR, 2, 2) == FaceColor::W)
  {
    repositionDownCornerFr();
  }
  else if (cube.colorAtFaceAndLoc(FaceOrientation::RI, 2, 0) == FaceColor::W)
  {
    repositionDownCornerRi();
  }
  else if (cube.colorAtFaceAndLoc(FaceOrientation::DO, 0, 2) == FaceColor::W)
  {
    repositionDownCornerDo();
  }
}

// ------------------------------------------------------------------------- //
void WhiteCorners::respositionBottomToFinal(const SolveStep &step)
{
  std::vector<FaceColor> adjacentTargetColors;
  transform(
    step.targetLocation.adjacentColors.begin(), 
    step.targetLocation.adjacentColors.end(), 
    back_inserter(adjacentTargetColors), 
    [&] (const auto colPair)
    {
      return colPair.first;
    }
  );

  std::vector<FaceColor> currFrontRightColors = {
    cube.colorAtFaceAndLoc(FaceOrientation::FR, 1, 1),
    cube.colorAtFaceAndLoc(FaceOrientation::RI, 1, 1)
  };

  std::vector<FaceColor> brAdjacentColors = getBrAdjacentFaceColors();

  if (!Util::compare(currFrontRightColors, adjacentTargetColors))
  {
    FaceOrientation targOri = step.targetLocation.face;
    int targi = step.targetLocation.position.first;
    int targj = step.targetLocation.position.second;

    auto newPos = getNewPositionAfterRightRotation(targi, targj);

    cube.rotateCubeRight();
    targets.clear();

    setupTargetLocations();

    retryTarget(FaceOrientation::UP, newPos.first, newPos.second);
    return;
  }

  while (!Util::compare(adjacentTargetColors, brAdjacentColors))
  {
    cube.d();
    brAdjacentColors = getBrAdjacentFaceColors();
  }

  doActualCubeRotations();
}

// ------------------------------------------------------------------------- //
bool WhiteCorners::nextUnsolvedCornerPiece(SolveStep &unsolvedPiece)
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
          if (
              (i == 0 && j == 0) ||
              (i == 0 && j == 2) ||
              (i == 2 && j == 0) ||
              (i == 2 && j == 2)
             ) 
          {
            auto adjColors = cube.getAdjacentColors(face->getOrientation(), 
                                                    i, j);
            std::vector<FaceColor> adjFaceColors{adjColors.first, 
                                                 adjColors.second};
            // find target with matching adjacent colors
            auto target = std::find_if(
              targets.begin(),
              targets.end(),
              [&] (const auto& targ) {
                std::vector<FaceColor> tarAdjacentColors{targ.adjacentColors
                                                           .at(0).first,
                                                         targ.adjacentColors
                                                           .at(1).first};
                return Util::compare(tarAdjacentColors, adjFaceColors);
            });

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
void WhiteCorners::repositionWhiteCornerPiece(SolveStep &unsolvedPiece)
{
  switch (unsolvedPiece.orientation)
  {
    case FaceOrientation::UP:
    {
      auto orien = (unsolvedPiece.startLocation.second == 2 ? 
                    FaceOrientation::RI : 
                    FaceOrientation::LE);
      repositionTopToBottom(orien, 
                            unsolvedPiece.startLocation.first, 
                            unsolvedPiece);
      break;
    }
    case FaceOrientation::LE:
    {
      if (unsolvedPiece.startLocation.first == 0)
      {
        auto iUp = (unsolvedPiece.startLocation.second == 0 ? 0 : 2);
        repositionTopToBottom(FaceOrientation::LE, iUp, unsolvedPiece);
      }
      else
      {
       respositionBottomToFinal(unsolvedPiece);
      }
      break;
    }
    case FaceOrientation::FR:
    {
      if (unsolvedPiece.startLocation.first == 0)
      {
        auto orien = (unsolvedPiece.startLocation.second == 0 ?
                      FaceOrientation::LE :
                      FaceOrientation::RI);
        repositionTopToBottom(orien, 2, unsolvedPiece);
      }
      else
      {
        respositionBottomToFinal(unsolvedPiece);
      }
      break;
    }
    case FaceOrientation::RI:
    {
      if (unsolvedPiece.startLocation.first == 0)
      {
        auto iUp = (unsolvedPiece.startLocation.second == 2 ? 0 : 2);
        repositionTopToBottom(FaceOrientation::RI, iUp, unsolvedPiece);
      }
      else
      {
        respositionBottomToFinal(unsolvedPiece);
      }
      break;
    }
    case FaceOrientation::BA:
    {
      if (unsolvedPiece.startLocation.first == 0)
      {
        auto orien = (unsolvedPiece.startLocation.second == 0 ?
                      FaceOrientation::RI :
                      FaceOrientation::LE);
        repositionTopToBottom(orien, 0, unsolvedPiece);
      }
      else
      {
        respositionBottomToFinal(unsolvedPiece);
      }
      break;
    }
    case FaceOrientation::DO:
    {
      respositionBottomToFinal(unsolvedPiece);
      break;
    }
    default:
    {
      break;
    }
  }
  return;
}

// ------------------------------------------------------------------------- //
void WhiteCorners::solveStep() {
  spdlog::info("Starting to solve white corners.");
  setupTargetLocations();
  SolveStep unsolvedPiece;

  while (nextUnsolvedCornerPiece(unsolvedPiece))
  {
    repositionWhiteCornerPiece(unsolvedPiece);
  }
  spdlog::info("White corners solved!");
}