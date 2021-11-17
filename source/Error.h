#ifndef INCLUDE_ERROR
#define INCLUDE_ERROR

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <fstream>
#include <string>
#include <cstdlib>

// A class for handling errors, throughout the program, in different ways.

class Error
{
	public:
		// Types of error that can occur.
		enum class Type{ STD, SDL, IMG, MIX };
		// The constructor is deleted.
		Error() = delete;
		// Takes a specified error message and type and logs it, the program will exit after use.
		static void log(const std::string, const Type);
		// The destructor is deleted.
		~Error() = delete;
};

#endif // INCLUDE_ERROR
