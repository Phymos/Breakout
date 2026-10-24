#include "raylib.h"
#include <cmath>
#include <vector>

const int screenWidth = 800;
const int screenHeight = 450;

struct Ball {
    Vector2 pos;
    Vector2 speed;
    float radius;
};

void ResetBall(Ball& ball)
{
    ball.pos = { screenWidth / 2.0f, screenHeight / 2.0f };
    ball.speed = { 300.0f, 200.0f };
}

void UpdateBall(Ball& ball, int& hp, float dt)
{
    ball.pos.x += ball.speed.x * dt;
    ball.pos.y += ball.speed.y * dt;

    if (ball.pos.x < ball.radius || ball.pos.x > screenWidth - ball.radius)
        ball.speed.x *= -1;
    if (ball.pos.y < ball.radius)
        ball.speed.y *= -1;

    if (ball.pos.y > screenHeight) {
		hp--;
		ResetBall(ball);
	}
}

struct Paddle
{
    Vector2 pos;
    Vector2 speed;
    Vector2 size;

    Paddle(Vector2 pos, Vector2 size){
        this->speed = { 500.0f, 0.0f };
        this->size = size;
        this->pos = pos;
    }
};

void UpdatePaddle(Paddle& p, int keyLeft, int keyRight, float dt){
        if (IsKeyDown(keyLeft)) p.pos.x -= p.speed.x * dt;
        if (IsKeyDown(keyRight)) p.pos.x += p.speed.x * dt;

        if (p.pos.x < 0) p.pos.x = 0;
        else if (p.pos.x > screenWidth - p.size.x) p.pos.x = screenWidth - p.size.x;
}

struct Brick {
    Rectangle rect;
    bool alive;
};


int main()
{
    InitWindow(screenWidth, screenHeight, "Breakout");
    SetTargetFPS(120);

    Ball ball = { { screenWidth / 2.0f, screenHeight / 2.0f }, { 300.0f, 200.0f }, 10.0f };

    Paddle paddle1 = { { screenWidth / 2.0f, 400}, {100, 20} };

	int hp = 3;
    bool gameOver = false;

	std::vector<Brick> bricks;
	for (int i = 0; i < 10; i++)
    	for (int j = 0; j < 6; j++)
        	bricks.push_back({ { 15.0f + 78 * i, 15.0f + 30 * j, 70.0f, 20.0f }, true });

    while (!WindowShouldClose())
    {
        // 1) Güncelle
        if (!gameOver)
        {
            float dt = GetFrameTime();

            UpdateBall(ball, hp, dt);

            UpdatePaddle(paddle1, KEY_A, KEY_D, dt);
            
            Rectangle r1 = { paddle1.pos.x, paddle1.pos.y, paddle1.size.x, paddle1.size.y };

            if (CheckCollisionCircleRec(ball.pos, ball.radius, r1) && ball.speed.y > 0)
                ball.speed.y = -fabsf(ball.speed.y);

			for (Brick& b : bricks) {
				if (b.alive && CheckCollisionCircleRec(ball.pos, ball.radius, b.rect)) {
					b.alive = false;
					ball.speed.y *= -1;
                    break;
				}
			}

            bool anyAlive = false;
            for (const Brick& b : bricks)
                if (b.alive) { anyAlive = true; break; }

            if (!anyAlive)
                gameOver = true;

            if (hp <= 0)
                gameOver = true;
        }

        if (IsKeyPressed(KEY_R) && gameOver)
        {
            gameOver = false;
            ResetBall(ball);
            hp = 3;
            for (Brick& b : bricks) b.alive = true;
        }

        // 2) Çiz
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleV(ball.pos, ball.radius, WHITE);
        DrawRectangleV(paddle1.pos, paddle1.size, WHITE);

        DrawText(TextFormat("HP: %d", hp), 20, 420, 20, WHITE);

        if (gameOver) {
            if (hp > 0) DrawText("YOU WIN!", 300, 200, 40, WHITE);
            else        DrawText("GAME OVER", 290, 200, 40, WHITE);
            DrawText("Press R to restart", 280, 260, 30, WHITE);
        }
 
		for (const Brick& b : bricks)
    		if (b.alive) DrawRectangleRec(b.rect, WHITE);

        EndDrawing();
    }

    CloseWindow();
}