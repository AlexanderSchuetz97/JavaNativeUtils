FROM ppc64le/debian:bookworm

RUN mkdir /jdk
RUN apt-get -y update && apt-get -y install wget bzip2

RUN cd /jdk && wget https://anaconda.org/powerai/java-openjdk-ppc64le/1.8.0_202/download/linux-ppc64le/java-openjdk-ppc64le-1.8.0_202-0.tar.bz2
RUN cd /jdk && tar -xvf java-openjdk-ppc64le-1.8.0_202-0.tar.bz2

RUN useradd -ms /bin/bash user
USER user