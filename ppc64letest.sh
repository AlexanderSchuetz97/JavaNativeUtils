#!/usr/bin/env bash
set -e
cd JavaNativeUtilsTest/docker/amd64

cd ../ppc64le
docker compose up --build --exit-code-from java-native-utils-test-ppc64le
