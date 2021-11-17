int main(int argc, char* argv[])
{
    // A constant loop that can only be hard-broken is entered.
    while (true)
    {
        // The application is initialised and readied for use.
        System::initialise();
        Menu::initialise();
        Game::initialise();

        Uint64 performanceFrequency = SDL_GetPerformanceFrequency();
        Uint64 lastCounter = SDL_GetPerformanceCounter();
        Uint64 endCounter = 0;
        Uint64 elapsedCounter = 0;

        float deltaTime = 1.0f / 60.0f;

        // The application main loop is entered and remains running until the state is not active.
        while (System::getState() == System::State::ACTIVE)
        {
            // Handles any events that may have occured during this iteration.
            while (SDL_PollEvent(System::getEvent()) != 0)
            {
                // Handles the application events.
                System::handle();
                if (Menu::getState() != Menu::State::INACTIVE) Menu::handle();
                else Game::handle();
            }

            // Goes through the main step of this iteration.
            System::stepBegin();
            if (Menu::getState() != Menu::State::INACTIVE)
            {
                Menu::step();
                Menu::render();
            }
            else
            {
                Game::step();
                Game::render();
            }

            endCounter = SDL_GetPerformanceCounter();
            elapsedCounter = endCounter - lastCounter;

            float elapsed = ((float)elapsedCounter / (float)performanceFrequency);
            while (elapsed < deltaTime)
            {
                float timeLeft = deltaTime - elapsed;
                Uint32 sleep = (Uint32)(1000.0f * timeLeft);
                if (sleep > 0) { SDL_Delay(sleep); }

                elapsedCounter = SDL_GetPerformanceCounter() - lastCounter;
                elapsed = ((float)elapsedCounter / (float)performanceFrequency);
            }

            lastCounter = SDL_GetPerformanceCounter();

            System::stepEnd();
        }

        // The application is terminated if the application's state is no longer active.
        Game::terminate();
        Menu::terminate();
        System::terminate();

        // If the system is resetting then continue this outer loop and return to the top.
        if (System::getState() == System::State::RESETTING) continue;
        // Otheriwse break from the loop and end the process.
        else break;
    }

    // Returns a value of 0 to show success.
    return 0;
}
