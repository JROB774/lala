// The image background for the game.
Image Game::background;
// The image for the planet.
Image Game::planet;
// The image for the game over screen.
Image Game::gameOver;
// The scrolling cloud background.
Background Game::clouds;
// The four creatures used in the gameplay.
Creature Game::happy, Game::angry, Game::shifty, Game::dummy;
// The current level of difficulty that can be represented in text.
std::stringstream Game::currentLevelText;
// The current pattern the player has to copy.
std::string Game::currentPattern = "\0";
// The counter to get the current position in the pattern.
int Game::patternCounter = 0;
// The flag that says whether input is locked.
bool Game::inputLocked = false;
// The current input the player has given.
int Game::currentInput = 0;
// The flag that says whether the game's highscore was saved.
bool Game::highscoreSaved = false;
// The game's current state.
Game::State Game::state = Game::State::NOT_IN_LEVEL;

void Game::initialise()
{
    // Loads and creates the game's images.
    background.create("Background");
    planet.create("Planet");
    gameOver.create("GameOver");

    // Loads and creates the game's scrolling backgroud.
    clouds.create("Clouds", 4);

    // Initialise the font class for use.
    Font::initialise();

    // Initialises the creature class for use.
    Creature::initialise();
    // Creates the four creatures.
    happy.create(268, 48, 0.0, "Happy");
    angry.create(408, 188, 90.0, "Angry");
    shifty.create(268, 328, 180.0, "Shifty");
    dummy.create(128, 188, 270.0, "Dummy");
}

void Game::handle()
{
    // If the game is currently in a level...
    if (state == State::IN_LEVEL)
    {
        // ...if input is not locked...
        if (!inputLocked)
        {
            // ...if it is then check for a key press...
            if (System::getEvent()->type == SDL_KEYDOWN)
            {
                // ...if there was one it checks to see if it was any of the arrow keys...
                switch (System::getEvent()->key.keysym.sym)
                {
                    // ...if it was then it sets the correct input value.
                    case(SDLK_UP) : currentInput = 1; break;
                    case(SDLK_RIGHT) : currentInput = 2; break;
                    case(SDLK_DOWN) : currentInput = 3; break;
                    case(SDLK_LEFT) : currentInput = 4; break;
                }
            }
        }
    }
    // If the game is over...
    else if (state == State::GAME_OVER)
    {
        // ...and if the 'R' key is pressed...
        if ((System::getEvent()->type == SDL_KEYDOWN) && (System::getEvent()->key.keysym.sym == SDLK_r))
        {
            // ...resets the game's values.
            currentPattern = "\0";
            currentInput = 0;
            patternCounter = 0;
            highscoreSaved = false;

            // Resets the game's state.
            state = State::NOT_IN_LEVEL;
        }
        // ...and if the 'Space' key is pressed...
        if ((System::getEvent()->type == SDL_KEYDOWN) && (System::getEvent()->key.keysym.sym == SDLK_SPACE))
        {
            // ...resets the game's values.
            currentPattern = "\0";
            currentInput = 0;
            patternCounter = 0;
            highscoreSaved = false;

            // Resets the game's state.
            state = State::NOT_IN_LEVEL;

            // Sets the menu's state so it is active again.
            Menu::setState(Menu::State::MENU);
        }
    }
}

void Game::step()
{
    // Checks to see what the current state of the game is...
    switch (state)
    {
        // If the game is currently not in a level a new pattern is generated.
        case(State::NOT_IN_LEVEL) : generatePattern(); break;
        // If the game is currently playing the pattern then play it.
        case(State::PLAYING_PATTERN) : playPattern(); break;
        // If the game is currently in a level then play the game.
        case(State::IN_LEVEL) : playGame(); break;
        // If the game is currently over save the new highscore, if there is one.
        case(State::GAME_OVER) : if (!highscoreSaved) saveHighscore();
    }

    // Sets the string stream for the current difficulty level.
    currentLevelText.str("");
    currentLevelText << currentPattern.length();

    // Steps through all the creature's steps.
    happy.step();
    angry.step();
    shifty.step();
    dummy.step();

    // DEBUG
    // std::cout << currentLevel << " : " << currentPattern << std::endl;
    // std::cout << "State: " << static_cast <int> (state) << std::endl;

    // If any of the creature's are active lock input.
    if ((happy.isActive() == 1) || (angry.isActive() == 1) || (shifty.isActive() == 1) || (dummy.isActive() == 1)) inputLocked = true;
    // Otherwise unlock input.
    else inputLocked = false;
}

void Game::render()
{
    // Renders the game's images to the screen.
    background.render(0, 0, 0.0, nullptr, SDL_FLIP_NONE);
    clouds.render();
    happy.render();
    angry.render();
    shifty.render();
    dummy.render();
    planet.render(0, 0, 0.0, nullptr, SDL_FLIP_NONE);
    Font::render(8, 8, 255, 255, 255, currentLevelText.str());
    if (state == State::GAME_OVER) gameOver.render(0, 0, 0.0, nullptr, SDL_FLIP_NONE);
}

void Game::terminate()
{
    // Destroys the game's images.
    background.destroy();
    planet.destroy();
    gameOver.destroy();

    // Destroys the game's scrolling background.
    clouds.destroy();

    // Terminates the font class.
    Font::terminate();

    // Destroys the four creatures.
    happy.destroy();
    angry.destroy();
    shifty.destroy();
    dummy.destroy();
    // Terminates the creature class.
    Creature::terminate();

    // Resets the game's values.
    currentPattern = "\0";
    currentInput = 0;
    patternCounter = 0;
    highscoreSaved = false;

    // Resets the game's state.
    state = State::NOT_IN_LEVEL;
}

