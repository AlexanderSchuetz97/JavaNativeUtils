#
# Copyright Alexander Schütz, 2021-2022
#
# This file is part of JavaNativeUtils.
#
# JavaNativeUtils is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# JavaNativeUtils is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# A copy of the GNU Lesser General Public License should be provided
# in the COPYING & COPYING.LESSER files in top level directory of JavaNativeUtils.
# If not, see <https://www.gnu.org/licenses/>.
#

#CLion cannot set environment variables for makefiles... pain!
#LINUX_CC_AMD64=/usr/bin/x86_64-linux-gnu-gcc
#LINUX_JDK=/usr/lib/jvm/java-17-openjdk-amd64
#WINDOWS_CC_AMD64=/usr/bin/x86_64-w64-mingw32-gcc-win32
#WINDOWS_JDK=/opt/winjdk/winjdk8

BUILD_BASE_DIR=build

WINDOWS_BUILD_DIR_AMD64=$(BUILD_BASE_DIR)/windows_amd64
WINDOWS_BUILD_DIR_AMD64_COMMON=$(WINDOWS_BUILD_DIR_AMD64)/common

WINDOWS_BUILD_DIR_I386=$(BUILD_BASE_DIR)/windows_i386
WINDOWS_BUILD_DIR_I386_COMMON=$(WINDOWS_BUILD_DIR_I386)/common

LINUX_BUILD_DIR_AMD64=$(BUILD_BASE_DIR)/linux_amd64
LINUX_BUILD_DIR_AMD64_POSIX=$(LINUX_BUILD_DIR_AMD64)/posix
LINUX_BUILD_DIR_AMD64_COMMON=$(LINUX_BUILD_DIR_AMD64)/common

LINUX_BUILD_DIR_AMD64_MUSL=$(BUILD_BASE_DIR)/linux_amd64_musl
LINUX_BUILD_DIR_AMD64_MUSL_POSIX=$(LINUX_BUILD_DIR_AMD64_MUSL)/posix
LINUX_BUILD_DIR_AMD64_MUSL_COMMON=$(LINUX_BUILD_DIR_AMD64_MUSL)/common

LINUX_BUILD_DIR_I386=$(BUILD_BASE_DIR)/linux_i386
LINUX_BUILD_DIR_I386_POSIX=$(LINUX_BUILD_DIR_I386)/posix
LINUX_BUILD_DIR_I386_COMMON=$(LINUX_BUILD_DIR_I386)/common

LINUX_BUILD_DIR_ARMHF=$(BUILD_BASE_DIR)/linux_armhf
LINUX_BUILD_DIR_ARMHF_POSIX=$(LINUX_BUILD_DIR_ARMHF)/posix
LINUX_BUILD_DIR_ARMHF_COMMON=$(LINUX_BUILD_DIR_ARMHF)/common

LINUX_BUILD_DIR_ARMEL=$(BUILD_BASE_DIR)/linux_armel
LINUX_BUILD_DIR_ARMEL_POSIX=$(LINUX_BUILD_DIR_ARMEL)/posix
LINUX_BUILD_DIR_ARMEL_COMMON=$(LINUX_BUILD_DIR_ARMEL)/common

LINUX_BUILD_DIR_AARCH64=$(BUILD_BASE_DIR)/linux_aarch64
LINUX_BUILD_DIR_AARCH64_POSIX=$(LINUX_BUILD_DIR_AARCH64)/posix
LINUX_BUILD_DIR_AARCH64_COMMON=$(LINUX_BUILD_DIR_AARCH64)/common

LINUX_BUILD_DIR_RISCV64=$(BUILD_BASE_DIR)/linux_riscv64
LINUX_BUILD_DIR_RISCV64_POSIX=$(LINUX_BUILD_DIR_RISCV64)/posix
LINUX_BUILD_DIR_RISCV64_COMMON=$(LINUX_BUILD_DIR_RISCV64)/common

