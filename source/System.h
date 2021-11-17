#ifndef INCLUDE_SYSTEM
#define INCLUDE_SYSTEM

#include <ctime>
#include "Error.h"
#include "Timer.h"

// The class that stores all the main system information and handles system functions that
// are to be used throughout the application.

class System
{
	public:
		// The states the system can be in.
		enum class State{ ACTIVE, RESETTING, INACTIVE };
		// The constructor is deleted.
		System() = delete;
		// Initialise the application and gets it ready for use.
		static void initialise();
		// Handles any system based events that may occur.
		static void handle();
		// The beginning of any step that occurs during the application's life.
		static void stepBegin();
		// The end of any step that occurs during the application's life.
		static void stepEnd();
		// Returns the base directory for all image files.
		static std::string getImageDirectory();
		// Returns the base directory for all sound files.
		static std::string getSoundDirectory();
		// Returns the width of the application window.
		static int getWindowWidth();
		// Returns the height of the application window.
		static int getWindowHeight();
		// Returns the application renderer.
		static SDL_Renderer* getRenderer();
		// Returns the application event handler.
		static SDL_Event* getEvent();
		// Returns the FPS timer.
		static Timer* getFpsTimer();
		// Returns the cap timer.
		static Timer* getCapTimer();
		// Returns whether colliders should be rendered or not.
		static bool getRenderColliders();
		// Returns whether the sound is muted or not.
		static bool isSoundMuted();
		// Returns the application's current state.
		static State getState();
		// Terminates the application and does system clean up.
		static void terminate();
		// The destructor is deleted.
		~System() = delete;
	private:
		// The directories for the application's resources.
		static const std::string IMAGE_DIRECTORY, SOUND_DIRECTORY;
		// The title of the application window.
		static const std::string WINDOW_TITLE;
		// The dimensions of the application window.
		static const int WINDOW_WIDTH, WINDOW_HEIGHT;
		// The application window.
		static SDL_Window* window;
		// The application window's renderer.
		static SDL_Renderer* renderer;
		// The application's event handler.
		static SDL_Event event;
		// The timers used for FPS related calculations.
		static Timer fpsTimer, capTimer;
		// The FPS cap for the application and the number of ticks per frame.
		static const int FPS, TPF;
		// The counter for frames during the application's life.
		static int frameCounter;
		// The average FPS for the application.
		static double averageFps;
		// The bool that stores whether colliders should be rendered or not.
		static bool renderColliders;
		// The bool that stores whether sounds should be muted or not.
		static bool soundMuted;
		// The application's current state.
		static State state;
		// Calculates the current average FPS for the application.
		static void calculateAverageFps();
		// Moves on to the next frame/step in the application's life.
		static void iterateFrame();
};

#endif // INCLUDE_SYSTEM
