#ifndef INCLUDE_SPAWNER
#define INCLUDE_SPAWNER

// Spawns and manages clouds.

class Spawner
{
    public:
        // The constructor.
        Spawner();
        // Initialises the class so its ready for use.
        static void initialise();
        // Creates a cloud.
        void create();
        // Moves all the clouds in play.
        void step();
        // Renders all the clouds in play.
        void render();
        // Destroys all the clouds in play.
        void destroy();
        // Terminates the class after use.
        static void terminate();
        // The destructor.
        ~Spawner();
    private:
        // The counter that determines when a cloud will be spawned.
        int spawnCounter;
        // The range of time in which a cloud will take to spawn.
        static const int SPAWN_MAX, SPAWN_MIN;
        // The list that stores all the cloud entities.
        std::vector <Cloud*> cloud;
};

#endif // INCLUDE_SPAWNER
