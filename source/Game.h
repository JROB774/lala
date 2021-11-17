#ifndef INCLUDE_GAME
#define INCLUDE_GAME

// Stores the main systems and functions of the game itself.

class Game
{
	public:
		// The states the game can be in.
		enum class State{ NOT_IN_LEVEL, PLAYING_PATTERN, IN_LEVEL, GAME_OVER };
		// The constructor is deleted.
		Game() = delete;
		// Initialises the game and readies it for play.
		static void initialise();
		// Handles all events for the user in the game itself.
		static void handle();
		// Moves through the current step of the game.
		static void step();
		// Renders everything within the game.
		static void render();
		// Terminates the game after play.
		static void terminate();
		// The destructor is deleted.
		~Game() = delete;
	private:
		// The image background for the game.
		static Image background;
		// The image for the planet.
		static Image planet;
		// The image for the game over screen.
		static Image gameOver;
		// The scrolling cloud background.
		static Background clouds;
		// The four creatures used in the gameplay.
		static Creature happy, angry, shifty, dummy;
		// The current level of difficulty that can be represented in text.
		static std::stringstream currentLevelText;
		// The current pattern the player has to copy.
		static std::string currentPattern;
		// The counter to get the current position in the pattern.
		static int patternCounter;
		// The flag that says whether input is locked.
		static bool inputLocked;
		// The current input the player has given.
		static int currentInput;
		// The flag that says whether the game's highscore was saved.
		static bool highscoreSaved;
		// The game's current state.
		static State state;
		// Generates a pattern for the current level.
		static void generatePattern();
		// Plays the current level's pattern to the player.
		static void playPattern();
		// Plays the main part of the game itself.
		static void playGame();
		// Saves new highscores to the highscores file.
		static void saveHighscore();
};

#endif // INCLUDE_GAME
