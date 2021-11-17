#ifndef INCLUDE_FONT
#define INCLUDE_FONT

#include "Image.h"

// The font that can be used to type up and visually represent ASCII characters
// to the screen.

class Font
{
	public:
		// The constructor is deleted.
		Font() = delete;
		// Initialises the font for use.
		static void initialise();
		// Renders the specified text to the screen.
		static void render(const int, const int, const Uint8, const Uint8, const Uint8, const std::string);
		// Returns the character width.
		static int getCharacterWidth();
		// Returns the character height.
		static int getCharacterHeight();
		// Terminates the font after use.
		static void terminate();
		// The destructor is deleted.
		~Font() = delete;
	private:
		// The font image file.
		static Image image;
		// The dimensions of each character.
		static const int CHARACTER_WIDTH, CHARACTER_HEIGHT;
		// The lenght of a tab.
		static const int TAB_LENGTH;
		// The individual ASCII characters.
		static SDL_Rect* character;
		// The total number of ASCII characters.
		static const int CHARACTER_TOTAL;
};

#endif // INCLUDE_FONT