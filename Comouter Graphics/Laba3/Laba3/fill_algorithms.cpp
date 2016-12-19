//
// Created by vpodilnyk on 21.11.16.
//

#include "fill_algorithms.hpp"


void draw_point(sf::Image &screen, int x, int y, int size) {
  int x_n = x + size;
  int y_n = y + size;
  for (int i = x; i <= x_n; ++i)
    for (int j = y; j <= y_n; ++j)
        screen.setPixel((unsigned)i, (unsigned)j, sf::Color::Green);
}

// sf::Color(150, 15, 200)

void draw_img(sf::RenderWindow &window, sf::Image &screen) {
  sf::Texture texture;
  texture.loadFromImage(screen);
  sf::Sprite sprite(texture);
  window.draw(sprite);
}


bool check_range(sf::Vector2i point) {
  return !((point.x > width || point.x < 0) || (point.y > height || point.y < 0));
}


void flood_fill(sf::RenderWindow &window,sf::Image &screen, sf::Vector2i point) {

  std::vector<sf::Vector2i> points;
  points.push_back(point);
  sf::Color target_color = screen.getPixel((unsigned int)point.x, (unsigned int)point.y);
  while (!points.empty()) {
    sf::Vector2i current_point = points.back();
    points.pop_back();
    draw_point(screen, current_point.x, current_point.y, 0);
    draw_img(window, screen);
    sf::Vector2i left(current_point.x - 1, current_point.y);
    sf::Vector2i right(current_point.x + 1, current_point.y);
    sf::Vector2i top(current_point.x, current_point.y - 1);
    sf::Vector2i bottom(current_point.x, current_point.y + 1);

    if (check_range(left) and screen.getPixel((unsigned int)left.x, (unsigned int)left.y) == target_color)
      points.push_back(left);

    if (check_range(right) and screen.getPixel((unsigned int)right.x, (unsigned int)right.y) == target_color)
      points.push_back(right);

    if (check_range(top) and screen.getPixel((unsigned int)top.x, (unsigned int)top.y) == target_color)
      points.push_back(top);

    if (check_range(bottom) and screen.getPixel((unsigned int)bottom.x, (unsigned int)bottom.y) == target_color)
      points.push_back(bottom);

    window.display();
  }
};


void bresenham_line(sf::RenderWindow &window, sf::Image &screen, sf::Vector2i first, sf::Vector2i second) {
    const bool steep = (abs(second.y - first.y) > abs(second.x - first.x));
    if(steep) {
      std::swap(first.x, first.y);
      std::swap(second.x, second.y);
    }

    if(first.x > second.x) {
      std::swap(first.x, second.x);
      std::swap(first.y, second.y);
    }
    int dx = second.x - first.x;
    int dy = abs(second.y - first.y);
    int error = dx / 2.0f;
    int ystep = (first.y < second.y) ? 1 : -1;
    int y = first.y, x = first.x, maxX = second.x;

    for (; x < maxX; ++x) {

      if (steep)
        draw_point(screen, y, x, 0);

      else
        draw_point(screen, x, y, 0);

      draw_img(window, screen);

      error -= dy;
      if(error < 0) {
        y += ystep;
        error += dx;
      }
    }
    window.display();
    return;
}



void draw_polygon(sf::RenderWindow &window, sf::Image &screen,  std::vector<sf::Vector2i> vect) {
  std::vector<sf::Vector2i>::iterator it, next, end = vect.end();
  --end;
  for (it = vect.begin(); it != end; ++it) {
    next = it + 1;
    bresenham_line(window, screen, *it, *next);
  }
  bresenham_line(window, screen, *next, *vect.begin());
}



