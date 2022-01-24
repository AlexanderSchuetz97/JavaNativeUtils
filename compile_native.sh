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



echo "Building the native libraries for JavaNativeUtils"

#load config
if [ -f config.sh ]
then
source config.sh
else
echo "Configuration file not found, this project requires a windows jdk and a linux jdk in order to build"
echo "Because of this, you will have to manually specify the path to both jdk homes in the file config.sh"
echo "This file will now be created, edit it, input your paths and then try again"
touch config.sh
echo "#!/usr/bin/env bash" > config.sh
echo "#You may want to change this to use the javah command from the LINUX_JDK if your system jdk is not the same as your LINUX_JDK" >> config.sh
echo "export JAVAH_COMMAND=javah" >> config.sh
echo "#If you are running a normal 64 bit linux change this to just gcc if you dont have gcc multi-lib installed" >> config.sh
echo "export LINUX_CC_AMD64=/usr/bin/x86_64-linux-gnu-gcc" >> config.sh
echo "export LINUX_CC_I386=/usr/bin/i686-linux-gnu-gcc" >> config.sh
echo "export LINUX_CC_ARMHF=/usr/bin/arm-linux-gnueabihf-gcc" >> config.sh
echo "export LINUX_CC_AARCH64=/usr/bin/aarch64-linux-gnu-gcc" >> config.sh
echo "export LINUX_JDK=" >> config.sh
echo "#You will have to change this unless you are using mingw-cross to compile the windows dll" >> config.sh
echo "export WINDOWS_CC_AMD64=/usr/bin/x86_64-w64-mingw32-gcc-win32" >> config.sh
echo "export WINDOWS_CC_I386=/usr/bin/i686-w64-mingw32-gcc" >> config.sh
echo "export WINDOWS_JDK=" >> config.sh
echo "#You may change this to any combination of the following: \"windows_amd64 windows_i386 linux_amd64 linux_i386 linux_armhf linux_aarch64\"" >> config.sh
echo "export BUILD_TARGETS=\"all\"" >> config.sh
echo "#-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -fno-stack-protector are added to prevent dependencies to new GLIBC versions. This makes the build more portable to older systems. If you dont care about this remove this." >> config.sh
echo "export LINUX_ADDITIONAL_CC_FLAGS=\"-U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0 -fno-stack-protector\"" >> config.sh
chmod +x config.sh
exit -1
fi

#Cleanup
rm -rf src/main/native/common/jni
mkdir -p src/main/native/common/jni
rm -f src/main/resources/*.dll
rm -f src/main/resources/*.so
rm -f src/main/native_src.tar
rm -f src/resources/native_src.tar

#Building headers
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.NativeLibraryLoaderHelper
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNILinuxNativeUtil
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNICommonNativeUtil
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNIWindowsNativeUtil
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNINativeField
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNINativeMemory
$JAVAH_COMMAND -cp src/main/java -d src/main/native/common/jni io.github.alexanderschuetz97.nativeutils.impl.JNINativeMethod

cd src/main/native
make clean

make $BUILD_TARGETS
cd ../resources/

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


cd ../../../
