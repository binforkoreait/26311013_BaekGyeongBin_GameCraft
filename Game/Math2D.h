#pragma once
#include <algorithm>
#include <cmath>

struct Vec2
{
    float x = 0, y = 0;

    Vec2 operator+(Vec2 b) const
    {
        return {x + b.x, y + b.y};
    }

    Vec2 operator-(Vec2 b) const
    {
        return {x - b.x, y - b.y};
    }

    Vec2 operator*(float s) const
    {
        return {x * s, y * s};
    }

    float Length() const
    {
        return std::sqrt(x * x + y * y);
    }

    Vec2 Normalized() const
    {
        float n = Length();
        return n > 0.0001f ? *this * (1 / n) : Vec2{};
    }
};

struct Bounds
{
    float left = 115, top = 135, right = 1165, bottom = 595;

    Vec2 Clamp(Vec2 p) const
    {
        return {std::clamp(p.x, left, right), std::clamp(p.y, top, bottom)};
    }
};
