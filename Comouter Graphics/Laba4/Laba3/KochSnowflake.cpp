#include "KochSnowflake.h"

void KochSnowflake::kochFractal(std::list<Line*> &lines) {
  std::list<Line*> newLines;
  std::list<Line*> delLines;
  for (auto it = lines.begin(); it != lines.end(); ++it) {
    auto firstLine = getFirstLine(*it);
    auto secondLine = getSecondLine(*it);
    auto thirdLine = getThirdLine(*it);
    auto fourthLine = getFourthLine(*it);

    newLines.push_back(firstLine);
    newLines.push_back(secondLine);
    newLines.push_back(thirdLine);
    newLines.push_back(fourthLine);

    delLines.push_back(*it);
  }

  for (auto it = newLines.begin(); it != newLines.end(); ++it)
    lines.push_back(*it);

  for (auto it = delLines.begin(); it != delLines.end(); ++it) {
    lines.remove(*it);
    delete (*it);
  }

};

Line* KochSnowflake::getFirstLine(Line* line) {
  return new Line(line->x, line->y, line->length/3, line->angle);
};

Line* KochSnowflake::getSecondLine(Line* line) {
  int deltaX = (int)(cos(line->angle * M_PI/180) * line->length/3);
  int deltaY = (int)(sin(line->angle * M_PI/180) * line->length/3);
  return new Line(line->x + deltaX, line->y + deltaY, line->length/3, line->angle - 60);
};

Line* KochSnowflake::getThirdLine(Line* line) {
  int deltaX = (int)(cos(line->angle * M_PI/180) * line->length/1.5);
  int deltaY = (int)(sin(line->angle * M_PI/180) * line->length/1.5);
  Line *new_line = new Line(line->x + deltaX, line->y + deltaY, line->length/3, line->angle - 120);
  new_line->x += cos(new_line->angle * M_PI/180) * new_line->length;
  new_line->y += sin(new_line->angle * M_PI/180) * new_line->length;
  new_line->angle -= 180;
  return new_line;
};

Line* KochSnowflake::getFourthLine(Line* line) {
  int deltaX = (int)(cos(line->angle * M_PI/180) * line->length/1.5);
  int deltaY = (int)(sin(line->angle * M_PI/180) * line->length/1.5);
  return new Line(line->x + deltaX, line->y + deltaY, line->length/3, line->angle);
};
