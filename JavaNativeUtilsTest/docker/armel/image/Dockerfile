FROM arm32v5/debian:bookworm

RUN apt-get -y update && apt-get -y install openjdk-17-jdk
RUN useradd -ms /bin/bash user
USER user