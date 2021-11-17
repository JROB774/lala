#ifndef INCLUDE_BACKGROUND
#define INCLUDE_BACKGROUND

// A background object that scrolls from right to left.

class Background
{
    public:
        // The default constructor.
        Background() = default;
        // Loads and creates the background so it's ready for use.
        void create(const std::string, const int);
        // Renders the background to the screen at the correct position.
        void render();
        // Destroys and cleans up the background.
        void destroy();
        // The destructor.
        ~Background();
    private:
        // The spped at which the background will scroll.
        int speed;
        // The offset of the background.
        int offset;
        // The raw background image.
        Image image;
};

#endif // INCLUDE_BACKGROUND
