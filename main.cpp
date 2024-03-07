#include "raylib.h"

int main(void)
{
    const int screenWidth = 360;
    const int screenHeight = 800;
    float percentage = screenWidth/2;
    Rectangle clickerposition = {percentage, 400};
    Vector2 circlepos = {percentage, 400};
    Rectangle mouse = {percentage, 400, 30, 30};
    int clicks = 0;
    bool collision = false;
    int multiplier = 1;
    int cost = 100;

    const int butxpos = 30;
    const int butypos = 100;
    Rectangle button = {butxpos, butypos, 50, 50};

    InitWindow(screenWidth, screenHeight, "Clicker");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(circlepos, 31.4, BLUE);

            DrawRectangle(butxpos, butypos, 50, 50, RED);

            mouse.x = GetMouseX() - mouse.width/2;
            mouse.y = GetMouseY() - mouse.height/2;

            if (collision = CheckCollisionRecs(clickerposition, mouse))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    clicks = clicks + multiplier;
                };
            };

            if (collision = CheckCollisionRecs(button, mouse))
            {
                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
                {
                    if (clicks >= cost)
                    {
                        clicks = clicks - cost;
                        multiplier ++;
                        cost = cost * multiplier;
                    }

                    else
                    {
                        DrawText("Insufficient funds", percentage - 50, 150 , 20, RED);
                    }
                }
            }

            DrawText(TextFormat("%i", clicks), percentage, 20, 40, LIGHTGRAY);

            DrawText(TextFormat("%i", multiplier), percentage, 70, 40, LIGHTGRAY);

            DrawText(TextFormat("%i", cost), butxpos, butypos + 50, 20, GREEN);

        EndDrawing();
    }

    CloseWindow();
    

    return 0;
}