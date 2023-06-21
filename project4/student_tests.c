/* 
* Name: James Zhang
* UID: 118843940
* Course: CMSC216 by Professor Yoon
* Section: 0301
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "event.h"
#include "calendar.h"
#include "my_memory_checker_216.h"

/*****************************************************/
/* In this file you will provide tests for your      */
/* calendar application.  Each test should be named  */
/* test1(), test2(), etc. Each test must have a      */
/* brief description of what it is testing (this     */
/* description is important).                        */
/*                                                   */
/* You can tell whether any test failed if after     */
/* executing the students tests, you executed        */
/* "echo $?" on the command line and you get a value */
/* other than 0.  "echo $?" prints the status of     */
/* the last command executed by the shell.           */ 
/*                                                   */
/* Notice that main just calls test1(), test2(), etc.*/
/* and once one fails, the program eventually        */
/* return EXIT_FAILURE; otherwise EXIT_SUCCESS will  */
/* be returned.                                      */
/*****************************************************/

static int comp_minutes(const void *ptr1, const void *ptr2) {
   return ((Event *)ptr1)->duration_minutes - ((Event *)ptr2)->duration_minutes;
}

/* This tests checks that add event doesn't add an event with the same name twice */
static int test1() {
   int days = 7;
   Calendar *calendar;

   if (init_calendar("Test1", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (add_event(calendar, "late night picnic", 10, 100, NULL, 1) == SUCCESS) {
         if (add_event(calendar, "late night picnic", 34, 132, NULL, 1) == FAILURE) {
            if (print_calendar(calendar, stdout, 1) == SUCCESS) {
               return destroy_calendar(calendar);
            }
         }
      }
   }
   return FAILURE;
}

static int test2() {
   int days = 0;
   Calendar *calendar;
   /* this tests trying to use init_calendar and add_event with invalid parameters
      - invaldi start time
      - invalid duration
      - invalid number of days given the number of days in the calendar 
   */
   if (init_calendar("Test2", days, comp_minutes, NULL, &calendar) == FAILURE) {
      if (init_calendar("Test2", 7, comp_minutes, NULL, &calendar) == SUCCESS) {
         if (add_event(calendar, "Event 1", -234, 10, NULL, 1) == FAILURE) {
            if (add_event(calendar, "Event 1", 100, -10, NULL, 1) == FAILURE) {
               if (add_event(calendar, "Event 1", 100, 100, NULL, 10) == FAILURE) {
                  if (print_calendar(calendar, stdout, 1) == SUCCESS) {
                     return destroy_calendar(calendar);
                  }
               }
            }
         }
      }
   }
   return FAILURE;
}

static int test3() {
   /* this tests basic functionality for find_event and that the out parameter is returned properly */
   int days = 7;
   Calendar *calendar;
   Event *event;

   if (init_calendar("Test3", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (add_event(calendar, "Hawaii", 10, 100, NULL, 1) == SUCCESS) {
         if (find_event(calendar, "Hawaii", NULL) == SUCCESS) {
            if (find_event(calendar, "Japan", NULL) == FAILURE) {
               if (find_event(calendar, "Hawaii", &event) == SUCCESS && strcmp(event->name, "Hawaii") == 0) {
                  destroy_calendar(calendar);
                  return SUCCESS;
               }
            }
         }
      }
   }
   return FAILURE;
}

static int test4() {
   /* this tests basic functionality for find_event_in_day and that the out parameter is returned properly */
   int days = 7;
   Calendar *calendar;
   Event *event;

   if (init_calendar("Test4", days, comp_minutes, NULL, &calendar) == SUCCESS) {
      if (add_event(calendar, "Massachusetts", 10, 100, NULL, 3) == SUCCESS) {
         if (find_event(calendar, "Massachusetts", NULL) == SUCCESS) {
            if (find_event_in_day(calendar, "Massachusetts", 3, &event) == SUCCESS) {
               if (find_event_in_day(calendar, "Massachusetts", 4, &event) == FAILURE) {
                  if (strcmp(event->name, "Massachusetts") == 0) {
                     destroy_calendar(calendar);
                     return SUCCESS;
                  }
               }
            }
         }
      }
   }
   return FAILURE;
}

static int test5() {
   /* this tests basic functionality for remove_event such as removing the first element in the 
   linked list and checking that an event cannot be removed twice */
   int days = 7;
   Calendar *calendar;
   
   init_calendar("Test 5", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "Bowling", 10, 10, NULL, 3);
   add_event(calendar, "Ice Skating", 20, 20, NULL, 3);
   if (remove_event(calendar, "Donuts") == FAILURE) {
      if (remove_event(calendar, "Bowling") == SUCCESS) {
         if (remove_event(calendar, "Bowling") == FAILURE) {
            return destroy_calendar(calendar);
         }
      }
   }
   return FAILURE;
}

static int test6() {
   /* this tests basic functionality of get_event_info*/
   int days = 7;
   Calendar *calendar;
   char *info = (void *) "some information";
   init_calendar("Test 5", days, comp_minutes, NULL, &calendar);
   add_event(calendar, "Bowling", 10, 10, info, 3);
   if (find_event(calendar, "Bowling", NULL) == SUCCESS) {
      if (get_event_info(calendar, "Bowling") != NULL) {
         if (get_event_info(calendar, "Not in the calendar") == NULL) {;
            return SUCCESS;
         }
      }
   }
   return FAILURE;
}

int main() {
   int result = SUCCESS;

   /***** Starting memory checking *****/
   start_memory_check();
   /***** Starting memory checking *****/

   if (test1() == FAILURE) result = FAILURE;
   if (test2() == FAILURE) result = FAILURE;
   if (test3() == FAILURE) result = FAILURE;
   if (test4() == FAILURE) result = FAILURE;
   if (test5() == FAILURE) result = FAILURE;
   if (test6() == FAILURE) result = FAILURE;

   /****** Gathering memory checking info *****/
   stop_memory_check();
   /****** Gathering memory checking info *****/
   
   if (result == FAILURE) {
      exit(EXIT_FAILURE);
   }

   return EXIT_SUCCESS;
}
