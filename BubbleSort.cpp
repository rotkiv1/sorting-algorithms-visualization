#include "BubbleSort.h"

void BubbleSort::bubbleSort(std::shared_ptr<sf::RenderWindow> screen,
                            std::vector<sf::RectangleShape>& vec,
                            std::function<void()> updateScreen) {
    for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = 0; j < vec.size() - i - 1; j++) {
            screen->clear(sf::Color::White);
            vec[j + 1].setFillColor(sf::Color::Red);
            vec[j].setFillColor(sf::Color::Red);
            updateScreen();
            if (vec[j + 1].getSize().y < vec[j].getSize().y) {
                auto temp = vec[j].getSize().y;
                vec[j].setSize({vec[j].getSize().x, vec[j + 1].getSize().y});
                vec[j + 1].setSize({vec[j + 1].getSize().x, temp});
            }
            vec[j].setFillColor(sf::Color(102, 157, 178));
            vec[j + 1].setFillColor(sf::Color(102, 157, 178));
            screen->clear(sf::Color::White);
            updateScreen();
            }
            for (auto k = vec.size() - i - 1; k < vec.size(); k++) {
                if (vec.size() - i - 1 == 1) {
                    vec.front().setFillColor(sf::Color(204, 153, 255));
                }
                vec[k].setFillColor(sf::Color(204, 153, 255));
            }
        }
}
