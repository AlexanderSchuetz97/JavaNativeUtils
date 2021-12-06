#
# Copyright Alexander Schütz, 2021
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

BUILD_BASE_DIR=build

WINDOWS_BUILD_DIR_AMD64=$(BUILD_BASE_DIR)/windows_amd64
WINDOWS_BUILD_DIR_AMD64_COMMON=$(WINDOWS_BUILD_DIR_AMD64)/common

WINDOWS_BUILD_DIR_I386=$(BUILD_BASE_DIR)/windows_i386
WINDOWS_BUILD_DIR_I386_COMMON=$(WINDOWS_BUILD_DIR_I386)/common

LINUX_BUILD_DIR_AMD64=$(BUILD_BASE_DIR)/linux_amd64
LINUX_BUILD_DIR_AMD64_COMMON=$(LINUX_BUILD_DIR_AMD64)/common

LINUX_BUILD_DIR_I386=$(BUILD_BASE_DIR)/linux_i386
LINUX_BUILD_DIR_I386_COMMON=$(LINUX_BUILD_DIR_I386)/common

LINUX_BUILD_DIR_ARMHF=$(BUILD_BASE_DIR)/linux_armhf
LINUX_BUILD_DIR_ARMHF_COMMON=$(LINUX_BUILD_DIR_ARMHF)/common

LINUX_BUILD_DIR_AARCH64=$(BUILD_BASE_DIR)/linux_aarch64
LINUX_BUILD_DIR_AARCH64_COMMON=$(LINUX_BUILD_DIR_AARCH64)/common

TARGET_DIR=../resources

WINDOWS_CFLAGS=-I. -I$(WINDOWS_JDK)/include -I$(WINDOWS_JDK)/include/win32

LINUX_CFLAGS=-I. -I$(LINUX_JDK)/include -I$(LINUX_JDK)/include/linux -fPIC $(LINUX_ADDITIONAL_CC_FLAGS)

WINDOWS_LIBS =-lhid -lsetupapi


COMMON_SOURCES=$(shell find common -name "*.c")
COMMON_HEADERS=$(shell find common -name "*.h")
WINDOWS_SOURCES=$(shell find windows -name "*.c")
WINDOWS_HEADERS=$(shell find windows -name "*.h")
LINUX_SOURCES=$(shell find linux -name "*.c")
LINUX_HEADERS=$(shell find linux -name "*.h")

WINDOWS_OBJECTS_AMD64=$(addprefix $(WINDOWS_BUILD_DIR_AMD64)/,$(patsubst %.c,%.o,$(notdir $(WINDOWS_SOURCES)))) $(addprefix $(WINDOWS_BUILD_DIR_AMD64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))
WINDOWS_OBJECTS_I386=$(addprefix $(WINDOWS_BUILD_DIR_I386)/,$(patsubst %.c,%.o,$(notdir $(WINDOWS_SOURCES)))) $(addprefix $(WINDOWS_BUILD_DIR_I386_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))

LINUX_OBJECTS_AMD64=$(addprefix $(LINUX_BUILD_DIR_AMD64)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AMD64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))
LINUX_OBJECTS_I386=$(addprefix $(LINUX_BUILD_DIR_I386)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_I386_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))
LINUX_OBJECTS_ARMHF=$(addprefix $(LINUX_BUILD_DIR_ARMHF)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_ARMHF_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))
LINUX_OBJECTS_AARCH64=$(addprefix $(LINUX_BUILD_DIR_AARCH64)/,$(patsubst %.c,%.o,$(notdir $(LINUX_SOURCES)))) $(addprefix $(LINUX_BUILD_DIR_AARCH64_COMMON)/,$(patsubst %.c,%.o,$(notdir $(COMMON_SOURCES))))

#######################################################################################################################
# WINDOWS AMD 64
#######################################################################################################################

$(WINDOWS_BUILD_DIR_AMD64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64_COMMON)
	$(WINDOWS_CC_AMD64) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_AMD64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64_COMMON)
	$(WINDOWS_CC_AMD64) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)


$(WINDOWS_BUILD_DIR_AMD64)/%.o: windows/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64)
	$(WINDOWS_CC_AMD64) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_AMD64)/%.o: windows/**/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for amd64"
	@mkdir -p $(WINDOWS_BUILD_DIR_AMD64)
	$(WINDOWS_CC_AMD64) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)

#######################################################################################################################
# WINDOWS I386
#######################################################################################################################

$(WINDOWS_BUILD_DIR_I386_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386_COMMON)
	$(WINDOWS_CC_I386) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_I386_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for windows i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386_COMMON)
	$(WINDOWS_CC_I386) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)


$(WINDOWS_BUILD_DIR_I386)/%.o: windows/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386)
	$(WINDOWS_CC_I386) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)

