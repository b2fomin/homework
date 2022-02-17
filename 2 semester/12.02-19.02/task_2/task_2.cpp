#include<iostream>
#include<chrono>
#include<algorithm>
#include<vector>
#include<deque>
#include<array>
#include<list>
#include<forward_list>

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
	template<typename ratio=std::chrono::microseconds>
	int time();
};

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

template<typename ratio>
int Stopwatch::time()
{
	if (!is_stopped) stoppoint = std::chrono::steady_clock::now();

	return std::chrono::duration_cast<ratio>(stoppoint - startpoint).count();
}

int main()
{
	//////////////////////////////////////////////////////
	const int size = 80001;
	std::vector<int> vector1;
	for (int i = size-1; i > -1; --i) vector1.push_back(i);

	std::array<int, size> array1;
	for (int i = 0; i < size; ++i) array1[i] = size-i;

	std::deque<int> deque1;
	for (int i = size-1; i > -1; --i) deque1.push_back(i);

	std::list<int> list1;
	for (int i = size-1; i > -1; --i) list1.push_back(i);

	std::forward_list<int> forward_list1;
	for (int i = 0; i < size; ++i) forward_list1.push_front(i);

	/////////////////////////////////////////////////////////////
	
	return 0;
}