FROM debian:bookworm

RUN apt-get -y update && apt-get -y install wget unzip build-essential clang
RUN mkdir /freebsd && cd /freebsd && wget http://ftp-archive.freebsd.org/pub/FreeBSD-Archive/old-releases/amd64/14.1-RELEASE/base.txz && tar -xvf base.txz
RUN mkdir /netbsd && cd /netbsd && wget http://ftp.netbsd.org/pub/NetBSD/NetBSD-10.0/amd64/binary/sets/base.tar.xz && tar -xvf base.tar.xz
RUN cd /netbsd && wget http://ftp.netbsd.org/pub/NetBSD/NetBSD-10.0/amd64/binary/sets/comp.tar.xz && tar -xvf comp.tar.xz
RUN mkdir /openbsd && cd /openbsd && wget https://cdn.openbsd.org/pub/OpenBSD/7.7/amd64/base77.tgz && tar -xvf base77.tgz
RUN cd /openbsd && wget https://cdn.openbsd.org/pub/OpenBSD/7.7/amd64/comp77.tgz && tar -xvf comp77.tgz
RUN mkdir /freebsdjdk && cd /freebsdjdk && wget http://ftp-archive.freebsd.org/pub/FreeBSD-Archive/ports/amd64/packages-9.2-release/java/openjdk-7.25.15.tbz && tar -xvf openjdk-7.25.15.tbz
RUN mkdir /netbsdjdk && cd /netbsdjdk && wget https://cdn.netbsd.org/pub/pkgsrc/packages/NetBSD/x86_64/10.0_2025Q1/All/openjdk21-1.21.0.5.11.tgz && tar -xvf openjdk21-1.21.0.5.11.tgz
RUN mkdir /openbsdjdk && cd /openbsdjdk && wget https://cdn.openbsd.org/pub/OpenBSD/7.7/packages/amd64/jdk-21.0.6.7.1v0.tgz && tar -xvf jdk-21.0.6.7.1v0.tgz