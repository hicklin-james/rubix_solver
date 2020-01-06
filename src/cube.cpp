/** Class header */
#include "cube.h"

/** Local headers */
#include "face_parser.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

/** System headers */
#include <iomanip>
#include <iostream>
#include <sstream>

// ------------------------------------------------------------------------- //
Cube::Cube(std::array<CubeFace, 6> faces) : cubeState(faces) {}

// ------------------------------------------------------------------------- //
std::array<CubeFace, 6>::const_iterator Cube::roBegin() const 
{
  return cubeState.begin();
}

// ------------------------------------------------------------------------- //
std::array<CubeFace, 6>::const_iterator Cube::roEnd() const 
{
  return cubeState.end();
}

// ------------------------------------------------------------------------- //
const CubeFace Cube::getFaceAtOrientation(FaceOrientation orientation) 
{
  switch (orientation) 
  {
    case FaceOrientation::FR: 
    {
      return cubeState[0];
      break;
    }
    case FaceOrientation::LE: 
    {
      return cubeState[1];
      break;
    }
    case FaceOrientation::RI: 
    {
      return cubeState[2];
      break;
    }
    case FaceOrientation::BA: 
    {
      return cubeState[5];
      break;
    }
    case FaceOrientation::DO: 
    {
      return cubeState[3];
      break;
    }
    case FaceOrientation::UP: 
    {
      return cubeState[4];
      break; 
    }
    default: 
    {
      CubeFace err_face = FaceParser::parseFaceFromString("W,W,W,W,W,W,W,W,W", 
                                      FaceOrientation::FO_ERR);
      return err_face;
    }
  }
}

// ------------------------------------------------------------------------- //
FaceColor Cube::colorAtFaceAndLoc(FaceOrientation orientation, 
                                          int i, int j) 
{
  auto face = getFaceAtOrientation(orientation);
  if (face.getOrientation() != FaceOrientation::FO_ERR) 
  {
    return face.squares[i][j];
  } 
  else 
  {
    return FaceColor::FC_ERR;
  }
}

// ------------------------------------------------------------------------- //
std::pair<FaceColor, FaceColor> Cube::getAdjacentColors(
  FaceOrientation orientation, int i, int j
)
{
  switch(orientation) {
    case FaceOrientation::FR:
    {
      if (i == 0 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 2, 0),
          colorAtFaceAndLoc(FaceOrientation::LE, 0, 2)
        );
      }
      else if (i == 0 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 2, 2),
          colorAtFaceAndLoc(FaceOrientation::RI, 0, 0)
        );
      }
      else if (i == 2 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::LE, 2, 2),
          colorAtFaceAndLoc(FaceOrientation::DO, 0, 0)
        );
      }
      else if (i == 2 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::RI, 2, 0),
          colorAtFaceAndLoc(FaceOrientation::DO, 0, 2)
        );
      }
      break;
    }
    case FaceOrientation::LE:
    {
      if (i == 0 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 0, 0),
          colorAtFaceAndLoc(FaceOrientation::BA, 0, 2)
        );
      }
      else if (i == 0 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 2, 0),
          colorAtFaceAndLoc(FaceOrientation::FR, 0, 0)
        );
      }
      else if (i == 2 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::DO, 2, 0),
          colorAtFaceAndLoc(FaceOrientation::BA, 2, 2)
        );
      }
      else if (i == 2 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::DO, 0, 0),
          colorAtFaceAndLoc(FaceOrientation::FR, 2, 0)
        );
      }
      break;
    }
    case FaceOrientation::RI:
    {
      if (i == 0 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 2, 2),
          colorAtFaceAndLoc(FaceOrientation::FR, 0, 2)
        );
      }
      else if (i == 0 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 0, 2),
          colorAtFaceAndLoc(FaceOrientation::BA, 0, 0)
        );
      }
      else if (i == 2 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::DO, 0, 2),
          colorAtFaceAndLoc(FaceOrientation::FR, 2, 2)
        );
      }
      else if (i == 2 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::DO, 2, 2),
          colorAtFaceAndLoc(FaceOrientation::BA, 2, 0)
        );
      }
      break;
    }
    case FaceOrientation::BA:
    {
      if (i == 0 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 0, 2),
          colorAtFaceAndLoc(FaceOrientation::RI, 0, 2)
        );
      }
      else if (i == 0 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::UP, 0, 0),
          colorAtFaceAndLoc(FaceOrientation::LE, 0, 0)
        );
      }
      else if (i == 2 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::DO, 2, 2),
          colorAtFaceAndLoc(FaceOrientation::RI, 2, 2)
        );
      }
      else if (i == 2 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::DO, 2, 0),
          colorAtFaceAndLoc(FaceOrientation::LE, 2, 0)
        );
      }
      break;
    }
    case FaceOrientation::DO:
    {
      if (i == 0 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::FR, 2, 0),
          colorAtFaceAndLoc(FaceOrientation::LE, 2, 2)
        );
      }
      else if (i == 0 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::FR, 2, 2),
          colorAtFaceAndLoc(FaceOrientation::RI, 2, 0)
        );
      }
      else if (i == 2 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::BA, 2, 2),
          colorAtFaceAndLoc(FaceOrientation::LE, 2, 0)
        );
      }
      else if (i == 2 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::BA, 2, 0),
          colorAtFaceAndLoc(FaceOrientation::RI, 2, 2)
        );
      }
      break;
    }
    case FaceOrientation::UP:
    {
      if (i == 0 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::LE, 0, 0),
          colorAtFaceAndLoc(FaceOrientation::BA, 0, 2)
        );
      }
      else if (i == 0 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::RI, 0, 2),
          colorAtFaceAndLoc(FaceOrientation::BA, 0, 0)
        );
      }
      else if (i == 2 && j == 0) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::LE, 0, 2),
          colorAtFaceAndLoc(FaceOrientation::FR, 0, 0)
        );
      }
      else if (i == 2 && j == 2) {
        return std::make_pair(
          colorAtFaceAndLoc(FaceOrientation::RI, 0, 0),
          colorAtFaceAndLoc(FaceOrientation::FR, 0, 2)
        );
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return std::make_pair(FaceColor::FC_ERR, FaceColor::FC_ERR);
}