LINUX_BUILD_DIR_MIPS64EL=$(BUILD_BASE_DIR)/linux_mips64el
LINUX_BUILD_DIR_MIPS64EL_POSIX=$(LINUX_BUILD_DIR_MIPS64EL)/posix
LINUX_BUILD_DIR_MIPS64EL_COMMON=$(LINUX_BUILD_DIR_MIPS64EL)/common

LINUX_BUILD_DIR_PPC64LE=$(BUILD_BASE_DIR)/linux_ppc64le
LINUX_BUILD_DIR_PPC64LE_POSIX=$(LINUX_BUILD_DIR_PPC64LE)/posix
LINUX_BUILD_DIR_PPC64LE_COMMON=$(LINUX_BUILD_DIR_PPC64LE)/common

LINUX_BUILD_DIR_S390X=$(BUILD_BASE_DIR)/linux_s390x
LINUX_BUILD_DIR_S390X_POSIX=$(LINUX_BUILD_DIR_S390X)/posix
LINUX_BUILD_DIR_S390X_COMMON=$(LINUX_BUILD_DIR_S390X)/common

FREEBSD_BUILD_DIR_AMD64=$(BUILD_BASE_DIR)/freebsd_amd64
FREEBSD_BUILD_DIR_AMD64_POSIX=$(FREEBSD_BUILD_DIR_AMD64)/posix
FREEBSD_BUILD_DIR_AMD64_COMMON=$(FREEBSD_BUILD_DIR_AMD64)/common

TARGET_DIR=../resources

#DEBUG_FLAGS=-ggdb -g3
DEBUG_FLAGS=-g0

WINDOWS_CFLAGS=-O3 $(DEBUG_FLAGS) -Werror -I. -I$(WINDOWS_JDK)/include -I$(WINDOWS_JDK)/include/win32

LINUX_CFLAGS=-O3 $(DEBUG_FLAGS) -Werror -I. -I$(LINUX_JDK)/include -I$(LINUX_JDK)/include/linux -fPIC $(LINUX_ADDITIONAL_CC_FLAGS)

#TODO ADD OPTIMIZE LATER
FREEBSD_CFLAGS=-I. -I$(FREEBSD_JDK)/include -I$(FREEBSD_JDK)/include/freebsd -fPIC

WINDOWS_LIBS=-lhid -lsetupapi -liphlpapi

LINUX_LIBS=-lrt -lc

FREEBSD_LIBS=-lc

COMMON_SOURCES=$(shell find common -name "*.c")
COMMON_HEADERS=$(shell find common -name "*.h")
POSIX_SOURCES=$(shell find posix -name "*.c")
POSIX_HEADERS=$(shell find posix -name "*.h")
WINDOWS_SOURCES=$(shell find windows -name "*.c")
WINDOWS_HEADERS=$(shell find windows -name "*.h")
LINUX_SOURCES=$(shell find linux -name "*.c")
LINUX_HEADERS=$(shell find linux -name "*.h")
FREEBSD_SOURCES=$(shell find freebsd -name "*.c")
FREEBSD_HEADERS=$(shell find freebsd -name "*.h")

WINDOWS_OBJECTS_AMD64=$(addprefix $(WINDOWS_BUILD_DIR_AMD64)/,$(patsubst %.c,%.o,$(notdir $(WINDOWS_SOURCES)))) $(addprefix $(WINDOWS_BUILD_DIR_AMD64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))
WINDOWS_OBJECTS_I386=$(addprefix $(WINDOWS_BUILD_DIR_I386)/,$(patsubst %.c,%.o,$(notdir $(WINDOWS_SOURCES)))) $(addprefix $(WINDOWS_BUILD_DIR_I386_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))

