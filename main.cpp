#include <iostream>
#include <SFML/Graphics.hpp>
// #include <sstream>
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include <math.h>

#define width 1600
#define height 1200
#define PI 3.141592653589793

#define GRID_X 3
#define GRID_Y 3

struct point
{
    double x;
    double y;
    point(double x, double y) : x(x), y(y){};
};

struct vector
{
    double angle;
    double magnitude;
    vector(double a, double m) : angle(a), magnitude(m){};
    point get_point()
    {
        return point(magnitude * std::cos(angle * PI / 180), -1 * magnitude * std::sin(angle * PI / 180));
    }
};

// double dot_product(vector v1, vector v2)
// {
// }

double dot_product(double x1, double y1, double x2, double y2)
{
    return x1 * x2 + y1 * y2;
}

double dot_product(point p1, point p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}

int get_angle_vector(int x, int y, double seed_ratio = 1)
{
    srand((x + y) * std::sin((x - y) * seed_ratio) * seed_ratio - std::pow(x, 3) + std::pow(y, 2) - (x * y));
    return rand() % 360;
}

double fade(double x)
{
    return 6 * std::pow(x, 5) - 15 * std::pow(x, 4) + 10 * std::pow(x, 3);
    // return 3 * std::pow(x, 2) - 2 * std::pow(x, 3);
    // return x;
}

vector difference_vector(double x1, double y1, double x2, double y2)
{
    double x_diff = x2 - x1;
    double y_diff = y2 - y1;
    double magnitude = sqrt((x_diff * x_diff) + (y_diff * y_diff));

    int angle = std::acos(x_diff / magnitude);
    if (angle < 0)
        angle = 360 + angle;

    return vector(angle, magnitude);
}

double arithmatic_mean(double *nums, int size)
{
    int total = 0;
    for (int i = 0; i < size; i++)
    {
        total += nums[i];
    }
    return total / size;
}

double perlin(double x, double y, double seed_ratio = 1)
{
    double x_min = std::floor(x);
    double x_max = std::ceil(x);
    double y_min = std::floor(y);
    double y_max = std::ceil(y);

    if (x_min == x_max)
        x_min -= 1;
    if (y_min == y_max)
        y_min -= 1;

    // std::cout << x_min << "\n";
    // std::cout << x_max << "\n";
    // std::cout << y_min << "\n";
    // std::cout << y_max << "\n";

    // srand(time(NULL));

    vector v1 = vector(get_angle_vector(x_min, y_min), 1);
    vector v2 = vector(get_angle_vector(x_max, y_min), 1);
    vector v3 = vector(get_angle_vector(x_min, y_max), 1);
    vector v4 = vector(get_angle_vector(x_max, y_max), 1);

    // std::cout << "Angle: " << v1.angle << " Magnitude: " << v1.magnitude << "\n";
    // std::cout << "Angle: " << v2.angle << " Magnitude: " << v2.magnitude << "\n";
    // std::cout << "Angle: " << v3.angle << " Magnitude: " << v3.magnitude << "\n";
    // std::cout << "Angle: " << v4.angle << " Magnitude: " << v4.magnitude << "\n";

    // point test = point(x - x_min, y - y_min);

    // std::cout << "Point X: " << v1.get_point().x << " Y: " << v1.get_point().y << "\n";
    // std::cout << "Difference X: " << test.x << " Y: " << test.y << "\n";
    // std::cout << "Dot Product: " << dot_product(v1.get_point(), point(x - x_min, y - y_min)) << "\n";

    double p_v1 = fade(1 - std::abs(x - x_min)) * fade(1 - std::abs(y - y_min)) * dot_product(v1.get_point(), point(x - x_min, y - y_min));
    double p_v2 = fade(1 - std::abs(x - x_max)) * fade(1 - std::abs(y - y_min)) * dot_product(v2.get_point(), point(x - x_max, y - y_min));
    double p_v3 = fade(1 - std::abs(x - x_min)) * fade(1 - std::abs(y - y_max)) * dot_product(v3.get_point(), point(x - x_min, y - y_max));
    double p_v4 = fade(1 - std::abs(x - x_max)) * fade(1 - std::abs(y - y_max)) * dot_product(v4.get_point(), point(x - x_max, y - y_max));
    // double p_v1 = fade(dot_product(v1.get_point(), point(x - x_min, y - y_min)));
    // double p_v2 = fade(dot_product(v2.get_point(), point(x - x_max, y - y_min)));
    // double p_v3 = fade(dot_product(v3.get_point(), point(x - x_min, y - y_min)));
    // double p_v4 = fade(dot_product(v4.get_point(), point(x - x_max, y - y_max)));

    // double nums[4] = {p_v1, p_v2, p_v3, p_v4};
    // return arithmatic_mean(nums, 4);
    double noise = (p_v1 + p_v2 + p_v3 + p_v4) / 4;
    return noise;
    // return noise > 0 ? std::pow(noise, 1.0/2) : -1 * std::pow(std::abs(noise), 1.0/2);

    // return 4/(1/p_v1 + 1/p_v2 + 1/p_v3 + 1/p_v4);

    // if (p_v1 * p_v2 * p_v3 * p_v4 > 0)
    // {
    //     return std::pow(p_v1 * p_v2 * p_v3 * p_v4, 1.0 / 4);
    // }
    // else
    // {
    //     return -1 * std::pow(std::abs(p_v1 * p_v2 * p_v3 * p_v4), 1.0 / 4);
    // }

    // vector d_v1 = difference_vector(x_min, y_min, x, y);
    // vector d_v2 = difference_vector(x_max, y_min, x, y);
    // vector d_v3 = difference_vector(x_min, y_max, x, y);
    // vector d_v4 = difference_vector(x_max, y_max, x, y);
}

