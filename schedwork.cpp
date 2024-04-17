#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day
);

bool workerAvailable(const AvailabilityMatrix& avail, size_t day, size_t worker);
bool exceededMaxShifts(const DailySchedule& sched, size_t worker, size_t maxShifts);


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below


    if (scheduleHelper(avail, dailyNeed, maxShifts, sched, 0)) {
        return true; // A valid schedule is found
    } else {
        return false; // No valid schedule found
    }

}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    size_t day
){
    if (day == avail.size()) {
        // Check if all workers have been assigned the required number of shifts
        for (size_t worker = 0; worker < avail[0].size()-1; ++worker) {
            if (!exceededMaxShifts(sched, worker, maxShifts)) {
                return false; // Not all workers have been assigned the required shifts
            }
        }
        return true; // All workers have been assigned the required shifts
    }

    if (sched.size() <= day) {
        sched.resize(day + 1);
    }

    // Go through all possible workers available
    for (size_t worker = 0; worker < avail[day].size(); ++worker){
        // Only progress when we find a valid worker
        if (workerAvailable(avail, day, worker) && !exceededMaxShifts(sched, worker, maxShifts)){
            
            // Add the worker
            sched[day].push_back(worker);

            // Go to next day if successful
            if (scheduleHelper(avail, dailyNeed, maxShifts, sched, day + 1)){
                return true;
            }

            sched[day].pop_back(); // This backtracks by removing the last added worker
        }
    }

    return false; // No existing valid schedule
}

bool workerAvailable(const AvailabilityMatrix& avail, size_t day, size_t worker) {
    return avail[day][worker]; // Since the value is already bool we can just return this element of the matrix
}

// Checks entire schedule to make sure we have not exceeded the max shift limit
bool exceededMaxShifts(const DailySchedule& sched, size_t worker, size_t maxShifts){
    size_t shifts = 0;
    for (size_t i = 0; i < sched.size(); ++i) {
        const std::vector<Worker_T>& day = sched[i];
        for (size_t j = 0; j < day.size(); ++j) {
            Worker_T w = day[j];
            if (w == worker) {
                shifts++;
                if (shifts > maxShifts) {
                    return true;
                }
            }
        }
    }
    return false;
}