void scan_line(sf::RenderWindow &window, sf::Image &screen, std::vector<sf::Vector2i> vect, sf::Vector2i max, sf::Vector2i min) {

  std::vector<sf::Vector2i> points;
  sf::Vector2i start_point, end_point;
  for (int i = min.y; i <= max.y; ++i) {

    points.clear();
    for (int j = min.x; j <= max.x; ++j) {
      if (screen.getPixel((unsigned int) j, (unsigned int) i) == sf::Color::Green) {
        points.push_back(sf::Vector2i(j, i));
          while (screen.getPixel((unsigned int) j, (unsigned int) i) != sf::Color::Black)
              ++j;
      }
    }

    if (!points.empty() and points.size()%2 == 1 and points.size() > 1) {
      std::vector<sf::Vector2i>::iterator iter, pos;
      for (iter = vect.begin(); iter != vect.end(); ++iter) {
        pos = std::find_if(points.begin(), points.end(), [&](sf::Vector2i item) {
            return distance(item, *iter) <= 5;
        });
        if (pos != points.end())
          points.insert(pos, *iter);
      }
    }

    while (!points.empty() and points.size() % 2 == 0 ) {
      end_point = points.back();
      points.pop_back();
      start_point = points.back();
      points.pop_back();
      if (is_vertex(vect, end_point) and is_vertex(vect, start_point))
        continue;
      if (!is_vertex(vect, end_point) or !is_vertex(vect, start_point))
        bresenham_line(window, screen, start_point, end_point);
    }
  }
}

bool is_vertex(std::vector<sf::Vector2i> vect, sf::Vector2i point) {
  return std::find(vect.begin(), vect.end(), point) != vect.end();
}

unsigned int distance(sf::Vector2i start, sf::Vector2i end){
    return (unsigned int)sqrt((start.x - end.x)*(start.x - end.x) + (start.y - end.y)*(start.y - end.y));
}

void xor_fill(sf::RenderWindow &window, sf::Image &screen, std::vector<sf::Vector2i> vect, sf::Vector2i max, sf::Vector2i min) {

  std::vector<sf::Vector2i> points;
  sf::Vector2i start_point, end_point;

  for (int i = min.y; i <= max.y; ++i) {

    points.clear();
    for (int j = min.x; j <= max.x; ++j) {
      if (screen.getPixel((unsigned int) j, (unsigned int) i) == sf::Color(150, 15, 200)) {
        points.push_back(sf::Vector2i(j, i));
        while (screen.getPixel((unsigned int) j, (unsigned int) i) != sf::Color(0, 0, 0))
          ++j;
      }
    }

    if (!points.empty() and points.size()%2 == 1 and points.size() > 1) {
      std::vector<sf::Vector2i>::iterator iter, pos;
      for (iter = vect.begin(); iter != vect.end(); ++iter) {
        pos = std::find_if(points.begin(), points.end(), [&](sf::Vector2i item) {
            return distance(item, *iter) <= 5;
        });
        if (pos != points.end())
          points.insert(pos, *iter);
      }
    }

    while (!points.empty() and points.size()%2 == 0 ) {
      end_point = points.back();
      points.pop_back();
      start_point = points.back();
      points.pop_back();
      if (is_vertex(vect, end_point) and is_vertex(vect, start_point))
        continue;
      if (!is_vertex(vect, end_point) or !is_vertex(vect, start_point))
        xor_line(window, screen, start_point, end_point);
    }
  }
}

void xor_line(sf::RenderWindow &window, sf::Image &screen, sf::Vector2i first, sf::Vector2i second) {
  char current_point, next_point;
  int y = first.y;
  for (int i = first.x; i != second.x ; ++i) {
    if (screen.getPixel((unsigned int)i, (unsigned int)y) == sf::Color::Green)
      current_point = 1;
    else
      current_point = 0;

    if (screen.getPixel((unsigned int)i + 1, (unsigned int)y) == sf::Color::Green)
      next_point = 1;
    else
      next_point = 0;

    if (current_point xor next_point) {
      draw_point(screen, i + 1, y, 0);
      draw_img(window, screen);
    }
  }
  window.display();
}
