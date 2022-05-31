#include "raylib.h"

int main()
{
    int width = 1020;
    int height = 640;
    char* title = "Spiffy Dasher";

    SetTargetFPS(60);

    InitWindow(width, height, title);

    while(!WindowShouldClose())
    {
        // Begin Drawing
        BeginDrawing();
        // Clear the current buffer to show the next buffer
        ClearBackground(BLACK);




        // Stop Drawing
        EndDrawing();

    }

    // Close window and unload OpenGL context
    CloseWindow();
    return 0;
}