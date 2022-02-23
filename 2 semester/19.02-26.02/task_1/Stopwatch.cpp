#include"Stopwatch.hpp"

Stopwatch::Stopwatch() : is_stopped{ true }
{}

void Stopwatch::start()
{
	if (is_stopped)
	{
		is_stopped = false;
		startpoint = std::chrono::steady_clock::now() - (stoppoint - startpoint);
	}
}

void Stopwatch::stop()
{
	if (!is_stopped)
	{
		is_stopped = true;
		stoppoint = std::chrono::steady_clock::now();
	}
}

void Stopwatch::reset()
{
	is_stopped = true;
	startpoint = stoppoint = std::chrono::steady_clock::now();
}
