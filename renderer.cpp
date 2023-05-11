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
            window->draw(*object->animator->sprite);
        }

        window->display();

        level->world->Step(timeStep * 100, 10, 10);
        std::this_thread::sleep_for(std::chrono::milliseconds((long long)(timeStep * 1000)));
    }
}


void render(sf::RenderWindow* window, Level* level, Animator* animator) {
//
//    while (window->isOpen())
//    {
//        sf::Event event{};
//        while (window->pollEvent(event))
//        {
//            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
//                window->close();
//        }
//        window->clear(sf::Color::White);
//
//        for (GameObject* object : *level->objects) {
//            object->update();
//            window->draw(*object->shape);
//
//        }
//        animator->update();
//        sf::Sprite sprite;
//        sprite.setTexture(*animator->getCurrentTexture());
//        sprite.setScale(0.2, 0.2);
//        window->draw(sprite);
//        std::cout << animator->getCurrentAnimation()->frame << '\r';
//
//        window->display();
//
//        level->world->Step(timeStep * 100, 10, 10);
//        std::this_thread::sleep_for(std::chrono::milliseconds((long long)(timeStep * 1000)));
//    }
}