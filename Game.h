#pragma once //ensures this file is only included once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
// Class that acts as the game engine
//update is all the working physics of the game , render is just realising that physics
class Game  // the whole game program will be an instance of the game class
{
private:
	//variables
	sf::RenderWindow* window; // we want to delete this when we want thus allocating dynamically
	sf::VideoMode videoMode;
	sf::Event ev;

	//mouse positions
	sf::Vector2i mousePosition;
	sf::Vector2f mousePositionView;

	//private functions
	void initVariables();
	void initWindow();
	void initFont();
	void initText();
	void initEnemies();

	//game logic
	unsigned points;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	int health;
	bool endGame;

	//resources
	sf::Font font;

	//text
	sf::Text uiText;

	//game objects
	std::vector <sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

public:
	//constructors / destructors
	Game();
	virtual ~Game();

	//accessors
	const bool running() const;
	const bool getEndGame() const;

	//functions
	void pollEvent();

	void updateMousePos();
	void updateEnemies();
	void updateText();
	void spawnEnemies();
	void update();

	void renderText();
	void renderEnemies();
	void render();
};

