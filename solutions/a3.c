#include <stdio.h>
#include <math.h> // Für die "sqrt" Funktion

// Aufgabe 3 a)
/*
int main(void) {
    const double w = 0.0000004;
    const double l = 0.00000025;
    const double u_gs = 2.0;
    const double i_d = 0.00015;
    const double u_t = 0.4;
    const double k = 0.000128;

    const double epsilon = 1e-5;

    if (u_gs < u_t) {
        printf("Der Transistor ist im Sperrbereich\n");
    } else {
        const double beta = k * w / l;
        const double i_d_sat = (beta / 2.0) * (u_gs - u_t) * (u_gs - u_t); // Sah-Modellgleichung

        if (i_d - epsilon <= i_d_sat && i_d_sat <= i_d + epsilon) { // Nicht "i_d == i_d_sat"!
            printf("Der Transistor ist im Sättigungsbereich\n");
        } else {
            printf("Der Transistor ist im linearen Bereich\n");
        }
    }
}
*/

// Aufgabe 3 b)
/*
int main(void) {
    const double w = 0.0000004;
    const double l = 0.00000025;
    const double u_gs = 2.0;
    const double i_d = 0.00015;
    const double u_t = 0.4;
    const double k = 0.000128;

    const double epsilon = 1e-5;

    if (u_gs < u_t) {
        printf("Der Transistor ist im Sperrbereich\n");
        printf("u_ds >= 0\n");
    } else {
        const double beta = k * w / l;
        const double i_d_sat = (beta / 2.0) * (u_gs - u_t) * (u_gs - u_t);

        if (i_d - epsilon <= i_d_sat && i_d_sat <= i_d + epsilon) {
            printf("Der Transistor ist im Sättigungsbereich\n");
            printf("u_ds >= %lf\n", u_gs - u_t);
        } else {
            const double u_ds_lin = (-(2.0 * (u_t - u_gs)) - sqrt((2.0 * (u_t - u_gs)) * (2.0 * (u_t - u_gs)) - (4.0 * (2.0 * i_d / beta)))) / 2.0; // Sah-Modellgleichung

            printf("Der Transistor ist im linearen Bereich\n");
            printf("u_ds = %lf\n", u_ds_lin);
        }
    }
}
*/

// Aufgabe 3 c)
int main(void) {
    const double u_gs = 2.0;
    const double u_ds = 0.55;
    const double w = 0.0000004;
    const double l = 0.00000025;
    const double u_t = 0.4;
    const double k = 0.000128;

    const double beta = k * w / l;

    if (u_gs < u_t && 0.0 < u_ds) {
        printf("Der Transistor ist im Sperrbereich\n");
        printf("i_d = 0\n");
    } else if (u_gs > u_t && 0.0 < u_ds && u_ds < u_gs - u_t) {
        const double i_d = beta * (u_gs - u_t - (u_ds / 2.0)) * u_ds;

        printf("Der Transistor ist im linearen Bereich\n");
        printf("i_d = %lf\n", i_d);
    } else if (u_gs > u_t && u_ds > u_gs - u_t) {
        const double i_d = (beta / 2.0) * (u_gs - u_t) * (u_gs - u_t);

        printf("Der Transistor ist im Sättigungsbereich\n");
        printf("i_d = %lf\n", i_d);
    } else {
        printf("Der Transistor bricht die Gesetze der Physik\n");
        printf("i_d = ???\n");
    }
}

