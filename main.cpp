//#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>
#include <sstream>
#include <vector>
#include <algorithm>
#include "Menu.hpp"
#include "Classes.hpp"

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

using namespace sf;
using namespace std;



typedef vector<SpaceObject*> Meteors; //для успешной работы случайных метеоров вынужден создать динамические объекты класса


int main()
{
    Clock clock;
    Clock gameTimeClock;//переменная игрового времени, здесь хранить время игры 
    int gameTime = 0;//объявил игровое время
    srand(time(NULL));
    int n = 0, i = 0, t = 0, j = 0; // counters

    if (menu())//вызов меню
    {
        RenderWindow window(VideoMode(1600, 800), L"Space Cat Protection!", Style::Default);// Объект, который, собственно, является главным окном приложения

        /////////////////////////Установка фоновых изображений///////////////////////////////

        Background background_game_on("back.png", window.getSize().x, window.getSize().y);
        Background background_game_over("gameover.png", window.getSize().x, window.getSize().y);

        /////////////////////////Настройки текста и шрифта///////////////////////////////

        Font font;
        font.loadFromFile("fonts\\Wolf4p.ttf");
        Text text("", font, 40);
        /*text.setColor(Color::Black);*/
        /*text.setStyle(Text::Bold);*/

        /////////////////////////Создание персонажей////////////////////////////////////

        SpaceObject Cat("spacecat_g.png", 150, 400, 100.0, 180.0);
        int cat_health = 5;
        int cat_health_calldown = 0;
        float damage_time = -1;
        // spacecat was created!
        //SpaceObject invisibleCat("spacecat_g.png", -100, -400, 100.0, 180.0); // неубиваемый котэ

        Meteors meteors;
        int meteors_amount = 6;
        float speed = 0.9; // скорость метеоров
        for (i = 0; i < meteors_amount; i++)
        {
            n = 100 + (rand() % (1401));
            meteors.push_back(new SpaceObject("meteor.png", 1650, n, 235.0, 165.0/*, 0, 82.5*/));
        } // meteors was created!

        SpaceObject Boom("boom.png", -100, -400, 240.0, 170.0); // взрыв метеора!
        float bx, by; // for Boom spawning


        //////////////////////////////////////////////////////////////////////////////

        gameTimeClock.restart();
        while (window.isOpen())
        {
            if (cat_health > 0)
                gameTime = gameTimeClock.getElapsedTime().asSeconds();

            float time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах
            clock.restart(); //перезагружает время
            time = time / 800; //скорость игры (чем больше делитель - тем плавнее но затратнее игра)

            n = 100 + (rand() % (1401));

            // Обрабатываем очередь событий в цикле
            Event event;
            while (window.pollEvent(event))
            {
                // Пользователь нажал на «крестик» и хочет закрыть окно?
                if (event.type == Event::Closed)
                    window.close(); // тогда закрываем его
            }


            //////////////////////////Meteors Random Generation////////////////////////////

            meteors[0]->sprite.setPosition(
                (meteors[0]->sprite.getPosition().x - speed * time), meteors[0]->sprite.getPosition().y
            );

            for (j = 1; j < meteors_amount; j++)
            {
                if (meteors[j - 1]->sprite.getPosition().x <= 800/*ширина экрана(1600) / 2*/
                    || meteors[j]->sprite.getPosition().x <= 1650 - speed * time/*избавляюсь от прерывости камней*/)
                    meteors[j]->sprite.setPosition(
                        (meteors[j]->sprite.getPosition().x - speed * time), meteors[j]->sprite.getPosition().y
                    );
                if (meteors[j - 1]->sprite.getPosition().x <= -470 * 0.5)
                    meteors[j - 1]->sprite.setPosition(1650, n);
            }
            ///////////////////////////////////Управление космическим котом/////////////////////////////////////////////////
            if (Cat.sprite.getPosition().x > 0.0)
                if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { Cat.sprite.move(-0.6 * time, 0); } //скорость, умножаем её навремя и получаем пройденное расстояние
            if (Cat.sprite.getPosition().x < 1600.0)
                if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) { Cat.sprite.move(0.6 * time, 0); }
            if (Cat.sprite.getPosition().y > -90.0)
                if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) { Cat.sprite.move(0, -0.8 * time); }
            if (Cat.sprite.getPosition().y < 710.0)
                if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { Cat.sprite.move(0, 0.8 * time); }

            /////////////////////////////////////Проверка на столкновение////////////////////////////////////////////////////

            for (t = 0; t < meteors_amount; t++)
                if (meteors[t]->sprite.getGlobalBounds().intersects(Cat.sprite.getGlobalBounds())) //если котэ и метеор сталкиваются
                {
                    bx = meteors[t]->sprite.getPosition().x;
                    by = meteors[t]->sprite.getPosition().y; //уркали коорды для Boom

                    meteors[t]->sprite.setPosition(1650, n);
                    cat_health--;
                    cat_health_calldown = cat_health;
                    damage_time = float(gameTime) + 0.5;
                    break;
                }

            if (gameTime <= damage_time)
            {
                Cat.sprite.setColor(Color::Red);
                cat_health = cat_health_calldown;
                Boom.sprite.setPosition(bx, by);
            }
            else
            {
                Cat.sprite.setColor(Color::White);
                Boom.sprite.setPosition(-100, -400);
            }

            //////////////////////////////////ОТРИСОВКА//////////////////////////////////////////////////////////////

            window.clear();
            window.draw(background_game_on.sprite);
            window.draw(Cat.sprite);
            for (t = 0; t < meteors_amount; t++)
                window.draw(meteors[t]->sprite);
            window.draw(Boom.sprite);

            ostringstream CatHealthString, gameTimeString;  //переменные здоровья и времени
            CatHealthString << cat_health;
            gameTimeString << gameTime; //формирую строки
            text.setString("Health: " + CatHealthString.str() + "\nLife Time: " + gameTimeString.str());//задаем строку тексту и вызываем сформированную выше строку методом .str()
            text.setPosition(100, 10); //задаем позицию текста
            window.draw(text); //рисую этот текст

            if (cat_health <= 0) // окно game over если кот умер
            {
                while (true)
                {
                    Event event;
                    while (window.pollEvent(event))
                    {
                        if (event.type == Event::Closed)
                        {
                            window.close();
                            break;
                        }
                    }
                    window.clear();
                    window.draw(background_game_over.sprite);
                    window.display();
                    if ((Keyboard::isKeyPressed(Keyboard::Enter)))
                        break;
                }
                window.close();
            }
            else window.display(); // иначе дисплей дальше
        }
        std::for_each(meteors.begin(), meteors.end(), default_delete<SpaceObject>()); // подчищаю динамическую память
        meteors.clear();
    }

    return 0;
}
