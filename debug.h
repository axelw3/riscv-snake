#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
/**
 * Read and print hardware counter values.
*/
void printHardwareCounters();

/**
 * Reset hardware counters.
*/
void resetHardwareCounters();
#endif

#endif