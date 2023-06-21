/* 
* Name: James Zhang
* UID: 118843940
* Course: CMSC216 by Professor Yoon
* Section: 0301
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "calendar.h"
#include "event.h"

/* 
1. This method dynamically allocates memory for a calendar and its name and 
events fields. If any dynamically allocated memory fails, or if days < 1 or 
name or calendar null, the function returns FAIURE.
Args:
    - const char *name
    - int days
    - int total_events
    - int (*comp_func) (const void *event1, const void *event2)
    - void (void *free_info_func) (void *info)
    - Calendar **calendar
Returns:
    - int SUCCESS or FAILURE
*/
int init_calendar(const char *name, int days, int (*comp_func) (const void *event1, const void *event2), 
                  void (*free_info_func) (void *ptr), Calendar **calendar) {
    /* null check */
    if (days >= 1 && name && calendar) {
        
        /* dynamically allocate memory for calendar, name, events array */
        *calendar = malloc(sizeof(Calendar)); 
        if (!(*calendar)) {
            return FAILURE;
        }
        /* initialize fields for calendar */
        (*calendar)->comp_func = comp_func;
        (*calendar)->free_info_func = free_info_func;
        (*calendar)->days = days;

        /* dynamically allocate memory for name and events now*/
        (*calendar)->name = malloc(strlen(name) + 1);
        if (!((*calendar)->name)) {
            return FAILURE;
        }
        strcpy(((*calendar)->name), name);
        (*calendar)->events = calloc(days, sizeof(Event *));
        if (!((*calendar)->events)) {
            return FAILURE;
        }
        /* set total events to 0*/
        (*calendar)->total_events = 0;
        return SUCCESS;
    }
    return FAILURE;
}

/*
2. This function prints some information about the calendar to the designated 
output parameter. It returns FAILURE if first and or second parameter are null; 
otherwise it returns SUCCESS
Args:
    - Calendar *calendar
    - FILE *file
    - int print_number_of_events
Returns:
    - int SUCCESS or FAILURE
*/
int print_calendar(Calendar *calendar, FILE *file, int print_all) {
    /* null check */
    if (calendar && file) {
        int i = 0;
        Event *curr;
        if (print_all) {
            fprintf(file, "Calendar's Name: \"%s\"\nDays: %d\nTotal Events: %d\n", 
                    calendar->name, calendar->days, calendar->total_events);
        }
        fprintf(file, "\n**** Events ****\n");
        if (calendar->total_events > 0){
            /* iterate through the array of event pointers */
            for (i = 0; i < calendar->days; i++) {
                fprintf(file, "Day %d\n", i + 1);
                curr = calendar->events[i];
                /* iterate through the linked list and print all events */
                while (curr) {
                    fprintf(file, "Event's Name: \"%s\", Start_time: %d, Duration: %d\n", curr->name, curr->start_time, curr->duration_minutes);
                    curr = curr->next;
                }
            }
        }
        return SUCCESS;
    }
    return FAILURE;
}

/*
3. This function takes specific event information add events to the given calendar.
This function also adds the event to the event list in ascending order using the 
comparison fucntion specified in init_calendar. The function dynamically allocates
memory for the new event and the new event's name.
*/

int add_event(Calendar *calendar, const char *name, int start_time, int duration_minutes,
    void *info, int event_day) {
    
    /* null check */
    if (calendar && name && event_day >= 1 && event_day <= calendar->days && 
        start_time >= 0 && start_time <= 2400 && duration_minutes > 0) {
        
            Event *curr = calendar->events[event_day - 1], *prev = NULL;

            /* dynamically allocate memory for event and event name */
            Event *event = malloc(sizeof(Event));
            if (!event) {
                return FAILURE;
            }
            event->name = malloc(strlen(name) + 1);
            if (!event->name) {
                return FAILURE;
            }
            /* initialize the new event */
            event->start_time = start_time;
            event->duration_minutes = duration_minutes;
            event->info = info;
            strcpy(event->name, name);

            /* now find insertion spot or see if event already exists (by name) */
            while (curr && (*(calendar->comp_func))(event, curr) >= 0) {
                if (strcmp(event->name, curr->name) == 0) {
                    return FAILURE;
                }
                prev = curr;
                curr = curr->next;
            }
            /* consider edge case - if not, then prev should point to insertion spot */
            event->next = curr;
            if (prev == NULL) {
                calendar->events[event_day - 1] = event;
            }
            else {
                prev->next = event;
            }
            calendar->total_events += 1;
            return SUCCESS;
    }
    return FAILURE;
}

