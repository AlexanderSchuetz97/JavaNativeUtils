#!/usr/bin/env bash
echo "Building the freebsd native libraries for JavaNativeUtils using Docker"
cd /project/JavaNativeUtilsJni/

export FREEBSD_JDK="/freebsdjdk/openjdk7"

export FREEBSD_CC_AMD64="clang -target x86_64-pc-freebsd --sysroot /freebsd"



cd src/main/native
make freebsd
cd ../resources/
chmod 777 *.so

if [ -f java_native_utils_amd64_freebsd.so ]; then
    echo "Building the freebsd amd64 so succeeded"
else
    echo "Building the freebsd amd64 so failed!"
    exit -1
fi
