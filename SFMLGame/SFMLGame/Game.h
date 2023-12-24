#pragma once
#include "Entity.h"
#include "EntityManager.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game {
	sf::RenderWindow m_window; //The window we will draw to
	EntityManager m_entities; // vector of entities to maintain
	sf::Font m_font; //The font we will use to draw
	sf::Text m_text;
	sf::Text m_rules;
	sf::Text m_messageText;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::RectangleShape m_timeline;
	sf::SoundBuffer m_shootSound;
	sf::Sound m_shootEffect;
	sf::SoundBuffer m_specialWeapondSoundBuffer;
	sf::Sound m_specialWeaponEffect;
	sf::Music m_bgmusic;
	sf::SoundBuffer m_killSoundBuffer;
	sf::Sound m_killSound;
	PlayerConfig m_playerConfig;
	EnemyConfig m_enemyConfig;
	BulletConfig m_bullerConfig;
	int m_score = 0;
	int m_currentFrame = 0;
	int m_lastEnemySpawnTime = 0;
	bool m_pause = false; //wether we update the game logic
	bool m_running = true; //wether the game is running
	bool m_gameFinish = false; //wether the game is finished or not
	float m_timeRemaining = 0;
	float m_totalTime = 0;
	float m_timeBarWidthPerSecond;
	size_t m_specialWeaponCount = 5;
	std::chrono::time_point<std::chrono::system_clock> m_startTime = std::chrono::system_clock::now();
	std::shared_ptr<Entity> m_player;

	void init(const std::string& config); //Initialize the GameState with a config file
	void setPaused(bool paused); //pause the game
	void setFinished(); //Finish the game

	void sMovement();
	void sUserInput();
	void sLifeSpan();
	void sRender();
	void sEnemySpawner();
	void sCollision();
	void sTimeline();

	void spawnPlayer();
	void spawnEnemy();
	void spawnSmallEnemies(std::shared_ptr<Entity> entity);
	void spawnBullet(std::shared_ptr<Entity> entity, const Vec2& mousePos);
	void spawnSpecialWeapon();
	void showMessage(std::string msg);
	void Timeline(float totalTime);

public:
	Game(const std::string& config); // constructor, takes in the config file
	void run();
};