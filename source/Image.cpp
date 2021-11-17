Image::Image()
{
    // Sets default values to everything.
    width = 0, height = 0;
    texture = nullptr;
}

void Image::create(const std::string arg_file)
{
    // Destroys the previous image, if there was one.
    destroy();

    // Loads the raw image data from disk.
    std::string directory = System::getImageDirectory() + arg_file + ".image";
    constexpr int BPP = 4; // We force the image to be in 32-bit RGBA format!
    int w,h,bpp;
    unsigned char* data = stbi_load(directory.c_str(), &w,&h,&bpp, BPP);
    if (data == nullptr) { Error::log("Could not load IMAGE file from disk!", Error::Type::STD); }

    // Loads the raw image data into a surface.
    int pitch = w*BPP;
    SDL_Surface* surface = SDL_CreateRGBSurfaceWithFormatFrom((void*)data, w,h,BPP*8,pitch, SDL_PIXELFORMAT_RGBA32);
    if (surface == nullptr) Error::log("Could not create a surface from an IMAGE file!", Error::Type::SDL);

    // Creates a texture using the previously loaded surface.
    texture = SDL_CreateTextureFromSurface(System::getRenderer(), surface);
    if (texture == nullptr) Error::log("Could not create a texture from a surface!", Error::Type::SDL);

    // The dimensions of the image are set.
    width = w, height = h;

    // The temporary surface is freed.
    SDL_FreeSurface(surface);
    surface = nullptr;

    // The raw image data is freed.
    stbi_image_free(data);
    data = nullptr;
}

void Image::render(const int arg_x, const int arg_y, const double arg_angle, const SDL_Point* arg_center, const SDL_RendererFlip arg_flip, SDL_Rect* arg_source) const
{
    // Creates the destination rect the image will be rendered to.
    SDL_Rect destination = { arg_x, arg_y, width, height };
    // If the source rect is not empty then the width and height from it are used as the destination's dimensions.
    if (arg_source != nullptr) destination.w = arg_source->w, destination.h = arg_source->h;

    // The image is rendered to the destination with a flip, if one is specified.
    SDL_RenderCopyEx(System::getRenderer(), texture, arg_source, &destination, arg_angle, arg_center, arg_flip);
}

void Image::setColourModulation(const Uint8 arg_r, const Uint8 arg_g, const Uint8 arg_b){ SDL_SetTextureColorMod(texture, arg_r, arg_g, arg_b); }

void Image::setAlphaModulation(const Uint8 arg_a){ SDL_SetTextureAlphaMod(texture, arg_a);  }

void Image::setBlendMode(const SDL_BlendMode arg_blendmode){ SDL_SetTextureBlendMode(texture, arg_blendmode); }

int Image::getWidth() const{ return width; }

int Image::getHeight() const{ return height; }

void Image::destroy()
{
    // If the image is not already destroyed...
    if (texture != nullptr)
    {
        // ...then destroy the image and reset all the values.
        width = 0, height = 0;
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

Image::~Image(){ destroy(); }
