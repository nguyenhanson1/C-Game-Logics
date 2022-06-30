#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main()
{
    int windowDimension[2];
    windowDimension[0] = 512;
    windowDimension[1] = 380;
    char* title = "Spiffy Dasher";

    SetTargetFPS(60);

    InitWindow(windowDimension[0], windowDimension[1], title);
    
    // ******** Player Information & variables **********
    int jumpVelocity{-600};

    const int gravity{1000};

    int velocity {0};

    float runningTime{0};

    bool bIsInAir = false;

    // ******** Hazard Information & variables *********
    AnimData Hazards[2];


    Texture2D Hazard = LoadTexture("Sidescroll Run textures/textures/12_nebula_spritesheet.png");
    AnimData HazardAnimData{{0.0,0.0, Hazard.width / 8, Hazard.height / 8},// initialization of rectangle data
                            {windowDimension[0], windowDimension[1] - Hazard.height/8},// initialization of vector2 position
                            0, // initialize current frame of animation
                            1.0/12.0, // update time for new frame of animation
                            0.0 // initialize running time of the current object
                            };

    int HazardVelocity{-600}; 

    AnimData Hazard2AnimData{{0.0,0.0, Hazard.width / 8, Hazard.height / 8},// initialization of rectangle data
                            {windowDimension[0] + 300, windowDimension[1] - Hazard.height/8},// initialization of vector2 position
                            0, // initialize current frame of animation
                            1.0/16.0, // update time for new frame of animation
                            0.0 // initialize running time of the current object
                            };

    Hazards[0] = HazardAnimData;
    Hazards[1] = Hazard2AnimData;

    // Texture File for animation file
    Texture2D Spiffy = LoadTexture("Sidescroll Run textures/textures/scarfy.png");
    AnimData SpiffyAnimData;
    // Set rectangle data of spiffy anim data
    SpiffyAnimData.rec.width = Spiffy.width/6;
    SpiffyAnimData.rec.height = Spiffy.height;
    SpiffyAnimData.rec.x = 0;
    SpiffyAnimData.rec.y = 0;
    // Set spiffy position
    SpiffyAnimData.pos.x =  windowDimension[0]/2 - SpiffyAnimData.rec.width/2;
    SpiffyAnimData.pos.y = windowDimension[1] - SpiffyAnimData.rec.height;
    SpiffyAnimData.frame = 0;
    SpiffyAnimData.updateTime = 1.0 / 12.0;
    SpiffyAnimData.runningTime = 0.0;

    while(!WindowShouldClose())
    {
        // Set Delta time depend on frame time
        float deltaTime{ GetFrameTime() };

        // ******** Spiffy update **********    
        // add running time per frame
        SpiffyAnimData.runningTime += deltaTime;    

        // Stop animation update if the character is in the air
        if(!bIsInAir)
        {
            // check running time whether to update or not
            if(SpiffyAnimData.runningTime > SpiffyAnimData.updateTime)
            {
                SpiffyAnimData.runningTime = 0;

                // Set the animation sprite
                SpiffyAnimData.rec.x = SpiffyAnimData.frame * SpiffyAnimData.rec.width;
                // Update Animation
                SpiffyAnimData.frame++;
                if (SpiffyAnimData.frame > 5)
                {
                    SpiffyAnimData.frame = 0;
                }
                
            }
        }
        

        // Begin Drawing
        BeginDrawing();
        // Clear the current buffer to show the next buffer
        ClearBackground(BLACK);

        // Update Velocity based on gravity
        if(SpiffyAnimData.pos.y >= windowDimension[1] - SpiffyAnimData.rec.height)
        {
            velocity = 0;
            bIsInAir = false;
        }
        else{
            velocity += gravity * deltaTime;
            bIsInAir = true;
        }

        if(IsKeyPressed(KEY_SPACE) && !bIsInAir)
        {
            velocity += jumpVelocity;
        }


        // Update Position
        SpiffyAnimData.pos.y += velocity * deltaTime;

        // ******** Hazard 1 update **********     

        Hazards[0].runningTime += deltaTime;

        if(Hazards[0].runningTime > Hazards[0].updateTime)
        {
            Hazards[0].runningTime = 0.0;
            Hazards[0].rec.x = Hazards[0].frame * Hazards[0].rec.width;
            Hazards[0].frame++;
            if( Hazards[0].frame > 7 )
            {
                Hazards[0].frame = 0;

            }
        }

        Hazards[0].pos.x +=  HazardVelocity * deltaTime;
 
        // ******** Hazard 2 update **********     

        Hazards[1].runningTime += deltaTime;

        if(Hazards[1].runningTime > Hazards[1].updateTime)
        {
            Hazards[1].runningTime = 0.0;
            Hazards[1].rec.x = Hazards[1].frame * Hazards[1].rec.width;
            Hazards[1].frame++;
            if( Hazards[1].frame > 7 )
            {
                Hazards[1].frame = 0;

            }
        }

        Hazards[1].pos.x +=  HazardVelocity * deltaTime;


        // Draw Hazard 1
        DrawTextureRec(Hazard, Hazards[0].rec, Hazards[0].pos, WHITE);

        // Draw Hazard 2
        DrawTextureRec(Hazard, Hazards[1].rec, Hazards[1].pos, WHITE);

        // Draw Spiffy
        DrawTextureRec(Spiffy, SpiffyAnimData.rec, SpiffyAnimData.pos, WHITE);

        // Stop Drawing
        EndDrawing();

    }


    UnloadTexture(Spiffy);
    UnloadTexture(Hazard);
    // Close window and unload OpenGL context
    CloseWindow();
    return 0;
}