// ------------------------------------------------------------------------- //
FaceColor Cube::getAdjacentFaceColor(FaceOrientation orientation, int i, int j) 
{
  switch(orientation) {
    case FaceOrientation::FR:
    {
      if (i == 0 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::UP, 2, 1);
      }
      else if (i == 1 && j == 0) {
        return colorAtFaceAndLoc(FaceOrientation::LE, 1, 2);
      }
      else if (i == 1 && j == 2) {
        return colorAtFaceAndLoc(FaceOrientation::RI, 1, 0);
      }
      else if (i == 2 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::DO, 0, 1);
      }
      break;
    }
    case FaceOrientation::LE:
    {
      if (i == 0 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::UP, 1, 0);
      }
      else if (i == 1 && j == 0) {
        return colorAtFaceAndLoc(FaceOrientation::BA, 1, 2);
      }
      else if (i == 1 && j == 2) {
        return colorAtFaceAndLoc(FaceOrientation::FR, 1, 0);
      }
      else if (i == 2 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::DO, 1, 0);
      }
      break;
    }
    case FaceOrientation::RI:
    {
      if (i == 0 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::UP, 1, 2);
      }
      else if (i == 1 && j == 0) {
        return colorAtFaceAndLoc(FaceOrientation::FR, 1, 2);
      }
      else if (i == 1 && j == 2) {
        return colorAtFaceAndLoc(FaceOrientation::BA, 1, 0);
      }
      else if (i == 2 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::DO, 1, 2);
      }
      break;
    }
    case FaceOrientation::BA:
    {
      if (i == 0 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::UP, 0, 1);
      }
      else if (i == 1 && j == 0) {
        return colorAtFaceAndLoc(FaceOrientation::RI, 1, 2);
      }
      else if (i == 1 && j == 2) {
        return colorAtFaceAndLoc(FaceOrientation::LE, 1, 0);
      }
      else if (i == 2 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::DO, 2, 1);
      }
      break;
    }
    case FaceOrientation::DO:
    {
      if (i == 0 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::FR, 2, 1);
      }
      else if (i == 1 && j == 0) {
        return colorAtFaceAndLoc(FaceOrientation::LE, 2, 1);
      }
      else if (i == 1 && j == 2) {
        return colorAtFaceAndLoc(FaceOrientation::RI, 2, 1);
      }
      else if (i == 2 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::BA, 2, 1);
      }
      break;
    }
    case FaceOrientation::UP:
    {
      if (i == 0 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::BA, 0, 1);
      }
      else if (i == 1 && j == 0) {
        return colorAtFaceAndLoc(FaceOrientation::LE, 0, 1);
      }
      else if (i == 1 && j == 2) {
        return colorAtFaceAndLoc(FaceOrientation::RI, 0, 1);
      }
      else if (i == 2 && j == 1) {
        return colorAtFaceAndLoc(FaceOrientation::FR, 0, 1);
      }
      break;
    }
    default:
    {
      break;
    }
  }
  return FaceColor::FC_ERR;
}

