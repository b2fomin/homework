#include<chrono>
#include<windows.h>
#include<iostream>

class Stopwatch
{
private:
	using timepoint = std::chrono::steady_clock::time_point;
	timepoint startpoint;
	timepoint stoppoint;
	bool is_stopped;

public:
	Stopwatch();
	void start();
	void stop();
	void reset();
	template<typename ratio>
	int time();
};

Stopwatch::Stopwatch(): is_stopped{ true }
{}

void Stopwatch::start()
{
	is_stopped = false;
	startpoint = std::chrono::steady_clock::now()-(stoppoint-startpoint);
}

void Stopwatch::stop()
{
	stoppoint = std::chrono::steady_clock::now();
}

void Stopwatch::reset()
{
	is_stopped = true;
	startpoint = stoppoint = std::chrono::steady_clock::now();
}

template<typename ratio>
int Stopwatch::time()
{
	if (!is_stopped) stop();
	return std::chrono::duration_cast<ratio>(stoppoint - startpoint).count();
}

int main()
{
	Stopwatch my_watch;

	my_watch.start();

	Sleep(1000);
	my_watch.stop();
	std::cout << my_watch.time<std::chrono::seconds>() << std::endl;

	my_watch.start();
	Sleep(2000);
	std::cout << my_watch.time<std::chrono::seconds>() << std::endl;

	my_watch.reset();
	Sleep(1000);
	std::cout << my_watch.time<std::chrono::seconds>() << std::endl;

	my_watch.start();
	Sleep(1000);
	std::cout << my_watch.time<std::chrono::seconds>() << std::endl;
}