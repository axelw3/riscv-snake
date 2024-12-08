#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
/**
 * Read and print hardware counter values.
 * @author owiren
*/
void printHardwareCounters();

/**
 * Reset hardware counters.
 * @author sethsson
*/
void resetHardwareCounters();
#endif

#endif