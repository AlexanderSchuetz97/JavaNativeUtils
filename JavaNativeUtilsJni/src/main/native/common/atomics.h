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
#include <stdlib.h>
#include <stdio.h>
#if (defined(__amd64__) || defined(__i386__))
#include <cpuid.h>
#endif




#if (defined(__amd64__))
#define ATOMIC_OPTIONAL_cmpxchg16b 1
#define ATOMIC_ALIGNED_cmpxchg16b
#define ATOMIC_ALIGNMENT_cmpxchg16b 8
#else
#define ATOMIC_ALIGNMENT_cmpxchg16b 1
#define ATOMIC_NO_cmpxchg16b
#endif

static volatile int cas16 = 0;

static inline bool supports_cmpxchg16b() {
#if (defined(__amd64__))
    if (cas16 == 0) {
        int eax, ebx, ecx, edx;
        __cpuid(1, eax, ebx, ecx, edx);
        if ((ecx & bit_CMPXCHG16B) == bit_CMPXCHG16B) {
            cas16 = 1;
        } else {
            cas16 = 2;
        }
    }

    return cas16 == 1;
#else
    return false;
#endif
}

static inline bool aligned_cmpxchg16b(void* ptr) {
    //AMD64 ONLY
    if ((((uintptr_t) ptr) & 0xF) != 0) {
        return false;
    }
    return true;
}

static inline bool cmpxchg16b(void* ptr, uint64_t* value) {
#if (defined(__amd64__))
    //Exists only as a hint for compiler.
    struct uint128 {
        char data[16];
    };

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
    return flag;
#else
    abort();
	return false;
#endif
}

#if (defined(__i386__))
#define ATOMIC_ALIGNMENT_cmpxchg8b 8
#define ATOMIC_OPTIONAL_cmpxchg8b
#define ATOMIC_ALIGNED_cmpxchg8b
#elif (defined(__riscv) || defined(__aarch64__))
#define ATOMIC_ALIGNMENT_cmpxchg8b 8
#define ATOMIC_ALIGNED_cmpxchg8b
#elif (defined(__amd64__))
#define ATOMIC_ALIGNMENT_cmpxchg8b 1
#else
#define ATOMIC_ALIGNMENT_cmpxchg8b 1
#define ATOMIC_NO_cmpxchg8b
#endif

static volatile int cas8 = 0;

static inline bool supports_cmpxchg8b() {
#if (defined(__amd64__) || defined(__riscv) || defined(__aarch64__))
    return true;
#elif (defined(__i386__))
    if (cas8 == 0) {
		int eax, ebx, ecx, edx;
		__cpuid(1, eax, ebx, ecx, edx);
		if ((ecx & bit_CMPXCHG8B) == bit_CMPXCHG8B) {
			cas8 = 1;
		} else {
			cas8 = 2;
		}
	}

	return cas8 == 1;
#else
	return false;
#endif
}

static inline bool aligned_cmpxchg8b(uint64_t* ptr) {
#if (defined(__i386__) || (defined(__riscv)) || (defined(__aarch64__)))
    if ((((uintptr_t) ptr) & 0x7) != 0) {
        return false;
    }
    return true;
#else
    return true;
#endif
}

static inline bool cmpxchg8b(uint64_t* ptr, uint64_t expect, uint64_t update) {
#if (defined(__amd64__))
    register uint64_t accumulator asm ("rax") = expect;
    bool flag;
    __asm__ __volatile__ (
            "LOCK; CMPXCHG %[update], %[pointer];"
            "SETZ %[flag];"
            : [pointer] "+m" (*ptr), [flag] "=r" (flag)
    : [expect] "r" (accumulator), [update] "r" (update)
    : "cc", "memory");
    return flag;
#elif (defined(__aarch64__))
    bool flag = false;
    register uint64_t expect_register asm ("x1") = expect;
    register uint64_t update_register asm ("x2") = update;
    __asm__ __volatile__ (
            "again%=:;"
            "ldaxr x3, [%[pointer]];"
            "cmp x3, x1;"
            "bne end%=;"
            "stlxr w3, x2, [%[pointer]];"
            "cbnz w3, again%=;"
            "mov %[flag], #1;"
            "end%=:;"

            : [flag] "+r" (flag)
            : "r" (update_register), "r" (expect_register), [pointer] "r" (ptr)
            : "memory", "x3"
    );

    return flag;
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

	return flag;
#elif (defined(__riscv))
    bool flag;
    __asm__ __volatile__ (
            "fence iorw, iorw;"
            "again%=:;"
            "lr.d.aq t0, (%[pointer]);"
            "bne t0, %[expect], fail%=;"
            "sc.d.rl t0, %[update], (%[pointer]);"
            "bne t0, x0, again%=;"
            "li %[flag], 1;"
            "tail end%=;"
            "fail%=:;"
            "li %[flag], 0;"
            "end%=:;"

            : [flag] "=r" (flag)
            : [expect] "r" (expect), [update] "r" (update), [pointer] "r" (ptr)
            : "memory", "t0"
    );
    return flag;
#else
    abort();
	return false;
#endif
}


