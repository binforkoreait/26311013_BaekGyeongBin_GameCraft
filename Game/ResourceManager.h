#pragma once
#include <glc2d.h>
#include <filesystem>
#include <string>
#include <vector>
#include "Math2D.h"

class ResourceManager
{
public:
    bool Load();
    void Release();
    void DrawBackground() const;
    void DrawCharacter(int row, int frame, Vec2 feet, bool flip) const;
    void DrawCrosshair(Vec2 center) const;
    void PlayStart() const;
    void PlayHit() const;

    const std::string& Error() const
    {
        return error_;
    }

private:
    int LoadTexture(const std::filesystem::path& path);
    int background_ = -1, characters_ = -1, hud_ = -1, startSound_ = -1;
    int music_ = -1, hit_ = -1;
    std::vector<int> textures_;
    std::string error_;
};
