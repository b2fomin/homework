#pragma once
#include<chrono>

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
	int time()
	{
		if (!is_stopped) stoppoint = std::chrono::steady_clock::now();

		return std::chrono::duration_cast<ratio>(stoppoint - startpoint).count();
	}

};
