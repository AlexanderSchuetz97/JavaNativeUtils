#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../armhf
docker compose up --build --exit-code-from java-native-utils-test-armhf