/* 
4. This method loopsd through the entire calendar and iterates 
through each linked list to find the event with the desired name.
Args:
    - Calendar *calendar
    - const char *name
    - Event **event
Returns:
    - int SUCCESS or FAILURE
    - event in the out-parameter
*/
int find_event(Calendar *calendar, const char *name, Event ** event) {
    /* null check */
    if (calendar && name) {
        int i = 0;
        Event *curr;
        /* loop through all days and iterate through all linked lists */
        for (i = 0; i < calendar->days; i++) {
            curr = calendar->events[i];
            while (curr) {
                if (strcmp(curr->name, name) == 0) {
                    /* only set event if not null */
                    if (event) {
                        *event = curr;
                    }
                    return SUCCESS;
                }
                curr = curr->next;
            }
        }
    }
    return FAILURE;
}

/* 
5. This method finds an event on a given day. It is very similar to the previous
method.
Args:
    - Calendar *calendar
    - const char *name
    - int day
    - Event ** event
Returns:    
    - int SUCCESS or FAILURE
    - event in the out-parameter
*/
int find_event_in_day(Calendar *calendar, const char *name, int day, Event **event) {
    /* null check */
    if (calendar && name) {
        Event *curr = calendar->events[day - 1];
        /* go to day and iterate through that linked list only */
        while (curr) {
            if (strcmp(curr->name, name) == 0) {
                if (event) {
                    *event = curr;
                }
                return SUCCESS;
            }
            curr = curr->next;
        }
    }
    return FAILURE;
}

/* 
6. This method searches for an event and removes it from the calendar.
Args:
    - Calendar *calendar
    - const char *name
Return:
    - int SUCCESS or FAILURE
*/
int remove_event(Calendar *calendar, const char *name) {
    /* null check */
    if (calendar && name) {
        int i;
        Event *curr, *prev = NULL;
        for (i = 0 ; i < calendar->days; i++) {
            curr = calendar->events[i];
            while (curr) {
                if (strcmp(curr->name, name) == 0) {
                    /* then remove it and deallocate memory*/

                    if (prev == NULL) {
                        calendar->events[i] = curr->next;
                    } else {
                        prev->next = curr->next;
                    }

                    /* free info and fields */
                    if (curr->info && calendar->free_info_func) {
                        (calendar->free_info_func)(curr->info);
                    }
                    free(curr->name);
                    free(curr);
                    calendar->total_events -= 1;
                    return SUCCESS;
                }
                prev = curr;
                curr = curr->next;
            }
        }
    }
    return FAILURE;
}

/* 
7. This method returns the info pointer associated with the specified event.
Args:
    - Calendar *calendar
    - const char *name
Returns:
    - void *info or NULL if the event is not found
*/
void *get_event_info(Calendar *calendar, const char *name) {
    /* we can assume both parameters aren't null*/
    Event *event;
    /* if the event exists then return its info*/
    if (find_event(calendar, name, &event) == SUCCESS) {
        return event->info;
    } else {
        return NULL;
    }
}

/*
8. This method removes all the events for the event day, setting the event list to empty. 
Adjust the total number of events accordinly and the deallocate any dynamically alllocated memory.
If an event has an info field and a free_info_func exists, use this func to deallocate info.
Args:
    - Calendar *calendar
    - int day
Returns:
    - int SUCCESS or FAILURE
*/
int clear_day(Calendar *calendar, int day) {
    /* null check */
    if (calendar && day >= 1 && day <= calendar->days) {
        int num_removed = 0;
        Event *curr = calendar->events[day - 1], *temp;
        while (curr) {
            /* store the next node because we won't have access to it after freeing it */
            temp = curr->next;
            if (curr->info && calendar->free_info_func) {
                (calendar->free_info_func)(curr->info);
            }
            /* free fields */
            free(curr->name);
            free(curr);
            num_removed += 1;
            /* move the current pointer to the next node */
            curr = temp;
        }
        calendar->total_events -= num_removed;
        calendar->events[day - 1] = NULL;
        return SUCCESS;
    }
    return FAILURE;
}

/*
9. This method clears an entire calendar and removes all of the event lists. The total number of events
should be adjusted accordingly and all allocated memory should be deallocated. 
Args:
    - Calendar *calendar
Returns:
    - int SUCCESS or FAILURE
*/
int clear_calendar(Calendar *calendar) {
    /* null check */
    if (calendar) {
        int i; 
        for (i = 0; i < calendar->days; i++) {
            /* clear each day in the calendar */
            clear_day(calendar, i + 1);
        }
        return SUCCESS;
    } 
    return FAILURE;
}

/*
10. This method frees memory dynamically allocated for the memory and individual events.
Args:
    - Calendar *calendar
Returns:
    - int SUCCESS or FAILURE
*/
int destroy_calendar(Calendar *calendar) {
    /* null check */
    if (calendar) {
        clear_calendar(calendar);
        /* now free the calendar's fields */
        free(calendar->events);
        free(calendar->name);
        free(calendar);
        return SUCCESS;
    }
    return FAILURE;
}