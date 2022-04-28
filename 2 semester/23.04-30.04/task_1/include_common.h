#pragma once
#include<SFML/Graphics.hpp>
#include<random>
#include<vector>
#include<memory>

const auto W = sf::VideoMode::getDesktopMode().width;
const auto H = sf::VideoMode::getDesktopMode().height;

constexpr float Dectorad = 0.017453f;

enum class EntityType
{
	Asteroid,
	Bullet,
	Player,
    Explosion
};

enum class AnimationType
{
    Explosion,
    Rock,
    Rock_small,
    Bullet,
    Player,
    Player_go,
    Explosion_ship
};