double stack_octaves(double x, double y, double S, double M, double T)
{
    double total = 0;
    for (int i = 0; i < T; i++)
    {
        double noise = perlin(x / S, y / S, i + 1);
        total += noise * M;
        M *= M;
        S *= S;
    }
    return total;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(width, height), "Perlin Noise", sf::Style::Close);

    sf::Clock clock;

    // double noise = perlin(1.999, 1.5);
    // std::cout << "\n\n"
    //           << "\n";
    // double noise2 = perlin(1.998, 1.5);

    // srand(22);

    // std::cout << "Noise 1: " << noise1 << "\n";
    // std::cout << "Noise 2: " << noise2 << "\n";
    // std::cout << "Noise 3: " << noise3 << "\n";
    // std::cout << "difs: " << noise2 - noise1 << " " << noise3 - noise2 << "\n\n";

    // std::cout << "control 1: " << noiseTest << "\n";
    // std::cout << "control 2: " << noiseTest2 << "\n";
    // std::cout << "dif: " << noiseTest - noiseTest2 << "\n";

    // double test = fade(1 - std::abs(1.9- 1)) * fade(1 - std::abs(1.9 - 1));

    // std::cout << "Fade: " << test << "\n";

    // std::cout << rand() << "\n";

    double *noises = new double[width * height];

    double max = -1;
    double min = 1;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double noise = stack_octaves((double)j / width * GRID_X, (double)i / width * GRID_Y, 0.5, 0.7, 2);
            noises[i * width + j] = noise;
            if (noise > max) {
                max = noise;
            } else if (noise < min) {
                min = noise;
            }
        }
    }

    double range = max - min;
    double scalar = 2.0/range;
    double sub = max*scalar - 1;

    sf::VertexArray points(sf::Points, width * height);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            points[i * width + j].position = sf::Vector2f(j, i);
            double noise = noises[i * width + j]*scalar - sub;
            noise += 1;
            // noise *= -1;
            // noises[i * width + j] = noise;
            // noise *= 1.8;
            // std::cout << noise << "\n";
            // points[i * width + j].color = sf::Color((uint32_t() - 1) * (1 + perlin((double)j / width * GRID_X, (double)i / width * GRID_Y)));
            points[i * width + j].color = sf::Color(noise * 127, noise * 127, noise * 127);
            // points[i * width + j].color = sf::Color(255, 255, noise > 0 ? 255 : 0);
            // points[i * width + j].color = sf::Color(noise * 127, noise * 127, 255);
        }
    }

    int skip = 2;

    sf::VertexArray line(sf::LineStrip, width / skip);

    for (int i = 0; i < width; i += skip)
    {
        // double noise1 = perlin((double)i / width * GRID_X, GRID_Y / 2);

        // double noise2 = perlin((double)i / width * (GRID_X * 2), GRID_Y);

        // double noise3 = perlin((double)i / width * (GRID_X * 4), GRID_Y * 2);

        // line[i].position = sf::Vector2f(i, (4 * noise1 + 2 * noise2 + noise3/2) * height / 8 + 500);
        // line[i/skip].position = sf::Vector2f(i, 500 + height * stack_octaves((double)i / width * GRID_X, GRID_Y / 2, 0.5, 0.7, 10));
        // line[i/skip].color = sf::Color::White;
    }
    // line[width-1] = sf::Vector2f(width, height / 2);

    while (window.isOpen())
    {
        window.clear();
        sf::Event event;
        while (window.pollEvent(event))
        {

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
            }
        }
        window.draw(points);
        // window.draw(line);
        window.display();
    }
    return 0;
}