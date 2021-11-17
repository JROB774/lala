#ifndef INCLUDE_SOUND
#define INCLUDE_SOUND

// A class for storing a sound type, this is used to play sounds.

class Sound
{
    public:
        // The constructor.
        Sound();
        // Creates a sound from a specified file.
        void create(const std::string);
        // Plays the sound a specified number of times.
        void play(const unsigned int) const;
        // Destroys the sound and does clean up.
        void destroy();
        // The destructor.
        ~Sound();
    private:
        // The raw MIX chunk.
        Mix_Chunk* chunk;
};

#endif // INCLUDE_SOUND
