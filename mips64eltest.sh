#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../mips64el
docker compose up --build --exit-code-from java-native-utils-test-mips64el
