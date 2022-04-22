#include"client.h"

int main()
{
	setlocale(LC_ALL, "RUS");
	Client client{ std::filesystem::current_path()/"client"};
	client.connect("127.0.0.1", 15001);
	while (true)
	{
		client.Update(true);
	}
}