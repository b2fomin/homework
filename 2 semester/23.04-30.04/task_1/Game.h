#pragma once
#include"Asteroid.h"
#include"Bullet.h"
#include"Player.h"
#include<string>
#include<map>
#include<Windows.h>// for message box

class Game
{
private:
	constexpr static int textures_number = 7;
	constexpr static float rock_radius = 25;
	constexpr static float small_rock_radius = 15;
	constexpr static int max_rocks = 10;
	const static sf::Time immortality_time;
private:
	sf::RenderWindow m_app;
	std::vector<sf::Texture> m_textures;
	sf::Sprite m_background;
	std::map<AnimationType, Animation> m_animations;
	std::map<std::shared_ptr<Entity>, std::shared_ptr<Entity>> m_collisions;
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::shared_ptr<Player> m_player;
	sf::Text score_and_HP;
	sf::Font font;
public:
	Game(const std::size_t width, const std::size_t height, const char* name)
		: m_app{ sf::VideoMode(width, height), name }
	{
		m_app.setFramerateLimit(60);

		if (!font.loadFromFile("task_1/font/DihjautiS-Regular.otf"))
		{
			throw std::exception("Can't load file");
		}

		score_and_HP.setFont(font);
		score_and_HP.setFillColor(sf::Color::Red);

		m_textures.resize(textures_number);
		m_textures[0].loadFromFile("task_1/images/spaceship.png");
		m_textures[1].loadFromFile("task_1/images/background.jpg");
		m_textures[2].loadFromFile("task_1/images/explosions/type_C.png");
		m_textures[3].loadFromFile("task_1/images/rock.png");
		m_textures[4].loadFromFile("task_1/images/fire_blue.png");
		m_textures[5].loadFromFile("task_1/images/rock_small.png");
		m_textures[6].loadFromFile("task_1/images/explosions/type_B.png");

		m_textures[0].setSmooth(true);
		m_textures[1].setSmooth(true);
		m_background.setTexture(m_textures[1]);

		m_animations.emplace(AnimationType::Explosion, Animation(m_textures[2], 0, 0, 256, 256, 48, 0.5));
		m_animations.emplace(AnimationType::Rock, Animation(m_textures[3], 0, 0, 64, 64, 16, 0.2));
		m_animations.emplace(AnimationType::Rock_small, Animation(m_textures[5], 0, 0, 64, 64, 16, 0.2));
		m_animations.emplace(AnimationType::Bullet, Animation(m_textures[4], 0, 0, 32, 64, 16, 0.8));
		m_animations.emplace(AnimationType::Player, Animation(m_textures[0], 40, 0, 40, 40, 1, 0));
		m_animations.emplace(AnimationType::Player_go, Animation(m_textures[0], 40, 40, 40, 40, 1, 0));
		m_animations.emplace(AnimationType::Explosion_ship, Animation(m_textures[6], 0, 0, 192, 192, 64, 0.5));

		auto size = m_app.getSize();
		for (int i = 0; i < 15; i++)
		{
			m_entities.push_back(std::make_shared<Asteroid>(m_animations.find(AnimationType::Rock)->second, size.x,
				size.y, rock_radius));
		}

		m_player = std::make_shared<Player>(m_animations.find(AnimationType::Player)->second, 3, 200, 200, 0, 0, 0, 20);
		m_entities.push_back(m_player);
	}
private:
	void create_collisions_map()
	{
		int rocks_count{ 0 };
		for (auto& entity1: m_entities)
		{
			if (entity1->get_type() != EntityType::Asteroid) continue;
			else ++rocks_count;
			if (rocks_count > max_rocks)
 			{
				entity1->set_HP(0);
				--rocks_count;
			}
			else
			{
				for (auto& entity2 : m_entities)
				{
					if (entity1 != entity2 && Entity::isCollide(entity1, entity2))
					{
						m_collisions[entity1] = entity2;
					}
				}
			}
		}
	}

	void update_entities_and_delete_dead_ones()
	{
		for (auto i = m_entities.begin(); i != m_entities.end();)
		{
			auto entity = *i;
			auto size = m_app.getSize();
			entity->update(size.x, size.y);
			entity->get_anim().update();

			if (entity->get_HP() == 0) { entity.reset(); i = m_entities.erase(i); }
			else i++;
		}
	}

