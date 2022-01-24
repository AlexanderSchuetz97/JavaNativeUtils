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

#include "atomics.h"
#define FFINLINE  inline __attribute__((always_inline))

bool FFINLINE xadd1b(uint8_t* ptr, uint8_t* vPtr) {
#if (defined(__amd64__) || defined(__i386__))
	uint8_t value = *vPtr;
	__asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#else
	return false;
#endif
}

bool FFINLINE xadd2b(uint16_t* ptr, uint16_t* vPtr) {
#if (defined(__amd64__) || defined(__i386__))
	uint16_t value = *vPtr;
	__asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#else
	return false;
#endif
}

bool FFINLINE xadd4b(uint32_t* ptr, uint32_t* vPtr) {
#if (defined(__amd64__) || defined(__i386__))
	uint32_t value = *vPtr;
	__asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#else
	return false;
#endif
}


bool FFINLINE xadd8b(uint64_t* ptr, uint64_t * vPtr) {
	uint64_t value = *vPtr;
#if (defined(__amd64__))
	__asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#elif (defined(__i386__))
	while(true) {
		uint64_t tempCur = *ptr;
		bool tempResult = true;
		cmpxchg8b(ptr, tempCur, tempCur+value, &tempResult);
		if (tempResult) {
			*vPtr = tempCur;
			return true;
		}
	}
#else
	return false;
#endif
}


bool FFINLINE cmpxchg8b(uint64_t* ptr, uint64_t expect, uint64_t update, bool* success) {
#if (defined(__amd64__))
	register uint64_t accumulator asm ("rax") = expect;
	bool flag;
	__asm__ __volatile__ (
			"LOCK; CMPXCHG %[update], %[pointer];"
			"SETZ %[flag];"
				: [pointer] "+m" (*ptr), [flag] "=r" (flag)
				: [expect] "r" (accumulator), [update] "r" (update)
				: "cc", "memory");
	*success = flag;
	return true;
#elif (defined(__i386__))
	register uint32_t eax asm ("eax") = ((uint32_t*)&expect)[0];
	register uint32_t edx asm ("edx") = ((uint32_t*)&expect)[1];
	register uint32_t ebx asm ("ebx") = ((uint32_t*)&update)[0];
	register uint32_t ecx asm ("ecx") = ((uint32_t*)&update)[1];
	bool flag;
	__asm__ __volatile__ (
			"LOCK; CMPXCHG8B %[pointer];"
			"SETZ %[flag];"
				: [pointer] "+m" (*ptr), [flag] "=r" (flag)
				: [expect1] "r" (edx), [expect2] "r" (eax), [update1] "r" (ecx), [update2] "r" (ebx)
				: "cc", "memory");

	*success = flag;
	return true;
#else
	return false;
#endif
}

bool FFINLINE cmpxchg4b(uint32_t* ptr, uint32_t expect, uint32_t update, bool* success) {
#if (defined(__amd64__) || defined(__i386__))
	register uint32_t accumulator asm ("eax") = expect;
	bool flag;
	__asm__ __volatile__ (
			"LOCK; CMPXCHG %[update], %[pointer];"
			"SETZ %[flag];"
				: [pointer] "+m" (*ptr), [flag] "=r" (flag)
				: [expect] "r" (accumulator), [update] "r" (update)
				: "cc", "memory");
	*success = flag;
	return true;
#else
	return false;
#endif
}

bool FFINLINE cmpxchg2b(uint16_t* ptr, uint16_t expect, uint16_t update, bool* success) {
#if (defined(__amd64__) || defined(__i386__))
	register uint16_t accumulator asm ("ax") = expect;
	bool flag;
	__asm__ __volatile__ (
			"LOCK; CMPXCHG %[update], %[pointer];"
			"SETZ %[flag];"
				: [pointer] "+m" (*ptr), [flag] "=r" (flag)
				: [expect] "r" (accumulator), [update] "r" (update)
				: "cc", "memory");
	*success = flag;
	return true;
#else
	return false;
#endif
}

bool FFINLINE cmpxchg1b(uint8_t* ptr, uint8_t expect, uint8_t update, bool* success) {
#if (defined(__amd64__) || defined(__i386__))
	register uint8_t accumulator asm ("al") = expect;
	bool flag;
	__asm__ __volatile__ (
			"LOCK; CMPXCHG %[update], %[pointer];"
			"SETZ %[flag];"
				: [pointer] "+m" (*ptr), [flag] "=r" (flag)
				: [expect] "r" (accumulator), [update] "r" (update)
				: "cc", "memory");
	*success = flag;
	return true;
#else
	return false;
#endif
}


//Exists only as a hint for compiler.
struct uint128 {
	char data[16];
};

bool FFINLINE cmpxchg16b(void* ptr, uint64_t* value, bool* success) {
#if (defined(__amd64__))
	register uint64_t rax asm ("rax") = value[0];
	register uint64_t rdx asm ("rdx") = value[1];
	register uint64_t rbx asm ("rbx") = value[2];
	register uint64_t rcx asm ("rcx") = value[3];
	bool flag;
	__asm__ __volatile__ (
			"LOCK; CMPXCHG16B %[pointer];"
			"SETZ %[flag];"
				: [pointer] "+m" (*((struct uint128*)ptr)), [flag] "=r" (flag)
				: [expect1] "r" (rdx), [expect2] "r" (rax), [update1] "r" (rcx), [update2] "r" (rbx)
				: "cc", "memory");
	*success = flag;
	return true;
#else
	return false;
#endif
}



bool FFINLINE xchg1b(uint8_t* ptr, uint8_t* vPtr) {
#if (defined(__amd64__) || defined(__i386__))
	uint8_t value = *vPtr;
	__asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#else
	return false;
#endif
}

bool FFINLINE xchg2b(uint16_t* ptr, uint16_t* vPtr) {
#if (defined(__amd64__) || defined(__i386__))
	uint16_t value = *vPtr;
	__asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#else
	return false;
#endif
}

bool FFINLINE xchg4b(uint32_t* ptr, uint32_t * vPtr) {
#if (defined(__amd64__) || defined(__i386__))
	uint32_t value = *vPtr;
	__asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#else
	return false;
#endif
}


bool FFINLINE xchg8b(uint64_t* ptr, uint64_t* vPtr) {
#if (defined(__amd64__))
	uint64_t value = *vPtr;
	__asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
				: [pointer] "+m" (*ptr), [value] "+r" (value)
				:
				: "memory");
	*vPtr = value;
	return true;
#elif (defined(__i386__))
	uint64_t value = *vPtr;
	while(true) {
		uint64_t tempCur = *ptr;
		bool tempResult = true;
		cmpxchg8b(ptr, tempCur, value, &tempResult);
		if (tempResult) {
			*vPtr = tempCur;
			return true;
		}
	}
#else
	return false;
#endif
}

