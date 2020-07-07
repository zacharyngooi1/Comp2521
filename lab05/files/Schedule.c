// Schedule ADT implementation

#include <stdio.h>
#include <stdlib.h>

#include "Schedule.h"
#include "Time.h"
#include "Tree.h"

struct schedule {
    Tree times;
    int  count;
};

// Creates a new schedule
Schedule ScheduleNew(void) {
    Schedule s = malloc(sizeof(*s));
    if (s == NULL) {
        fprintf(stderr, "Insufficient memory!\n");
        exit(EXIT_FAILURE);
    }

    s->times = TreeNew();
    s->count = 0;
    return s;
}

// Frees all memory associated with a given schedule
void ScheduleFree(Schedule s) {
    TreeFree(s->times);
    free(s);
}

// Gets the number of times added to the schedule
int  ScheduleCount(Schedule s) {
    return s->count;
}

// Attempts to schedule a new landing time. Returns true if the time was
// successfully added, and false otherwise.
bool ScheduleAdd(Schedule s, Time t) {
    // Base case
    if (s == NULL){
        return false;
    }

    if (t == NULL){
        return false;
    }


    // check if tree floor is not null
    if (TreeFloor(s->times, t) != NULL) {
        Time less = TimeCopy(TreeFloor(s->times, t));
        Time add_less = TimeAddMinutes(less,10);
        if (TimeCmp(t, add_less) <= 0) {
            return false;
        }
        // Free memory
        TimeFree(less);
    }

    // Check if ceiling is not null
    if (TreeCeiling(s->times, t) != NULL) {
        Time more = TimeCopy(TreeCeiling(s->times, t));
        Time take_more = TimeSubtractMinutes(more,10);
        if (TimeCmp(t, take_more) >= 0) {
            return false;
        }
        // Free memory
        TimeFree(more);
    }

    TreeInsert(s->times, t);
    s->count++;
    return true;
}

// Shows  all  the landing times in the schedule. If mode is 1, only the
// times are shown. If mode is 2, the underlying data structure is shown
// as well.
void ScheduleShow(Schedule s, int mode) {
    if (mode == 1) {
        TreeList(s->times);
    } else if (mode == 2) {
        TreeShow(s->times);
    }
}
