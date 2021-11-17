#ifndef INCLUDE_ANIMATION
#define INCLUDE_ANIMATION

// Stores and wraps all the information for a specific animation to be played.
// Handles all the inner workings of an animation easily so less work needs to be done.

class Animation
{
    public:
        // The constructor.
        Animation();
        // Creates the animation using multiple specified values to create it.
        void create(const int, const int, const int, const int, const int, const int);
        // Returns the current sprite to be rendered in the animation.
        SDL_Rect* getCurrentSprite();
        // Destorys and cleans up the animation.
        void destroy();
        // The destructor.
        ~Animation();
    private:
        // The total number of sprites in the animation.
        int spriteTotal;
        // The current sprite to be returned.
        int currentSprite;
        // Counts how many frames have passed for the delay.
        int delayCounter;
        // The delay before the sprite is iterated.
        int delay;
        // The rectangular cuts of the larger image being used.
        SDL_Rect* sprite;
};

#endif // INCLUDE_ANIMATION
