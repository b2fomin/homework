#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>

#include "visualizer.hpp"

int main(int argc, char ** argv)
{
    try 
	{
		Visualizer visualizer{ 1000, 1000, std::complex<float>{-0.2, 0.75} };

		visualizer.run();
    }
    catch (const std::exception & exception) 
	{
        std::cerr << exception.what() << '\n';

		system("pause");

        return EXIT_FAILURE;
    }
	catch (...)
	{
		std::cerr << "Unknown exception\n";

		system("pause");

		return EXIT_FAILURE;
	}

	system("pause");

    return EXIT_SUCCESS;
}
