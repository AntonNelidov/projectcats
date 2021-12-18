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



typedef vector<SpaceObject*> Meteors; //��� �������� ������ ��������� �������� �������� ������� ������������ ������� ������


int main()
{
    Clock clock;
    Clock gameTimeClock;//���������� �������� �������, ����� ������� ����� ���� 
    int gameTime = 0;//������� ������� �����
    srand(time(NULL));
    int n = 0, i = 0, t = 0, j = 0; // counters

    if (menu())//����� ����
    {
        RenderWindow window(VideoMode(1600, 800), L"Space Cat Protection!", Style::Default);// ������, �������, ����������, �������� ������� ����� ����������

        /////////////////////////��������� ������� �����������///////////////////////////////

        Background background_game_on("back.png", window.getSize().x, window.getSize().y);
        Background background_game_over("gameover.png", window.getSize().x, window.getSize().y);

        /////////////////////////��������� ������ � ������///////////////////////////////

        Font font;
        font.loadFromFile("fonts\\Wolf4p.ttf");
        Text text("", font, 40);
        /*text.setColor(Color::Black);*/
        /*text.setStyle(Text::Bold);*/

        /////////////////////////�������� ����������////////////////////////////////////

        SpaceObject Cat("spacecat_g.png", 150, 400, 100.0, 180.0);
        int cat_health = 5;
        int cat_health_calldown = 0;
        float damage_time = -1;
        // spacecat was created!
        //SpaceObject invisibleCat("spacecat_g.png", -100, -400, 100.0, 180.0); // ����������� ����

        Meteors meteors;
        int meteors_amount = 6;
        float speed = 0.9; // �������� ��������
        for (i = 0; i < meteors_amount; i++)
        {
            n = 100 + (rand() % (1401));
            meteors.push_back(new SpaceObject("meteor.png", 1650, n, 235.0, 165.0/*, 0, 82.5*/));
        } // meteors was created!

        SpaceObject Boom("boom.png", -100, -400, 240.0, 170.0); // ����� �������!
        float bx, by; // for Boom spawning


        //////////////////////////////////////////////////////////////////////////////

        gameTimeClock.restart();
        while (window.isOpen())
        {
            if (cat_health > 0)
                gameTime = gameTimeClock.getElapsedTime().asSeconds();

            float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
            clock.restart(); //������������� �����
            time = time / 800; //�������� ���� (��� ������ �������� - ��� ������� �� ��������� ����)

            n = 100 + (rand() % (1401));

            // ������������ ������� ������� � �����
            Event event;
            while (window.pollEvent(event))
            {
                // ������������ ����� �� �������� � ����� ������� ����?
                if (event.type == Event::Closed)
                    window.close(); // ����� ��������� ���
            }


            //////////////////////////Meteors Random Generation////////////////////////////

            meteors[0]->sprite.setPosition(
                (meteors[0]->sprite.getPosition().x - speed * time), meteors[0]->sprite.getPosition().y
            );

            for (j = 1; j < meteors_amount; j++)
            {
                if (meteors[j - 1]->sprite.getPosition().x <= 800/*������ ������(1600) / 2*/
                    || meteors[j]->sprite.getPosition().x <= 1650 - speed * time/*���������� �� ���������� ������*/)
                    meteors[j]->sprite.setPosition(
                        (meteors[j]->sprite.getPosition().x - speed * time), meteors[j]->sprite.getPosition().y
                    );
                if (meteors[j - 1]->sprite.getPosition().x <= -470 * 0.5)
                    meteors[j - 1]->sprite.setPosition(1650, n);
            }
            ///////////////////////////////////���������� ����������� �����/////////////////////////////////////////////////
            if (Cat.sprite.getPosition().x > 0.0)
                if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) { Cat.sprite.move(-0.6 * time, 0); } //��������, �������� � ������� � �������� ���������� ����������
            if (Cat.sprite.getPosition().x < 1600.0)
                if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) { Cat.sprite.move(0.6 * time, 0); }
            if (Cat.sprite.getPosition().y > -90.0)
                if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) { Cat.sprite.move(0, -0.8 * time); }
            if (Cat.sprite.getPosition().y < 710.0)
                if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { Cat.sprite.move(0, 0.8 * time); }

            /////////////////////////////////////�������� �� ������������////////////////////////////////////////////////////

            for (t = 0; t < meteors_amount; t++)
                if (meteors[t]->sprite.getGlobalBounds().intersects(Cat.sprite.getGlobalBounds())) //���� ���� � ������ ������������
                {
                    bx = meteors[t]->sprite.getPosition().x;
                    by = meteors[t]->sprite.getPosition().y; //������ ������ ��� Boom

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

            //////////////////////////////////���������//////////////////////////////////////////////////////////////

            window.clear();
            window.draw(background_game_on.sprite);
            window.draw(Cat.sprite);
            for (t = 0; t < meteors_amount; t++)
                window.draw(meteors[t]->sprite);
            window.draw(Boom.sprite);

            ostringstream CatHealthString, gameTimeString;  //���������� �������� � �������
            CatHealthString << cat_health;
            gameTimeString << gameTime; //�������� ������
            text.setString("Health: " + CatHealthString.str() + "\nLife Time: " + gameTimeString.str());//������ ������ ������ � �������� �������������� ���� ������ ������� .str()
            text.setPosition(100, 10); //������ ������� ������
            window.draw(text); //����� ���� �����

            if (cat_health <= 0) // ���� game over ���� ��� ����
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
            else window.display(); // ����� ������� ������
        }
        std::for_each(meteors.begin(), meteors.end(), default_delete<SpaceObject>()); // �������� ������������ ������
        meteors.clear();
    }

    return 0;
}
