FROM s390x/debian:bookworm

RUN mkdir /jdk
RUN apt-get -y update && apt-get -y install wget bzip2 build-essential

RUN cd /jdk && wget https://github.com/adoptium/temurin11-binaries/releases/download/jdk-11.0.21%2B9/OpenJDK11U-jdk_s390x_linux_hotspot_11.0.21_9.tar.gz
RUN cd /jdk && tar -xvf OpenJDK11U-jdk_s390x_linux_hotspot_11.0.21_9.tar.gz

RUN useradd -ms /bin/bash user
USER user


