#pragma once
#include "raylib.h"
#include <string>

struct Node
{
    int row, col;
    Vector2 position;
    Vector2 size;
    Color fillColor = GRAY, outlineColor = BLACK;
    bool blocked = false;
    bool visited = false;
    std::string text = "";
    Node* parent = nullptr;

    Node(int row, int col, Vector2 position, Vector2 size)
        : row(row), col(col), position(position), size(size) {
    }

    void Reset()
    {
        fillColor = GRAY;
        outlineColor = BLACK;
        blocked = false;
        visited = false;
        text = "";
        parent = nullptr;
    }

    void Draw()
    {
        DrawRectangleV(position, size, fillColor);

        int textHeight = (int)(size.y * 0.8f);
        int textWidth = MeasureText(text.c_str(), textHeight);

        DrawText(
            text.c_str(),
            (int)(position.x + (size.x - textWidth) * 0.5f),
            (int)(position.y + (size.y - textHeight) * 0.5f),
            textHeight,
            BLACK
        );

        DrawRectangleLines(
            (int)position.x,
            (int)position.y,
            (int)size.x,
            (int)size.y,
            outlineColor
        );
    }
};