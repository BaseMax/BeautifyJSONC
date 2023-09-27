/*
 * @Name: Beautify JSON C
 * @License: GPL-3.0
 * @Date: 27/09/2023
 * @Repository: https://github.com/BaseMax/BeautifyJSONC
 */

#include <stdio.h>
#include <stdlib.h>
#include "beautify_json.h"

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
