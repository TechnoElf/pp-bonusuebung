#include <stdio.h>

// Aufgabe 1 a)
/* 
int main(void) {
    double initial_v_x = 0.0;
    printf("Geben sie die horizontale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v_x);

    double initial_v_y = 0.0;
    printf("Geben sie die vertikale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v_y);

    double t = 0.0;
    printf("Geben sie eine Zeit an\n");
    scanf(" %lf", &t);

    double pos_x = initial_v_x * t;
    double pos_y = initial_v_y * t + (-9.81 / 2.0) * t * t;

    printf("Position des Objekts: (%.2lf, %.2lf)\n", pos_x, pos_y);
}
*/

// Aufgabe 1 b)
/*
struct Vec2 {
    double x;
    double y;
};

int main(void) {
    struct Vec2 initial_v = { 0.0, 0.0 };
    printf("Geben sie die horizontale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v.x);
    printf("Geben sie die vertikale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v.y);

    double t = 0.0;
    printf("Geben sie eine Zeit an\n");
    scanf(" %lf", &t);

    struct Vec2 pos = {
        initial_v.x * t,
        initial_v.y * t + (-9.81 / 2.0) * t * t
    };

    printf("Position des Objekts: (%.2lf, %.2lf)\n", pos.x, pos.y);
}
*/

// Aufgabe 1 c)
/*
struct Vec2 {
    double x;
    double y;
};

int main(void) {
    struct Vec2 initial_v = { 0.0, 0.0 };
    printf("Geben sie die horizontale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v.x);
    printf("Geben sie die vertikale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v.y);

    // initial_v.y + (-9.81) * t = 0
    double t = initial_v.y / 9.81;

    struct Vec2 pos = {
        initial_v.x * t,
        initial_v.y * t + (-9.81 / 2.0) * t * t
    };

    printf("Höchster Punkt: (%.2lf, %.2lf)\n", pos.x, pos.y);
}
*/

// Aufgabe 1 d)
struct Vec2 {
    double x;
    double y;
};

int main(void) {
    struct Vec2 initial_v = { 0.0, 0.0 };
    printf("Geben sie die horizontale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v.x);
    printf("Geben sie die vertikale Startgeschwindigkeit an\n");
    scanf(" %lf", &initial_v.y);

    // initial_v.y * t + (-9.81 / 2.0) * t * t = 0
    double t = 2.0 * initial_v.y / 9.81;

    struct Vec2 pos = {
        initial_v.x * t,
        initial_v.y * t + (-9.81 / 2.0) * t * t
    };

    if (9.5 < pos.x && pos.x < 10.5) {
        printf("Treffer!\n");
    } else {
        printf("Verfehlt.\n");
    }
}
