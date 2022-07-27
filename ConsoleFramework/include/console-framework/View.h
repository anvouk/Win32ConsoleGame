#pragma once

class Player;
class Map;

class View {
public:
    explicit View();

    void Clear() const;

    bool CalculatePlayerOffset(const Map& map, const Player& player);

    [[nodiscard]] int GetWidth() const { return m_w; }
    [[nodiscard]] int GetHeight() const { return m_h; }

    [[nodiscard]] int GetOffsetX() const { return m_offsetX; }
    [[nodiscard]] int GetOffsetY() const { return m_offsetY; }

private:
    int m_w, m_h;
    int m_offsetX, m_offsetY;
};
