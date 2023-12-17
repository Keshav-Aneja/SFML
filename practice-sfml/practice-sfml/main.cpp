#include "iostream";
#include "fstream";
#include <SFML/Graphics.hpp>

using namespace std;
sf::Font myFont;
class Circle {
public:
    sf::CircleShape circle;
    sf::Text label;
    string text;
    float pos_x, pos_y, mov_x, mov_y;
    int r, g, b, radius;

    Circle(string& text, float& pos_x, float& pos_y, float& mov_x, float& mov_y, int r, int g, int b, int radius)
        : text(text)
        , pos_x(pos_x)
        , pos_y(pos_y)
        , mov_x(mov_x)
        , mov_y(mov_y)
        , r(r)
        , g(g)
        , b(b)
        , radius(radius)
    {
        circle.setRadius(radius);
        circle.setPosition(pos_x, pos_y);
        circle.setFillColor(sf::Color(r, g, b));
        label.setFont(myFont);
        label.setString(text);
        label.setPosition(pos_x + radius - label.getGlobalBounds().width / 2, pos_y + radius - label.getGlobalBounds().height / 2);
    }

    void move() {
        circle.setPosition(circle.getPosition().x + mov_x, circle.getPosition().y + mov_y);
        label.setPosition(label.getPosition().x + mov_x, label.getPosition().y + mov_y);
    }
};
class Rectangle {
public:
    sf::RectangleShape rectangle;
    sf::Text label;
    string text;
    float pos_x, pos_y, mov_x, mov_y, l, w;
    int r, g, b;

    Rectangle(string& text, float& pos_x, float& pos_y, float& mov_x, float& mov_y, int r, int g, int b, float l, float w)
        : text(text)
        , pos_x(pos_x)
        , pos_y(pos_y)
        , mov_x(mov_x)
        , mov_y(mov_y)
        , r(r)
        , g(g)
        , b(b)
        , l(l)
        , w(w)
    {
        rectangle.setSize(sf::Vector2f(l,w));
        rectangle.setPosition(pos_x, pos_y);
        rectangle.setFillColor(sf::Color(r, g, b));
        label.setFont(myFont);
        label.setString(text);
        label.setPosition(pos_x + l/2 - label.getGlobalBounds().width / 2, pos_y + w/2 - label.getGlobalBounds().height / 2);
    }

    void move() {
        rectangle.setPosition(rectangle.getPosition().x + mov_x, rectangle.getPosition().y + mov_y);
        label.setPosition(label.getPosition().x + mov_x, label.getPosition().y + mov_y);
    }
};
int main()
{

    const int wwidth = 1280;
    const int wheight = 720;
    vector<Circle> circles;
    vector<Rectangle> rectangles;
    sf::RenderWindow window(sf::VideoMode(wwidth, wheight), "My First Window!", sf::Style::Default);
    if (!myFont.loadFromFile("calgary.ttf"))
    {
        cout << "Couldn't load the font";
        exit(-1);
    }
    std::ifstream fin("config.txt");
    string CmdType;
    while (fin >> CmdType)
    {
        if (CmdType == "Circle")
        {
            string text;
            float pos_x, pos_y, mov_x, mov_y;
            int r, g, b, radius;
            fin >> text >> pos_x >> pos_y >> mov_x >> mov_y >> r >> g >> b >> radius;
            Circle c1(text,pos_y,pos_y,mov_x,mov_y,r,g,b,radius);
            circles.push_back(c1);
        }
        if (CmdType == "Rectangle")
        {
            string text;
            float pos_x, pos_y, mov_x, mov_y,l,w;
            int r, g, b;
            fin >> text >> pos_x >> pos_y >> mov_x >> mov_y >> r >> g >> b >> l >> w;
            Rectangle r1(text, pos_y, pos_y, mov_x, mov_y, r, g, b, l,w);
            rectangles.push_back(r1);
        }
    }
    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        for (auto& x : circles)
        {
            x.move();
            if (x.circle.getGlobalBounds().left < 0 || x.circle.getGlobalBounds().left + x.radius*2 > wwidth)
            {
                x.mov_x *= -1.0f;
            }
            if (x.circle.getGlobalBounds().top < 0 || x.circle.getGlobalBounds().top + x.radius*2 > wheight)
            {
                x.mov_y *= -1.0f;
            }
        }
        for (auto& x : rectangles)   
        {
            x.move();
            if (x.rectangle.getGlobalBounds().left < 0 || x.rectangle.getGlobalBounds().left + x.l > wwidth)
            {
                x.mov_x *= -1.0f;
            }
            if (x.rectangle.getGlobalBounds().top < 0 || x.rectangle.getGlobalBounds().top + x.w * 2 > wheight)
            {
                x.mov_y *= -1.0f;
            }
        }
        window.clear();
        for (auto& c : circles)
        {
            window.draw(c.circle);
            window.draw(c.label);
        }
        for (auto& r: rectangles)
        {
            window.draw(r.rectangle);
            window.draw(r.label);
        }
        window.display();
    }

    return 0;
}