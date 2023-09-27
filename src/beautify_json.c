/*
*    @Author:   MaximilianEdison (MaxianEdison)
*    @Date:     2023-09-27 09:45:31
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INDENT_SIZE 4

void beautify_json(FILE *input_file, FILE *output_file) {
    int indent_level = 0;
    int inside_string = 0;
    int c, prev_char = -1;

    while ((c = fgetc(input_file)) != EOF){
        if (c == '"' && prev_char == '\\') {
            inside_string = !inside_string;
        }
        if (!inside_string) {
            if (c == '{' || c == '[') {
                fputc(c, output_file);
                fputc('\n', output_file);
                indent_level++;
                for (int j = 0; j < indent_level * INDENT_SIZE; j++) {
                    fputc(' ', output_file);
                }
            } else if (c == '}' || c == ']') {
                fputc('\n', output_file);
                indent_level--;
                for (int j = 0; j < indent_level * INDENT_SIZE; j++) {
                    fputc(' ', output_file);
                }
                fputc(c, output_file);
            } else if (c == ',') {
                fputc(c, output_file);
                fputc('\n', output_file);
                for(int j = 0; j < indent_level * INDENT_SIZE; j++) {
                    fputc(' ', output_file);
                }
            } else {
                fputc(c, output_file);
            }
        } else {
            fputc(c, output_file);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input_file = fopen(argv[1], "r");
    if (input_file == NULL) {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    FILE *output_file = fopen(argv[2], "w");
    if (output_file == NULL) {
        perror("Error opening output file");
        fclose(input_file);
        return EXIT_FAILURE;
    }

    beautify_json(input_file, output_file);

    fclose(input_file);
    fclose(output_file);

    return EXIT_SUCCESS;
}
