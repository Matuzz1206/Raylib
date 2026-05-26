#include "raylib.h"
#include "Pathfind.h"

int main()
{
    InitWindow(Pathfind::screenWidth, Pathfind::screenHeight, "Random Backtracking Pathfinding");

    Pathfind pathfind;
    pathfind.Main();
    pathfind.Start();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        pathfind.Interaction();
        pathfind.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        pathfind.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}