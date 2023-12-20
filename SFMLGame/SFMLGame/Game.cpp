#include "Game.h"
#include "Physics.h"
#include <iostream>

Game::Game(const std::string& config)
{
	init(config);
}

void Game::init(const std::string& config)
{
	//TODO : Readin config file here
	// use the premade playerConfig, enemyConfig, BulletConfig variables;

	//setup default window parameters
	m_window.create(sf::VideoMode(1280, 720), "Game2");
	m_window.setFramerateLimit(60);
	if (!m_font.loadFromFile("gilroy.ttf"))
	{
		std::cout << "Error Loading Font\n";
		exit(-1);
	}
	m_text.setFont(m_font);
	m_text.setCharacterSize(40);
	m_text.setPosition(50, 50);
	m_text.setFillColor(sf::Color::White);
	spawnPlayer();
}
void Game::run() {
	//TODO: Add pause functionality in here
	//Some system should work while pause (rendering)
	//Some system shouldn't (movement/input)

	while (m_running) //This running variable is gonna be true until we exit
	{
		m_entities.update();

		if (!m_pause)
		{
		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		}
		sRender();

		
		//Increment the current frame
		//may need to be moved from here when pause implemented
		m_currentFrame++;
	}
}

void Game::setPaused(bool paused)
{
	//TODO
}
//respawn the player in the middle of the screen
void Game::spawnPlayer() {
	//TODO: Finish adding all the properties of the player with the correct values from the config

	//We create every entity by calling the EntityManader.addEntity(tag)
	//This returns a std::shared_ptr<Entity>, so we use auto to save typing
	auto entity = m_entities.addEntity("player");

	//Give this entity a transform so it spawns at (200,200) with velocity (1,1) at angle (0)
	float mx = m_window.getSize().x / 2.0f;
	float my = m_window.getSize().y / 2.0f;
	entity->cTransform = std::make_shared<CTransform>(Vec2(mx,my), Vec2(1.0f, 1.0f), 0.0f);

	//The entity shape will have a radius of 32, 8 sides, dark grey fill, and red outline of thickness 4
	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	//Add an input component to the player so we can use inputs
	entity->cInput = std::make_shared<CInput>();

	//Since, we want this entity to be our player, set our Game's variable to this Entity
	//This goes slightly against the EntityManager paradigm, but we use the player so much it's worth it
	m_player = entity;
}

void Game::spawnEnemy() {
	//jaise player ka kara tha waise hi karna
	//TODO: make sure the enemy is spawned properly with the m_enemyConfig variables
	//the enemy must be spawned completely within the bounds of the window

	//record when the most recent enemy was spawned
	m_lastEnemySpawnTime = m_currentFrame;
	auto enemy = m_entities.addEntity("enemy");
	float ex = 10 + (rand() % (1+m_window.getSize().x-10));
	float ey = 10 + (rand() % (1+m_window.getSize().y-10));
	float emx = (rand() % (10)) - 5;
	float emy = (rand() % (10)) - 5;
	int points = floor(3 + (rand() % 8));
	enemy->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(emx, emy), 0.0f);
	enemy->cShape = std::make_shared<CShape>(20.0f, points, sf::Color(255, 0, 255), sf::Color(0, 255, 0), 4.0f);
	enemy->cCollision = std::make_shared<CCollision>(20.0f);
	m_score++;
}

//spawns the small enemies, when a big one (input entity e) explodes
void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	//TODO: spawn small enemies at the location of the input enemy e

	// when we create a smaller enemy, we have to read the values of the original enemy
	// - spawn a number of small enemies equal to the vertices of the original enemy
	// - set each small enemy to the same color as it's original, but with half the size
	// - small entities are worth double the points of the original enemy
}

//spawns a bullet from the given entity to a target location
void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2& target)
{
	//TODO: implement the spawning of bullet which travels towards the target
	// - bullet speed is given as a scalar speed
	// - we can se the velocity, using the concept of normalization
	auto bullet = m_entities.addEntity("bullet");
	Vec2 currentPlayerPos = { m_player->cTransform->pos.x, m_player->cTransform->pos.y };
	float bulletSpeed = 10;
	Vec2 bulletVelocity = target;
	bulletVelocity.subtract(currentPlayerPos).normalize().scale(bulletSpeed);
	bullet->cTransform = std::make_shared<CTransform>(currentPlayerPos, bulletVelocity, 0);
	bullet->cShape = std::make_shared<CShape>(10,8,sf::Color(255,255,255),sf::Color(255,0,0),2);
	bullet->cCollision = std::make_shared<CCollision>(15);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	//TODO: implement your own special weapon
}

