#include "raylib.h"

int main()
{
    // Window Dimension
    int width{600};
    int height{400};

    InitWindow(width, height, "axce");
    
    // Circle Coordinates & radius
    int circleX{175};
    int circleY{100};
    int circleRadius{25};
    
    // Rectangle coordinates and values
    int recX{150};
    int recY{150};
    int directionX = 10;
    int directionY = 10;
    int recWidth = 100;
    int recHeight = 50;

    bool collisionCheck;
    // Set target FPS (maximum)
    SetTargetFPS(60);

    // While loop to render the window
    // WindowShouldClose: Check if KEY_ESCAPE pressed or Close icon pressed
    // return true if the above are triggered else false
    while(!WindowShouldClose())
    {
        
        // Setup canvas (framebuffer) to start drawing
        BeginDrawing(); 
        
        // Set background color (framebuffer clear color)
        ClearBackground(RED);
        
        // **** Games Logic Begins ****
        
        collisionCheck = (circleX - circleRadius <= recX + recWidth // check if left boundary of circle and right boundary of rectangle
                           && circleX + circleRadius >= recX // check if right boundary of circle and left boundary of rectangle
                           && circleY - circleRadius <= recY + recHeight // check top boundary of the circle and bottom boundary of rectangle
                           && circleY + circleRadius >= recY); // check bottom boundary of the circle and top boundary of rectangle))
        
        // Draw a color-filled circle
        DrawCircle(circleX, circleY, circleRadius, BLUE);

        // Go right
        if(IsKeyDown(KEY_D) && circleX < width - circleRadius)
        {
            circleX += 10;
        }

        // Go left
        if(IsKeyDown(KEY_A) && circleX > circleRadius)
        {
            circleX -= 10;
        }

        // *** Coordinate start from top left corner so 0 is the top and max value is the bottom for Y
        // Go up
        if(IsKeyDown(KEY_W) && circleY > circleRadius)
        {
            circleY -= 10;
        }

        // Go down 
        if(IsKeyDown(KEY_S) && circleY < height - circleRadius)
        {
            circleY += 10;
        }


        DrawRectangle(recX,recY,recWidth,recHeight,BLUE);



        recX += directionX;
        recY += directionY;
        
        if(collisionCheck)
        {
            directionX = 0;
            directionY = 0;
            DrawText("Hit!", recX + recWidth/3, recY + recHeight/3, 20, RED);
        }

        if(recX < 0 || recX > width - recWidth) // Check with boundary condition along the x-axis
        
        {
            directionX = -directionX;
        }
        if(recY < 0 || recY > height - recHeight) // Check with boundary condition along the y-axis
        {
            directionY = -directionY;
        }

       


        // **** Games Logic End ****
        
        // End canvas drawing and swap buffers (double buffering)
        EndDrawing();  
    }
    return 0;
}