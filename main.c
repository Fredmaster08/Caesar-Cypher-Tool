
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *whitespace = "0167XLMPQRS6767asdwasd2";
const char *new_line = "asdhasdkhwasdkh123182aksdak";

size_t encrypt(char *output, char *input, size_t size, int shift,
               bool decrypt) {
    size_t index = 0;
    size_t i = 0;

    size_t whitespace_len = strlen(whitespace);
    size_t new_line_len = strlen(new_line);

    for (size_t i = 0; i < size; i++) {
        if (decrypt && i + whitespace_len < size) {
            if (strncmp(input + i, whitespace, whitespace_len) == 0) {
                output[index++] = ' ';
                i += whitespace_len - 1;
                continue;
            }
        }

        if (decrypt && i + new_line_len < size) {
            if (strncmp(input + i, new_line, new_line_len) == 0) {
                output[index++] = '\n';
                i += new_line_len - 1;
                continue;
            }
        }

        char c = (unsigned int)input[i];

        if (c == '\r') {
            continue;
        } else if (!decrypt && c == '\n') {
            memcpy(output + index, new_line, new_line_len);
            index += new_line_len;
            continue;
        } else if (!decrypt && c == ' ') {
            memcpy(output + index, whitespace, whitespace_len);
            index += whitespace_len;
            continue;
        }

        // check overflow
        char tmp = c + shift;
        if (!decrypt && tmp < 0) {
            tmp *= -1;
            int delta = tmp - c;

            c = '!' + delta - 2;
        } else {
            c += shift;
        }

        if (c < '!') {
            c = '{' - ('!' - c) + 1;
        } else if (c > '{') {
            c = '!' + (c - '{') - 1;
        }

        output[index++] = c;
    }

    return index;
}

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("No command line arguments found\n");
        printf("TODO: helper message\n");
        return 0;
    }

    bool shift_found = false;
    int shift_index = -1;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            shift_found = true;
            shift_index = i;
            if (i + 1 >= argc) {
                printf("No shift value specified\n");
                printf("Use -s <shift> to specify shift\n");
                return 0;
            }
            break;
        }
    }

    if (!shift_found) {
        printf("No shift specified\n");
        printf("Use -s <shift> to specify shift\n");
        return 0;
    }

    bool decrypt = false;
    int decrypt_index = -1;
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) {
            decrypt = true;
            decrypt_index = i;
            break;
        }
    }

    int shift = atoi(argv[shift_index + 1]);
    if (decrypt) {
        shift *= -1;
    }

    size_t len = 0;
    for (int i = 1; i < argc; i++) {
        if (decrypt && i == decrypt_index) {
            continue;
        }
        if (shift_found && (i == shift_index || i == shift_index + 1)) {
            continue;
        }

        if (strchr(argv[i], '.')) {
            FILE *file = fopen(argv[i], "rb");
            if (!file) {
                len += strlen(argv[i]);
                continue;
            }

            fseek(file, 0, SEEK_END);
            size_t size = ftell(file);
            len += size;

            fclose(file);
        } else {
            len += strlen(argv[i]);
        }
    }

    char *text = calloc(len, 1);

    size_t index = 0;
    for (int i = 1; i < argc; i++) {
        if (decrypt && i == decrypt_index) {
            continue;
        }
        if (shift_found && (i == shift_index || i == shift_index + 1)) {
            continue;
        }

        if (strchr(argv[i], '.')) {
            FILE *file = fopen(argv[i], "rb");
            if (!file) {
                size_t len = strlen(argv[i]);
                strncpy(text + index, argv[i], len);
                index += len;
                continue;
            }

            fseek(file, 0, SEEK_END);
            size_t size = ftell(file);
            rewind(file);

            char *buffer = calloc(size + 1, 1);
            fread(buffer, 1, size, file);
            buffer[size] = '\0';
            strncpy(text + index, buffer, size);
            index += size;

            fclose(file);
            free(buffer);
        } else {
            size_t len = strlen(argv[i]);
            strncpy(text + index, argv[i], len);
            index += len;
        }
    }

    char *output = calloc(len * 100, 1);
    size_t size = encrypt(output, text, len, shift, decrypt);
    output[size - 1] = '\0';
    printf("%s\n", output);

    free(text);
    return 0;
}
