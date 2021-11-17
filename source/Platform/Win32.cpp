int main(int argc, char* argv[])
{
    // A constant loop that can only be hard-broken is entered.
    while (true)
    {
        // The application is initialised and readied for use.
        System::initialise();
        Menu::initialise();
        Game::initialise();
        System::getFpsTimer()->start();

        // The application main loop is entered and remains running until the state is not active.
        while (System::getState() == System::State::ACTIVE)
        {
            // Starts the timer used in frame calculations.
            System::getCapTimer()->start();
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
