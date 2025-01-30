#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "readaline.h"

// Helper function to create a temporary file
FILE *create_temp_file(const char *content) {
    FILE *temp = tmpfile();
    if (temp == NULL) {
        perror("Failed to create temporary file");
        exit(1);
    }
    fputs(content, temp);
    rewind(temp);
    return temp;
}

void test_readaline_normal_case() {
    FILE *file = create_temp_file("Hello, World!\nSecond Line\n");
    char *line = NULL;
    
    size_t length = readaline(file, &line);
    assert(length == 14); // "Hello, World!\n" (including newline)
    assert(strcmp(line, "Hello, World!\n") == 0);
    free(line);

    length = readaline(file, &line);
    assert(length == 13); // "Second Line\n"
    assert(strcmp(line, "Second Line\n") == 0);
    free(line);

    length = readaline(file, &line);
    assert(length == 0); // EOF reached
    assert(line == NULL);

    fclose(file);
}

void test_readaline_empty_file() {
    FILE *file = create_temp_file("");
    char *line = NULL;

    size_t length = readaline(file, &line);
    assert(length == 0);
    assert(line == NULL);

    fclose(file);
}

void test_readaline_long_line() {
    char long_line[1100];
    memset(long_line, 'A', 1000);
    long_line[1000] = '\n';
    long_line[1001] = '\0';

    FILE *file = create_temp_file(long_line);
    char *line = NULL;

    size_t length = readaline(file, &line);
    assert(length == 1001);
    assert(line[1000] == '\n');

    free(line);
    fclose(file);
}

void test_readaline_null_params() {
    FILE *file = create_temp_file("Test\n");

    assert(readaline(NULL, NULL) == 0); // Should exit or print an error
    assert(readaline(file, NULL) == 0); // Should exit or print an error

    fclose(file);
}

int main() {
    test_readaline_normal_case();
    test_readaline_empty_file();
    test_readaline_long_line();
    test_readaline_null_params();

    printf("All readaline tests passed!\n");
    return 0;
}
