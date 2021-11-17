Timer::Timer()
{
    // Sets default values to everything.
    started = false, paused = false;
    startTicks = 0, pauseTicks = 0;
}

void Timer::start()
{
    // Sets the timer's state to started.
    started = true, paused = false;
    // Stores the current amount of ticks since the application's initialisation.
    startTicks = SDL_GetTicks();
    pauseTicks = 0;
}

void Timer::pause()
{
    // Checks to see if the timer is started and unpaused...
    if (started && !paused)
    {
        // ...if so then the timer is paused...
        paused = true;
        // ...and the number of ticks the timer has been running for is stored.
        pauseTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
    // Checks to see if the timer is started and paused...
    else if (started && paused)
    {
        // ...if so then the timer is unpaused...
        paused = false;
        // ...and the time at which the timer was paused is subtracted from the current time to make up.
        startTicks = SDL_GetTicks() - pauseTicks;
        pauseTicks = 0;
    }
}

void Timer::stop()
{
    // Resets the values of everything.
    started = false, paused = false;
    startTicks = 0, pauseTicks = 0;
}

Uint32 Timer::getTicks() const
{
    // Declares a variable to store the ticks the timer has been running for.
    Uint32 ticks = 0;

    // Checks to see if the timer is started...
    if (started)
    {
        // ...if so then it checks to see if the timer is paused, if so then the ticks are set to how many up until the timer's pause...
        if (paused) ticks = pauseTicks;
        // ...otherwise a calculation is done to work out how many ticks have occured since the timer has been started.
        else ticks = SDL_GetTicks() - startTicks;
    }

    // The number of ticks the timer has been running for is then returned.
    return ticks;
}
