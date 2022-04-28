#include "Game.h" 
#pragma warning(disable:4996)

int main() // в main очень много кода, а должно быть условно только создание эуземпл€ра класса Game а потом вызов run()
{
	Game game{ W, H, "Asteroid" };
	game.Run();
}