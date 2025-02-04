#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

// little to big endian converter
size_t ltob(const char* buff, const size_t typesize);
// converts a number to its string rappresentation
char* num_to_str(const size_t num, const size_t base);

#endif