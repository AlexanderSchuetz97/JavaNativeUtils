#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../amd64_musl
docker compose up --build --exit-code-from java-native-utils-test-amd64-musl
