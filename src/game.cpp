#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <unistd.h>
#include <cstdint>

using namespace std;

const int32_t WIDTH = 40, HEIGHT = 20;
const int32_t ESC = 27;
const int32_t FPS = 10, FRAME_TIME = 1000 / (FPS > 0 ? FPS : 15);
const int32_t MAX_SCORE = (WIDTH * HEIGHT) / 4;

int32_t delta_time = 1;
bool game_over;
int32_t head_x, head_y, fruit_x, fruit_y, score;
int32_t tail_x[MAX_SCORE + 1], tail_y[MAX_SCORE + 1];
int32_t next_direction[][2] = {
    {0, 0},  //  STOP
    {1, 0},  //  RIGHT
    {0, -1}, //  UP
    {-1, 0}, //  LEFT
    {0, 1}   //  DOWN
};

enum e_direction
{
    STOP = 0,
    RIGHT,
    UP,
    LEFT,
    DOWN
} direction;

void setup();
void draw();
void input();
void logic();
int32_t bounded_rand(int32_t lower_bound, int32_t upper_bound);
void freeplay();
void update_score();
void update_directions();
bool is_side_border(int32_t position_x);
bool is_head(int32_t position_y, int32_t position_x);
bool is_fruit(int32_t position_y, int32_t position_x);
void generate_fruit();
void get_direction_input();
void update_tail();
bool is_tail(int32_t position_y, int32_t position_x);
void next_frame(clock_t start_time);

/**
 *
 * DRIVER FUNCTION
 *
 */
int32_t main()
{
    srand(time(NULL));
    setup();
    while (!game_over && score < MAX_SCORE)
    {
        clock_t start_time = clock();
        
        draw();
        input();
        logic();
        next_frame(start_time);
    }
    if (score >= MAX_SCORE)
    {
        cout << "\nDamn you really beat the Snake Game! :D\n";
    }
    return 0;
}

void setup()
{
    game_over = false;
    head_x = 1 + WIDTH / 2;
    head_y = 1 + HEIGHT / 2;
    generate_fruit();
    direction = STOP;
    string output;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < PATH_MAX * 2; j++) {
            output += ' ';
        }
        output += '\n';
    }
    cout << "\x1b[d" << output;
}

void draw()
{
    string output;

    for (int32_t position_y = 0; position_y < HEIGHT + 2; ++position_y)
    {
        if (position_y == 0 || position_y == HEIGHT + 1)
        {
            for (int32_t position_y = 0; position_y < WIDTH + 2; ++position_y)
            {
                output += '#';
            }
            output += '\n';
            continue;
        }
        for (int32_t position_x = 0; position_x < WIDTH + 2; ++position_x)
        {
            if (is_side_border(position_x))
            {
                output += '#';
            }
            else if (is_head(position_y, position_x))
            {
                output += 'O';
            }
            else if (is_fruit(position_y, position_x))
            {
                output += (char)254;
            }
            else if (is_tail(position_y, position_x))
            {
                output += 'o';
            }
            else
            {
                output += ' ';
            }
        }
        output += '\n';
    }
    cout << "\x1b[d" << output << "Score: " << score << '\n';
}

bool is_fruit(int32_t position_y, int32_t position_x)
{
    return position_x == fruit_x && position_y == fruit_y;
}

bool is_head(int32_t position_y, int32_t position_x)
{
    return position_x == head_x && position_y == head_y;
}

bool is_side_border(int32_t position_x)
{
    return position_x == 0 || position_x == WIDTH + 1;
}

int32_t bounded_rand(int32_t lower_bound, int32_t upper_bound)
{
    return lower_bound + rand() % (upper_bound - lower_bound + 1);
}

void input()
{
    if (_kbhit())
    {
        get_direction_input();
    }
}

void get_direction_input()
{
    e_direction new_direction = direction;

    switch (getch())
    {
    case 'a':
        new_direction = LEFT;
        break;
    case 'w':
        new_direction = UP;
        break;
    case 's':
        new_direction = DOWN;
        break;
    case 'd':
        new_direction = RIGHT;
        break;
    case ESC:
        game_over = true;
        return;
    }

    if (abs(direction - new_direction) != 2)
    {
        direction = new_direction;
    }
}

void logic()
{
    if (is_tail(head_y, head_x) || is_tail(fruit_x, fruit_y))
    {
        game_over = true;
    }
    update_tail();
    update_directions();
    freeplay();
    update_score();
}

void update_directions()
{
    head_x += next_direction[direction][0];
    head_y += next_direction[direction][1];
}

void freeplay()
{
    if (head_x == 0)
    {
        head_x = WIDTH;
    }
    if (head_x == WIDTH + 1)
    {
        head_x = 1;
    }
    if (head_y == 0)
    {
        head_y = HEIGHT;
    }
    if (head_y == HEIGHT + 1)
    {
        head_y = 1;
    }
}

void update_score()
{
    if (is_fruit(head_y, head_x))
    {
        ++score;
        fruit_x = bounded_rand(1, WIDTH);
        fruit_y = bounded_rand(1, HEIGHT);
    }
}

void generate_fruit()
{
    do {
        fruit_x = bounded_rand(1, WIDTH);
        fruit_y = bounded_rand(1, HEIGHT);
    } while (is_head(fruit_y, fruit_x) || is_tail(fruit_y, fruit_x));
}

void update_tail()
{
    int32_t prev_x = tail_x[0];
    int32_t prev_y = tail_y[0];

    tail_x[0] = head_x;
    tail_y[0] = head_y;
    for (int32_t i = 1; i < score; ++i)
    {
        int32_t temp_x = tail_x[i];
        int32_t temp_y = tail_y[i];

        tail_x[i] = prev_x;
        tail_y[i] = prev_y;
        prev_x = temp_x;
        prev_y = temp_y;
    }
}

bool is_tail(int32_t position_y, int32_t position_x)
{
    for (int32_t i = 0; i < score; ++i)
    {
        if (tail_x[i] == position_x && tail_y[i] == position_y)
        {
            return true;
        }
    }
    return false;
}

void next_frame(clock_t start_time)
{
    const int32_t CYCLE_TIME_LIMIT = (direction == UP || direction == DOWN ? (int32_t)(FRAME_TIME * 2) : FRAME_TIME);
    clock_t cycle_time = clock() - start_time;

    if (cycle_time < CYCLE_TIME_LIMIT)
    {
        usleep((CYCLE_TIME_LIMIT - cycle_time) * 1000);
    }
}
