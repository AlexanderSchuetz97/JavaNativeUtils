FROM ubuntu:18.04

RUN apt-get -y update && apt-get -y install wget unzip build-essential gcc-mingw-w64 openjdk-8-jdk gcc-mingw-w64-i686 gcc-mingw-w64-x86-64 gcc-powerpc64le-linux-gnu gcc-mips64el-linux-gnuabi64 gcc-i686-linux-gnu gcc-arm-linux-gnueabihf gcc-mips64-linux-gnuabi64 gcc-arm-linux-gnueabi gcc-powerpc-linux-gnu gcc-s390x-linux-gnu gcc-aarch64-linux-gnu gcc-riscv64-linux-gnu
RUN mkdir /windowsJDK
RUN cd /windowsJDK && wget https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u292-b10/OpenJDK8U-jdk_x64_windows_hotspot_8u292b10.zip
RUN cd /windowsJDK && unzip *.zip
RUN wget https://musl.cc/x86_64-linux-musl-cross.tgz && tar -xvzf x86_64-linux-musl-cross.tgz