void Game::sMovement() {
	//TODO: implement all entity movement in this function
	// you should read the m_player->cInput component to determine if the player is moving or not
	m_player->cTransform->velocity = { 0,0 };
	if (m_player->cInput->up)
	{
		m_player->cTransform->velocity.y = -5;
	}
	if (m_player->cInput->down)
	{
		m_player->cTransform->velocity.y = 5;
	}
	if (m_player->cInput->right)
	{
		m_player->cTransform->velocity.x = 5;
	}
	if (m_player->cInput->left)
	{
		m_player->cTransform->velocity.x = -5;
	}
	//sample movement speed update
	//m_player->cTransform->pos.x += m_player->cTransform->velocity.x;
	//m_player->cTransform->pos.y += m_player->cTransform->velocity.y;
	for (auto& e : m_entities.getEntities())
	{
		e->cTransform->pos.x += e->cTransform->velocity.x;
		e->cTransform->pos.y += e->cTransform->velocity.y;
	}

}

void Game::sLifeSpan() {
	//TODO: implement the lifespan functionality

	//for all entities
	// if entity has no lifespan compoenent, skip it
	// if entity has > 0 remaining lifespan, subtract 1
	// if it has lifespan and is alive
	//		scale the aplha channel properly
	// if it has lifespan and time is up
	//		destroy the entity
}
void Game::sCollision() {
	//TODO: implement all proper collision between entities
	// be sure to use the collision radius not the shape radius
	for (auto b : m_entities.getEntities("bullet"))
	{
		for (auto e : m_entities.getEntities("enemy"))
		{
			if (Physics::isCollided(b, e))
			{
				std::cout << "Collision Detected\n";
			}
		}
	}
	for (auto e : m_entities.getEntities("enemy"))
	{
		float cx = e->cTransform->pos.x;
		float cy = e->cTransform->pos.y;
		if (cx - e->cCollision->radius < 0 || cx + e->cCollision->radius > m_window.getSize().x)
		{
			e->cTransform->velocity.x *= -1.0f;
		}
		if (cy - e->cCollision->radius < 0 || cy + e->cCollision->radius > m_window.getSize().y)
		{
			e->cTransform->velocity.y *= -1.0f;
		}
	}
}

void Game::sEnemySpawner() {
	//TODO: code which implements enemy spawning should go here

	// (use m_currentFrame - m_lastEnemySpawnTime) to determine
	// how long it has been since the last enemy appeared
	if (m_currentFrame - m_lastEnemySpawnTime > 60)
	{
		spawnEnemy();
	}
}

void Game::sRender() {
	//TODO: change the code below to draw all of the entities
	// sample drawing of the player entity we have created

	m_window.clear();

	//set the position of the shape based on the entity's transform->pos
	//m_player->cShape->circle.setPosition(m_player->cTransform->pos.x, m_player->cTransform->pos.y);

	//set the rotation of the shape based on the entity's transform->angle
	//m_player->cTransform->angle += 1.0f;
	//m_player->cShape->circle.setRotation(m_player->cTransform->angle);

	//draw the entity's sf::CircleShape
	//m_window.draw(m_player->cShape->circle);

	for (auto e : m_entities.getEntities())
	{
		e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);
		e->cTransform->angle += 1.0f;
		e->cShape->circle.setRotation(e->cTransform->angle);
		m_window.draw(e->cShape->circle);
	}
	std::string score = std::to_string(m_score);
	score = "Entites " + score;
	m_text.setString(score);
	m_window.draw(m_text);
	m_window.display();
}

void Game::sUserInput() {
	//TODO: handle user input here
	// note that you should only be setting player's input compoent variables here
	// you should not implement the player's movement logic here
	// the movement system will read the variables you change in here

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		//this event triggers when the window is closed
		if (event.type == sf::Event::Closed)
		{
			m_running = false;
		}
		//this event is triggered when the key is pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key is pressed\n";
				//TODO: set player's input component "up" to be true
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::A:
				std::cout << "A key is pressed\n";
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				std::cout << "S key is pressed\n";
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				std::cout << "D key is pressed\n";
				m_player->cInput->right = true;
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				std::cout << "W key is pressed\n";
				//TODO: set player's input component "up" to be false
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				std::cout << "A key is pressed\n";
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				std::cout << "S key is pressed\n";
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				std::cout << "D key is pressed\n";
				m_player->cInput->right = false;
				break;
			default:
				break;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				std::cout << "Left mouse button is clicked (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				//call spawnBulletHere
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				std::cout << "Right mouse button is clicked (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
				//call spawnSpecialWeapon here
			}
		}
	}
}