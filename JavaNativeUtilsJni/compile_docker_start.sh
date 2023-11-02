#!/usr/bin/env bash
cd docker
docker-compose up --build --exit-code-from java-native-utils-builder

