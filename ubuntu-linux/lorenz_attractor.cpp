#include <stdio.h>
#include <cmath>
#include <vector>
#include "include/raylib.h"

#define sigma       10.0f
#define rho         28.0f
#define beta        8.0f/3.0f
#define dt          0.01f
#define STEP(x)     euler(x);
#define STATECOUNT  100000

inline void sum(Vector3 &s, Vector3 &a, float fa){
    s.x += a.x*fa;
    s.y += a.y*fa;
    s.z += a.z*fa;
}

inline void la(Vector3 &state, Vector3 &inc){
    inc.x = sigma * (state.y - state.x) * dt;
    inc.y = (state.x * (rho - state.z) - state.y) * dt;
    inc.z = (state.x * state.y - beta * state.z) * dt;
}

void euler(Vector3 &vec){

    Vector3 k;
    la(vec, k);
    sum(vec, k, 1.f);

}

void rk(Vector3 &vec){
    
    Vector3 k, in = {vec.x, vec.y, vec.z}, pk = {in.x, in.y, in.z}, res = {0.f, 0.f, 0.f};

    la(pk, k); // k1 = D(yn)
    sum(res, k, 1.f/6.f); // res += k1*h

    // yn + k1/2
    pk.x = in.x + (k.x/2.f);
    pk.y = in.y + (k.y/2.f);
    pk.z = in.z + (k.z/2.f);

    la(pk, k); // k2 = D(yn + k1/2)
    sum(res, k, 1.f/3.f); // res += k2*2h

    // yn + k2/2
    pk.x = in.x + (k.x/2.f);
    pk.y = in.y + (k.y/2.f);
    pk.z = in.z + (k.z/2.f);

    la(pk, k); // k3 = D(yn + k2/2)
    sum(res, k, 1.f/3.f); // res += k3*2h

    // yn + k3
    pk.x = in.x + k.x;
    pk.y = in.y + k.y;
    pk.z = in.z + k.z;

    la(pk, k); // k4 = D(yn + k3)
    sum(res, k, 1.f/6.f); // res += k4*h

    sum(vec, res, 1.f); // res = res/6, adding res

}

int main() {

    InitWindow(800, 600, "3D Lorenz Attractor");
    SetTargetFPS(60);
    
    Vector3 state = {0.1f, 0.f, 0.f};
    Vector3 inc;

    Camera camera = {0};
    camera.position = (Vector3){0.0f, 40.0f, 80.0f};
    camera.up       = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy     = 45.0f;

    float radius = 90.0f;
    float height = 30.0f;
    float speed  = 0.2f;

    Vector3 center = {0.0f, 0.0f, 0.0f};
    camera.target = center;

    Vector3 trail[STATECOUNT];
    size_t size = 1;

    trail[0].x = state.x;
    trail[0].y = state.y;
    trail[0].z = state.z;
    
    while (!WindowShouldClose()) {
        
        if(size < STATECOUNT){

            STEP(state)

            trail[size].x = state.x;
            trail[size].y = state.y;
            trail[size].z = state.z;

            size++;

        }
        
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        center = {0.0f, 0.0f, 0.0f};

        for (int i = 0; i < size; i++) {
            
            center.x += trail[i].x;
            center.y += trail[i].y;
            center.z += trail[i].z;
            float t = (float)i / size;
            Color c = {(unsigned char)(255 * t), 0, (unsigned char)(255 * (1 - t)), 255};
            DrawSphere(trail[i], 0.2f, c);
        }

        center.x /= (float)size;
        center.y /= (float)size;
        center.z /= (float)size;

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
