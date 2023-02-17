

class Bullet
{
public:
    int x;
    int y;
    int width;
    int height;
    int speed;

    Bullet()
    {
        x = 0;
        y = 0;
        width = width;
        height = height;
        speed = 0;
    }

    void update()
    {
        if (this->y < 0)
        {
            this->y -= speed;
        }
    }

    // bool collidesWidth(Bullet *o)
    // {
    //     // Test if the bullet collides with Enemy.
    //     // If it does, make it invisible and return true
    // }
};
