#!/usr/bin/env bash
echo "Building the freebsd native libraries for JavaNativeUtils using Docker"
cd /project/JavaNativeUtilsJni/

export FREEBSD_JDK="/freebsdjdk/openjdk7"

export FREEBSD_CC_AMD64="clang -target x86_64-pc-freebsd --sysroot /freebsd"

export NETBSD_JDK="/netbsdjdk/java/openjdk21"
export NETBSD_CC_AMD64="clang -target x86_64-pc-netbsd --sysroot /netbsd"



cd src/main/native
make freebsd netbsd
cd ../resources/
chmod 777 *.so

if [ -f java_native_utils_amd64_freebsd.so ]; then
    echo "Building the freebsd amd64 so succeeded"
else
    echo "Building the freebsd amd64 so failed!"
    exit -1
fi

if [ -f java_native_utils_amd64_netbsd.so ]; then
    echo "Building the netbsd amd64 so succeeded"
else
    echo "Building the netbsd amd64 so failed!"
    exit -1
fi

