#include "vec2.h";
#include <SFML/Graphics.hpp>

//A transform talks about where an entity is, how fast it's going, etc.
class CTransform{
    public:
    Vec2 pos = {0.0,0.0};
    Vec2 velocity = {0.0,0.0};
    float angle = 0;

    CTransform(const Vec2& p, const Vec2& v, float a)
        : pos(p), velocity(v), angle(a)
        {

        }
}