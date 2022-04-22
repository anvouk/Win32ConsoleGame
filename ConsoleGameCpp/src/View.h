#pragma once

class Map;

class View {
public:
    explicit View();

    void Clear() const;

    bool CalculatePlayerOffset(const Map& map);

    [[nodiscard]] int GetWidth() const { return w; }
    [[nodiscard]] int GetHeight() const { return h; }

    [[nodiscard]] int GetOffsetX() const { return offset_x; }
    [[nodiscard]] int GetOffsetY() const { return offset_y; }

private:
    int w, h;
    int offset_x, offset_y;
};