void Game::generatePattern()
{
    // Declares a temporary variable for generation use.
    int piece = 0;

    // Generates a piece for the pattern.
    piece = rand() % 4 + 1;

    // Decides what the next piece of the pattern will be and adds it.
    switch (piece)
    {
        case(1) : currentPattern += "1"; break;
        case(2) : currentPattern += "2"; break;
        case(3) : currentPattern += "3"; break;
        case(4) : currentPattern += "4"; break;
    }

    // Sets the state so the game will now play the newly generated pattern.
    state = State::PLAYING_PATTERN;
}

void Game::playPattern()
{
    // Declares some function specific variables.
    static int frameCounter = -1;
    static char currentPatternPiece = '\0';
    static int currentPatternCounter = 0;

    // If the frame counter is empty, reset it.
    if (frameCounter < 0) frameCounter = 50;
    // If the frame counter is done counting...
    else if (frameCounter == 0)
    {
        // ...get the current pattern piece.
        currentPatternPiece = currentPattern.at(currentPatternCounter);

        // Depending on what it is activate the correct creature.
        switch (currentPatternPiece)
        {
            case('1') : happy.activate(); break;
            case('2') : angry.activate(); break;
            case('3') : shifty.activate(); break;
            case('4') : dummy.activate(); break;
        }

        // Iterate the counter so it'll play the next piece.
        currentPatternCounter++;

        // If the whole pattern has been read...
        if (static_cast <unsigned int> (currentPatternCounter) == currentPattern.length())
        {
            // ...reset the function's values.
            frameCounter = -1;
            currentPatternPiece = '\0';
            currentPatternCounter = 0;

            // Sets the game's new state.
            state = State::IN_LEVEL;
        }
    }

    // Deiterate the frame counter.
    frameCounter--;
}

void Game::playGame()
{
    // Checks to see what the player's current input is, if anything...
    switch (currentInput)
    {
        // ...depending on the input the corresponding creature is activated.
        case(1) : happy.activate(); break;
        case(2) : angry.activate(); break;
        case(3) : shifty.activate(); break;
        case(4) : dummy.activate(); break;
    }

    // Checks to see if the current input was correct to the current part of the pattern.
    switch (currentInput)
    {
        case(1) : {
            if ('1' != currentPattern.at(patternCounter)) state = State::GAME_OVER;
            else patternCounter++;
            currentInput = 0;
            break;
        }
        case(2) : {
            if ('2' != currentPattern.at(patternCounter)) state = State::GAME_OVER;
            else patternCounter++;
            currentInput = 0;
            break;
        }
        case(3) : {
            if ('3' != currentPattern.at(patternCounter)) state = State::GAME_OVER;
            else patternCounter++;
            currentInput = 0;
            break;
        }
        case(4) : {
            if ('4' != currentPattern.at(patternCounter)) state = State::GAME_OVER;
            else patternCounter++;
            currentInput = 0;
            break;
        }
    }

    // If the pattern is complete...
    if (static_cast <unsigned int> (patternCounter) == currentPattern.length())
    {
        // ...resets some of the game's values.
        patternCounter = 0;
        state = State::NOT_IN_LEVEL;
    }
}

void Game::saveHighscore()
{
    // Declares some temporary variables for use.
    std::ifstream readFile("Highscores.dat");
    std::ofstream writeFile;
    std::string rawData = "\0";
    std::istringstream readData;
    std::ostringstream writeData;
    int highscore[5];
    int newHighscore = static_cast <int> (currentPattern.length()) - 1;
    int highscorePosition = 999;

    // Reads the highscores and stores them.
    if (readFile.is_open())
    {
        std::getline(readFile, rawData);
        readFile.close();
    }
    else Error::log("Could not open the highscores file for reading!", Error::Type::STD);

    // Stores the raw data in a stream and extracts the individual highscores.
    readData.str(rawData);
    readData >> highscore[0] >> highscore[1] >> highscore[2] >> highscore[3] >> highscore[4];

    // Finds out where the new highscore should be placed if anywhere.
    for (int i = 4; i >= 0; i--)
    {
        if (newHighscore > highscore[i]){ highscorePosition = i; continue; }
        else break;
    }

    // If the score is a new highscore...
    if (highscorePosition != 999)
    {
        // ...move all the scores down one to make room for the new highscore.
        for (int i = 4; i >= highscorePosition; i--) highscore[i] = highscore[i - 1];

        // ...move all the scores down one to make room for the new highscore.
        // for (int i = 4; i > highscorePosition + 1; i--) highscore[i] = highscore[i - 1];

        // Insert thew new highscore.
        highscore[highscorePosition] = newHighscore;

        // Stores the new list of highscores in a stream.
        writeData << highscore[0] << " " << highscore[1] << " " << highscore[2] << " " << highscore[3] << " " << highscore[4] << " ";

        // Writes the new highscores to the highscores file.
        writeFile.open("Highscores.dat", std::ios::trunc);

        if (writeFile.is_open())
        {
            writeFile << writeData.str() << "\n\nDO NOT EDIT OR DELETE THIS FILE";
            writeFile.close();
        }
        else Error::log("Could not open the highscores file for writing!", Error::Type::STD);
    }

    // Sets the flag to say the highscores have been saved.
    highscoreSaved = true;
}
