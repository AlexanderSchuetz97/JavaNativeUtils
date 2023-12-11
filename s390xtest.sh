#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../s390x
docker compose up --build --exit-code-from java-native-utils-test-s390x