$(WINDOWS_BUILD_DIR_I386)/%.o: windows/**/%.c $(COMMON_HEADERS) $(WINDOWS_HEADERS)
	@echo "Compiling windows file $@ for i386"
	@mkdir -p $(WINDOWS_BUILD_DIR_I386)
	$(WINDOWS_CC_I386) -O3 -c -o $@ $< $(WINDOWS_CFLAGS)

#######################################################################################################################
# LINUX AMD 64
#######################################################################################################################

$(LINUX_BUILD_DIR_AMD64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_COMMON)
	$(LINUX_CC_AMD64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64_COMMON)
	$(LINUX_CC_AMD64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64)
	$(LINUX_CC_AMD64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AMD64)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for amd64"
	@mkdir -p $(LINUX_BUILD_DIR_AMD64)
	$(LINUX_CC_AMD64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX I386
#######################################################################################################################

$(LINUX_BUILD_DIR_I386_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386_COMMON)
	$(LINUX_CC_I386) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386_COMMON)
	$(LINUX_CC_I386) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386)
	$(LINUX_CC_I386) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_I386)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for i386"
	@mkdir -p $(LINUX_BUILD_DIR_I386)
	$(LINUX_CC_I386) -O3 -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX ARMHF
#######################################################################################################################

$(LINUX_BUILD_DIR_ARMHF_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF_COMMON)
	$(LINUX_CC_ARMHF) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF_COMMON)
	$(LINUX_CC_ARMHF) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF)
	$(LINUX_CC_ARMHF) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_ARMHF)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for armhf"
	@mkdir -p $(LINUX_BUILD_DIR_ARMHF)
	$(LINUX_CC_ARMHF) -O3 -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# LINUX AARCH64
#######################################################################################################################

$(LINUX_BUILD_DIR_AARCH64_COMMON)/%.o: common/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64_COMMON)
	$(LINUX_CC_AARCH64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64_COMMON)/%.o: common/**/%.c $(COMMON_HEADERS)
	@echo "Compiling common file $@ for linux aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64_COMMON)
	$(LINUX_CC_AARCH64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64)/%.o: linux/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64)
	$(LINUX_CC_AARCH64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

$(LINUX_BUILD_DIR_AARCH64)/%.o: linux/**/%.c $(COMMON_HEADERS) $(LINUX_HEADERS)
	@echo "Compiling linux file $@ for aarch64"
	@mkdir -p $(LINUX_BUILD_DIR_AARCH64)
	$(LINUX_CC_AARCH64) -O3 -c -o $@ $< $(LINUX_CFLAGS)

#######################################################################################################################
# Targets
#######################################################################################################################

all: windows_amd64 windows_i386 linux_amd64 linux_i386 linux_armhf linux_aarch64
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
	$(WINDOWS_CC_I386) -shared -o $(TARGET_DIR)/java_native_utils_i386.dll $(WINDOWS_OBJECTS_I386) $(WINDOWS_LIBS)
	@echo ""

linux_amd64: $(LINUX_OBJECTS_AMD64)
	@echo ""
	@echo "Linking linux shared object for amd64"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_AMD64) -shared -o $(TARGET_DIR)/java_native_utils_amd64.so $(LINUX_OBJECTS_AMD64)
	@echo ""

linux_i386: $(LINUX_OBJECTS_I386)
	@echo ""
	@echo "Linking linux shared object for i386"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_I386) -shared -o $(TARGET_DIR)/java_native_utils_i386.so $(LINUX_OBJECTS_I386)
	@echo ""

linux_armhf: $(LINUX_OBJECTS_ARMHF)
	@echo ""
	@echo "Linking linux shared object for armhf"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_ARMHF) -shared -o $(TARGET_DIR)/java_native_utils_armhf.so $(LINUX_OBJECTS_ARMHF)
	@echo ""

linux_aarch64: $(LINUX_OBJECTS_AARCH64)
	@echo ""
	@echo "Linking linux shared object for aarch64"
	@mkdir -p $(TARGET_DIR)
	$(LINUX_CC_AARCH64) -shared -o $(TARGET_DIR)/java_native_utils_aarch64.so $(LINUX_OBJECTS_AARCH64)
	@echo ""


clean:
	rm -rf $(TARGET_DIR)/java_native_utils_i386.dll
	rm -rf $(TARGET_DIR)/java_native_utils_amd64.dll
	rm -rf $(TARGET_DIR)/java_native_utils_amd64.so
	rm -rf $(TARGET_DIR)/java_native_utils_i386.so
	rm -rf $(TARGET_DIR)/java_native_utils_armhf.so
	rm -rf $(TARGET_DIR)/java_native_utils_aarch64.so
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