LINUX_OBJECTS_AMD64=$(addprefix $(LINUX_BUILD_DIR_AMD64)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AMD64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AMD64_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_AMD64_MUSL=$(addprefix $(LINUX_BUILD_DIR_AMD64_MUSL)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AMD64_MUSL_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AMD64_MUSL_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_I386=$(addprefix $(LINUX_BUILD_DIR_I386)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_I386_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_I386_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_ARMHF=$(addprefix $(LINUX_BUILD_DIR_ARMHF)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_ARMHF_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_ARMHF_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_ARMEL=$(addprefix $(LINUX_BUILD_DIR_ARMEL)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_ARMEL_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_ARMEL_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_AARCH64=$(addprefix $(LINUX_BUILD_DIR_AARCH64)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AARCH64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AARCH64_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_RISCV64=$(addprefix $(LINUX_BUILD_DIR_RISCV64)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_RISCV64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_RISCV64_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_MIPS64EL=$(addprefix $(LINUX_BUILD_DIR_MIPS64EL)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_MIPS64EL_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_MIPS64EL_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_PPC64LE=$(addprefix $(LINUX_BUILD_DIR_PPC64LE)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_PPC64LE_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_PPC64LE_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))
LINUX_OBJECTS_S390X=$(addprefix $(LINUX_BUILD_DIR_S390X)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_S390X_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_S390X_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))


FREEBSD_OBJECTS_AMD64=$(addprefix $(FREEBSD_BUILD_DIR_AMD64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES)))) $(addprefix $(FREEBSD_BUILD_DIR_AMD64_POSIX)/,$(patsubst %.c,%.o,$(notdir $(POSIX_SOURCES))))

#######################################################################################################################
# FREEBSD AMD 64
#######################################################################################################################

$(FREEBSD_BUILD_DIR_AMD64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for freebsd amd64"
	@mkdir -p $(FREEBSD_BUILD_DIR_AMD64_COMMON)
	$(FREEBSD_CC_AMD64) -c -o $@ $< $(FREEBSD_CFLAGS)

$(FREEBSD_BUILD_DIR_AMD64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for freebsd amd64"
	@mkdir -p $(FREEBSD_BUILD_DIR_AMD64_COMMON)
	$(FREEBSD_CC_AMD64) -c -o $@ $< $(FREEBSD_CFLAGS)

$(FREEBSD_BUILD_DIR_AMD64_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for freebsd amd64"
	@mkdir -p $(FREEBSD_BUILD_DIR_AMD64_POSIX)
	$(FREEBSD_CC_AMD64) -c -o $@ $< $(FREEBSD_CFLAGS)

$(FREEBSD_BUILD_DIR_AMD64_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for freebsd amd64"
	@mkdir -p $(FREEBSD_BUILD_DIR_AMD64_POSIX)
	$(FREEBSD_CC_AMD64) -c -o $@ $< $(FREEBSD_CFLAGS)

$(FREEBSD_BUILD_DIR_AMD64)/%.o: freebsd/%.c $(COMMON_HEADERS) $(POSIX_HEADERS) $(FREEBSD_HEADERS)
	@echo "Compiling freebsd file $@ for amd64"
	@mkdir -p $(FREEBSD_BUILD_DIR_AMD64)
	$(FREEBSD_CC_AMD64) -c -o $@ $< $(FREEBSD_CFLAGS)

$(FREEBSD_BUILD_DIR_AMD64)/%.o: freebsd/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS) $(FREEBSD_HEADERS)
	@echo "Compiling freebsd file $@ for amd64"
	@mkdir -p $(FREEBSD_BUILD_DIR_AMD64)
	$(FREEBSD_CC_AMD64) -c -o $@ $< $(FREEBSD_CFLAGS)

#######################################################################################################################
# WINDOWS AMD 64
#######################################################################################################################

$(WINDOWS_BUILD_DIR_AMD64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64_COMMON)
	$(WINDOWS_CC_AMD64) -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_AMD64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64_COMMON)
	$(WINDOWS_CC_AMD64) -c -o $@ $< $(WINDOWS_CFLAGS)


$(WINDOWS_BUILD_DIR_AMD64)/%.o: windows/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64)
	$(WINDOWS_CC_AMD64) -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_AMD64)/%.o: windows/**/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64)
	$(WINDOWS_CC_AMD64) -c -o $@ $< $(WINDOWS_CFLAGS)

#######################################################################################################################
# WINDOWS I386
#######################################################################################################################

$(WINDOWS_BUILD_DIR_I386_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386_COMMON)
	$(WINDOWS_CC_I386) -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_I386_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386_COMMON)
	$(WINDOWS_CC_I386) -c -o $@ $< $(WINDOWS_CFLAGS)


$(WINDOWS_BUILD_DIR_I386)/%.o: windows/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386)
	$(WINDOWS_CC_I386) -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_I386)/%.o: windows/**/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386)
	$(WINDOWS_CC_I386) -c -o $@ $< $(WINDOWS_CFLAGS)

