#ifndef INCLUDE_TIMER
#define INCLUDE_TIMER

// A class that stores a timer that counts in ticks, it is mainly used for system based
// calculations such as the FPS but it can have other uses.

class Timer
{
	public:
		// The constructor.
		Timer();
		// Starts the timer.
		void start();
		// Pauses or unpauses the timer based on its current state.
		void pause();
		// Stops the timer and resets its stored time value.
		void stop();
		// Returns the number of ticks the timer has been running for.
		Uint32 getTicks() const;
		// The default destructor.
		~Timer() = default;
	private:
		// The state values of the timer.
		bool started, paused;
		// The tick storage for the timer.
		Uint32 startTicks, pauseTicks;
};

#endif // INCLUDE_TIMER
