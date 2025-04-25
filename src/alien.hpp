 #include <iostream>
 #include <raylib.h>
 #include "laser.hpp"


 class Alien {
    public:
        Alien(int type, Vector2 position);
        void Update(int direction);
        void Draw();
        int GetType();
        void FireLasers();
        static void UnloadImages();

        static Texture2D images [3];
        int type;
        Vector2 position;
        std::vector<Laser> lasers;
    
    private:
        float lastFireTime;
       // Texture2D image;

};