FROM debian:bookworm

RUN apt-get -y update && apt-get -y install wget unzip build-essential clang
RUN mkdir /freebsd && cd /freebsd && wget https://download.freebsd.org/releases/amd64/14.1-RELEASE/base.txz && tar -xvf base.txz
RUN mkdir /freebsdjdk && cd /freebsdjdk && wget http://ftp-archive.freebsd.org/pub/FreeBSD-Archive/ports/amd64/packages-9.2-release/java/openjdk-7.25.15.tbz && tar -xvf openjdk-7.25.15.tbz