#if (defined(__i386__))
#define ATOMIC_OPTIONAL_cmpxchg4b
#define ATOMIC_ALIGNMENT_cmpxchg4b 1
#elif (defined(__riscv))
#define ATOMIC_ALIGNED_cmpxchg4b
#define ATOMIC_ALIGNMENT_cmpxchg4b 4
#elif (defined(__aarch64__))
#define ATOMIC_ALIGNED_cmpxchg4b
#define ATOMIC_ALIGNMENT_cmpxchg4b 4
#elif (defined(__amd64__))
#define ATOMIC_ALIGNMENT_cmpxchg4b 1
#else
#define ATOMIC_ALIGNMENT_cmpxchg4b 1
#define ATOMIC_NO_cmpxchg4b
#endif


static inline bool supports_cmpxchg4b() {
#if (defined(__amd64__) || defined(__riscv) || defined(__aarch64__))
    return true;
#elif (defined(__i386__))
    //TODO check cpuid for compare and set shit
    return true;
#endif
}

static inline bool aligned_cmpxchg4b(uint32_t* ptr) {
#if defined(__riscv) || defined(__aarch64__)
    if ((((uintptr_t) ptr) & 0x3) != 0) {
        return false;
    }

    return true;
#else
    return true;
#endif
}

static inline bool cmpxchg4b(uint32_t* ptr, uint32_t expect, uint32_t update) {

#if (defined(__amd64__) || defined(__i386__))
    register uint32_t accumulator asm ("eax") = expect;
    bool flag;
    __asm__ __volatile__ (
            "LOCK; CMPXCHG %[update], %[pointer];"
            "SETZ %[flag];"
            : [pointer] "+m" (*ptr), [flag] "=r" (flag)
    : [expect] "r" (accumulator), [update] "r" (update)
    : "cc", "memory");
    return flag;
#elif (defined(__aarch64__))
    bool flag = false;
    register uint64_t expect_register asm ("x1") = expect;
    register uint64_t update_register asm ("x2") = update;
    __asm__ __volatile__ (
            "again%=:;"
            "ldaxr w3, [%[pointer]];"
            "cmp w3, w1;"
            "bne end%=;"
            "stlxr w3, w2, [%[pointer]];"
            "cbnz w3, again%=;"
            "mov %[flag], #1;"
            "end%=:;"

            : [flag] "+r" (flag)
            : "r" (update_register), "r" (expect_register), [pointer] "r" (ptr)
            : "memory", "x3"
    );

    return flag;
#elif (defined(__riscv))
    bool flag = false;
    __asm__ __volatile__ (
            "fence iorw, iorw;"
            "again%=:;"
            "lr.w.aq t0, (%[pointer]);"
            "bne t0, %[expect], end%=;"
            "sc.w.rl t0, %[update], (%[pointer]);"
            "bne t0, x0, again%=;"
            "li %[flag], 1;"
            "end%=:;"

            : [flag] "+r" (flag)
            : [expect] "r" (expect), [update] "r" (update), [pointer] "r" (ptr)
            : "memory", "t0"
    );
    return flag;
#else
    abort();
	return false;
#endif
}

#if (defined(__amd64__) || defined(__i386__))
#define ATOMIC_ALIGNMENT_cmpxchg2b 1
#else
#define ATOMIC_ALIGNMENT_cmpxchg2b 1
#define ATOMIC_NO_cmpxchg2b
#endif

static inline bool supports_cmpxchg2b() {
#if (defined(__amd64__) || defined(__i386__))
    return true;
#else
    return false;
#endif
}

static inline bool aligned_cmpxchg2b(uint16_t* ptr) {
#if (defined(__amd64__) || defined(__i386__))
    return true;
#else
    return true;
#endif
}

static inline bool cmpxchg2b(uint16_t* ptr, uint16_t expect, uint16_t update) {
#if (defined(__amd64__) || defined(__i386__))
    register uint16_t accumulator asm ("ax") = expect;
    bool flag;
    __asm__ __volatile__ (
            "LOCK; CMPXCHG %[update], %[pointer];"
            "SETZ %[flag];"
            : [pointer] "+m" (*ptr), [flag] "=r" (flag)
    : [expect] "r" (accumulator), [update] "r" (update)
    : "cc", "memory");
    return flag;
#else
    abort();
	return false;
#endif
}

#if (defined(__amd64__) || defined(__i386__))
#define ATOMIC_ALIGNMENT_cmpxchg1b 1
#else
#define ATOMIC_ALIGNMENT_cmpxchg1b 1
#define ATOMIC_NO_cmpxchg1b
#endif

static inline bool supports_cmpxchg1b() {
#if (defined(__amd64__) || defined(__i386__))
    return true;
#else
    return false;
#endif
}

static inline bool aligned_cmpxchg1b(uint8_t* ptr) {
    return true;
}


