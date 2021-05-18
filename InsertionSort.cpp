#include "InsertionSort.h"

void InsertionSort::insertionSort(std::shared_ptr<sf::RenderWindow> screen,
                                  std::vector<sf::RectangleShape>& vec,
                                  std::function<void()> updateScreen,
                                  int& left) {
    for (auto i = 1; i < vec.size(); i++) {
        for (auto k = left; k < vec.size(); k++) {
            vec[k].setFillColor(sf::Color(102, 157, 178));
        }
        auto key = vec[i].getSize().y;
        auto j = i - 1;
        while (j >= 0 && vec[j].getSize().y > key) {
            vec[j].setFillColor(sf::Color::Red);
            vec[j + 1].setSize({vec[j + 1].getSize().x, vec[j].getSize().y});
            vec[j + 1].setFillColor(sf::Color(204, 153, 255));
            j--;
            screen->clear(sf::Color::White);
            updateScreen();
        }
        vec[j + 1].setSize({vec[j + 1].getSize().x, key});
        left++;
        for (auto k = 0; k < left; k++) {
            vec[k].setFillColor(sf::Color(204, 153, 255));
        }
        screen->clear(sf::Color::White);
        updateScreen();
    }
}