#######################################################################################################################
# LINUX AMD 64
#######################################################################################################################

$(LINUX_BUILD_DIR_AMD64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_COMMON)
	$(LINUX_CC_AMD64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_COMMON)
	$(LINUX_CC_AMD64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_POSIX)
	$(LINUX_CC_AMD64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_POSIX)
	$(LINUX_CC_AMD64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64)
	$(LINUX_CC_AMD64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64)
	$(LINUX_CC_AMD64) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX AMD 64 musl
#######################################################################################################################

$(LINUX_BUILD_DIR_AMD64_MUSL_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux amd64 musl"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_MUSL_COMMON)
	$(LINUX_CC_AMD64_MUSL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_MUSL_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux amd64 musl"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_MUSL_COMMON)
	$(LINUX_CC_AMD64_MUSL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_MUSL_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux amd64 musl"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_MUSL_POSIX)
	$(LINUX_CC_AMD64_MUSL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_MUSL_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux amd64 musl"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_MUSL_POSIX)
	$(LINUX_CC_AMD64_MUSL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_MUSL)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for amd64 musl"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_MUSL)
	$(LINUX_CC_AMD64_MUSL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_MUSL)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for amd64 musl"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_MUSL)
	$(LINUX_CC_AMD64_MUSL) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX I386
#######################################################################################################################

$(LINUX_BUILD_DIR_I386_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386_COMMON)
	$(LINUX_CC_I386) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386_COMMON)
	$(LINUX_CC_I386) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386_POSIX)
	$(LINUX_CC_I386) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386_POSIX)
	$(LINUX_CC_I386) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386)
	$(LINUX_CC_I386) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386)
	$(LINUX_CC_I386) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX ARMHF
#######################################################################################################################

$(LINUX_BUILD_DIR_ARMHF_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF_COMMON)
	$(LINUX_CC_ARMHF) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF_COMMON)
	$(LINUX_CC_ARMHF) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF_POSIX)
	$(LINUX_CC_ARMHF) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF_POSIX)
	$(LINUX_CC_ARMHF) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF)
	$(LINUX_CC_ARMHF) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF)
	$(LINUX_CC_ARMHF) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX ARMEL
#######################################################################################################################

