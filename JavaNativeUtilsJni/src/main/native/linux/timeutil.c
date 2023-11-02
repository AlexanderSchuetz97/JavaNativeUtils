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
#include "../common/timeutil.h"
#include <time.h>
#include <stdbool.h>
#include <errno.h>

#define NANOSECONDS_PER_MILISECOND 1000000


void sleepMillis(uint64_t aMillis) {
	uint64_t tempMillisWithoutSeconds = aMillis % 1000;
	struct timespec tempTime;
	tempTime.tv_sec = (aMillis - (tempMillisWithoutSeconds)) / 1000;
	tempTime.tv_nsec = tempMillisWithoutSeconds * NANOSECONDS_PER_MILISECOND;

	struct timespec tempRem;
	while(true) {
		if (nanosleep(&tempTime, &tempRem) == 0) {
			return;
		}

		int err = errno;

		if (err == EINTR) {
			tempTime.tv_sec = tempRem.tv_sec;
			tempTime.tv_nsec = tempRem.tv_nsec;
			continue;
		}

		return;
	}

}

uint64_t currentTimeMillis() {
    struct timespec spec;

    clock_gettime(CLOCK_REALTIME, &spec);

    return spec.tv_sec * 1000 + (spec.tv_nsec / NANOSECONDS_PER_MILISECOND);
}