#if (defined(__i386__))
//GCC runs out of registers when trying to inline this function for i386
static __attribute__ ((noinline)) bool cmpxchg1b(uint8_t* ptr, uint8_t expect, uint8_t update) {
#else
static inline bool cmpxchg1b(uint8_t* ptr, uint8_t expect, uint8_t update) {
#endif
#if (defined(__amd64__) || defined(__i386__))
    register uint8_t accumulator asm ("al") = expect;
    bool flag;
    __asm__ __volatile__ (
            "LOCK; CMPXCHG %[update], %[pointer];"
            "SETZ %[flag];"
            : [pointer] "+m" (*ptr), [flag] "=r" (flag)
    : [expect] "r" (accumulator), [update] "r" (update)
    : "cc", "memory");
    return flag;
#else
    abort();
	return false;
#endif
}

//ADD AND RETURN OLD VALUE

static inline uint8_t xadd1b(uint8_t* ptr, uint8_t value) {
#if (defined(__amd64__) || defined(__i386__))
    __asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;

#else
    volatile uint8_t *vol = (volatile uint8_t*) ptr;
    uint8_t old = *vol;
    while(!cmpxchg1b(ptr, old, old+value)) {
        old = *vol;
    }

    return old;
#endif
}

static inline uint16_t xadd2b(uint16_t* ptr, uint16_t value) {
#if (defined(__amd64__) || defined(__i386__))
    __asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;
#else
    volatile uint16_t *vol = (volatile uint16_t*) ptr;
    uint16_t old = *vol;
    while(!cmpxchg2b(ptr, old, old+value)) {
        old = *vol;
    }

    return old;
#endif
}

static inline uint32_t xadd4b(uint32_t* ptr, uint32_t value) {
#if (defined(__amd64__) || defined(__i386__))
    __asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;
#elif (defined(__riscv))
    __asm__ __volatile__ (
            "fence iorw, iorw;"
            "amoadd.w %[value], %[value], (%[pointer]);"
            : [value] "+r" (value)
            : [pointer] "r" (ptr)
            : "memory"
    );
    return value;
#else
    volatile uint32_t *vol = (volatile uint32_t*) ptr;
    uint32_t old = *vol;
    while(!cmpxchg4b(ptr, old, old+value)) {
        old = *vol;
    }

    return old;
#endif
}


static inline uint64_t xadd8b(uint64_t* ptr, uint64_t value) {
#if (defined(__amd64__))
    __asm__ __volatile__ ("LOCK; XADD %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;
#elif (defined(__riscv))
    __asm__ __volatile__ (
            "fence iorw, iorw;"
            "amoadd.d %[value], %[value], (%[pointer]);"
            : [value] "+r" (value)
            : [pointer] "r" (ptr)
            : "memory"
    );
    return value;
#else
    volatile uint64_t *vol = (volatile uint64_t*) ptr;
    uint64_t old = *vol;
    while(!cmpxchg8b(ptr, old, old+value)) {
        old = *vol;
    }

    return old;
#endif
}

//REPLACE

static inline uint8_t xchg1b(uint8_t* ptr, uint8_t value) {
#if (defined(__amd64__) || defined(__i386__))
    __asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;
#else
    volatile uint8_t *vol = (volatile uint8_t*) ptr;
    uint8_t old = *vol;
    while(!cmpxchg1b(ptr, old, value)) {
        old = *vol;
    }

    return old;
#endif
}

static inline uint16_t xchg2b(uint16_t* ptr, uint16_t value) {
#if (defined(__amd64__) || defined(__i386__))
    __asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;
#else
    volatile uint16_t *vol = (volatile uint16_t*) ptr;
    uint16_t old = *vol;
    while(!cmpxchg2b(ptr, old, value)) {
        old = *vol;
    }

    return old;
#endif
}

static inline uint32_t xchg4b(uint32_t* ptr, uint32_t value) {
#if (defined(__amd64__) || defined(__i386__))
    __asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;
#elif (defined(__riscv))
    __asm__ __volatile__ (
            "fence iorw, iorw;"
            "amoswap.w %[value], %[value], (%[pointer]);"
            : [value] "+r" (value)
            : [pointer] "r" (ptr)
            : "memory"
    );
    return value;
#else
    volatile uint32_t *vol = (volatile uint32_t*) ptr;
    uint32_t old = *vol;
    while(!cmpxchg4b(ptr, old, value)) {
        old = *vol;
    }

    return old;
#endif
}


static inline uint64_t xchg8b(uint64_t* ptr, uint64_t value) {
#if (defined(__amd64__))
    __asm__ __volatile__ ("LOCK; XCHG %[value], %[pointer];"
            : [pointer] "+m" (*ptr), [value] "+r" (value)
    :
    : "memory");
    return value;
#elif (defined(__riscv))
    __asm__ __volatile__ (
            "fence iorw, iorw;"
            "amoswap.d %[value], %[value], (%[pointer]);"
            : [value] "+r" (value)
            : [pointer] "r" (ptr)
            : "memory"
    );
    return value;
#else
    volatile uint64_t *vol = (volatile uint64_t*) ptr;
    uint64_t old = *vol;
    while(!cmpxchg8b(ptr, old, value)) {
        old = *vol;
    }

    return old;
#endif
}

#endif /* UTIL_ATOMICS_H_ */