$(LINUX_BUILD_DIR_ARMEL_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux armel"
	@mkdir -p $(LINUX_BUILD_DIR_ARMEL_COMMON)
	$(LINUX_CC_ARMEL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMEL_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux armel"
	@mkdir -p $(LINUX_BUILD_DIR_ARMEL_COMMON)
	$(LINUX_CC_ARMEL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMEL_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux armel"
	@mkdir -p $(LINUX_BUILD_DIR_ARMEL_POSIX)
	$(LINUX_CC_ARMEL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMEL_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux armel"
	@mkdir -p $(LINUX_BUILD_DIR_ARMEL_POSIX)
	$(LINUX_CC_ARMEL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMEL)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for armel"
	@mkdir -p $(LINUX_BUILD_DIR_ARMEL)
	$(LINUX_CC_ARMEL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMEL)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for armel"
	@mkdir -p $(LINUX_BUILD_DIR_ARMEL)
	$(LINUX_CC_ARMEL) -c -o $@ $< $(LINUX_CFLAGS)


#######################################################################################################################
# LINUX AARCH64
#######################################################################################################################

$(LINUX_BUILD_DIR_AARCH64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64_COMMON)
	$(LINUX_CC_AARCH64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64_COMMON)
	$(LINUX_CC_AARCH64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_POSIX)
	$(LINUX_CC_AARCH64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64_POSIX)
	$(LINUX_CC_AARCH64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64_POSIX)
	$(LINUX_CC_AARCH64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64)
	$(LINUX_CC_AARCH64) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX RISCV64
#######################################################################################################################

$(LINUX_BUILD_DIR_RISCV64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux riscv64"
	@mkdir -p $(LINUX_BUILD_DIR_RISCV64_COMMON)
	$(LINUX_CC_RISCV64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_RISCV64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux riscv64"
	@mkdir -p $(LINUX_BUILD_DIR_RISCV64_COMMON)
	$(LINUX_CC_RISCV64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_RISCV64_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux riscv64"
	@mkdir -p $(LINUX_BUILD_DIR_RISCV64_POSIX)
	$(LINUX_CC_RISCV64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_RISCV64_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux riscv64"
	@mkdir -p $(LINUX_BUILD_DIR_RISCV64_POSIX)
	$(LINUX_CC_RISCV64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_RISCV64)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for riscv64"
	@mkdir -p $(LINUX_BUILD_DIR_RISCV64)
	$(LINUX_CC_RISCV64) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_RISCV64)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for riscv64"
	@mkdir -p $(LINUX_BUILD_DIR_RISCV64)
	$(LINUX_CC_RISCV64) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX MIPS64EL
#######################################################################################################################

$(LINUX_BUILD_DIR_MIPS64EL_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux mips64el"
	@mkdir -p $(LINUX_BUILD_DIR_MIPS64EL_COMMON)
	$(LINUX_CC_MIPS64EL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_MIPS64EL_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux mips64el"
	@mkdir -p $(LINUX_BUILD_DIR_MIPS64EL_COMMON)
	$(LINUX_CC_MIPS64EL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_MIPS64EL_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_MIPS64EL_POSIX)
	$(LINUX_CC_MIPS64EL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_MIPS64EL_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_MIPS64EL_POSIX)
	$(LINUX_CC_MIPS64EL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_MIPS64EL)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for mips64el"
	@mkdir -p $(LINUX_BUILD_DIR_MIPS64EL)
	$(LINUX_CC_MIPS64EL) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_MIPS64EL)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for mips64el"
	@mkdir -p $(LINUX_BUILD_DIR_MIPS64EL)
	$(LINUX_CC_MIPS64EL) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX PPC64LE
#######################################################################################################################

$(LINUX_BUILD_DIR_PPC64LE_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux ppc64le"
	@mkdir -p $(LINUX_BUILD_DIR_PPC64LE_COMMON)
	$(LINUX_CC_PPC64LE) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_PPC64LE_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux ppc64le"
	@mkdir -p $(LINUX_BUILD_DIR_PPC64LE_COMMON)
	$(LINUX_CC_PPC64LE) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_PPC64LE_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux ppc64le"
	@mkdir -p $(LINUX_BUILD_DIR_PPC64LE_POSIX)
	$(LINUX_CC_PPC64LE) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_PPC64LE_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux ppc64le"
	@mkdir -p $(LINUX_BUILD_DIR_PPC64LE_POSIX)
	$(LINUX_CC_PPC64LE) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_PPC64LE)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for ppc64le"
	@mkdir -p $(LINUX_BUILD_DIR_PPC64LE)
	$(LINUX_CC_PPC64LE) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_PPC64LE)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for ppc64le"
	@mkdir -p $(LINUX_BUILD_DIR_PPC64LE)
	$(LINUX_CC_PPC64LE) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX S390X
#######################################################################################################################

$(LINUX_BUILD_DIR_S390X_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux s390x"
	@mkdir -p $(LINUX_BUILD_DIR_S390X_COMMON)
	$(LINUX_CC_S390X) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_S390X_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux s390x"
	@mkdir -p $(LINUX_BUILD_DIR_S390X_COMMON)
	$(LINUX_CC_S390X) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_S390X_POSIX)/%.o: posix/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux s390x"
	@mkdir -p $(LINUX_BUILD_DIR_S390X_POSIX)
	$(LINUX_CC_S390X) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_S390X_POSIX)/%.o: posix/**/%.c $(COMMON_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling posix file $@ for linux s390x"
	@mkdir -p $(LINUX_BUILD_DIR_S390X_POSIX)
	$(LINUX_CC_S390X) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_S390X)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for s390x"
	@mkdir -p $(LINUX_BUILD_DIR_S390X)
	$(LINUX_CC_S390X) -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_S390X)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS) $(POSIX_HEADERS)
	@echo "Compiling linux file $@ for s390x"
	@mkdir -p $(LINUX_BUILD_DIR_S390X)
	$(LINUX_CC_S390X) -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# Targets
#######################################################################################################################

all: windows_amd64 windows_i386 linux_amd64 linux_amd64_musl linux_i386 linux_armhf linux_armel linux_aarch64 linux_riscv64 linux_mips64el linux_ppc64le linux_s390x
	rm -rf $(BUILD_BASE_DIR)
	@echo "DONE"

windows_amd64: $(WINDOWS_OBJECTS_AMD64)
	@echo ""
	@echo "Linking windows dynamic linker library for amd64"
	@mkdir -p $(TARGET_DIR)
	$(WINDOWS_CC_AMD64) -shared -o $(TARGET_DIR)/java_native_utils_amd64.dll $(WINDOWS_OBJECTS_AMD64) $(WINDOWS_LIBS)
	@echo ""

windows_i386: $(WINDOWS_OBJECTS_I386)
	@echo ""
	@echo "Linking windows dynamic linker library for i386"
	@mkdir -p $(TARGET_DIR)
	$(WINDOWS_CC_I386) -Wl,--export-all-symbols -Wl,--add-stdcall-alias -m32 -shared -o $(TARGET_DIR)/java_native_utils_i386.dll $(WINDOWS_OBJECTS_I386) $(WINDOWS_LIBS)
	@echo ""

linux_amd64: $(LINUX_OBJECTS_AMD64)
	@echo ""
	@echo "Linking linux shared object for amd64"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_AMD64) -shared -o $(TARGET_DIR)/java_native_utils_amd64.so $(LINUX_OBJECTS_AMD64) $(LINUX_LIBS)
	@echo ""

linux_amd64_musl: $(LINUX_OBJECTS_AMD64_MUSL)
	@echo ""
	@echo "Linking linux shared object for amd64 musl"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_AMD64_MUSL) -shared -o $(TARGET_DIR)/java_native_utils_amd64_musl.so $(LINUX_OBJECTS_AMD64_MUSL) $(LINUX_LIBS)
	@echo ""

linux_i386: $(LINUX_OBJECTS_I386)
	@echo ""
	@echo "Linking linux shared object for i386"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_I386) -shared -o $(TARGET_DIR)/java_native_utils_i386.so $(LINUX_OBJECTS_I386) $(LINUX_LIBS)
	@echo ""

linux_armhf: $(LINUX_OBJECTS_ARMHF)
	@echo ""
	@echo "Linking linux shared object for armhf"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_ARMHF) -shared -o $(TARGET_DIR)/java_native_utils_armhf.so $(LINUX_OBJECTS_ARMHF) $(LINUX_LIBS)
	@echo ""

