#include "Game.h" 
#pragma warning(disable:4996)

int main() // � main ����� ����� ����, � ������ ���� ������� ������ �������� ���������� ������ Game � ����� ����� run()
{
	const auto W = sf::VideoMode::getDesktopMode().width;
	const auto H = sf::VideoMode::getDesktopMode().height;

	Game game{ W, H, "Asteroid" };
	game.Run();
}