#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../amd64
docker compose up --build --exit-code-from java-native-utils-test-amd64
