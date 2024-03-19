#include "raylib.h"
#include <math.h>

typedef enum screen {title, mini, shop} screen;

int main(void)
{
    const int screenWidth = 360;
    const int screenHeight = 800;
    float percentage = screenWidth/2.0f;
    int health = 100, dmg = 5, money = 0, multiplier = 1, cost = 100;
    float minitime = 0;

    Vector2 circlepos = {percentage, 400};
    float circlerad = 31.4;

    Vector2 shooter = {percentage, 400};
    float shootrad = 7.6;
    float angle = 0.0f;
    float delx = 0.0f, dely = 0.0f, del2x = 0.0f, del2y = 0.0f;

    const int butxpos = 30, butypos = 100, but2xpos = 30, but2ypos = 180, but3xpos = 30, but3ypos = 260;
    Rectangle button = {butxpos, butypos, 50, 50};
    Rectangle button2 = {but2xpos, but2ypos, 50, 50};
    Rectangle button3 = {but3xpos, but3ypos, 50, 50};

    InitWindow(screenWidth, screenHeight, "Clicker");

    screen current = title;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 point_mouse = GetMousePosition();

        switch(current)
        {
            case title:
            {
                if (CheckCollisionPointCircle(point_mouse, circlepos, 31.4))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        health -= dmg * multiplier;
                    }

                    if (health == 0)
                    {
                        health = 100;
                        money += 10;
                    }
                }
                
                if (CheckCollisionPointRec(point_mouse, button))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost)
                        {
                            money = money - cost;
                            multiplier ++;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, button2))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        current = mini;
                    }
                }

                if (CheckCollisionPointRec(point_mouse, button3))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        current = shop;
                    }
                }
            } break;

            case mini:
            {
                minitime += GetFrameTime();

                if (minitime >= 30)
                {
                    current = title;
                }

                if (!CheckCollisionPointCircle(point_mouse, circlepos, circlerad - shootrad && circlerad == shootrad))
                {
                    delx = point_mouse.x - circlepos.x;
                    dely = point_mouse.y - circlepos.y;

                    angle = atan2f(dely,delx);

                    del2x = (circlerad - shootrad)*cosf(angle);
                    del2y = (circlerad - shootrad)*sinf(angle);

                    point_mouse.x = circlepos.x + del2x;
                    point_mouse.y = circlepos.y + del2y;
                }
            } break;

            case shop:
            {
                if (CheckCollisionPointRec(point_mouse, button))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        current = title;
                    }
                }
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (current)
        {
            case title:
            {
                DrawCircleV(circlepos, 31.4, BLUE);

                DrawRectangleRec(button, RED);

                DrawRectangleRec(button2, RED);

                DrawRectangleRec(button3, RED);

                DrawText(TextFormat("%01i $", money), percentage, 20, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i x", multiplier), percentage, 70, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i / 100", health), percentage + 50, 400, 20, GREEN);

                DrawText(TextFormat("%01i $", cost), butxpos, butypos + 50, 20, GREEN);

                DrawText("Mini-game", but2xpos, but2ypos + 50, 20, GREEN);

                DrawText("Shop", but3xpos, but3ypos + 50, 20, GREEN);

            } break;

            case mini:
            {
                DrawCircleV(circlepos, 31.4, BLUE);

                DrawCircleV(point_mouse, shootrad, RED);

                DrawText(TextFormat("%02.2f", minitime), percentage, 20, 40, RED);
            } break;

            case shop:
            {
                DrawRectangleRec(button, RED);

                DrawText("Back", butxpos, butypos + 50, 20, GREEN);
            }
        }   

        EndDrawing();
    }

    CloseWindow();
    

    return 0;
}