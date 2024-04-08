#pragma once
#include <map>
class time
{
public:
	void setTimerMS(int time, double deltaTime);
private:

	// need a map of all queued timers
	//Key: Time set, Can it run?
	std::map<int, bool> queuedTimers; // Using a map due to requiring order so it can always check the first in queue.
};

/*
	Idea
	I'll have a list of timers which are checked each frame.
	i'll use getTicks to set a Now once the timer has been set.

*/