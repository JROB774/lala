#ifndef INCLUDE_MENU
#define INCLUDE_MENU

#include <sstream>
#include <fstream>
#include "Font.h"

// The class that stores the menus and allows for navigation through them.

class Menu
{
	public:
		// The states the menu can be in.
		enum class State{MENU, HIGHSCORES, INACTIVE};
		// The constructor is deleted.
		Menu() = delete;
		// Initialises the menu so it is ready to be used.
		static void initialise();
		// Handles input on the menu.
		static void handle();
		// The step for the menu.
		static void step();
		// Renders the menu to the screen.
		static void render();
		// Sets the menu's current state.
		static void setState(State);
		// Gets the menu's current state.
		static State getState();
		// Temrminates the menu after use.
		static void terminate();
		// The destructor is deleted.
		~Menu() = delete;
	private:
		// The menu image.
		static Image menu;
		// The highscores image.
		static Image highscores;
		// The highscores string stream that can be presented.
		static std::stringstream highscoresText;
		// The menu's current state.
		static State state;
		// Resets the game's highscores.
		static void resetHighscores();
};

#endif // INCLUDE_MENU