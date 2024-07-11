#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../amd64
docker compose up --build --exit-code-from java-native-utils-test-amd64

cd ../amd64_musl
docker compose up --build --exit-code-from java-native-utils-test-amd64-musl

cd ../i386
docker compose up --build --exit-code-from java-native-utils-test-i386

cd ../riscv64
docker compose up --build --exit-code-from java-native-utils-test-risc64

cd ../aarch64
docker compose up --build --exit-code-from java-native-utils-test-aarch64

cd ../armhf
docker compose up --build --exit-code-from java-native-utils-test-armhf

cd ../armel
docker compose up --build --exit-code-from java-native-utils-test-armel

cd ../mips64el
docker compose up --build --exit-code-from java-native-utils-test-mips64el

cd ../ppc64le
docker compose up --build --exit-code-from java-native-utils-test-ppc64le

cd ../s390x
docker compose up --build --exit-code-from java-native-utils-test-s390x
