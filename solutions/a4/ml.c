#include <stdio.h>
#include <stdlib.h>

#define IMAGE_SIZE 4
#define VEC_LEN IMAGE_SIZE * IMAGE_SIZE

float* load_file(const char* name, unsigned int m, unsigned int n) {
    FILE* f = fopen(name, "rb");
    if (f == NULL) {
        fprintf(stderr, "Failed to open file \"%s\"\n", name);
        return NULL;
    }

    struct bmp_header {
        unsigned short magic;
        unsigned int file_len;
        unsigned int reserved;
        unsigned int pixel_offset;
    } __attribute__((packed)) bmp_header = { 0 };
    fread(&bmp_header, sizeof(bmp_header), 1, f);
    if (bmp_header.magic != 0x4d42) {
        fclose(f);
        fprintf(stderr, "File \"%s\" has wrong format\n", name);
        return NULL;
    }

    struct bmp_core_header {
        unsigned int header_len;
        unsigned short width;
        unsigned short height;
        unsigned short color_planes_count;
        unsigned short bits_per_pixel;
    } __attribute__((packed)) bmp_core_header = { 0 };
    fread(&bmp_core_header, sizeof(bmp_core_header), 1, f);
    if (bmp_core_header.color_planes_count != 1 || bmp_core_header.bits_per_pixel != 8 || bmp_core_header.width != n || bmp_core_header.height != m) {
        fclose(f);
        fprintf(stderr, "File \"%s\" has wrong format\n", name);
        return NULL;
    }

    fseek(f, bmp_header.pixel_offset, SEEK_SET);

    float* pixel_array = malloc(n * m * sizeof(float));
    if (pixel_array == NULL) {
        fclose(f);
        fprintf(stderr, "Failed to allocate buffer while loading file \"%s\"\n", name);
        return NULL;
    }

    for(int y = m - 1; y >= 0; y--) {
        for(int x = 0; x < m; x++) {
            unsigned char pixel = (unsigned char) fgetc(f);
            pixel_array[y * n + x] = (float) pixel / 255.0;
        }

        for (int i = m; i < 4; i++) {
            fgetc(f);
        }
    }

    fclose(f);
    return pixel_array;
}

void print_mat(float* mat, unsigned int m, unsigned int n) {
    for(int y = 0; y < m; y++) {
        for(int x = 0; x < n; x++) {
            printf("%3.1f ", mat[y * n + x]);
        }
        printf("\n");
    }
}

float* make_i_mat(unsigned int n) {
    float* mat = malloc(n * n * sizeof(float));
    if (mat == NULL) {
        fprintf(stderr, "Failed to allocate buffer for identity matrix\n");
        return NULL;
    }

    for(int y = 0; y < n; y++) {
        for(int x = 0; x < n; x++) {
            mat[y * n + x] = y == x ? 1.0 : 0.0;
        }
    }

    return mat;
}

float* tp_mat(float* mat, unsigned int m, unsigned int n) {
    float* mat_t = malloc(n * m * sizeof(float));
    if (mat_t == NULL) {
        fprintf(stderr, "Failed to allocate buffer for transposed matrix\n");
        return NULL;
    }

    for(int y = 0; y < m; y++) {
        for(int x = 0; x < n; x++) {
            mat_t[x * m + y] = mat[y * n + x];
        }
    }

    return mat_t;
}

float* inv_mat(float* mat, unsigned int n) {
    float* mat_i = make_i_mat(n);
    if (mat_i == NULL) {
        return NULL;
    }

    for (int y = 0; y < n - 1; y++) {
        float factor = mat[y * n + y];
        for (int x = 0; x < n; x++) {
            mat[y * n + x] /= factor;
            mat_i[y * n + x] /= factor;
        }

        for (int i = y + 1; i < n; i++) {
            factor = mat[i * n + y] / mat[y * n + y];
            for (int x = 0; x < n; x++) {
                mat[i * n + x] -= factor * mat[y * n + x];
                mat_i[i * n + x] -= factor * mat_i[y * n + x];
            }
        }

        for (int i = y + 1; i < n; i++) {
            if (mat[i * n + i] == 0.0) {
                int j = i + 1;
                for (;;) {
                    if (mat[j * n + j] != 0.0) {
                        break;
                    }

                    if (j == n) {
                        free(mat_i);
                        fprintf(stderr, "Failed to invert matrix\n");
                        return NULL;
                    }

                    j++;
                }

                for (int x = 0; x < n; x++) {
                    *(unsigned int*)&mat[i * n + x] ^= *(unsigned int*)&mat[j * n + x];
                    *(unsigned int*)&mat[j * n + x] ^= *(unsigned int*)&mat[i * n + x];
                    *(unsigned int*)&mat[i * n + x] ^= *(unsigned int*)&mat[j * n + x];
                    *(unsigned int*)&mat_i[i * n + x] ^= *(unsigned int*)&mat_i[j * n + x];
                    *(unsigned int*)&mat_i[j * n + x] ^= *(unsigned int*)&mat_i[i * n + x];
                    *(unsigned int*)&mat_i[i * n + x] ^= *(unsigned int*)&mat_i[j * n + x];
                }
            }
        }
    }

    float factor = mat[(n - 1) * n + (n - 1)];
    for (int x = 0; x < n; x++) {
        mat[(n - 1) * n + x] /= factor;
        mat_i[(n - 1) * n + x] /= factor;
    }

    for (int y = n - 1; y > 0; y--) {
        for (int i = 0; i < y; i++) {
            factor = mat[i * n + y] / mat[y * n + y];
            for (int x = 0; x < n; x++) {
                mat[i * n + x] -= factor * mat[y * n + x];
                mat_i[i * n + x] -= factor * mat_i[y * n + x];
            }
        }
    }

    return mat_i;
}

