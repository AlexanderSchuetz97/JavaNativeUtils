FROM ppc64le/debian:bookworm

RUN mkdir /jdk
RUN apt-get -y update && apt-get -y install wget bzip2 build-essential

#This link died, the offical openjdk from debian doesnt install due to a qemu usermode bug...
#This jdk did work but since the link died i have just added the file to the repo...
#RUN cd /jdk && wget https://anaconda.org/powerai/java-openjdk-ppc64le/1.8.0_202/download/linux-ppc64le/java-openjdk-ppc64le-1.8.0_202-0.tar.bz2
ADD linux-ppc64le_java-openjdk-ppc64le-1.8.0_202-0.tar.bz2 /jdk
#RUN cd /jdk && tar -xvf java-openjdk-ppc64le-1.8.0_202-0.tar.bz2

RUN useradd -ms /bin/bash user
USER user