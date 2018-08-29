#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSG_USAGE "Usage: %s num1 num2 ... numN\n"
#define MSG_MEMORY "Not enough memory.\n"
#define HEIGHT 18
#define BLOCK "\u2588"
#define NONBLOCK " "
#define MAX_STR_LEN 32

char* str_lpad(const char* string, char pad, int length) {
    char* buffer = NULL;
    buffer = malloc(length + 1);

    if (buffer != NULL) {
        memset(buffer, pad, length);
        strcpy((buffer + length - strlen(string)),
            string);
    }

    return buffer;
}

int main(int argc, char* argv[])
{

    if (argc == 1) {
        printf(MSG_USAGE, argv[0]);
        return EXIT_FAILURE;
    }

    int n = argc - 1;
    double *nums = NULL;
    bool axes = true;

    // allocate space for and copy the numbers into memory
    nums = malloc(n * sizeof(double));

    if (nums == NULL) {
        printf(MSG_MEMORY);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i++) {
        *(nums + i - 1) = atof(argv[i]);
    }

    // find the minimum and maximum numbers
    double min = 0.0f,
           max = 0.0f;

    for (int i = 0; i < n; i++) {
        if (i == 0 || nums[i] > max) {
            max = nums[i];
        }
        if (i == 0 || nums[i] < min) {
            min = nums[i];
        }
    }

    // calculate the numbers to put on the y axis
    char* minString = NULL;
    char* maxString = NULL;

    minString = malloc(MAX_STR_LEN);
    maxString = malloc(MAX_STR_LEN);

    if (minString == NULL || maxString == NULL) {
        printf(MSG_MEMORY);
        return EXIT_FAILURE;
    }

    // get the length of the longest string to be printed
    // on the y axis
    int minStringLen = snprintf(minString, MAX_STR_LEN, "%.2f", min);
    int maxStringLen = snprintf(maxString, MAX_STR_LEN, "%.2f", max);

    int yAxisStringLength = maxStringLen;
    if (minStringLen > yAxisStringLength) {
        yAxisStringLength = minStringLen;
    }

    // the height of each unit step on the y axis
    double scale = (max - min) / HEIGHT;

    for (int y = 0; y <= HEIGHT; y++) {
        for (int x = 0; x <= n; x++) {
            if (x == 0 && axes) {

                // print the y axis
                if (y % 2 == 0) {

                    char* p_num = NULL;
                    p_num = malloc(MAX_STR_LEN);

                    if (p_num == NULL) {
                        printf(MSG_MEMORY);
                        return EXIT_FAILURE;
                    }

                    snprintf(p_num, MAX_STR_LEN, "%.2f", max - scale * y);
                    
                    char* p_str = NULL;
                    p_str = str_lpad(p_num, ' ', yAxisStringLength);
                    printf("%s \u2502", p_str);
                    free(p_num);
                    free(p_str);

                } else {

                    char* p_str = NULL;
                    p_str = str_lpad("", ' ', yAxisStringLength);
                    printf("%s \u2502", p_str);
                    free(p_str);

                }
            } else {
                // print the data
                printf(nums[x - 1] >= max - scale * y ? BLOCK : NONBLOCK);
            }
        }
        printf("\n");
    }

    // print the x axis
    
    char* p_str = NULL;
    p_str = str_lpad("", ' ', yAxisStringLength);
    printf("%s \u2515", p_str);
    free(p_str);

    for (int i = 0; i < n; i++) {
        printf("\u2501");
    }

    printf("\n");

    free(minString);
    free(maxString);
    free(nums);

    return EXIT_SUCCESS;
}
