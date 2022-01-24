//
// Copyright Alexander Schütz, 2021-2022
//
// This file is part of JavaNativeUtils.
//
// JavaNativeUtils is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JavaNativeUtils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// A copy of the GNU Lesser General Public License should be provided
// in the COPYING & COPYING.LESSER files in top level directory of JavaNativeUtils.
// If not, see <https://www.gnu.org/licenses/>.
//


#ifndef UTIL_ATOMICS_H_
#define UTIL_ATOMICS_H_
#include <stdint.h>
#include <stdbool.h>


bool xadd1b(uint8_t* ptr, uint8_t* vPtr);

bool xadd2b(uint16_t* ptr, uint16_t* vPtr);

bool xadd4b(uint32_t* ptr, uint32_t* vPtr);

bool xadd8b(uint64_t* ptr, uint64_t* vPtr);

bool cmpxchg8b(uint64_t* ptr, uint64_t expect, uint64_t update, bool* success);

bool cmpxchg4b(uint32_t* ptr, uint32_t expect, uint32_t update, bool* success);

bool cmpxchg2b(uint16_t* ptr, uint16_t expect, uint16_t update, bool* success);

bool cmpxchg1b(uint8_t* ptr, uint8_t expect, uint8_t update, bool* success);

bool cmpxchg16b(void* ptr, uint64_t* value, bool* success);

bool xchg1b(uint8_t* ptr, uint8_t* value);

bool xchg2b(uint16_t* ptr, uint16_t* value);

bool xchg4b(uint32_t* ptr, uint32_t* value);

bool xchg8b(uint64_t* ptr, uint64_t* value);


#endif /* UTIL_ATOMICS_H_ */