// ------------------------------------------------------------------------- //
void Cube::printMoveHistory() const 
{
  std::string historyString = "";
  for (auto move : moveHistory) 
  {
     historyString += move + ",";
  }
  historyString.pop_back();
  std::cout << "Moves required: " << historyString << std::endl;
}

// ------------------------------------------------------------------------- //
void Cube::printCube() const 
{
  std::ostringstream stringBuf;
  stringBuf << "Current cube state:" << std::endl;
  stringBuf << std::left << std::setw(8) << "";
  cubeState[4].printRow(0, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[4].printRow(1, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[4].printRow(2, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  stringBuf << "- - -" << std::endl;

  cubeState[1].printRow(0, stringBuf);
  stringBuf << " | ";
  cubeState[0].printRow(0, stringBuf);
  stringBuf << " | ";
  cubeState[2].printRow(0, stringBuf);
  stringBuf << " | ";
  cubeState[5].printRow(0, stringBuf);
  stringBuf << std::endl;
  cubeState[1].printRow(1, stringBuf);
  stringBuf << " | ";
  cubeState[0].printRow(1, stringBuf);
  stringBuf << " | ";
  cubeState[2].printRow(1, stringBuf);
  stringBuf << " | ";
  cubeState[5].printRow(1, stringBuf);
  stringBuf << std::endl;
  cubeState[1].printRow(2, stringBuf);
  stringBuf << " | ";
  cubeState[0].printRow(2, stringBuf);
  stringBuf << " | ";
  cubeState[2].printRow(2, stringBuf);
  stringBuf << " | ";
  cubeState[5].printRow(2, stringBuf);
  stringBuf << std::endl;

  stringBuf << std::left << std::setw(8) << "";
  stringBuf << "- - -" << std::endl;
  stringBuf << std::left << std::setw(8) << "";
  cubeState[3].printRow(0, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[3].printRow(1, stringBuf);
  stringBuf << std::endl << std::left << std::setw(8) << "";
  cubeState[3].printRow(2, stringBuf);
  stringBuf << std::endl;

  spdlog::info(stringBuf.str());
}

// ------------------------------------------------------------------------- //
void Cube::rotateCubeLeft() 
{
  moveHistory.push_back("RLE");
  const auto tempF = std::move(cubeState[0]);
  const auto tempL = std::move(cubeState[1]);
  const auto tempB = std::move(cubeState[5]);
  const auto tempR = std::move(cubeState[2]);

  cubeState[0] = std::move(tempR);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[1] = std::move(tempF);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[5] = std::move(tempL);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[2] = std::move(tempB);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[4].rotateFaceClockwise();
  cubeState[3].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::rotateCubeRight() 
{
  moveHistory.push_back("RRI");
  const auto tempF = std::move(cubeState[0]);
  const auto tempL = std::move(cubeState[1]);
  const auto tempB = std::move(cubeState[5]);
  const auto tempR = std::move(cubeState[2]);

  cubeState[2] = std::move(tempF);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[5] = std::move(tempR);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[1] = std::move(tempB);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[0] = std::move(tempL);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[4].rotateFaceAntiClockwise();
  cubeState[3].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::rotateCubeUp() 
{
  moveHistory.push_back("RUP");
  const auto tempF = std::move(cubeState[0]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempD = std::move(cubeState[3]);
  const auto tempB = std::move(cubeState[5]);

  cubeState[4] = std::move(tempF);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[5] = std::move(tempU);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[5].rotateFaceClockwise();
  cubeState[5].rotateFaceClockwise();
  cubeState[3] = std::move(tempB);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[3].rotateFaceClockwise();
  cubeState[3].rotateFaceClockwise();
  cubeState[0] = std::move(tempD);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[1].rotateFaceAntiClockwise();
  cubeState[2].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::rotateCubeDown() 
{
  moveHistory.push_back("RDO");
  const auto tempF = std::move(cubeState[0]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempD = std::move(cubeState[3]);
  const auto tempB = std::move(cubeState[5]);

  cubeState[3] = std::move(tempF);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[5] = std::move(tempD);
  cubeState[5].setOrientation(FaceOrientation::BA);
  cubeState[5].rotateFaceClockwise();
  cubeState[5].rotateFaceClockwise();
  cubeState[4] = std::move(tempB);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[4].rotateFaceClockwise();
  cubeState[4].rotateFaceClockwise();
  cubeState[0] = std::move(tempU);
  cubeState[0].setOrientation(FaceOrientation::FR);
  cubeState[1].rotateFaceClockwise();
  cubeState[2].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::rotateCubeClockwise() 
{
  moveHistory.push_back("RCW");
  const auto tempL = std::move(cubeState[1]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempR = std::move(cubeState[2]);
  const auto tempD = std::move(cubeState[3]);

  cubeState[2] = std::move(tempU);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[2].rotateFaceClockwise();
  cubeState[3] = std::move(tempR);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[3].rotateFaceClockwise();
  cubeState[1] = std::move(tempD);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[1].rotateFaceClockwise();
  cubeState[4] = std::move(tempL);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[4].rotateFaceClockwise();

  cubeState[0].rotateFaceClockwise();
  cubeState[5].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::rotateCubeAntiClockwise() 
{
  moveHistory.push_back("RAC");
  const auto tempL = std::move(cubeState[1]);
  const auto tempU = std::move(cubeState[4]);
  const auto tempR = std::move(cubeState[2]);
  const auto tempD = std::move(cubeState[3]);

  cubeState[2] = std::move(tempD);
  cubeState[2].setOrientation(FaceOrientation::RI);
  cubeState[2].rotateFaceAntiClockwise();
  cubeState[3] = std::move(tempL);
  cubeState[3].setOrientation(FaceOrientation::DO);
  cubeState[3].rotateFaceAntiClockwise();
  cubeState[1] = std::move(tempU);
  cubeState[1].setOrientation(FaceOrientation::LE);
  cubeState[1].rotateFaceAntiClockwise();
  cubeState[4] = std::move(tempR);
  cubeState[4].setOrientation(FaceOrientation::UP);
  cubeState[4].rotateFaceAntiClockwise();

  cubeState[0].rotateFaceAntiClockwise();
  cubeState[5].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::f() 
{
  moveHistory.push_back("f");
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[2]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[2][2], 
                                      cubeState[1].squares[1][2], 
                                      cubeState[1].squares[0][2]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[0]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[2][0], 
                                       cubeState[2].squares[1][0], 
                                       cubeState[2].squares[0][0]};

  cubeState[4].squares[2] = std::move(leftRotated);
  cubeState[2].squares[0][0] = topRotated[0];
  cubeState[2].squares[1][0] = topRotated[1];
  cubeState[2].squares[2][0] = topRotated[2];
  cubeState[3].squares[0] = std::move(rightRotated);
  cubeState[1].squares[0][2] = bottomRotated[0];
  cubeState[1].squares[1][2] = bottomRotated[1];
  cubeState[1].squares[2][2] = bottomRotated[2];

  cubeState[0].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::fi() 
{
  moveHistory.push_back("fi");
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[2]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[0][2], 
                                      cubeState[1].squares[1][2], 
                                      cubeState[1].squares[2][2]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[0]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[0][0], 
                                       cubeState[2].squares[1][0], 
                                       cubeState[2].squares[2][0]};

  cubeState[1].squares[0][2] = topRotated[2];
  cubeState[1].squares[1][2] = topRotated[1];
  cubeState[1].squares[2][2] = topRotated[0];
  cubeState[3].squares[0] = std::move(leftRotated);
  cubeState[2].squares[0][0] = bottomRotated[2];
  cubeState[2].squares[1][0] = bottomRotated[1];
  cubeState[2].squares[2][0] = bottomRotated[0];
  cubeState[4].squares[2] = std::move(rightRotated);

  cubeState[0].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::r() 
{
  moveHistory.push_back("r");
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][2], 
                                     cubeState[4].squares[1][2], 
                                     cubeState[4].squares[2][2]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][0], 
                                      cubeState[5].squares[1][0], 
                                      cubeState[5].squares[2][0]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][2], 
                                        cubeState[3].squares[1][2], 
                                        cubeState[3].squares[2][2]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][2], 
                                       cubeState[0].squares[1][2], 
                                       cubeState[0].squares[2][2]};

  cubeState[5].squares[0][0] = topRotated[2];
  cubeState[5].squares[1][0] = topRotated[1];
  cubeState[5].squares[2][0] = topRotated[0];
  cubeState[3].squares[0][2] = backRotated[2];
  cubeState[3].squares[1][2] = backRotated[1];
  cubeState[3].squares[2][2] = backRotated[0];
  cubeState[0].squares[0][2] = bottomRotated[0];
  cubeState[0].squares[1][2] = bottomRotated[1];
  cubeState[0].squares[2][2] = bottomRotated[2];
  cubeState[4].squares[0][2] = frontRotated[0];
  cubeState[4].squares[1][2] = frontRotated[1];
  cubeState[4].squares[2][2] = frontRotated[2];

  cubeState[2].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::ri() 
{
  moveHistory.push_back("ri");
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][2], 
                                     cubeState[4].squares[1][2], 
                                     cubeState[4].squares[2][2]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][0], 
                                      cubeState[5].squares[1][0], 
                                      cubeState[5].squares[2][0]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][2], 
                                        cubeState[3].squares[1][2], 
                                        cubeState[3].squares[2][2]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][2], 
                                       cubeState[0].squares[1][2], 
                                       cubeState[0].squares[2][2]};

  cubeState[0].squares[0][2] = topRotated[0];
  cubeState[0].squares[1][2] = topRotated[1];
  cubeState[0].squares[2][2] = topRotated[2];
  cubeState[3].squares[0][2] = frontRotated[0];
  cubeState[3].squares[1][2] = frontRotated[1];
  cubeState[3].squares[2][2] = frontRotated[2];
  cubeState[5].squares[0][0] = bottomRotated[2];
  cubeState[5].squares[1][0] = bottomRotated[1];
  cubeState[5].squares[2][0] = bottomRotated[0];
  cubeState[4].squares[0][2] = backRotated[2];
  cubeState[4].squares[1][2] = backRotated[1];
  cubeState[4].squares[2][2] = backRotated[0];

  cubeState[2].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::l() 
{
  moveHistory.push_back("l");
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][0], 
                                     cubeState[4].squares[1][0], 
                                     cubeState[4].squares[2][0]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][2], 
                                      cubeState[5].squares[1][2], 
                                      cubeState[5].squares[2][2]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][0], 
                                        cubeState[3].squares[1][0], 
                                        cubeState[3].squares[2][0]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][0], 
                                       cubeState[0].squares[1][0], 
                                       cubeState[0].squares[2][0]};

  cubeState[0].squares[0][0] = topRotated[0];
  cubeState[0].squares[1][0] = topRotated[1];
  cubeState[0].squares[2][0] = topRotated[2];
  cubeState[3].squares[0][0] = frontRotated[0];
  cubeState[3].squares[1][0] = frontRotated[1];
  cubeState[3].squares[2][0] = frontRotated[2];
  cubeState[5].squares[0][2] = bottomRotated[2];
  cubeState[5].squares[1][2] = bottomRotated[1];
  cubeState[5].squares[2][2] = bottomRotated[0];
  cubeState[4].squares[0][0] = backRotated[2];
  cubeState[4].squares[1][0] = backRotated[1];
  cubeState[4].squares[2][0] = backRotated[0];

  cubeState[1].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::li() 
{
  moveHistory.push_back("li");
  std::array<FaceColor,3> topRotated{cubeState[4].squares[0][0], 
                                     cubeState[4].squares[1][0], 
                                     cubeState[4].squares[2][0]};
  std::array<FaceColor,3> backRotated{cubeState[5].squares[0][2], 
                                      cubeState[5].squares[1][2], 
                                      cubeState[5].squares[2][2]};
  std::array<FaceColor,3> bottomRotated{cubeState[3].squares[0][0], 
                                        cubeState[3].squares[1][0], 
                                        cubeState[3].squares[2][0]};
  std::array<FaceColor,3> frontRotated{cubeState[0].squares[0][0], 
                                       cubeState[0].squares[1][0], 
                                       cubeState[0].squares[2][0]};  

  cubeState[4].squares[0][0] = frontRotated[0];
  cubeState[4].squares[1][0] = frontRotated[1];
  cubeState[4].squares[2][0] = frontRotated[2];
  cubeState[5].squares[0][2] = topRotated[2];
  cubeState[5].squares[1][2] = topRotated[1];
  cubeState[5].squares[2][2] = topRotated[0];
  cubeState[3].squares[0][0] = backRotated[2];
  cubeState[3].squares[1][0] = backRotated[1];
  cubeState[3].squares[2][0] = backRotated[0];
  cubeState[0].squares[0][0] = bottomRotated[0];
  cubeState[0].squares[1][0] = bottomRotated[1];
  cubeState[0].squares[2][0] = bottomRotated[2];

  cubeState[1].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::u() 
{
  moveHistory.push_back("u");
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[0]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[0]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[0]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[0]);

  cubeState[1].squares[0] = std::move(frontRotated);
  cubeState[5].squares[0] = std::move(leftRotated);
  cubeState[2].squares[0] = std::move(backRotated);
  cubeState[0].squares[0] = std::move(rightRotated);

  cubeState[4].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::ui() 
{
  moveHistory.push_back("ui");
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[0]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[0]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[0]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[0]);

  cubeState[1].squares[0] = std::move(backRotated);
  cubeState[5].squares[0] = std::move(rightRotated);
  cubeState[2].squares[0] = std::move(frontRotated);
  cubeState[0].squares[0] = std::move(leftRotated);

  cubeState[4].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::d() 
{
  moveHistory.push_back("d");
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[2]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[2]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[2]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[2]);

  cubeState[2].squares[2] = std::move(frontRotated);
  cubeState[5].squares[2] = std::move(rightRotated);
  cubeState[1].squares[2] = std::move(backRotated);
  cubeState[0].squares[2] = std::move(leftRotated);

  cubeState[3].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::di() 
{
  moveHistory.push_back("di");
  std::array<FaceColor,3> leftRotated = std::move(cubeState[1].squares[2]);
  std::array<FaceColor,3> backRotated = std::move(cubeState[5].squares[2]);
  std::array<FaceColor,3> rightRotated = std::move(cubeState[2].squares[2]);
  std::array<FaceColor,3> frontRotated = std::move(cubeState[0].squares[2]);

  cubeState[2].squares[2] = std::move(backRotated);
  cubeState[5].squares[2] = std::move(leftRotated);
  cubeState[1].squares[2] = std::move(frontRotated);
  cubeState[0].squares[2] = std::move(rightRotated);

  cubeState[3].rotateFaceAntiClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::b() 
{
  moveHistory.push_back("b");
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[0]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[0][0], 
                                      cubeState[1].squares[1][0], 
                                      cubeState[1].squares[2][0]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[2]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[0][2], 
                                       cubeState[2].squares[1][2], 
                                       cubeState[2].squares[2][2]};

  cubeState[4].squares[0] = std::move(rightRotated);
  cubeState[1].squares[0][0] = topRotated[2];
  cubeState[1].squares[1][0] = topRotated[1];
  cubeState[1].squares[2][0] = topRotated[0];
  cubeState[3].squares[2] = std::move(leftRotated);
  cubeState[2].squares[0][2] = bottomRotated[2];
  cubeState[2].squares[1][2] = bottomRotated[1];
  cubeState[2].squares[2][2] = bottomRotated[0];

  cubeState[5].rotateFaceClockwise();
}

// ------------------------------------------------------------------------- //
void Cube::bi() 
{
  moveHistory.push_back("bi");
  std::array<FaceColor,3> topRotated = std::move(cubeState[4].squares[0]);
  std::array<FaceColor,3> leftRotated{cubeState[1].squares[0][0], 
                                      cubeState[1].squares[1][0], 
                                      cubeState[1].squares[2][0]};
  std::array<FaceColor,3> bottomRotated = std::move(cubeState[3].squares[2]);
  std::array<FaceColor,3> rightRotated{cubeState[2].squares[0][2], 
                                       cubeState[2].squares[1][2], 
                                       cubeState[2].squares[2][2]};

  cubeState[4].squares[0][0] = leftRotated[2];
  cubeState[4].squares[0][1] = leftRotated[1];
  cubeState[4].squares[0][2] = leftRotated[0];
  cubeState[1].squares[0][0] = bottomRotated[0];
  cubeState[1].squares[1][0] = bottomRotated[1];
  cubeState[1].squares[2][0] = bottomRotated[2];
  cubeState[3].squares[2][0] = rightRotated[2];
  cubeState[3].squares[2][1] = rightRotated[1];
  cubeState[3].squares[2][2] = rightRotated[0];
  cubeState[2].squares[0][2] = topRotated[0];
  cubeState[2].squares[1][2] = topRotated[1];
  cubeState[2].squares[2][2] = topRotated[2];

  cubeState[5].rotateFaceAntiClockwise();
}