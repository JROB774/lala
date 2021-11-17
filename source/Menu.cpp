// The menu image.
Image Menu::menu;
// The highscores image.
Image Menu::highscores;
// The highscores string stream that can be presented.
std::stringstream Menu::highscoresText;
// The menu's current state.
Menu::State Menu::state = Menu::State::MENU;

void Menu::initialise()
{
	// Loads and creates the menu's images.
	menu.create("Menu");
	highscores.create("Highscores");
}

void Menu::handle()
{
	// If a key is pressed...
	if (System::getEvent()->type == SDL_KEYDOWN)
	{
		// ...and the user is on the main menu...
		if (state == State::MENU)
		{
			// ...and if the 'Space' key was pressed then play the game.
			if (System::getEvent()->key.keysym.sym == SDLK_SPACE) state = State::INACTIVE;
			// ...and if the 'H' key was pressed then go to the highscores menu.
			else if (System::getEvent()->key.keysym.sym == SDLK_h) state = State::HIGHSCORES;
		}
		// ...and the user is on the highscores menu...
		else if (state == State::HIGHSCORES)
		{
			// ...and the 'H' key is pressed go back to the main menu.
			if (System::getEvent()->key.keysym.sym == SDLK_h) state = State::MENU;
			// ...and the 'R' key is pressed reset the highscores.
			if (System::getEvent()->key.keysym.sym == SDLK_r) resetHighscores();
		}
	}
}

void Menu::step()
{
	// If on the highscores page...
	if (state == State::HIGHSCORES)
	{
		// ...create the stream for reading the highscores file.
		std::ifstream readFile("Highscores.dat");
		// The storage for the raw string of data from the file.
		std::string data = "\0";
		// Stores a piece of the raw data temporarily.
		std::string dataPiece = "\0";
		// A counter that determines how many scores have been read.
		int scoreCounter = 1;

		// Resets the value of the highscores text.
		highscoresText.str("");

		// If the file is opened successfully...
		if (readFile.is_open())
		{
			// ...it gets the data from the file and stores it and then closes the file.
			std::getline(readFile, data);
			readFile.close();
		}
		// Otherwise send an error and exit the application.
		else Error::log("Could not open the highscores file for reading!", Error::Type::STD);

		// Loop until the entire string of data has been read.
		for (unsigned int i = 0; i < data.length(); i++)
		{
			// If a piece of score is being read append it to the current score.
			if (data.at(i) != ' ') dataPiece += data.at(i);
			// Otherwise...
			else
			{
				// ...add the score to the highscores text as well as other information.
				highscoresText << scoreCounter << "." << dataPiece << "\n";
				// Reset the current score being read.
				dataPiece = "\0";

				// Iterate the current score being read.
				scoreCounter++;
			}
		}
	}
}

void Menu::render()
{
	// Renders the menu's images to the screen.
	if (state == State::MENU) menu.render(0, 0, 0.0, nullptr, SDL_FLIP_NONE);
	else if (state == State::HIGHSCORES)
	{
		highscores.render(0, 0, 0.0, nullptr, SDL_FLIP_NONE);
		Font::render(32, 140, 114, 52, 74, highscoresText.str());
	}
}

void Menu::setState(Menu::State arg_state){ state = arg_state; }

Menu::State Menu::getState(){ return state; }

void Menu::terminate()
{
	// Destroys all the menu's images.
	menu.destroy();
	highscores.destroy();

	// Resets the menu's state.
	state = State::MENU;
}

void Menu::resetHighscores()
{
	// Opens the highscores file for writing.
	std::ofstream writeFile("Highscores.dat", std::ios::trunc);

	// If the file is opened successfully...
	if (writeFile.is_open())
	{
		// Resets the file's information and closes the file.
		writeFile << "0 0 0 0 0 \n\nDO NOT EDIT OR DELETE THIS FILE";
		writeFile.close();
	}
	// Otherwise send an error and exit the application.
	else Error::log("Could not open the highscores file for writing!", Error::Type::STD);
}
