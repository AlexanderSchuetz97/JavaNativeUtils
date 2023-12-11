FROM amd64/alpine:latest

RUN apk add wget bash build-base
RUN wget https://github.com/adoptium/temurin21-binaries/releases/download/jdk-21.0.1%2B12/OpenJDK21U-jdk_x64_alpine-linux_hotspot_21.0.1_12.tar.gz
RUN tar -xzf OpenJDK21U-jdk_x64_alpine-linux_hotspot_21.0.1_12.tar.gz

RUN adduser user --disabled-password

USER user