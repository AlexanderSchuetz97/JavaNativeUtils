FROM mips64le/debian:bookworm

RUN apt-get -y update && apt-get -y install openjdk-17-jdk build-essential
RUN useradd -ms /bin/bash user
USER user