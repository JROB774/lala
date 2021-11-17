#ifndef INCLUDE_CLOUD
#define INCLUDE_CLOUD

// A background entity that moves from right to left for visual effect.

class Cloud
{
	public:
		// The constructor.
		Cloud(const int);
		// Initialises the class so its ready for use.
		static void initialise();
		// Creates a cloud.
		void create();
		// Moves the cloud.
		void step();
		// Renders the cloud.
		void render();
		// Returns whether the cloud is dead or not.
		bool isDead() const;
		// Terminates the class after use.
		static void terminate();
		// The default destructor.
		~Cloud() = default;
	private:
		// The size of the cloud.
		int size;
		// The x and y coordinates of the cloud.
		int x, y;
		// The sprite dimensions.
		static const int SPRITE_WIDTH, SPRITE_HEIGHT;
		// The velocity range of the clouds.
		static const int VELOCITY_MAX, VELOCITY_MIN;
		// The clouds velocity.
		int velocity;
		// The image file for all clouds.
		static Image image;
		// THe sprites for the different sized clouds.
		static Animation large, medium, small;
		// The bool that stores whether the cloud is dead or not.
		bool dead;
};

#endif // INCLUDE_CLOUD
