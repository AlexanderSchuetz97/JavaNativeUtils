#!/usr/bin/env bash
#
# Copyright Alexander Schütz, 2021-2024
#
# This file is part of JavaNativeUtils.
#
# JavaNativeUtils is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# JavaNativeUtils is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# A copy of the GNU General Public License should be provided
# in the COPYING file in top level directory of JavaNativeUtils.
# If not, see <https://www.gnu.org/licenses/>.
#



echo "Building the native libraries for JavaNativeUtils using Docker"
cd /project/JavaNativeUtilsJni/
export JAVAH_COMMAND="javah -encoding utf-8"
export LINUX_CC_AMD64=/usr/bin/x86_64-linux-gnu-gcc
export LINUX_CC_AMD64_MUSL=/x86_64-linux-musl-cross/bin/x86_64-linux-musl-gcc
export LINUX_CC_I386=/usr/bin/i686-linux-gnu-gcc
export LINUX_CC_ARMHF=/usr/bin/arm-linux-gnueabihf-gcc
export LINUX_CC_ARMEL=/usr/bin/arm-linux-gnueabi-gcc
export LINUX_CC_AARCH64=/usr/bin/aarch64-linux-gnu-gcc
export LINUX_CC_RISCV64=/usr/bin/riscv64-linux-gnu-gcc
export LINUX_CC_MIPS64EL=/usr/bin/mips64el-linux-gnuabi64-gcc
export LINUX_CC_PPC64LE=/usr/bin/powerpc64le-linux-gnu-gcc
export LINUX_CC_S390X=/usr/bin/s390x-linux-gnu-gcc

export MACOS_CC_AMD64="/zig/zig-linux-x86_64-0.13.0/zig cc -target x86_64-macos"

export LINUX_JDK=/usr/lib/jvm/java-8-openjdk-amd64
export WINDOWS_CC_AMD64=/usr/bin/x86_64-w64-mingw32-gcc-win32
export WINDOWS_CC_I386=/usr/bin/i686-w64-mingw32-gcc
export WINDOWS_JDK=/windowsJDK/jdk8u292-b10
export MACOS_JDK=/macJDK/jdk8u292-b10/Contents/Home


export LINUX_ADDITIONAL_CC_FLAGS="-D_FILE_OFFSET_BITS=64"
export BUILD_TARGETS="all"
#export BUILD_TARGETS="linux_riscv64"
#export BUILD_TARGETS="linux_aarch64"
#export BUILD_TARGETS="windows_amd64"
#windows_amd64 windows_i386
#Cleanup
rm -rf src/main/native/common/jni
mkdir -p src/main/native/common/jni
rm -f src/main/resources/*.dll
rm -f src/main/resources/*.so
rm -f src/main/resources/*.dynlib



#Building headers
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.NativeLibraryLoaderHelper
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.JNILinuxNativeUtil
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.JNICommonNativeUtil
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.JNIWindowsNativeUtil
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.JNINativeField
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.JNINativeMemory
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.JNINativeMethod
$JAVAH_COMMAND -cp /project/JavaNativeUtilsJni/src/main/java:/project/JavaNativeUtilsApi/src/main/java -d src/main/native/common/jni eu.aschuetz.nativeutils.impl.JNIPosixNativeUtil

chmod -R 777 src/main/native/common/jni

cd src/main/native
make clean

make -j 12 $BUILD_TARGETS
cd ../resources/

#Container creates them as "root" this may cause issues...
chmod 777 *.so
chmod 777 *.dynlib
chmod 777 *.dll

#Confirm success

if [[ $BUILD_TARGETS == *"windows_amd64"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_amd64.dll ]; then
        echo "Building the windows amd64 dll succeeded"
    else
        echo "Building the windows amd64 dll failed!"
        exit -1
    fi
fi


if [[ $BUILD_TARGETS == *"windows_i386"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_i386.dll ]; then
        echo "Building the windows i386 dll succeeded"
    else
        echo "Building the windows i386 dll failed!"
        exit -1
    fi
fi


if [[ $BUILD_TARGETS == *"linux_amd64"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_amd64.so ]; then
        echo "Building the linux amd64 so succeeded"
    else
        echo "Building the linux amd64 so failed!"
        exit -1
    fi
fi

if [[ $BUILD_TARGETS == *"linux_amd64_musl"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_amd64_musl.so ]; then
        echo "Building the linux amd64 musl so succeeded"
    else
        echo "Building the linux amd64 musl so failed!"
        exit -1
    fi
fi



if [[ $BUILD_TARGETS == *"linux_i386"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_i386.so ]; then
        echo "Building the linux i386 so succeeded"
    else
        echo "Building the linux i386 so failed!"
        exit -1
    fi
fi

if [[ $BUILD_TARGETS == *"linux_armhf"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_armhf.so ]; then
        echo "Building the linux armhf so succeeded"
    else
        echo "Building the linux armhf so failed!"
        exit -1
    fi
fi

if [[ $BUILD_TARGETS == *"linux_armel"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_armel.so ]; then
        echo "Building the linux armel so succeeded"
    else
        echo "Building the linux armel so failed!"
        exit -1
    fi
fi

if [[ $BUILD_TARGETS == *"linux_aarch64"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_aarch64.so ]; then
        echo "Building the linux aarch64 so succeeded"
    else
        echo "Building the linux aarch64 so failed!"
        exit -1
    fi
fi

if [[ $BUILD_TARGETS == *"linux_riscv64"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_riscv64.so ]; then
        echo "Building the linux riscv64 so succeeded"
    else
        echo "Building the linux riscv64 so failed!"
        exit -1
    fi
fi

if [[ $BUILD_TARGETS == *"linux_mips64el"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_mips64el.so ]; then
        echo "Building the linux mips64el so succeeded"
    else
        echo "Building the linux mips64el so failed!"
        exit -1
    fi
fi


if [[ $BUILD_TARGETS == *"linux_ppc64le"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_ppc64le.so ]; then
        echo "Building the linux ppc64le so succeeded"
    else
        echo "Building the linux ppc64le so failed!"
        exit -1
    fi
fi


if [[ $BUILD_TARGETS == *"linux_s390x"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_s390x.so ]; then
        echo "Building the linux s390x so succeeded"
    else
        echo "Building the linux s390x so failed!"
        exit -1
    fi
fi

if [[ $BUILD_TARGETS == *"macos_amd64"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_amd64.dynlib ]; then
        echo "Building the macos amd64 dynlib succeeded"
    else
        echo "Building the macos amd64 dynlib failed!"
        exit -1
    fi
fi


cd ../../../