linux_armel: $(LINUX_OBJECTS_ARMEL)
	@echo ""
	@echo "Linking linux shared object for armel"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_ARMEL) -shared -o $(TARGET_DIR)/java_native_utils_armel.so $(LINUX_OBJECTS_ARMEL) $(LINUX_LIBS)
	@echo ""

linux_aarch64: $(LINUX_OBJECTS_AARCH64)
	@echo ""
	@echo "Linking linux shared object for aarch64"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_AARCH64) -shared -o $(TARGET_DIR)/java_native_utils_aarch64.so $(LINUX_OBJECTS_AARCH64) $(LINUX_LIBS)
	@echo ""

linux_riscv64: $(LINUX_OBJECTS_RISCV64)
	@echo ""
	@echo "Linking linux shared object for riscv64"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_RISCV64) -shared -o $(TARGET_DIR)/java_native_utils_riscv64.so $(LINUX_OBJECTS_RISCV64) $(LINUX_LIBS)
	@echo ""

linux_mips64el: $(LINUX_OBJECTS_MIPS64EL)
	@echo ""
	@echo "Linking linux shared object for mips64el"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_MIPS64EL) -shared -o $(TARGET_DIR)/java_native_utils_mips64el.so $(LINUX_OBJECTS_MIPS64EL) $(LINUX_LIBS)
	@echo ""

