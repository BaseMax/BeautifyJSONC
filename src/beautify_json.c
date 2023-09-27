/*
*
*    @Name: Beautify JSON C
*    @License: GPL-3.0
*    @Date:     27/09/2023
*    @Repository:   https://github.com/BaseMax/BeautifyJSONC
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INDENT_SIZE 4

void beautifyJson(FILE *inputFile, FILE *outputFile) {
    int indentLevel = 0;
    int insideString = 0;
    int c;
    int prevChar = -1;
    int prevNonSpaceChar = -1;

    while ((c = fgetc(inputFile)) != EOF) {
        if (c == '"' && prevChar != '\\') {
            insideString = !insideString;
        }

        if (!insideString) {
            if (c == '{' || c == '[') {
                if (prevChar != ',' && prevChar != '{' && prevChar != '[') {
                    if (prevNonSpaceChar != -1 && prevNonSpaceChar != '\n') {
                        fputc('\n', outputFile);
                    }
                    for (int j = 0; j < indentLevel * INDENT_SIZE; j++) {
                        fputc(' ', outputFile);
                    }
                }
                fputc(c, outputFile);
                fputc('\n', outputFile);
                indentLevel++;
                for (int j = 0; j < indentLevel * INDENT_SIZE; j++) {
                    fputc(' ', outputFile);
                }
            } else if (c == '}' || c == ']') {
                indentLevel--;
                if (prevChar != ',' && prevChar != '{' && prevChar != '[') {
                    if (prevNonSpaceChar != -1 && prevNonSpaceChar != '\n') {
                        fputc('\n', outputFile);
                    }
                    for (int j = 0; j < indentLevel * INDENT_SIZE; j++) {
                        fputc(' ', outputFile);
                    }
                }
                fputc(c, outputFile);
            } else if (c == ',') {
                fputc(c, outputFile);
                if (prevChar != '{' && prevChar != '[') {
                    if (prevNonSpaceChar != -1 && prevNonSpaceChar != '\n') {
                        fputc('\n', outputFile);
                    }
                    for (int j = 0; j < indentLevel * INDENT_SIZE; j++) {
                        fputc(' ', outputFile);
                    }
                }
            } else if (c != ' ') {
                fputc(c, outputFile);
            }
        } else {
            fputc(c, outputFile);
        }

        if (c != ' ') {
            prevNonSpaceChar = c;
        }
        prevChar = c;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s input_file output_file\n", argv[0]);
        return 1;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen(argv[2], "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    beautifyJson(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}

