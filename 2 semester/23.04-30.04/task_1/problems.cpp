#include "Game.h" 
#pragma warning(disable:4996)

int main() // � main ����� ����� ����, � ������ ���� ������� ������ �������� ���������� ������ Game � ����� ����� run()
{
	Game game{ W, H, "Asteroid" };
	game.Run();
}