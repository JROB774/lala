// The sprite dimensions.
const int Cloud::SPRITE_WIDTH = 152, Cloud::SPRITE_HEIGHT = 120;
// The velocity range of the clouds.
const int Cloud::VELOCITY_MAX = 4, Cloud::VELOCITY_MIN = 1;
// The image file for all clouds.
Image Cloud::image;
// THe sprites for the different sized clouds.
Animation Cloud::large, Cloud::medium, Cloud::small;

Cloud::Cloud(const int arg_null){ /* Does nothing. */ }

void Cloud::initialise()
{
    // Loads and creates the image for all clouds.
    image.create("Clouds");

    // Creates the sprites for the clouds.
    large.create(0, 0, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 0);
    medium.create(SPRITE_WIDTH, 0, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 0);
    small.create((SPRITE_WIDTH * 2), 0, SPRITE_WIDTH, SPRITE_HEIGHT, 1, 0);
}

void Cloud::create()
{
    // Generates a random size for the cloud.
    size = rand() % 3;

    // Sets a random position for the cloud.
    x = System::getWindowWidth();
    y = rand() % System::getWindowHeight() + (0 + SPRITE_HEIGHT);

    // Sets a random velocity for the cloud.
    velocity = rand() % VELOCITY_MAX + VELOCITY_MIN;

    // Makes sure the cloud is alive.
    dead = false;
}

void Cloud::step()
{
    // Moves the cloud from right to left.
    x -= velocity;

    // If the cloud is off-screen make it dead.
    if ((x + SPRITE_WIDTH) <= 0) dead = true;
}

void Cloud::render()
{
    // Renders the cloud to the screen depending on its size.
    switch (size)
    {
        case(0) : image.render(x, y, 0.0, nullptr, SDL_FLIP_NONE, large.getCurrentSprite()); break;
        case(1) : image.render(x, y, 0.0, nullptr, SDL_FLIP_NONE, medium.getCurrentSprite()); break;
        case(2) : image.render(x, y, 0.0, nullptr, SDL_FLIP_NONE, small.getCurrentSprite()); break;
    }
}

bool Cloud::isDead() const{ return dead; }

void Cloud::terminate()
{
    // Destroys the cloud's image.
    image.destroy();

    // Destroys the cloud's sprites.
    large.destroy();
    medium.destroy();
    small.destroy();
}
