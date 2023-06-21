/* 
* Name: James Zhang
* UID: 118843940
* Course: CMSC216 by Professor Yoon
* Section: 0301
*/

#include <stdio.h>
#include <string.h>
#include "document.h"

/* 
1. This method initializes Document *doc to be empty with the specified
name and 0 paragraphs.
Args:
    - Document *doc
    - const char *name
Returns:
    - int SUCCESS or FAILURE
*/
int init_document(Document *doc, const char *name) {

    /* null check */
    if (doc && name && strlen(name) <= MAX_STR_SIZE) {

        /* initialize document to be empty */
        strcpy(doc->name, name);
        doc->number_of_paragraphs = 0; 
        return SUCCESS;
    }
    return FAILURE;
}

/*
2. This sets the number of paragraphs of the document to 0.
Args:
    - Document *doc
Returns:
    - int SUCCESS or FAILURE
*/
int reset_document(Document *doc) {
    
    /* null check */
    if (doc) {

        doc->number_of_paragraphs = 0;
        return SUCCESS;
    }
    return FAILURE;
}

/*
3. This method prints basic information about each document
as well as the contents of the document.
Args:
    - Document *doc
Returns:
    - int SUCCESS or FAILURE
*/
int print_document(Document *doc) {
    
    /* null check */
    if (doc) {

        /* print basic info */
        int i, j, lines;
        printf("Document name: \"%s\"\n", doc->name);
        printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);
        
        /* looping through each paragraph in doc */
        for (i = 0; i < doc->number_of_paragraphs; i++) {
            
            lines = doc->paragraphs[i].number_of_lines;
            if (lines > 0) {
                
                /* print each line of the current paragraph */
                for (j = 0; j < lines; j++) {

                    /* JUST CHANGED HERE; I DIDN'T PRINT EMPTY LINES BEFORE */
                    printf("%s\n", doc->paragraphs[i].lines[j]);
                }

                /* print the blank line between paragraphs if paragraph 
                last paragraph */
                if (i < doc->number_of_paragraphs-1) {
                    printf("\n");
                }
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/*
4. This method adds a paragraph after the specified paragraph number
which is one-indexed. If 0, the paragraph is added to the beginning of 
the doc. Due to this one indexing, given some paragraph_number n, we
would add a new paragraph at index n and push everything after it back 
by 1 index.
Args:
    - Document *doc
    - int paragraph_number
Returns:
    - int SUCCESS or FAILURE
*/
int add_paragraph_after(Document *doc, int paragraph_number) {

    /* null check */
    if (doc && doc->number_of_paragraphs < MAX_PARAGRAPHS
        && paragraph_number <= doc->number_of_paragraphs && paragraph_number >= 0) {
        
        int i;

        /* move each paragraph down by 1*/
        for (i = doc->number_of_paragraphs; i > paragraph_number; i--) {
            doc->paragraphs[i] = doc->paragraphs[i-1];
        }

        doc->paragraphs[paragraph_number].number_of_lines = 0;
        doc->number_of_paragraphs += 1;
        return SUCCESS;
    }
    return FAILURE;
}

/*
5. This method adds a new line after the specified line number, which is
one-indexed. If 0, line is added to the beginning of the paragraph.
Args:
    - Document *doc
    - int paragraph_number
    - int line_number
    - const char *new_line
Returns:
    - int SUCCESS or FAILURE
*/
int add_line_after(Document *doc, int paragraph_number, int line_number, 
                    const char *new_line) {

    /* null check */
    if (doc && paragraph_number < MAX_PARAGRAPHS && 
        doc->paragraphs[paragraph_number-1].number_of_lines <= MAX_PARAGRAPH_LINES
        && line_number <= doc->paragraphs[paragraph_number-1].number_of_lines
        && line_number >= 0) {

            /* due to one-indexing -> ex) 2nd paragraph is index 1*/
            int i, lines = doc->paragraphs[paragraph_number-1].number_of_lines;
            
            /* push back lines by 1 */
            for (i = lines; i > line_number; i--) {
                strcpy(doc->paragraphs[paragraph_number-1].lines[i], doc->paragraphs[paragraph_number-1].lines[i-1]);
            }

            /* set new line and increment num of lines */
            strcpy(doc->paragraphs[paragraph_number-1].lines[line_number], new_line);
            doc->paragraphs[paragraph_number-1].number_of_lines += 1;
            return SUCCESS;
    }
    return FAILURE;
}

/*
6. This method returns the number_of_lines out parameter of a paragraph
Args:
    - Document *doc
    - int paragraph_number
    - int *number_of_lines
Returns:
    - set the value of number_of_lines to the parameter
    - int SUCCESS or FAILURE
*/
int get_number_lines_paragraph(Document *doc, int paragraph_number, int *number_of_lines) {

    /* null check */ 
    if (doc && number_of_lines && paragraph_number < MAX_PARAGRAPHS) {

        *number_of_lines = doc->paragraphs[paragraph_number].number_of_lines;
        return SUCCESS;
    }
    return FAILURE;
}

/*
7. This method appends a line to the specified paragraph.
Args:
    - Document *doc
    - int paragraph_number
    - const char *new_line
*/
int append_line(Document *doc, int paragraph_number, const char *new_line) {

    /* null check */
    if (doc && paragraph_number <= MAX_PARAGRAPHS && 
        doc->paragraphs[paragraph_number-1].number_of_lines < MAX_PARAGRAPH_LINES
        && paragraph_number >= 0) {
        
        int num = doc->paragraphs[paragraph_number-1].number_of_lines;
        add_line_after(doc, paragraph_number, num, new_line);

        return SUCCESS;
    }
    return FAILURE;
}

/*
8. This removes the specified line number from the specified paragraph.
Args:
    - Document *doc
    - int paragraph_number
    - int line_number
Returns:
    - int SUCCESS or FAILURE
*/
int remove_line(Document *doc, int paragraph_number, int line_number) {

    /* null check */
    if (doc && paragraph_number <= MAX_PARAGRAPHS
        && line_number <= doc->paragraphs[paragraph_number-1].number_of_lines
        && paragraph_number >= 0 && line_number >= 0) {
        
        int i, num_lines = doc->paragraphs[paragraph_number-1].number_of_lines;

        /* move lines forward */
        for (i = line_number-1; i+1 < num_lines; i++) {
            strcpy(doc->paragraphs[paragraph_number-1].lines[i], doc->paragraphs[paragraph_number-1].lines[i+1]);
        }

        /* just added the decrementing number of lines line */
        strcpy(doc->paragraphs[paragraph_number-1].lines[num_lines-1], "");
        doc->paragraphs[paragraph_number-1].number_of_lines--;
        return SUCCESS;
    } 
    return FAILURE;
}

/*
9. This method adds the first data_lines number of lines of data to the document.
Empty string means a new paragraph.
Args:
    - Document *doc
    - char data[][MAX_STR_SIZE + 1]
    - int data_lines
Returns:
    - int SUCCESS or FAILURE
*/
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1], int data_lines) {

    /* null check */
    if (doc && data && data_lines > 0) {
        
        int i, paragraph = 1;
        add_paragraph_after(doc, doc->number_of_paragraphs);

        for (i = 0; i < data_lines; i++) {

            /* if "" then start a new paragraph*/
            if (strcmp(data[i], "") == 0) {
                add_paragraph_after(doc, paragraph++);
            }

            /* if not "" then add it to the current paragraph */
            if (strcmp(data[i], "") != 0) {
                append_line(doc, paragraph, data[i]);
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/*
10. This method replaces the text target with the test replacement everywhere
in the document.
*/
int replace_text(Document *doc, const char *target, const char *replacement) {

    /* null check */
    if (doc && target && replacement) {
        
        int i, j, length = strlen(target), lines;
        char *p, *instance, temp_char, new_str[MAX_STR_SIZE];

        for (i = 0; i < doc->number_of_paragraphs; i++) {
            lines = doc->paragraphs[i].number_of_lines;
            
            for (j = 0; j < lines; j++) {
                
                /* reset for the new line */
                p = doc->paragraphs[i].lines[j];
                strcpy(new_str, "");

                /* while there exists a needle in the haystack */
                while (strstr(p, target)) {

                    /* instance points to the first instance of target in the line*/
                    instance = strstr(p, target);

                    /* string manipulation so we can strcpy */
                    temp_char = instance[0];
                    instance[0] = '\0';
                    strcat(new_str, p);

                    /* after copying to newstr, change instance back */
                    instance[0] = temp_char;

                    /* add replacement to new str */
                    strcat(new_str, replacement);

                    /* first move instance down by length it's directly after target*/
                    instance += length;
                    p = instance;
                }

                /* once no more instances left, we need to finish copying the line */
                strcat(new_str, p);
                strcpy(doc->paragraphs[i].lines[j], new_str);
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/*
11. This method wraps the desired text in [ and ].
Args:
    - Document *doc
    - const char *target
Returns:
    - int SUCCESS or FAILURE
*/
int highlight_text(Document *doc, const char *target) {
    
    /* null check */
    if (doc && target) {
        char str[MAX_STR_SIZE + 1] = {'\0'};
        strcat(str, HIGHLIGHT_START_STR);
        strcat(str, target);
        strcat(str, HIGHLIGHT_END_STR);
        replace_text(doc, target, str);
        return SUCCESS;
    }
    return FAILURE;
}

/*
12. This method removes the desired text from anywhere in the document
Args:
    - Document *doc
    - const char *target
Returns:
    - int SUCCESS or FAILURE
*/
int remove_text(Document *doc, const char *target) {

    /* null check */
    if (doc && target) {
        replace_text(doc, target, "");
        return SUCCESS;
    }
    return FAILURE;
}