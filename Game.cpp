#include "Game.h"
// private functions
void Game::initVariables()
{
	this->window = nullptr;
	this->points = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this -> enemySpawnTimerMax; // stars at max to load an enemy and resets to 0
	this->maxEnemies = 10;
	this->health = 20;
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "Game1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(135);
}
void Game::initFont()
{
	this->font.loadFromFile("Font/Pacifico.ttf"); //initialising function for all fonts
}

void Game::initText()  //initialising function for all texts
{
	this->uiText.setFont(this->font); //font
	this->uiText.setCharacterSize(22); // size
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setString("NONE");  //string
}

void Game::initEnemies()	
{	//default rendering position is 0 , 0  ; origin is at top left
	this->enemy.setPosition(400, 300);  //you refer to the top left point of the shape , not the center
	this->enemy.setSize(sf::Vector2f(100.f, 100.f)); // vector to set size , .f to show its already float
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f)); // actual size is size * scale
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::White);
	this->enemy.setOutlineThickness(1.f);
}
//constructor destructor
Game::Game()
{
	this->initVariables();
	this->initWindow();	
	this->initEnemies();
	this->initFont();
	this->initText();
}

Game::~Game() //destructor
{
	delete this->window;
}
const bool Game::running() const
{
	return this -> window -> isOpen();
}

const bool Game::getEndGame() const
{
	return this -> endGame;
}

void Game::pollEvent() //polling events 
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
			{
				this->window->close();
			}
		}
	}
}
//public functions

void Game::updateMousePos()
{
	this->mousePosition = sf::Mouse::getPosition(*this->window); //updates mouse position after every frame
	this->mousePositionView = this->window->mapPixelToCoords(this->mousePosition);
}
void Game::spawnEnemies()
{
	//sets their colours and positions
	//spawns randomly
	//adds them to the vector
	this->enemy.setPosition( //randomly spawn on the top
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);
	this->enemy.setFillColor(sf::Color::Green);
	this->enemies.push_back(this->enemy);

}

void Game::updateEnemies() //just update the number and positions of the enemies
{
	if (this->enemies.size() < this->maxEnemies) //checking if enemies are less than max enemies
	{
		if (this->enemySpawnTimer == this->enemySpawnTimerMax)
		{
			this->spawnEnemies(); //rendering enemies
			this->enemySpawnTimer = 0.f; //resetting timer
		}
		else
		{
			enemySpawnTimer += 1.f; //updating timer
		}
	}

	for (int i = 0 ; i < this -> enemies.size() ;i++) //move enemies , check if mouse is pressed m then check if it is pressed on the enemy
	{
		bool deleted = false;
		this->enemies[i].move(0.f, 2.f);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (this->enemies[i].getGlobalBounds().contains(this->mousePositionView))
			{
				deleted = true;
				//adding points
				this->points += 10;
				std::cout << "You have " << this->points << "points" << std::endl;
			}
		}

		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			deleted = true;
			this -> health -= 1;
			std::cout << "Your health is: " << this->health << std::endl;
		}

		if (deleted)
		{
			this->enemies.erase(enemies.begin() + i);
		}
	}
}

void Game::updateText()
{
	std::stringstream ss; //works like streams - cout and cin
	ss << "POINTS: " << this->points;
	this->uiText.setString(ss.str());
}

void Game::update() //updatign according to polling events
{
	this->pollEvent();
	if (this->endGame == false)
	{
		this->updateMousePos();

		//std::cout << "Mouse position is:" << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << std::endl;
		//this outputs mouse's relative position every frame wet to the window the program opens
		this->updateEnemies();
		this->updateText();

	}

	if (this->health <= 0)
	{
		this -> endGame = true;
	}

	if (this -> endGame)
	{
		std::cout << "Congratulations , You had " << this->points << " points!!" << std::endl; //final display of points
	}
}

void Game::renderText()
{
	this->window->draw(uiText);   //render uiText
}

void Game::renderEnemies()
{
	//rendering enemies
	for (auto& i : this->enemies)
	{
		this->window->draw(i);
	}
}

void Game::render() //render updates values , clear frame , reloa objects , display 
{
	this->window->clear();

	//render game objects
	this->renderEnemies();
	this->renderText();
	this->window->display();

}
