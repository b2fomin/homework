#include "Game.h" 
#pragma warning(disable:4996)

int main() // в main очень много кода, а должно быть условно только создание эуземпл€ра класса Game а потом вызов run()
{
	const auto W = sf::VideoMode::getDesktopMode().width;
	const auto H = sf::VideoMode::getDesktopMode().height;

	Game game{ W, H, "Asteroid" };
	game.Run();
}