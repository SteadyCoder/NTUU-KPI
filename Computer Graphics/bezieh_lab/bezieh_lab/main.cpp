#include "algo.h"

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "lab2");
  window.setFramerateLimit(30);
  window.clear();
  sf::RectangleShape pixel(sf::Vector2f(X,Y));
  sf::Vector2f base_points[4];
  std::thread *thread = nullptr;
  std::thread *t_thread = nullptr;
  std::thread *r_thread = nullptr;
  std::thread *z_thread = nullptr;
  int sign;
  sf::Vector2f offset;
  int i = 0;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))

      switch (event.type) {
        // window closed
        case sf::Event::Closed:
          window.close();
          break;

          // key pressed
        case sf::Event::MouseButtonPressed:
          if (event.mouseButton.button == sf::Mouse::Left && i < 4) {
            base_points[i].x = event.mouseButton.x;
            base_points[i].y = event.mouseButton.y;
            ++i;
            pixel.setPosition(event.mouseButton.x, event.mouseButton.y);
            window.draw(pixel);
          }
          break;


        case sf::Event::KeyPressed:
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            window.clear();
            thread = new std::thread(bezier_curve, base_points, 4, 0.001);
            thread->join();
            delete thread;
          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            window.clear();
            r_thread = new std::thread(rotate, 10);
            r_thread->join();
            delete r_thread;
          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
            window.clear();
            z_thread = new std::thread(zoom, 1.1);
            z_thread->join();
            delete z_thread;
          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            window.clear();
            z_thread = new std::thread(zoom, 0.91);
            z_thread->join();
            delete z_thread;
          }

          else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            window.clear();
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
              offset = sf::Vector2f(0, -1);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
              offset = sf::Vector2f(0, 1);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
              offset = sf::Vector2f(-1, 0);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
              offset = sf::Vector2f(1, 0);

            t_thread = new std::thread(transport, offset);
            t_thread->join();
            delete t_thread;
          }

        default:
          break;
      }


    if (counter != 0) {
      for (int j = 0; j < MAX_BUFFER_SIZE; ++j) {
        gate.lock();
        if (counter != 0) {
          pixel.setPosition(abs((int) buffer[j].x), abs((int) buffer[j].y));
          window.draw(pixel);
          --counter;
        }
        gate.unlock();
      }
    }
    window.display();
  }
  
  return 0;
}
