void Background::create(const std::string arg_file, const int arg_speed)
{
    // Sets the speed and offset of the background.
    speed = arg_speed;
    offset = 0;

    // Loads and creates the raw background image.
    image.create(arg_file);
}

void Background::render()
{
    // Moves the background.
    offset -= speed;
    if (offset < -image.getWidth()) offset = 0;

    // Renders two copies of the background to make it appear like it's scrolling.
    image.render(offset, 0, 0.0, nullptr, SDL_FLIP_NONE);
    image.render(offset + image.getWidth(), 0, 0.0, nullptr, SDL_FLIP_NONE);
}

void Background::destroy()
{
    // Resets the background's speed and offset.
    speed = 0;
    offset = 0;

    // Destroys the raw background image.
    image.destroy();
}

Background::~Background(){ destroy(); }
