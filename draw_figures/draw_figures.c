/*
* Name: James Zhang
* UID: 118843940
* Course: CMSC216 by Professor Yoon
* Section: 0301
*/

#include <stdio.h>
/*
* Determines if a given character is valid
* Args:
    - char character
* Returns: 
    - 1 if valid, 0 if invalid
*/
int valid_character(char character) {
    return (character == '*' || character == '%' || character == '#');
}

/*
* Draws a rectangle of appropriate character and shape
* Args:
    - char character
    - int width of the rectangle
    - int length of the rectangle
* Returns: 
    - 1 if valid, 0 if invalid
*/
int draw_rectangle(char character, int width, int length) {
    int i, j, result;

    /* successful */
    if (valid_character(character) == 1 && width > 0 && length > 0) {
        for (i = 0; i < width; i++) {
            for (j = 0; j < length; j++) {
                printf("%c", character);
            }
        printf("\n");
        result = 1;
        }
    } 
    
    /* unsuccessful */
    else {
        printf("Invalid data provided.\n");
        result = 0;
    }
    return result;
}

/*
* Draws a triangle of appropriate character and shape
* Args:
    - char character
    - int size (height)
* Returns: 
    - 1 if valid, 0 if invalid
*/
int draw_triangle(char character, int size) {
    int i, j, result, level = 1;
    int max = 2 * size - 1, space, num_space;
    
    /* successful */
    if (valid_character(character) == 1 && size > 0) {
        for (i = 0; i < size; i++) {

            /* printing whitespace*/
            space = (max - level)/2;
            for (num_space = 0; num_space < space; num_space++) {
                printf("%c", ' ');
            }
            
            /* printing the triangle*/
            for (j = 0; j < level; j++) {
                printf("%c", character);
            }

            printf("\n");
            level = level + 2;
        }
        result = 1;
    } 
    else {
        printf("Invalid data provided.\n");
        result = 0;
    }
    return result;
}

int main() {
    char option, character;
    int length, width, size;
    do {
        printf("Enter 1(rectangle), 2(triangle), 3(other), 0(quit): ");
        scanf(" %c", &option);

        /* rectangle */
        if (option == '1') {
            printf("Enter character, width and length: ");
            scanf(" %c%d%d", &character, &width, &length);
            draw_rectangle(character, width, length);
        } 
        
        /* triangle */
        else if (option == '2') {
            printf("Enter character and size: ");
            scanf(" %c%d", &character, &size);
            draw_triangle(character, size);
        }

        /* invalid choices (choosing not to implement option 3)*/
        else if (option != '0') {
            printf("Invalid choice.\n");
        }
    }
    while (option != '0');
    printf("Bye Bye.\n");
    return 0;
}
