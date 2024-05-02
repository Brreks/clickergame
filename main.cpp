#include "raylib.h"
#include <math.h>

typedef enum screen {title, mini, aftermini, shop, winner} screen;

int main(void)
{
    const int screenWidth = 360;
    const int screenHeight = 800;
    float percentage = screenWidth/2.0f;
    int health = 100, dmg = 5, money = 0, multiplier = 1, cost = 100, passive = 0;
    float minitime = 0, intimer = 0;

    Vector2 circlepos = {percentage, 350};

    const int butw = 50, buth = 50;

    float mpstime = 0;
    float deltatime = 0;

    const int butxpos = 50, butypos = 650, but2xpos = 150, but2ypos = 650, but3xpos = 250, but3ypos = 650;
    Rectangle button = {butxpos, butypos, butw, buth};
    Rectangle minibut = {but2xpos, but2ypos, butw, buth};
    Rectangle shpbut = {but3xpos, but3ypos, butw, buth};

    Rectangle taskbar = {0, 600, 360, 200};

    const int shopx = 30, shopy = 60, shop2x = 30, shop2y = 160, shop3x = 30, shop3y = 260, shop4x = 30, shop4y = 360;
    Rectangle shop1 = {shopx, shopy, butw, buth};
    Rectangle shop2 = {shop2x, shop2y, butw, buth};
    Rectangle shop3 = {shop3x, shop3y, butw, buth};
    Rectangle shop4 = {shop4x, shop4y, butw, buth};

    const int winx = 30, winy = 460, wincost = 1000000;
    Rectangle win = {winx, winy, butw, buth};

    const int clkx = percentage, clky = 400, clkrad = 25;
    Vector2 clkr = {(float)clkx, clky};
    int nmbclkr = 0, moneymini = 0;

    InitWindow(screenWidth, screenHeight, "Clicker");

    screen current = title;
    screen lastused = title;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 point_mouse = GetMousePosition();

        deltatime = GetFrameTime();
        mpstime += deltatime;
                
        if (mpstime >= 1)
        {
            money += passive;
            mpstime = 0;
        }  

        switch(current)
        {
            case title:
            {
                if (intimer < 15)
                {
                    if (current == title || current == shop)
                    {
                        intimer += deltatime;
                    }
                } 

                if (CheckCollisionPointCircle(point_mouse, circlepos, 31.4))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        health -= dmg * multiplier;
                    }

                    if (health <= 0)
                    {
                        health = 100;
                        money += 100;
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

                if (CheckCollisionPointRec(point_mouse, minibut))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (intimer >= 15)
                        {
                            current = mini;
                            intimer = 0;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shpbut))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        current = shop;
                    }
                }

                if (lastused == aftermini)
                {
                    lastused = title;
                    nmbclkr = 0;
                    minitime = 0;
                }
            } break;

            case mini:
            {
                minitime += GetFrameTime();

                if (minitime >= 30)
                {
                    current = aftermini;
                }

                if (IsKeyPressed(KEY_P))
                {
                    current = aftermini;
                }

                if (CheckCollisionPointCircle(point_mouse, clkr, clkrad))
                {
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        clkr.x = GetRandomValue(clkrad, screenWidth-clkrad);
                        clkr.y = GetRandomValue(clkrad, 800-clkrad);
                        moneymini += 10 * multiplier;
                        nmbclkr += 1;
                        money += moneymini;
                    }
                } 
                
            } break;

            case aftermini:
            {
                lastused = mini;
                WaitTime(2);
                current = title;
                lastused = aftermini;
            }

            case shop:
            {
                if (CheckCollisionPointRec(point_mouse, button))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        current = title;
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shop1))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost)
                        {
                            passive += 1;
                            money = money - cost;
                            multiplier++;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shop2))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost*1.33)
                        {
                            passive += 10;
                            money = money - cost*1.33;
                            multiplier++;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shop3))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost*1.76)
                        {
                            passive += 100;
                            money = money - cost*1.76;
                            multiplier++;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shop4))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost*2.33)
                        {
                            passive += 1000;
                            money = money - cost*2.33;
                            multiplier++;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, win))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= wincost)
                        {
                            current = winner;
                        }
                    }
                }
            } break;

            case winner:
            {
                lastused = winner;
            }
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (current)
        {
            case title:
            {
                DrawCircleV(circlepos, 31.4, BLUE);

                DrawRectangleRec(taskbar, BLUE);

                DrawRectangleRec(button, RED);

                DrawRectangleRec(minibut, RED);

                DrawRectangleRec(shpbut, RED);

                DrawText(TextFormat("dmg = %01i", dmg*multiplier), taskbar.x, taskbar.y - 20, 20, GREEN);

                DrawText(TextFormat("%01i $", money), percentage - 45, 20, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i x", multiplier), percentage - 45, 70, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i mps", passive), percentage - 45, 120, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i / 100", health), percentage - 45, 400, 20, GREEN);

                DrawText(TextFormat("%01i $", cost), butxpos, butypos + 50, 20, GREEN);

                DrawText("Mini-game", but2xpos - 20, but2ypos + 50, 20, GREEN);

                DrawText("Shop", but3xpos, but3ypos + 50, 20, GREEN);

                if (intimer < 15)
                {
                    DrawText(TextFormat("%02.2f / 15.00", intimer), 125, 630, 20, LIGHTGRAY);
                }

                else 
                {
                    DrawText("PLAY", 150, 630, 20, GREEN);
                }

            } break;

            case mini:
            {
                DrawCircleV(clkr, clkrad, BLUE);

                DrawText(TextFormat("%02.2f", minitime), percentage - 45, 20, 40, RED);

                DrawText(TextFormat("%01i clicked", nmbclkr), percentage - 45, 60, 40, LIGHTGRAY);

            } break;

            case aftermini:
            {
                ClearBackground(BLACK);

                DrawText(TextFormat("%01i * 50 $", nmbclkr), percentage - 75, 300, 40, RED);

                DrawText(TextFormat("%01i $", moneymini), percentage - 75, 340, 40, RED);

            } break;

            case shop:
            {
                DrawRectangleRec(taskbar, BLUE);

                DrawRectangleRec(shop1, RED);

                DrawText(TextFormat("%01i $", cost), shopx, shopy + 50, 20, GREEN);

                DrawText("Adds 1 mps", shopx + 70, shopy + 20, 20, GREEN);

                DrawRectangleRec(shop2, RED);
                
                DrawText(TextFormat("%01i $", cost*4), shop2x, shop2y + 50, 20, GREEN);

                DrawText("Adds 10 mps", shop2x + 70, shop2y + 20, 20, GREEN);

                DrawRectangleRec(shop3, RED);

                DrawText(TextFormat("%01i $", cost*16), shop3x, shop3y + 50, 20, GREEN);

                DrawText("Adds 100 mps", shop3x + 70, shop3y + 20, 20, GREEN);

                DrawRectangleRec(shop4, RED);

                DrawText(TextFormat("%01i $", cost*64), shop4x, shop4y + 50, 20, GREEN);

                DrawText("Adds 1000 mps", shop4x + 70, shop4y + 20, 20, GREEN);

                DrawRectangleRec(win, RED);

                DrawText(TextFormat("%01i $", wincost), winx, winy + 50, 20, GREEN);

                DrawText("Win Button", winx + 70, winy + 20, 20, GREEN);

                DrawRectangleRec(button, RED);

                DrawText("Back", butxpos, butypos + 50, 20, GREEN);

            } break;

            case winner:
            {
                ClearBackground(BLACK);

                DrawText("YOU HAVE WON", percentage - 150, 300, 40, RED);

                DrawText("THE GAME", percentage - 150, 340, 40, RED);

                DrawText("Press ESC to quit the game", percentage - 150, 400, 20, RED);
            }
        }   

        EndDrawing();
    }

    CloseWindow();
    

    return 0;
}