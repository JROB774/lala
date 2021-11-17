Animation::Animation()
{
    // Sets default values for everything.
    spriteTotal = 0;
    currentSprite = 0;
    delayCounter = 0;
    delay = 0;
    sprite = nullptr;
}

void Animation::create(const int arg_x_offset, const int arg_y_offset, const int arg_w, const int arg_h, const int arg_sprite_total, const int arg_delay)
{
    // Sets the total number of sprites in the animation.
    spriteTotal = arg_sprite_total;

    // Sets the specified delay for the sprites in the animation.
    delay = arg_delay;

    // Reserves memory for the individual sprites in the animation.
    sprite = new(std::nothrow) SDL_Rect[arg_sprite_total];
    if (sprite == nullptr) Error::log("Could not reserve enough memory for the animation's sprites!", Error::Type::STD);
    // Cuts all the sprites in a strip from an iamge.
    for (int i = 0, ix = arg_x_offset; i < spriteTotal; i++, ix += arg_w) sprite[i] = { ix, arg_y_offset, arg_w, arg_h };
}

SDL_Rect* Animation::getCurrentSprite()
{
    // If the current sprite has been delayed long enough...
    if (delayCounter == delay)
    {
        // ...iterate to the next sprite and reset the counter.
        currentSprite++;
        delayCounter = 0;
    }
    // ...othersie iterate the counter.
    else delayCounter++;

    // If the current sprite is out of the animation's bounds it is reset.
    if (currentSprite == spriteTotal) currentSprite = 0;

    // Return the current sprite to be rendered in the animation/
    return &sprite[currentSprite];
}

void Animation::destroy()
{
    // Resets all the values.
    currentSprite = 0;
    delayCounter = 0;
    delay = 0;

    // Delets and cleans up the memory reserved for the animation's sprites.
    delete[] sprite;
    sprite = nullptr;
}

Animation::~Animation(){ destroy(); }
