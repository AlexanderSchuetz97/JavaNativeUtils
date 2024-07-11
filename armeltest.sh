#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../armel
docker compose up --build --exit-code-from java-native-utils-test-armel