	void check_keyboard(sf::Event& _event)
	{
		if (_event.type == sf::Event::KeyPressed &&
			_event.key.code == sf::Keyboard::Space)
		{
			m_entities.push_back(std::make_shared<Bullet>(m_animations.find(AnimationType::Bullet)->second,
				m_player->get_x(), m_player->get_y(), 0.f, 0.f, m_player->get_angle(), 10));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) m_player->set_angle(m_player->get_angle() + 3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  m_player->set_angle(m_player->get_angle() - 3);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) m_player->set_thrust(true);
		else m_player->set_thrust(false);
	}

public:
	void Run()
	{
		sf::Event _event;
		sf::Clock clock;
		while (m_player->is_alive())
		{
			m_app.pollEvent(_event);
			if (_event.type == sf::Event::Closed)
			{
				m_app.close();
				break;
			}

			check_keyboard(_event);

			create_collisions_map();
			for (auto& collision : m_collisions)
			{
				if (collision.first->get_type() == EntityType::Asteroid)
				{
					bool is_immortal;
					if (clock.getElapsedTime() >= immortality_time) is_immortal = false;
					else is_immortal = true;

					if (collision.second->get_type() == EntityType::Bullet)
					{
						collision.second->set_HP(collision.second->get_HP() - 1);
						m_player->score_increase();
					}

					if (!is_immortal && collision.second->get_type() == EntityType::Player)
					{
						collision.second->set_HP(collision.second->get_HP() - 1);
						m_entities.push_back(std::make_shared<Entity>(EntityType::Explosion,
							m_animations.find(AnimationType::Explosion_ship)->second, 1, collision.first->get_x(), collision.first->get_y(), 0, 0, 0, 1));

						auto player_HP = m_player->get_HP();
						auto player_score = m_player->get_score();
						auto player_thrust = m_player->get_thrust();
						auto size = m_app.getSize();
						m_entities.erase(std::find(m_entities.begin(), m_entities.end(), m_player));
						m_player.reset();
						m_player = std::make_shared<Player>(m_animations.find(AnimationType::Player)->second, player_HP, size.x / 2, size.y / 2, 0, 0, 0, 20);
						m_player->set_score(player_score);
						m_player->set_thrust(player_thrust);
						m_entities.push_back(m_player);
						clock.restart();
					}

					if (!is_immortal || collision.second->get_type()==EntityType::Bullet)
					{
						collision.first->set_HP(0);

						m_entities.push_back(std::make_shared<Entity>(EntityType::Explosion,
							m_animations.find(AnimationType::Explosion)->second, 1, collision.first->get_x(), collision.first->get_y(), 0, 0, 0, 20));


						for (int i = 0; i < 2; i++)
						{
							if (collision.first->get_r() == small_rock_radius) continue;
							
							std::random_device rd;
							std::default_random_engine gen{ rd() };
							std::uniform_int_distribution<int> angle_dist(0, 360);

							m_entities.push_back(std::make_shared<Asteroid>(m_animations.find(AnimationType::Rock_small)->second,
								collision.first->get_x(), collision.first->get_y(), angle_dist(gen), small_rock_radius));
						}
					}
				}

			}

			m_collisions.clear();

			if (m_player->get_thrust())  m_player->set_anim(m_animations.find(AnimationType::Player_go)->second);
			else   m_player->set_anim(m_animations.find(AnimationType::Player)->second);

			for (auto& e : m_entities)
				if (e->get_type() == EntityType::Explosion)
					if (e->get_anim().isEnd()) e->set_HP(0);


			if (rand() % 150 == 0)
			{
				auto size = m_app.getSize();

				m_entities.push_back(std::make_shared<Asteroid>(m_animations.find(AnimationType::Rock)->second, size.x,
					size.y, rock_radius));
			}

			update_entities_and_delete_dead_ones();

			score_and_HP.setString("score: " + std::to_string(m_player->get_score()) +
				"\nLifes: " + std::to_string(m_player->get_HP()));
			m_app.draw(m_background);
			m_app.draw(score_and_HP);
			for (auto& i : m_entities) i->draw(m_app);
			m_app.display();
		}

		const std::wstring string = L"You've scored " +
			std::to_wstring(m_player->get_score()) + L" points";

		int msg = MessageBox(nullptr, string.data(), L"Account Details", MB_OK);

	}
	

};

const sf::Time Game::immortality_time = sf::seconds(3);