linux_ppc64le: $(LINUX_OBJECTS_PPC64LE)
	@echo ""
	@echo "Linking linux shared object for ppc64le"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_PPC64LE) -shared -o $(TARGET_DIR)/java_native_utils_ppc64le.so $(LINUX_OBJECTS_PPC64LE) $(LINUX_LIBS)
	@echo ""

linux_s390x: $(LINUX_OBJECTS_S390X)
	@echo ""
	@echo "Linking linux shared object for s390x"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_S390X) -shared -o $(TARGET_DIR)/java_native_utils_s390x.so $(LINUX_OBJECTS_S390X) $(LINUX_LIBS)
	@echo ""

freebsd: $(FREEBSD_OBJECTS_AMD64)
	@echo ""
	@echo "Linking freebsd shared object for amd64"
	@mkdir -p $(TARGET_DIR)
	$(FREEBSD_CC_AMD64) -shared -o $(TARGET_DIR)/java_native_utils_amd64_freebsd.so $(FREEBSD_OBJECTS_AMD64) $(FREEBSD_LIBS)
	@echo ""

clean:
	rm -rf $(TARGET_DIR)/java_native_utils_i386.dll
	rm -rf $(TARGET_DIR)/java_native_utils_amd64.dll
	rm -rf $(TARGET_DIR)/java_native_utils_amd64.so
	rm -rf $(TARGET_DIR)/java_native_utils_amd64_musl.so
	rm -rf $(TARGET_DIR)/java_native_utils_i386.so
	rm -rf $(TARGET_DIR)/java_native_utils_armhf.so
	rm -rf $(TARGET_DIR)/java_native_utils_armel.so
	rm -rf $(TARGET_DIR)/java_native_utils_aarch64.so
	rm -rf $(TARGET_DIR)/java_native_utils_riscv64.so
	rm -rf $(TARGET_DIR)/java_native_utils_mips64el.so
	rm -rf $(TARGET_DIR)/java_native_utils_ppc64le.so
	rm -rf $(TARGET_DIR)/java_native_utils_s390x.so
	rm -rf $(TARGET_DIR)/java_native_utils_amd64_freebsd.so
	rm -rf $(BUILD_BASE_DIR)
	@echo "DONE"

info:
	@echo "INFO"
	@echo "Linux compiler $(LINUX_CC_AMD64)"
	@echo "Windows compiler $(WINDOWS_CC_AMD64)"
	@echo "Linux JDK Path $(LINUX_JDK)"
	@echo "Windows JDK Path $(WINDOWS_JDK)"
	@echo "Common Sources $(COMMON_SOURCES)"
	@echo "Common Headers $(COMMON_HEADERS)"
	@echo "Windows Sources $(WINDOWS_SOURCES)"
	@echo "Windows Headers $(WINDOWS_HEADERS)"
	@echo "Linux Sources $(LINUX_SOURCES)"
	@echo "Linux Headers $(LINUX_HEADERS)"
	@echo "Windows Objects $(WINDOWS_OBJECTS_AMD64)"
	@echo "Linux Objects $(LINUX_OBJECTS_AMD64)"


.PHONY: clean
