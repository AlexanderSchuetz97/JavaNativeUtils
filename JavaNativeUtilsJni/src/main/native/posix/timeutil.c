//
// Copyright Alexander Schütz, 2021-2024
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

    //on 32-bit systems tv_sec is 32 bit
	tempTime.tv_sec = (time_t) ((aMillis - (tempMillisWithoutSeconds)) / 1000);
	tempTime.tv_nsec = (time_t) (tempMillisWithoutSeconds * NANOSECONDS_PER_MILISECOND);

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

    //on 32-bit systems tv_sec is 32 bit
    uint64_t sec = spec.tv_sec;
    uint64_t n_sec = spec.tv_nsec;

    return sec * 1000 + (n_sec / NANOSECONDS_PER_MILISECOND);
}
