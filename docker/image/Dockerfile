FROM ubuntu:18.04

RUN apt-get -y update
RUN apt-get -y install wget unzip build-essential gcc-mingw-w64 openjdk-8-jdk gcc-mingw-w64-i686 gcc-mingw-w64-x86-64 gcc-i686-linux-gnu gcc-arm-linux-gnueabihf gcc-aarch64-linux-gnu
RUN mkdir /windowsJDK
RUN cd /windowsJDK && wget https://github.com/AdoptOpenJDK/openjdk8-binaries/releases/download/jdk8u292-b10/OpenJDK8U-jdk_x64_windows_hotspot_8u292b10.zip
RUN cd /windowsJDK && unzip *.zip

