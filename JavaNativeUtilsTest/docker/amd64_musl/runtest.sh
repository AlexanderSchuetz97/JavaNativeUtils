#!/usr/bin/env bash

set -e

/jdk-21.0.1+12/bin/java -XX:ErrorFile=/project/java_error%p.log -jar /project/JavaNativeUtilsTest/target/JavaNativeUtilsTest-*-jar-with-dependencies.jar