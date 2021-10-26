#include "Time.h"

using namespace std::chrono;

Time::Time()
{
	last = steady_clock::now();
}

float Time::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float Time::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}