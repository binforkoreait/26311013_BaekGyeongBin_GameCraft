#include "GameRenderer.h"
#include <algorithm>

bool GameRenderer::Initialize()
{
    pauseFont_ = g2_FontCreate("Arial", 48);
    return pauseFont_ >= 0;
}

void GameRenderer::Render(const ResourceManager& resources, const Player& player,
                          const ZombieManager& zombies, const GameStateController& state,
                          Vec2 mouse) const
{
    resources.DrawBackground();

    struct Sprite
    {
        Vec2 position;
        int row;
        int frame;
        bool flip;
    };

    std::vector<Sprite> sprites;
    sprites.push_back({player.Position(), 0, player.Frame(), player.FacingLeft()});
    for (const auto& zombie : zombies.Zombies())
    {
        sprites.push_back(
            {zombie.Position(), zombie.SpriteRow(), zombie.Frame(), zombie.FacingLeft()});
    }
    std::sort(sprites.begin(), sprites.end(),
              [](const Sprite& first, const Sprite& second)
              {
                  return first.position.y < second.position.y;
              });
    for (const auto& sprite : sprites)
    {
        resources.DrawCharacter(sprite.row, sprite.frame, sprite.position, sprite.flip);
    }
    if (state.IsPaused())
    {
        g2_FontDrawText(pauseFont_, {530, 295}, 0xFFFFD580, "PAUSED");
    }
    else
    {
        resources.DrawCrosshair(mouse);
    }
}
