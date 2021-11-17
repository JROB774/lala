// The title of the application window.
const std::string System::WINDOW_TITLE = "La La";
// The dimensions of the application window.
const int System::WINDOW_WIDTH = 640, System::WINDOW_HEIGHT = 480;
// The application window.
SDL_Window* System::window = nullptr;
// The application window's renderer.
SDL_Renderer* System::renderer = nullptr;
// The application's event handler.
SDL_Event System::event;
// The timers used for FPS related calculations.
Timer System::fpsTimer, System::capTimer;
// The FPS cap for the application and the number of ticks per frame.
const int System::FPS = 60, System::TPF = 1000 / FPS;
// The counter for frames during the application's life.
int System::frameCounter = 0;
// The average FPS for the application.
double System::averageFps = 0.0;
// The bool that stores whether colliders should be rendered or not.
bool System::renderColliders = false;
// The bool that stores whether sounds should be muted or not.
bool System::soundMuted = false;
// The application's current state.
System::State System::state = System::State::INACTIVE;

void System::initialise()
{
	// Checks to see if the application is resetting...
	if (state != State::RESETTING)
	{
		// ...if it is not then the main systems are initialised.
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) Error::log("Could not initialise SDL!", Error::Type::SDL);
		if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0) Error::log("Could not initialise MIX!", Error::Type::MIX);

		// Creates the application window.
		window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == nullptr) Error::log("Could not create the game application window!", Error::Type::SDL);

		// Creates the application window's renderer.
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (renderer == nullptr) Error::log("Could not create the game application renderer!", Error::Type::SDL);
	}

	// Sets a random seed using the current time.
	srand(static_cast <unsigned int> (time(NULL)));

	// After initialisation, the current system state is set to active.
	state = State::ACTIVE;
}

void System::handle()
{
	// If the exit button is clicked then the system's state is set to inactive.
	if (event.type == SDL_QUIT) state = State::INACTIVE;
	// If a key is pressed...
	else if (event.type == SDL_KEYDOWN)
	{
		switch (event.key.keysym.sym)
		{
			// ...check to see if the "Esc" key was pressed, if so then the system's state is set to inactive.
			case(SDLK_ESCAPE) : state = State::INACTIVE; break;
			// ...check to see if the "M" key was pressed, if so then whether sound should be muted or not is toggled.
			case(SDLK_m) : soundMuted = !soundMuted; break;
		}
	}
}

void System::stepBegin()
{
	// Calculates the current average FPS the system is running at.
	calculateAverageFps();
	// Sets the renderer's draw colour.
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	// Renders the draw colour across the entire application window.
	SDL_RenderClear(renderer);
}

void System::stepEnd()
{
	// Renders everything set to render during the step to the application window.
	SDL_RenderPresent(renderer);
	// Iterates to the next frame in the application's life.
	iterateFrame();
}

std::string System::getImageDirectory()
{
	#ifdef PLATFORM_WIN32
	#ifdef BUILD_DEBUG
	return "../../assets/Images/";
	#else
	return "Resources/Images/";
	#endif
	#endif
	#ifdef PLATFORM_WEB
	return "assets/Images/";
	#endif
}

std::string System::getSoundDirectory()
{
	#ifdef PLATFORM_WIN32
	#ifdef BUILD_DEBUG
	return "../../assets/Sounds/";
	#else
	return "Resources/Sounds/";
	#endif
	#endif
	#ifdef PLATFORM_WEB
	return "assets/Sounds/";
	#endif
}

int System::getWindowWidth(){ return WINDOW_WIDTH; }

int System::getWindowHeight(){ return WINDOW_HEIGHT; }

SDL_Renderer* System::getRenderer(){ return renderer; }

SDL_Event* System::getEvent(){ return &event; }

Timer* System::getFpsTimer(){ return &fpsTimer; }

Timer* System::getCapTimer(){ return &capTimer; }

bool System::getRenderColliders(){ return renderColliders; }

bool System::isSoundMuted(){ return soundMuted; }

System::State System::getState(){ return state; }

void System::terminate()
{
	// Resets everything used for FPS calculations.
	fpsTimer.stop(), capTimer.stop();
	frameCounter = 0;
	averageFps = 0.0;

	// Checks to see if the application is resetting...
	if (state != State::RESETTING)
	{
		// ...if not then the application window is destroyed,
		SDL_DestroyWindow(window);
		window = nullptr;

		// The window's renderer is also destroyed.
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;

		// Finally, the main systems are terminated.
		Mix_Quit();
		SDL_Quit();
	}
}

void System::calculateAverageFps()
{
	// Uses an algorithm to determine the average FPS of the application.
	averageFps = frameCounter / (fpsTimer.getTicks() / 1000.0);
	if (averageFps > 2000000) averageFps = 0;
}

void System::iterateFrame()
{
	// Declares a variable to store the extra frame ticks.
	int frameTicks = 0;

	// Calculates how many ticks occured during the frame and what the remainder is.
	frameTicks = capTimer.getTicks();
	// Waits out the reminaing ticks to complete the frame.
	if (frameTicks < TPF) SDL_Delay(TPF - frameTicks);

	// Moves on to the next frame.
	frameCounter++;
}
