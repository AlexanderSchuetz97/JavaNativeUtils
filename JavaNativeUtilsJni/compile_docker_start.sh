#!/usr/bin/env bash
cd docker
docker compose up --build --exit-code-from java-native-utils-builder
cd freebsd
docker compose up --build --exit-code-from java-native-utils-builder-freebsd

cd ..
cd ..

cd src/main/resources
cp -r * ../../../target/classes
cd ../../..
