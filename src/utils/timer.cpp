#include "timer.hpp"

Timer::Timer() {
	time(&last_activity);
}

Timer::~Timer() {}

double	Timer::GetElapsed() const {
	time_t current;
	time(&current);
	return difftime(current, last_activity);
}

void	Timer::Reset() {
	time(&last_activity);
}
