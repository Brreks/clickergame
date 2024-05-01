#include "raylib.h"
#include <math.h>

typedef enum screen {title, mini, shop, winner} screen;

#define max_shots 10

typedef struct Bullet {
    Vector2 pos;
    Vector2 vel;
    float rad;
    float rotation;
    int life;
    bool active;
    Color color;
} Bullet;

static Bullet bullet[max_shots] = {0};


int main(void)
{
    const int screenWidth = 360;
    const int screenHeight = 800;
    float percentage = screenWidth/2.0f;
    int health = 100, dmg = 5, money = 0, multiplier = 1, cost = 100, passive = 0;
    float minitime = 0;

    Vector2 circlepos = {percentage, 350};
    float circlerad = 31.4;

    float shootrad = 7.6;
    float angle = 0.0f;
    float delx = 0.0f, dely = 0.0f, del2x = 0.0f, del2y = 0.0f;

    const int butw = 50, buth = 50;

    float mpstime = 0;
    float deltatime = 0;

    const int butxpos = 50, butypos = 650, but2xpos = 150, but2ypos = 650, but3xpos = 250, but3ypos = 650;
    Rectangle button = {butxpos, butypos, butw, buth};
    Rectangle button2 = {but2xpos, but2ypos, butw, buth};
    Rectangle button3 = {but3xpos, but3ypos, butw, buth};

    Rectangle taskbar = {0, 600, 360, 200};

    const int shopx = 30, shopy = 60, shop2x = 30, shop2y = 160, shop3x = 30, shop3y = 260, shop4x = 30, shop4y = 360;
    Rectangle shop1 = {shopx, shopy, butw, buth};
    Rectangle shop2 = {shop2x, shop2y, butw, buth};
    Rectangle shop3 = {shop3x, shop3y, butw, buth};
    Rectangle shop4 = {shop4x, shop4y, butw, buth};

    const int winx = 30, winy = 460, wincost = 1000000;
    Rectangle win = {winx, winy, butw, buth};

    InitWindow(screenWidth, screenHeight, "Clicker");

    screen current = title;

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

                if (IsKeyPressed(KEY_P))
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
                };

                for (int i = 0; i < max_shots; i++)
                {
                    bullet[i].pos = {0,0};
                    bullet[i].vel = {0,0};
                    bullet[i].rad = 2;
                    bullet[i].active = false;
                    bullet[i].life = 0;
                    bullet[i].color = PURPLE;
                }

                if (IsKeyPressed(KEY_SPACE))
                {
                for (int i = 0; i < max_shots; i++)
                    {   
                        if (!bullet[i].active)
                        {
                        bullet[i].pos = {point_mouse.x, point_mouse.y};
                        bullet[i].active = true;
                        bullet[i].vel.x = 1;
                        bullet[i].vel.y = 1;
                        bullet[i].rotation = angle;
                        break;
                        }
                    }
                }

                for (int i = 0; i < max_shots; i++)
                {
                    if (bullet[i].active)
                    {
                        bullet[i].life++;
                    }
                }

                for (int i = 0; i < max_shots; i++)
                {
                    if(bullet[i].active)
                    {
                        bullet[i].pos.x += bullet[i].vel.x;
                        bullet[i].pos.y -= bullet[i].vel.y;

                        if (bullet[i].life >= 800)
                        {
                            bullet[i].pos = {0,0};
                            bullet[i].vel = {0,0};
                            bullet[i].life = 0;
                            bullet[i].active = false;
                        }
                    }
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

                if (CheckCollisionPointRec(point_mouse, shop1))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost)
                        {
                            passive += 1;
                            money = money - cost;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shop2))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost*4)
                        {
                            passive += 10;
                            money = money - cost*4;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shop3))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost*16)
                        {
                            passive += 100;
                            money = money - cost*16;
                            cost = cost * multiplier;
                        }
                    }
                }

                if (CheckCollisionPointRec(point_mouse, shop4))
                {
                    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        if (money >= cost*64)
                        {
                            passive += 1000;
                            money = money - cost*64;
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

                DrawRectangleRec(button2, RED);

                DrawRectangleRec(button3, RED);

                DrawText(TextFormat("dmg = %01i", dmg*multiplier), taskbar.x, taskbar.y - 20, 20, GREEN);

                DrawText(TextFormat("%01i $", money), percentage - 45, 20, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i x", multiplier), percentage - 45, 70, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i mps", passive), percentage - 45, 120, 40, LIGHTGRAY);

                DrawText(TextFormat("%01i / 100", health), percentage - 45, 400, 20, GREEN);

                DrawText(TextFormat("%01i $", cost), butxpos, butypos + 50, 20, GREEN);

                DrawText("Mini-game", but2xpos - 20, but2ypos + 50, 20, GREEN);

                DrawText("Shop", but3xpos, but3ypos + 50, 20, GREEN);

            } break;

            case mini:
            {

                DrawCircleV(circlepos, 31.4, BLUE);

                DrawCircleV(point_mouse, shootrad, RED);

                DrawText(TextFormat("%02.2f", minitime), percentage - 45, 20, 40, RED);

                for (int i = 0; i < max_shots; i++)
                {
                    if (bullet[i].active)
                    {
                        DrawCircleV(bullet[i].pos, bullet[i].rad, PURPLE);
                    }
                }
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
            }
        }   

        EndDrawing();
    }

    CloseWindow();
    

    return 0;
}