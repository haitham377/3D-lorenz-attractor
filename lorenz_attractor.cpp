#include<cmath>
#include<deque>
#include "raylib.h"
const float sigma = 10.0f;
const float rho   = 28.0f;
const float beta  = 8.0f/3.0f;
const float dt    = 0.01f;



int main() {
    InitWindow(800, 600, "3D Lorenz Attractor");
    SetTargetFPS(60);
    
    float x = 0.1f;
    float y = 0.0f;
    float z = 0.0f;

    Camera camera = {0};
    camera.position = (Vector3){0.0f, 40.0f, 80.0f};
    camera.up       = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy     = 45.0f;

    float radius = 90.0f;
    float height = 30.0f;
    float speed  = 0.2f;

    Vector3 center = {0.0f, 0.0f, 0.0f};
    camera.target = center;

    std::deque<Vector3> trail;

    trail.push_back({x, y, z});

    
    while (!WindowShouldClose()) {
        float dx = sigma * (y - x) * dt;
        float dy = (x * (rho - z) - y) * dt;
        float dz = (x * y - beta * z) * dt;
        
        x += dx;
        y += dy;
        z += dz;

        trail.push_back({x, y, z});

        if (trail.size() > 2000) trail.pop_front();
        
        BeginDrawing();

        ClearBackground(BLACK);

        BeginMode3D(camera);
        center = {0.0f, 0.0f, 0.0f};

        for (int i = 0; i < trail.size(); i++) {
            center.x += trail[i].x;
            center.y += trail[i].y;
            center.z += trail[i].z;
            float t = (float)i / trail.size();
            Color c = {(unsigned char)(255 * t), 0, (unsigned char)(255 * (1 - t)), 255};
            DrawSphere(trail[i], 0.2f, c);
        }

        center.x /= (float)trail.size();
        center.y /= (float)trail.size();
        center.z /= (float)trail.size();

        EndMode3D();
        EndDrawing();

        camera.position.x = radius * cos(GetTime() * speed) + center.x;
        camera.position.z = radius * sin(GetTime() * speed) + center.z;;
        camera.position.y = center.y;

        camera.target = center;
    }


    CloseWindow();
    return 0;
}
