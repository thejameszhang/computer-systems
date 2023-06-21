/*
* Name: James Zhang
* UID: 118843940
* Course: CMSC216 by Professor Yoon
* Section: 0301
*/

#include "text_manipulation.h"
#include <stdio.h>
#include <string.h>

/*
This function places in the result char array a copy of the source string:
right aligned and all trailing spaces removed.
Args:
    - a constant pointer to the `source` string (address of first char in string)
    - a pointer to a `result` string
    - `length` of the `result` string, including the NULL byte
Returns:
    - SUCCESS 0
    - FAILURE -1
*/
int right_align(const char *src, char *res, int length) {
    
    if (src && res) {

        char src_cpy[MAX_STR_LEN + 1];
        const char *src_ptr = src;
        char *start = src_cpy;
        int src_length = strlen(src), i = 0, cutoff;

        if (src_length > 0 && length > 0) {

            while (i < src_length) {

                /* if not whitespace then add to src_cpy */
                if (*src != ' ') {
                    src++;

                    /* set these non-whitespace chars to the cpy */
                    while (src_ptr < src) {
                        *start++ = *src_ptr++;
                    }
                } 

                /* if white space char, just skip it*/
                else {
                    src++;
                }
                i++;
                }
            }

            *start = '\0';
            cutoff = length - strlen(src_cpy);
            
            if (cutoff > 0) {
                /* set everything before the cutoff to whitespace */
                for (i = 0; i < cutoff - 1; i++) {
                    res[i] = ' ';
                }

                strcat(res, src_cpy);
                return SUCCESS;
            }
        }  
    return FAILURE;
}

/*
This function will compact the `str` by removing all spaces in the string.
After the function, the string should only contain non-whitespace chars
from the original string followed by the NULL byte. If the second parameter
is not null, `out` will be set the number of words in the string parameter.
Args:
    - a pointer to `str` a char array
    - a pointer variable to an integer
Returns:
    - SUCCESS 0
    - FAILURE 1
*/


int compact(char *str, int *out) {

    /* first failure */
    if (str != NULL && out != NULL) {

        char *r = str;
        char temp;
        int result = 0, length, i;
        length = strlen(str);
        
        if (length != 0) {
            
            /* 
            calculating the number of words 
            - this is equal to the number of spaces with chars after it
            */
            i = 0;
            while (str[i] != '\0' && str[i + 1] != '\0') {
                if (str[i] == ' ' && str[i + 1] != ' ') {
                    result++;
                }
                i++;
            }

            if (str[0] != ' ') {
                result++;
            }
            *out = result;

            /* "removing" white spaces */
            i = 0;
            while (*r != '\0') {

                if (*r != ' ' && *r != '\0') { 
                    temp = *r; 
                    *r = ' '; 
                    str[i] = temp;
                    i++;
                }
                r++;
            }

            i = 0;
            while (str[i] != ' ' && str[i] != '\0') {
                i++;
            }
            if (str[i] == ' ') {
                str[i] = '\0';
            }
            return SUCCESS;
        }
    }
    return FAILURE;
}



