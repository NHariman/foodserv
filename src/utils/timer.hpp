#ifndef TIMER_HPP
#define TIMER_HPP

#include <ctime>

class Timer {
	public:
	Timer();
	~Timer();

	double	GetElapsed() const;
	void	Reset();

	private:
	time_t last_activity;
};

#endif /* TIMER_HPP */
