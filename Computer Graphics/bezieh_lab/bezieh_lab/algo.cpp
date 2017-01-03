//
// Created Ivan Tkachenko
//

#include "algo.h"
std::vector<sf::Vector2f> buffer(MAX_BUFFER_SIZE);
std::vector<sf::Vector2f> coordinates(MAX_BUFFER_SIZE);
int counter = 0;
std::mutex gate;

float power(float t, int i){
  if (!i) return 1;
  else return (i == 1) ? t : t * power(t, i - 1);
}
int factorial(int n) {
  return  (n <= 1) ? 1 : n * factorial(n - 1);
}

double get_bezier_basis(int current_point, int num_of_points, float parameter) {
  return (factorial(num_of_points) / (factorial(current_point) * factorial(num_of_points - current_point))) * \
  power(parameter, current_point) * power(1 - parameter, num_of_points - current_point);
}

void bezier_curve(sf::Vector2f *vector, int length, float step) {
  double basis;
  int j = 0;

  for (float t = 0; t < 1 + step; t += step) {
    if (t > 1)
      t = 1;
    gate.lock();
    for (int i = 0; i < length; ++i) {
      basis = get_bezier_basis(i, length - 1, t);
      buffer[j].x += vector[i].x * basis;
      buffer[j].y += vector[i].y * basis;
      coordinates[j] = buffer[j];
    }

    ++j;
    ++counter;
    gate.unlock();
  }
}



void zoom(float scale) {
  for (int i = 0; i < MAX_BUFFER_SIZE; ++i) {
    gate.lock();
    buffer[i] = coordinates[i];
    buffer[i].x *= scale;
    buffer[i].y *= scale;
    coordinates[i] = buffer[i];
    ++counter;
    gate.unlock();
  }
}

void rotate(float angle) {
  for (int i = 0; i < MAX_BUFFER_SIZE; ++i) {
    gate.lock();
    buffer[i] = coordinates[i];
    buffer[i].x = coordinates[i].x * cos(angle) - coordinates[i].y * sin(angle);
    buffer[i].y = coordinates[i].x * sin(angle) + coordinates[i].y * cos(angle);
    coordinates[i] = buffer[i];
    ++counter;
    gate.unlock();
  }
}

void transport(sf::Vector2f offset) {
  for (int i = 0; i < MAX_BUFFER_SIZE; ++i) {
    gate.lock();
    buffer[i] = coordinates[i];
    buffer[i] += offset;
    coordinates[i] = buffer[i];
    ++counter;
    gate.unlock();
  }
}
