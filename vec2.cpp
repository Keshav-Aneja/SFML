#include <iostream>
using namespace std;

class Vec2{
    public:
        float x = 0;
        float y = 0;

        Vec2() {}
        Vec2(float xin, float yin)
        : x(xin)
        , y(yin)
        {}

        Vec2 operator + (const Vec2& rhs)
        {
            return Vec2(x + rhs.x, y + rhs.y);
        }
        Vec2 operator - (const Vec2& rhs)
        {
            return Vec2(x - rhs.x, y - rhs.y);
        }

        void operator += (const Vec2& rhs)
        {
            x += rhs.x;
            y += rhs.y;
        }
        // Instead of this being void and returning nothing, you can do something called chaining, we can return a Vec2 reference which is a reference to the object itself, "this" will be instance of the current object. *this will dereference the object. So now i can actually return the reference to the current object. So I can do something like this v1.add(v2).add(v3) - chaining

        // v1.add(v2) will still add v2 to v1 additionally it will also return a reference to v1, so that we can further add .add(v3)
        Vec2& add(const Vec2& v)
        {
            x += v.x;
            y += v.y;
            return *this;
        }

        Vec2& scale(float s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        Vec2& rotate(float deg)
        {
            return *this;
        }

        // So after returning the reference to the objects we can do something like this, v1.scale(2).rotate(30).add(v4).normalize().scale(10); - so instead of being 3 lines of code, we can do it in a single line

        // this same kind of thing happens with (std::cout<<) this also returns a reference to cout, so we are able to do chaining like this, cout << ... << ... << ... ;

        float dist(const Vec2&v) const{
            return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
        }
};

int main(){
    Vec2 v1(100,200);
    Vec2 v2(50,75);
    //operator overloading
    Vec2 v3 = v1 + v2;
    //add
    v1.add(v2);
    v1.add(v2).add(v3);
    cout<<v1.x;
    float dist =  v1.dist(v2);
    return 0;
}