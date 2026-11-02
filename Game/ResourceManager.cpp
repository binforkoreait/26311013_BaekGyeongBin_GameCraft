#include "ResourceManager.h"

int ResourceManager::LoadTexture(const std::filesystem::path& path)
{
    const int id = g2_TextureLoad(path.u8string().c_str(), 0);
    if (id >= 0)
    {
        textures_.push_back(id);
    }
    else
    {
        error_ = "Cannot load texture: " + path.u8string();
    }
    return id;
}

bool ResourceManager::Load()
{
    wchar_t module[32768]{};
    const DWORD size = GetModuleFileNameW(nullptr, module, 32768);
    if (size == 0 || size >= 32768)
    {
        error_ = "Cannot locate executable directory.";
        return false;
    }
    const auto root = std::filesystem::path(module).parent_path() / "Resources";
    const auto images = root / "Images" / "LastZone";
    background_ = LoadTexture(images / "arena_v1.png");
    if (background_ < 0)
    {
        return false;
    }
    characters_ = LoadTexture(images / "characters_walk_v1.png");
    if (characters_ < 0)
    {
        return false;
    }
    hud_ = LoadTexture(images / "hud_icons_v1.png");
    if (hud_ < 0)
    {
        return false;
    }
    startSound_ = g2_SoundLoad((root / "Sounds" / "start.wav").u8string().c_str());
    music_ = g2_SoundLoad((root / "Sounds" / "bgm.wav").u8string().c_str());
    hit_ = g2_SoundLoad((root / "Sounds" / "hit.wav").u8string().c_str());
    if (startSound_ < 0 || music_ < 0 || hit_ < 0)
    {
        error_ = "Cannot load game sounds.";
        return false;
    }
    g2_SoundPlay(music_, true);
    return true;
}

void ResourceManager::Release()
{
    for (int id : {music_, hit_})
    {
        if (id >= 0) { g2_SoundStop(id); g2_SoundRelease(id); }
    }
    music_ = hit_ = -1;
    if (startSound_ >= 0)
    {
        g2_SoundRelease(startSound_);
    }
    startSound_ = -1;
    for (int id : textures_)
    {
        g2_TextureRelease(id);
    }
    textures_.clear();
    background_ = characters_ = hud_ = -1;
}

void ResourceManager::DrawBackground() const
{
    const VEC2 position(0, 0);
    const VEC2 scale(1280.0f / g2_TextureWidth(background_),
                     720.0f / g2_TextureHeight(background_));
    g2_Draw2D(background_, nullptr, &position, &scale);
}

void ResourceManager::DrawCharacter(int row, int frame, Vec2 feet, bool flip) const
{
    const int w = g2_TextureWidth(characters_);
    const auto edge = [](int index, int size)
    {
        return (index * size + 2) / 4;
    };
    // Measured row gutters prevent a neighbouring zombie head from leaking in.
    const int rowTop[]{10, 294, 612, 892};
    const int rowBottom[]{285, 600, 892, 1230};
    const RECT source{edge(frame, w), rowTop[row], edge(frame + 1, w), rowBottom[row]};
    const VEC2 position(feet.x - 48, feet.y - 90);
    const VEC2 scale((flip ? -96.0f : 96.0f) / (source.right - source.left),
                     96.0f / (source.bottom - source.top));
    g2_Draw2D(characters_, &source, &position, &scale);
}

void ResourceManager::DrawCrosshair(Vec2 center) const
{
    const RECT source{940, 290, 1225, 595};
    const VEC2 position(center.x - 16, center.y - 16), scale(32.0f / 285, 32.0f / 305);
    g2_Draw2D(hud_, &source, &position, &scale);
}

void ResourceManager::PlayStart() const
{
    if (startSound_ >= 0)
    {
        g2_SoundReset(startSound_);
        g2_SoundPlay(startSound_);
    }
}

void ResourceManager::PlayHit() const
{
    if (hit_ >= 0) { g2_SoundReset(hit_); g2_SoundPlay(hit_); }
}
