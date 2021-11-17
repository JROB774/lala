#include "Error.h"

void Error::log(const std::string arg_message, const Type arg_type)
{
	// Creates a file stream for appending data.
	std::ofstream file("Error.log", std::ios::app);

	// Checks to see if the file is open...
	if (file.is_open())
	{
		// ...if it is then the type of error is checked and logs the appropriate information.
		switch (arg_type)
		{
			case(Type::STD) : file << "STD: " << arg_message << "\n"; break;
			case(Type::SDL) : file << "SDL: " << arg_message << "(" << SDL_GetError() << ")\n"; break;
			case(Type::IMG) : file << "IMG: " << arg_message << "(" << IMG_GetError() << ")\n"; break;
			case(Type::MIX) : file << "MIX: " << arg_message << "(" << Mix_GetError() << ")\n"; break;
		}

		// Closes the file after use.
		file.close();
	}

	// Exits the program with a state of failure.
	exit(EXIT_FAILURE);
}