#include<SFML/Graphics.hpp>
#include<iostream>

using namespace std;

struct GAME
{
	sf::Texture plane, bullet, rock, background;
};

int timer = 0;


void creatBullet(sf::Sprite& BULLET, vector<sf::Sprite>& Bullet, sf::Sprite& PLANE);
void shooting(vector<sf::Sprite>& Bullet, sf::RenderWindow& win);
void creatRock(sf::RenderWindow& win, sf::Sprite& ROCK, vector<sf::Sprite>& Rock);
void drawRock(sf::RenderWindow& win, vector<sf::Sprite>& Rock);
void checkBullet(vector<sf::Sprite>& Rock, vector<sf::Sprite>& Bullet);

int main()
{
	srand(time(NULL));
	GAME game;
	// load image
	game.bullet.loadFromFile("resources/bullet.png");
	game.rock.loadFromFile("resources/rock.png");
	game.plane.loadFromFile("resources/plane.png");
	game.background.loadFromFile("resources/BACKGROUND2.jpg");
	//
	sf::Sprite BULLET(game.bullet);
	//
	vector<sf::Sprite> Bullet;
	//
	sf::Sprite ROCK(game.rock);
	vector<sf::Sprite>Rock;
	//
	sf::Sprite PLANE(game.plane);
	// set background
	sf::Sprite BACKROUND(game.background);
	// load background 
	sf::RenderWindow window(sf::VideoMode(game.background.getSize().x, game.background.getSize().y)
		, "GAME ", sf::Style::Default);
	window.setFramerateLimit(60);
	// set pos plane
	PLANE.setPosition(250.f, 300.f);
	while (window.isOpen())
	{
		sf::Event evnt;
		// draw background
		window.draw(BACKROUND);
		// set plane move mouse
		PLANE.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
		window.draw(PLANE);
		creatRock(window, ROCK, Rock);
		while (window.pollEvent(evnt))
		{

			if (evnt.type == evnt.Closed)	window.close();
			if (evnt.type == evnt.MouseButtonPressed)
			{
				creatBullet(BULLET, Bullet, PLANE);
			}
		}
		//drawRock(window, Rock);
		shooting(Bullet, window);
		checkBullet(Rock, Bullet);
		window.display();
		window.clear();
	}
}
void creatBullet(sf::Sprite &BULLET, vector<sf::Sprite> &Bullet, sf::Sprite &PLANE)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		BULLET.setPosition(PLANE.getPosition().x, PLANE.getPosition().y);
		Bullet.push_back(BULLET);
	}
}
void shooting(vector<sf::Sprite>& Bullet, sf::RenderWindow& win)
{
	for (int i = 0;i < Bullet.size();i++)
	{
		Bullet[i].move(0.f, -4.f);
		win.draw(Bullet[i]);
	}
	for (int i = 0;i < Bullet.size();i++)
	{
		if (Bullet[i].getPosition().y <= 10)
		{
			Bullet.erase(Bullet.begin() + i);
		}
	}
}
void creatRock(sf::RenderWindow& win, sf::Sprite& ROCK, vector<sf::Sprite>& Rock)
{
	if (timer >= 20)
	{
		ROCK.setPosition(rand() % (win.getSize().x) - ROCK.getGlobalBounds().width, 10.f);
		Rock.push_back(ROCK);
		timer = 0;
	}
	timer++;
	for (int i = 0;i < Rock.size();i++)
	{
		Rock[i].move(0.f, 3.f);
		win.draw(Rock[i]);
	}
	
}
//void drawRock(sf::RenderWindow& win, vector<sf::Sprite>& Rock)
//{
//	for (int i = 0;i < Rock.size();i++)
//	{
//		Rock[i].move(0.f, 1.8f);
//		win.draw(Rock[i]);
//	}
//}
void checkBullet(vector<sf::Sprite>& Rock, vector<sf::Sprite>& Bullet)
{
	for (int i = 0;i < Bullet.size();i++)
	{
		for (int j = 0;j < Rock.size();j++)
		{
			if (Bullet[i].getGlobalBounds().intersects(Rock[j].getGlobalBounds()))
			{
				Bullet.erase(Bullet.begin() + i);
				Rock.erase(Rock.begin() + j);
				break;
			}
		}
	}
}