#pragma once

class Player;
class Map;

class View {
public:
    explicit View();

    void Clear() const;

    bool CalculatePlayerOffset(const Map& map, const Player& player);

    [[nodiscard]] int GetWidth() const { return w; }
    [[nodiscard]] int GetHeight() const { return h; }

    [[nodiscard]] int GetOffsetX() const { return offsetX; }
    [[nodiscard]] int GetOffsetY() const { return offsetY; }

private:
    int w, h;
    int offsetX, offsetY;
};
