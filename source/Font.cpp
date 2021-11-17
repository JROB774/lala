#include "Font.h"

// The font image file.
Image Font::image;
// The dimensions of each character.
const int Font::CHARACTER_WIDTH = 30, Font::CHARACTER_HEIGHT = 48;
// The lenght of a tab.
const int Font::TAB_LENGTH = (Font::CHARACTER_WIDTH * 4);
// The individual ASCII characters.
SDL_Rect* Font::character = nullptr;
// The total number of ASCII characters.
const int Font::CHARACTER_TOTAL = 128;

void Font::initialise()
{
	// Loads and creates the font image.
	image.create("Font");

	// Reserves enough memory to store all the individual characters.
	character = new(std::nothrow) SDL_Rect[CHARACTER_TOTAL];
	// If there was not enough space the program is aborted.
	if (character == nullptr) Error::log("Could not reserve enough memory for the font's characters!", Error::Type::STD);

	// Cuts up the font image into individual characters.
	for (int i = 0, ix = 0, iy = 0; i < CHARACTER_TOTAL; i++, ix += CHARACTER_WIDTH)
	{
		character[i] = { ix, iy, CHARACTER_WIDTH, CHARACTER_HEIGHT };
		if (ix >= image.getWidth()) ix = 0, iy += CHARACTER_HEIGHT;
	}
}

void Font::render(const int arg_x, const int arg_y, const Uint8 arg_r, const Uint8 arg_g, const Uint8 arg_b, const std::string arg_text)
{
	// Initialises a temporary varaible to store character values.
	int characterValue = 0;

	// Sets the colour of the text to be rendered.
	image.setColourModulation(arg_r, arg_g, arg_b);

	// Whilst there is still text to render iterate through the loop.
	for (unsigned int i = 0, ix = arg_x, iy = arg_y; i < arg_text.length(); i++)
	{
		// Checks what the current character is...
		switch (arg_text.at(i))
		{
			// ...if it's a new line shift the position downwards.
			case('\n') : ix = arg_x, iy += CHARACTER_HEIGHT; break;
			// ...if it's a tab then move the position to the right.
			case('\t') : ix += TAB_LENGTH; break;
			// ...if it's any other character...
			default:
			{
				// Store the current character's value.
				characterValue = static_cast <unsigned char> (arg_text.at(i));
				// Render the character at the correct position.
				image.render(ix, iy, 0.0, nullptr, SDL_FLIP_NONE, &character[characterValue]);
				// Move the position.
				ix += CHARACTER_WIDTH;
				break;
			}
		}
	}
}

int Font::getCharacterWidth(){ return CHARACTER_WIDTH; }

int Font::getCharacterHeight(){ return CHARACTER_HEIGHT; }

void Font::terminate()
{
	// Destroys the font image.
	image.destroy();

	// Deletes and cleans up all the character from memory.
	delete[] character;
	character = nullptr;
}