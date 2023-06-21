/* 
* Name: James Zhang
* UID: 118843940
* Course: CMSC216 by Professor Yoon
* Section: 0301
*/

#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>
#include <ctype.h>
#include "document.h"

/*
This method does not call add_paragraph when any of these things occur:
    - paragraph_number does not represent a number, is a negative value, or
    is missing
    - additional info is proved after 
Args:
    - char res[]
    - char paragraph_number[]
*/
void add_paragraph_after_check(Document *doc, int res, char paragraph_number[]) {

    int num; 
    if (res == 2 && (atoi(paragraph_number) > 0 || strcmp(paragraph_number, "0") == 0)) {
        num = add_paragraph_after(doc, atoi(paragraph_number));
        if (num == FAILURE) {
            printf("add_paragraph_after failed\n");
        }
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call add_line_after in these conditions:
    - paragraph_nuumber does not represent a number, is a neg value or 0, 
    is missing
    - line_number does not represent a number, is negative, or is missing
    - * is missing
Args:
    - int res
    - char paragraph_number[]
    - char line_number
    - char asterisk
    - char line[]
*/
void add_line_after_check(Document *doc, int res, char paragraph_number[], char line_number[],
                                    char asterisk, char *line) {
    int num;
    if (res == 4 && atoi(paragraph_number) > 0 && 
        (atoi(line_number) > 0 || strcmp(line_number, "0") == 0) 
        && asterisk == '*' && line) {
        num = add_line_after(doc, atoi(paragraph_number), atoi(line_number), line);
        if (num == FAILURE) {
            printf("add_line_after failed\n");
        } 
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call print_document in these conditions:
    - data appears after print_document (res != 1)
Args:
    - int res
*/
void print_document_check(Document *doc, int res) {
    if (res == 1) {
        print_document(doc);
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call append_line in these conditions:
    - paragraph_number does not represent a number, is neg value or 0, 
    is missing, or * is missing
Args:
    - int res
    - char paragraph_number[]
    - char asterisk
    - char line[]
*/
void append_line_check(Document *doc, int res, char paragraph_number[], char asterisk, char *line) {
    int num;
    if (res == 3 && atoi(paragraph_number) > 0 && asterisk == '*') {
        num = append_line(doc, atoi(paragraph_number), line);
        if (num == FAILURE) {
            printf("append_line failed\n");
        }
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call remove_line in the following conditions:
    - paragraph_number does not represent a num, is neg or 0, is missing
    - line_number does not represent a num, is neg or 0, is missing
    - any data appears after the line number
Args:
    - int res
    - char paragraph_number[], char line_number[]
*/
void remove_line_check(Document *doc, int res, char paragraph_number[], char line_number[]) {
    int num;
    if (res == 3 && atoi(paragraph_number) > 0 && atoi(line_number) > 0) {
        num = remove_line(doc, atoi(paragraph_number), atoi(line_number));
        if (num == FAILURE) {
            printf("append_line failed\n");
        } 
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call load_file in the following conditions:
    - FILENAME is missing
    - any data appears after FILENAME   
Args:
    - int res
    - char filename[]
*/
void load_file_check(Document *doc, int res, char filename[]) {
    int num;
    if (res == 2) {
        num = load_file(doc, filename);
        if (num == FAILURE) {
            printf("load_file failed\n");
        } 
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call replace_text in the following conditions:
    - both \"TARGET\" and \"REPLACEMENT\" are missing
    - only \"TARGET\" is provided
Args:
    - int res
    - char target[]
    - char replacement[]
*/
void replace_text_check(Document *doc, char line[]) {
    int num, count = 0, length = strlen(line), i; 

    char *start_first, *end_first, *start_second, *end_second;
    for (i = 0; i < length; i++) {
        if (line[i] == '"') {
            count++;
        }
    }

    if (count >= 4) {
        start_first = strchr(line, '"') + 1;
        end_first = strchr(start_first, '"');
        *end_first = '\0';
        start_second = strchr(end_first + 1, '"') + 1;
        end_second = strchr(start_second, '"');
        *end_second = '\0';

        num = replace_text(doc, start_first, start_second);
        if (num == FAILURE) {
            printf("replace_text failed\n");
        }
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call highlight_text in the following conditions:
    - if TARGET is missing
Args:
    - int res
    - char target[]
*/
void highlight_text_check(Document *doc, char line[]) {
    
    char *start, *end;
    int i, count = 0, length = strlen(line);
    for (i = 0; i < length; i++) {
        if (line[i] == '"') {
            count++;
        }
    }

    if (count >= 2) {
        start = strchr(line, '"') + 1;
        end = strchr(start, '"');
        *end = '\0';
        highlight_text(doc, start);
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call remove_text in the following conditions:
    - if TARGET is missing
Args:
    - int res
    - char target[]
*/
void remove_text_check(Document *doc, char line[]) {
    
    int i, count = 0, length = strlen(line);
    char *start, *end;
    for (i = 0; i < length; i++) {
        if (line[i] == '"') {
            count++;
        }
    }

    if (count >= 2) {
        start = strchr(line, '"') + 1;
        end = strchr(start, '"');
        *end = '\0';
        remove_text(doc, start);
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call save_document in the following conditions:
    - if FILENAME is missing
    - any data appears after FILENAME
Args:
    - int res
    - char filename[]
*/
void save_document_check(Document *doc, int res, char filename[]) {
    int num;
    if (res == 2) {
        num = save_document(doc, filename);
        if (num == FAILURE) {
            printf("save_document failed\n");
        }
    } else {
        printf("Invalid Command\n");
    }
}

/*
This method does not call reset_document in the following conditions
    - data appears after reset_document
Args:
    - int res
*/
void reset_document_check(Document *doc, int res) {
    if (res == 1) {
        reset_document(doc);
    } else {
        printf("Invalid Command\n");
    }
}

/*
This helper method returns SUCCESS if there exist non-whitespace chars
in the line.
Args:
    - char line[]
Returns:
    - int SUCCESS or FAILURE;
*/
int check_spaces(char line[]) {
    int length = strlen(line), i;
    for (i = 0; i < length; i++) {
        if (isspace(line[i]) == 0) {
            return SUCCESS;
        }
    }
    return FAILURE;
}

int make_decision(Document *doc, char *line) {

    /* represent the parameters scanned */
    char one[MAX_STR_SIZE];
    char two[MAX_STR_SIZE];
    char three[MAX_STR_SIZE];
    char four[MAX_STR_SIZE];
    char asterisk, *ptr;
    int res;

    /* decisions will be made depending on number of correctly assigned vars */
    res = sscanf(line, " %s %s %s %s", one, two, three, four);

    /* if not a blank line */
    if (check_spaces(line) == SUCCESS) {

        /* continue if it is not a comment */
        if (one[0] != '#') {
            
            /* now determine which checker method to call by the first param*/
            if (strcmp(one, "add_paragraph_after") == 0) {
                add_paragraph_after_check(doc, res, two);
            } 
            
            /* be careful this has an asterisk check */
            else if (strcmp(one, "add_line_after") == 0) {
                res = sscanf(line, " %s %s %s %c", one, two, three, &asterisk);
                ptr = strstr(line, "*") + 1;
                add_line_after_check(doc, res, two, three, asterisk, ptr);
            }

            else if (strcmp(one, "print_document") == 0) {
                print_document_check(doc, res);
            }

            else if (strcmp(one, "quit") == 0 || strcmp(one, "exit") == 0) {
                if (res > 1) {
                    printf("Invalid Command\n");
                } 
                return 1;
            }

            /* be careful this has an asterisk check */
            else if (strcmp(one, "append_line") == 0) {
                res = sscanf(line, " %s %s %c", one, two, &asterisk);
                ptr = strstr(line, "*") + 1;
                append_line_check(doc, res, two, asterisk, ptr);
            }

            else if (strcmp(one, "remove_line") == 0) {
                remove_line_check(doc, res, two, three);
            }

            else if (strcmp(one, "load_file") == 0) {
                load_file_check(doc, res, two);
            }

            else if (strcmp(one, "replace_text") == 0) {
                replace_text_check(doc, line);
            }

            else if (strcmp(one, "highlight_text") == 0) {
                highlight_text_check(doc, line);
            }

            else if (strcmp(one, "remove_text") == 0) {
                remove_text_check(doc, line);
            }

            else if (strcmp(one, "save_document") == 0) {
                save_document_check(doc, res, two);
            }

            else if (strcmp(one, "reset_document") == 0) {
                reset_document_check(doc, res);
            }
        }
    }
    return 0;
}


/**/
int main(int argc, char *argv[]) {

    FILE *input;
    char line[MAX_STR_SIZE + 1];
    int num;
    
    /* initialize a single document with the name main_document */
    Document doc;
    const char *doc_name = "main_document";
    init_document(&doc, doc_name);

    /* if too many arguments in the command line */
    if (argc > 2) {
        fprintf(stderr, "Usage: user_interface\n");
        fprintf(stderr, "Usage: user_interface <filename>\n");
        exit(EX_USAGE);
    }

    /* if 1 or 2 arguments, we can continue */
    else if (argc == 2 || argc == 1) {

        if (argc == 2) {
            input = fopen(argv[1], "r");

            /* check if file was opened correctly */
            if (!input) {
                fprintf(stderr, "%s cannot be opened.\n", argv[1]);
                exit(EX_OSERR);
            }
        } else {
            input = stdin;
        }
        
        if (input) {
            
            /* read the file line by line */
            while (fgets(line, 1024, input) != NULL) {

                /* for each line need to make a decision */
                line[strcspn(line, "\n")] = 0;
                if (argc == 1) {
                    printf("> ");
                }
                num = make_decision(&doc, line);
                if (num == 1) {
                    fclose(input);
                    return SUCCESS;
                }
            }
            fclose(input);
        } 
    }
    return SUCCESS;
}