float* mul_mat(float* mat1, unsigned int m1, unsigned int n1, float* mat2, unsigned int m2, unsigned int n2) {
    if (n1 != m2) {
        fprintf(stderr, "Failed to multiply matrices\n");
        return NULL;
    }

    float* mat = malloc(m1 * n2 * sizeof(float));
    if (mat == NULL) {
        fprintf(stderr, "Failed to allocate buffer for identity matrix\n");
        return NULL;
    }

    for (int y = 0; y < m1; y++) {
        for (int x = 0; x < n2; x++) {
            mat[y * n2 + x] = 0.0;
            for (int i = 0; i < n1; i++) {
                mat[y * n2 + x] += mat1[y * n1 + i] * mat2[i * n2 + x];
            }
        }
    }

    return mat;
}

int get_training_input(float** in, float** out) {
    int t_count = 0;
    for (;;) {
        char name[16] = { 0 };
        snprintf(name, 16, "t%i_0.bmp", t_count);
        FILE* f = fopen(name, "rb");
        if (f == NULL) {
            char name[16] = { 0 };
            snprintf(name, 16, "t%i_1.bmp", t_count);
            FILE* f = fopen(name, "rb");
            if (f == NULL) {
                break;
            } else {
                fclose(f);
                t_count++;
            }
        } else {
            fclose(f);
            t_count++;
        }
    }

    *out = malloc(t_count * sizeof(float));

    for (int i = 0; i < t_count; i++) {
        char name[16] = { 0 };
        snprintf(name, 16, "t%i_0.bmp", i);
        FILE* f = fopen(name, "rb");
        if (f != NULL) {
            fclose(f);
            (*out)[i] = 0.0;
        } else {
            (*out)[i] = 1.0;
        }
    }

    *in = malloc(VEC_LEN * t_count * sizeof(float));

    for (int i = 0; i < t_count; i++) {
        char name[16] = { 0 };
        snprintf(name, 16, "t%i_%i.bmp", i, (unsigned int) (*out)[i]);
        float* input = load_file(name, IMAGE_SIZE, IMAGE_SIZE);
        for (int j = 0; j < VEC_LEN; j++) {
            (*in)[i * VEC_LEN + j] = input[j];
        }
        free(input);
    }

    return t_count;
}

int main(void) { 
    float* input;
    float* output;
    int t_count = get_training_input(&input, &output);

    float* input_t = tp_mat(input, t_count, VEC_LEN);
    float* input_t_times_input = mul_mat(input_t, VEC_LEN, t_count, input, t_count, VEC_LEN);
    float* input_inv = inv_mat(input_t_times_input, VEC_LEN);
    if (input_inv == NULL) {
        return 1;
    }
    float* input_inv_times_input_t = mul_mat(input_inv, VEC_LEN, VEC_LEN, input_t, VEC_LEN, t_count);
    float* parameters = mul_mat(input_inv_times_input_t, VEC_LEN, t_count, output, t_count, 1);
    float* parameters_t = tp_mat(parameters, VEC_LEN, 1);

    free(input);
    free(output);
    free(input_t);
    free(input_t_times_input);
    free(input_inv);
    free(input_inv_times_input_t);
    free(parameters);

    for (int i = 0; i < 4; i++) {
        char name[16] = { 0 };
        snprintf(name, 16, "i%i.bmp", i);
        float* in = load_file(name, IMAGE_SIZE, IMAGE_SIZE);
        float* out = mul_mat(parameters_t, 1, VEC_LEN, in, VEC_LEN, 1);
        printf("Image %i: %f\n", i, out[0]);
        free(in);
        free(out);
    }
    
    free(parameters_t);

    return 0;
}

