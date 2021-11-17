#ifndef INCLUDE_IMAGE
#define INCLUDE_IMAGE

// A class for storing an image type, this is used for rendering images to the window.

class Image
{
    public:
        // The constructor.
        Image();
        // Creates an image from a specified file.
        void create(const std::string);
        // Renders the image, or image clip, to the specific coordinates on the window.
        void render(const int, const int, const double, const SDL_Point* arg_center, const SDL_RendererFlip, SDL_Rect* = nullptr) const;
        // Sets the colour of the image file.
        void setColourModulation(const Uint8, const Uint8, const Uint8);
        // Sets the alpha transparency of the image.
        void setAlphaModulation(const Uint8);
        // Sets the blend mode of the image.
        void setBlendMode(const SDL_BlendMode);
        // Returns the image's width.
        int getWidth() const;
        // Returns the image's height.
        int getHeight() const;
        // Destroys the image and does clean up.
        void destroy();
        // The destructor.
        ~Image();
    private:
        // The dimensions of the image.
        int width, height;
        // The raw SDL texture.
        SDL_Texture* texture;
};

#endif // INCLUDE_IMAGE
