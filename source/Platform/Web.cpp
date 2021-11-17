void main_loop()
{
    static Uint64 performanceFrequency = SDL_GetPerformanceFrequency();
    static Uint64 lastCounter = SDL_GetPerformanceCounter();
    static Uint64 endCounter = 0;
    static Uint64 elapsedCounter = 0;

    static float updateTimer = 0.0f;

    float updateRate = 1.0f / 60.0f;

    while (SDL_PollEvent(System::getEvent()) != 0)
    {
        System::handle();
        if (Menu::getState() != Menu::State::INACTIVE) Menu::handle();
        else Game::handle();
    }

    bool updated = false;
    while (updateTimer >= updateRate)
    {
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
        updateTimer -= updateRate;
        updated = true;
    }

    endCounter = SDL_GetPerformanceCounter();
    elapsedCounter = endCounter - lastCounter;
    lastCounter = SDL_GetPerformanceCounter();

    updateTimer += (float)elapsedCounter / (float)performanceFrequency;

    if(updated)
    {
        System::stepEnd();
    }
}

void main_start_cpp()
{
    System::initialise();
    Menu::initialise();
    Game::initialise();

    emscripten_set_main_loop(main_loop, -1, 1);
}

extern "C"
{
    void main_start()
    {
        main_start_cpp();
    }

    int main(int argc, char* argv[])
    {
        EM_ASM
        (
            FS.mkdir("/LALA");
            FS.mount(IDBFS, {}, "/LALA");
            FS.syncfs(true, function(err)
            {
                assert(!err);
                ccall("main_start");
            });
        );

        return 0;
    }
}
