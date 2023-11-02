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
package eu.aschuetz.nativeutils.api;

public interface CpuConst {
    int CPUID_FEAT_ECX_SSE3         = 1 << 0;
    int CPUID_FEAT_ECX_PCLMUL       = 1 << 1;
    int CPUID_FEAT_ECX_DTES64       = 1 << 2;
    int CPUID_FEAT_ECX_MONITOR      = 1 << 3;
    int CPUID_FEAT_ECX_DS_CPL       = 1 << 4;
    int CPUID_FEAT_ECX_VMX          = 1 << 5;
    int CPUID_FEAT_ECX_SMX          = 1 << 6;
    int CPUID_FEAT_ECX_EST          = 1 << 7;
    int CPUID_FEAT_ECX_TM2          = 1 << 8;
    int CPUID_FEAT_ECX_SSSE3        = 1 << 9;
    int CPUID_FEAT_ECX_CID          = 1 << 10;
    int CPUID_FEAT_ECX_SDBG         = 1 << 11;
    int CPUID_FEAT_ECX_FMA          = 1 << 12;
    int CPUID_FEAT_ECX_CX16         = 1 << 13;
    int CPUID_FEAT_ECX_XTPR         = 1 << 14;
    int CPUID_FEAT_ECX_PDCM         = 1 << 15;
    int CPUID_FEAT_ECX_PCID         = 1 << 17;
    int CPUID_FEAT_ECX_DCA          = 1 << 18;
    int CPUID_FEAT_ECX_SSE4_1       = 1 << 19;
    int CPUID_FEAT_ECX_SSE4_2       = 1 << 20;
    int CPUID_FEAT_ECX_X2APIC       = 1 << 21;
    int CPUID_FEAT_ECX_MOVBE        = 1 << 22;
    int CPUID_FEAT_ECX_POPCNT       = 1 << 23;
    int CPUID_FEAT_ECX_TSC          = 1 << 24;
    int CPUID_FEAT_ECX_AES          = 1 << 25;
    int CPUID_FEAT_ECX_XSAVE        = 1 << 26;
    int CPUID_FEAT_ECX_OSXSAVE      = 1 << 27;
    int CPUID_FEAT_ECX_AVX          = 1 << 28;
    int CPUID_FEAT_ECX_F16C         = 1 << 29;
    int CPUID_FEAT_ECX_RDRAND       = 1 << 30;
    int CPUID_FEAT_ECX_HYPERVISOR   = 1 << 31;
    int CPUID_FEAT_EDX_FPU          = 1 << 0;
    int CPUID_FEAT_EDX_VME          = 1 << 1;
    int CPUID_FEAT_EDX_DE           = 1 << 2;
    int CPUID_FEAT_EDX_PSE          = 1 << 3;
    int CPUID_FEAT_EDX_TSC          = 1 << 4;
    int CPUID_FEAT_EDX_MSR          = 1 << 5;
    int CPUID_FEAT_EDX_PAE          = 1 << 6;
    int CPUID_FEAT_EDX_MCE          = 1 << 7;
    int CPUID_FEAT_EDX_CX8          = 1 << 8;
    int CPUID_FEAT_EDX_APIC         = 1 << 9;
    int CPUID_FEAT_EDX_SEP          = 1 << 11;
    int CPUID_FEAT_EDX_MTRR         = 1 << 12;
    int CPUID_FEAT_EDX_PGE          = 1 << 13;
    int CPUID_FEAT_EDX_MCA          = 1 << 14;
    int CPUID_FEAT_EDX_CMOV         = 1 << 15;
    int CPUID_FEAT_EDX_PAT          = 1 << 16;
    int CPUID_FEAT_EDX_PSE36        = 1 << 17;
    int CPUID_FEAT_EDX_PSN          = 1 << 18;
    int CPUID_FEAT_EDX_CLFLUSH      = 1 << 19;
    int CPUID_FEAT_EDX_DS           = 1 << 21;
    int CPUID_FEAT_EDX_ACPI         = 1 << 22;
    int CPUID_FEAT_EDX_MMX          = 1 << 23;
    int CPUID_FEAT_EDX_FXSR         = 1 << 24;
    int CPUID_FEAT_EDX_SSE          = 1 << 25;
    int CPUID_FEAT_EDX_SSE2         = 1 << 26;
    int CPUID_FEAT_EDX_SS           = 1 << 27;
    int CPUID_FEAT_EDX_HTT          = 1 << 28;
    int CPUID_FEAT_EDX_TM           = 1 << 29;
    int CPUID_FEAT_EDX_IA64         = 1 << 30;
    int CPUID_FEAT_EDX_PBE          = 1 << 31;
}

