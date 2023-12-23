#include "Vec2.h"
#include <math.h>

Vec2::Vec2() {

}

Vec2::Vec2(float xin, float yin)
    : x(xin), y(yin)
{

}

Vec2 Vec2::operator + (const Vec2& rhs) const
{
    return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{

    return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator * (const float val) const
{

    return Vec2(x * val, y * val);
}

Vec2 Vec2::operator / (const float val) const
{

    return Vec2(x / val, y / val);
}

bool Vec2::operator == (const Vec2& rhs) const
{

    return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{

    return (!(x == rhs.x && y == rhs.y));
}

void Vec2::operator += (const Vec2& rhs)
{
    x = x + rhs.x;
    y = y + rhs.y;
}

void Vec2::operator -= (const Vec2& rhs)
{
    x = x - rhs.x;
    y = y - rhs.y;
}

void Vec2::operator *= (const float val)
{
    x *= val;
    y *= val;
}

void Vec2::operator /= (const float val)
{
    x /= val;
    y /= val;
}

float Vec2::dist(const Vec2& rhs) const
{
    return (sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y)));
}

float Vec2::length() const
{
    return (sqrt(x * x + y * y));
}

Vec2& Vec2::normalize()
{
    float len = length();
    if (len != 0)
    {
        x /= len;
        y /= len;
    }
    return *this;
}

Vec2& Vec2::add(const Vec2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2& Vec2::subtract(const Vec2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}
Vec2& Vec2::scale(float val)
{
    x *= val;
    y *= val;
    return *this;
}
float degToRad(float val)
{
    return val * 3.1415 / 180;
}
Vec2& Vec2::rotate(float val)
{
    normalize();
    val = degToRad(val);
    float xval = x * cos(val) - y * sin(val);
    float yval = x * sin(val) + y * cos(val);
    x = xval;
    y = yval;
    return *this;
}