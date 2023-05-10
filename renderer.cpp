#include "renderer.h"

void render(sf::RenderWindow* window, Level* level) {

    while (window->isOpen())
    {
        sf::Event event{};
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window->close();
        }
        window->clear(sf::Color::White);

        for (GameObject* object : *level->objects) {
            object->update();
            window->draw(*object->shape);
        }

        std::cout << level->objects->at(0)->toStringBodyPosition() << '\r';

        window->display();

        level->world->Step(0.1f, 10, 10);

    }
}
