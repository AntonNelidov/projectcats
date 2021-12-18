#pragma once

using namespace sf;
using namespace std;

int menu()
{
	Texture  titleTexture, startTexture, start1Texture, exitTexture, exit1Texture, catTexture, menuBackground;
	titleTexture.loadFromFile("images\\title.png");
	startTexture.loadFromFile("images\\start.png");
	exitTexture.loadFromFile("images\\exit.png");
	start1Texture.loadFromFile("images\\startif.png");
	exit1Texture.loadFromFile("images\\exitif.png");
	menuBackground.loadFromFile("images\\menuback.png");
	catTexture.loadFromFile("images\\spacecat_g.png");

	Sprite menu1(startTexture), menu2(exitTexture), menuBg(menuBackground),
		title(titleTexture), spacecat(catTexture);
	bool isMenu = 1;
	int menuNum = 0;

	spacecat.setPosition(1200, 400);
	title.setPosition(0, 0);
	menu1.setPosition(100, 600);
	menu2.setPosition(100, 710);
	menuBg.setPosition(0, 0);

	RenderWindow menu(VideoMode(1600, 800), L"Space Menu", Style::Default);
	//// Добавление иконки
	//sf::Image icon;
	//if (!icon.loadFromFile("image/icon2.png"))
	//{
	//	return -1;
	//}
	//menu.setIcon(32, 32, icon.getPixelsPtr());

	bool returner = 1; // спец для грамотной работы окна меню
	menu.setFramerateLimit(60);

	int condition_controller = 0;
	//////////////////////////////МЕНЮ ЭКРАН///////////////////
	while (menu.isOpen() && isMenu == true)
	{
		Event event;
		while (menu.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == Event::Closed)
			{
				returner = 0;
				menu.close(); // тогда закрываем его
			}
		}
		menu.clear();
		menu1.setTexture(startTexture);
		menu2.setTexture(exitTexture);
		menuNum = 0;

		spacecat.setPosition(1350, 200);
		spacecat.setScale(-3.5, 3.5);
		/*if (spacecat.getPosition().y > 250.0 && condition_controller == 0)
			spacecat.move(spacecat.getPosition().x, spacecat.getPosition().y - 1);
		else
			condition_controller = 1;

		if(condition_controller == 1 && spacecat.getPosition().y < 550.0)
				spacecat.move(spacecat.getPosition().x, spacecat.getPosition().y + 1);
		else
			condition_controller = 0;*/

		if (IntRect(100, 600, 375, 75).contains(sf::Mouse::getPosition(menu))) { menu1.setTexture(start1Texture); menuNum = 1; }
		if (IntRect(100, 710, 375, 75).contains(sf::Mouse::getPosition(menu))) { menu2.setTexture(exit1Texture); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) { returner = 1; isMenu = false; }
			if (menuNum == 2) { returner = 0; menu.close(); isMenu = false; }
		}


		menu.draw(menuBg);

		menu.draw(spacecat);
		menu.draw(title);
		menu.draw(menu1);
		menu.draw(menu2);
		menu.display();
	}
	return returner;
	////////////////////////////////////////////////////
}