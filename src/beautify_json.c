#include "beautify_json.h"
#include <stdio.h>

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
