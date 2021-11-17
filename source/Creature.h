#ifndef INCLUDE_CREATURE
#define INCLUDE_CREATURE

// The creatures found on the planet used in the game. They are to be interacted
// with for gameplay purposes.

class Creature
{
    public:
        // The states the creature can be in.
        enum class State{ IDLE, ACTIVE };
        // The default constructor.
        Creature() = default;
        // Initialises the class.
        static void initialise();
        // Creates a creature instance at the set position.
        void create(const int, const int, const double, const std::string);
        // Activates the creature.
        void activate();
        // The step for the creature.
        void step();
        // Renders the creature to the screen.
        void render();
        // Gets whether the creature is active or not.
        int isActive() const;
        // Destroys the creature instance.
        void destroy();
        // Terminates the class.
        static void terminate();
        // The destructor.
        ~Creature();
    private:
        // The creature's position coordinates.
        int x, y;
        // The creature's angle.
        double angle;
        // The dimensions of all creature's sprites.
        static const int SPRITE_WIDTH, SPRITE_HEIGHT;
        // The center point of all sprites.
        static const SDL_Point SPRITE_CENTER;
        // The creature's specific image file.
        Image image;
        // The idle animation.
        static Animation idle;
        // The active animation.
        static Animation active;
        // The creature's specific sound file.
        Sound sound;
        // The creature's current state.
        State state;
        // The frame counter for when the creature is active.
        int frameCounter;
};

#endif // INCLUDE_CREATURE
