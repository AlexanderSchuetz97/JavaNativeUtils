#!/usr/bin/env bash
#
# Copyright Alexander Schütz, 2021-2022
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
cd /src
export JAVAH_COMMAND="javah -encoding utf-8"
export LINUX_CC_AMD64=/usr/bin/x86_64-linux-gnu-gcc
export LINUX_CC_I386=/usr/bin/i686-linux-gnu-gcc
export LINUX_CC_ARMHF=/usr/bin/arm-linux-gnueabihf-gcc
export LINUX_CC_AARCH64=/usr/bin/aarch64-linux-gnu-gcc
export LINUX_JDK=/usr/lib/jvm/java-8-openjdk-amd64
export WINDOWS_CC_AMD64=/usr/bin/x86_64-w64-mingw32-gcc-win32
export WINDOWS_CC_I386=/usr/bin/i686-w64-mingw32-gcc
export WINDOWS_JDK=/windowsJDK/jdk8u292-b10
export BUILD_TARGETS="all"
#windows_amd64 windows_i386
export LINUX_ADDITIONAL_CC_FLAGS="-D_FILE_OFFSET_BITS=64"
#Cleanup
rm -rf src/main/native/common/jni
mkdir -p src/main/native/common/jni
rm -f src/main/resources/*.dll
rm -f src/main/resources/*.so


#Building headers
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.NativeLibraryLoaderHelper
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNILinuxNativeUtil
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNICommonNativeUtil
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNIWindowsNativeUtil
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNINativeField
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNINativeMemory
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNINativeMethod

chmod -R 777 src/main/native/common/jni

cd src/main/native
make clean

make -j 12 $BUILD_TARGETS
cd ../resources/

#Container creates them as "root" this may cause issues...
chmod 777 *.so
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

if [[ $BUILD_TARGETS == *"linux_aarch64"* ]] || [[ $BUILD_TARGETS == "all" ]]; then
    if [ -f java_native_utils_armhf.so ]; then
        echo "Building the linux aarch64 so succeeded"
    else
        echo "Building the linux aarch64 so failed!"
        exit -1
    fi
fi

cp -r * ../../../target/classes


cd ../../../
