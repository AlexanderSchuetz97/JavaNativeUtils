#!/usr/bin/env bash

set -e

/jdk/bin/java -Xint -XX:ErrorFile=/project/java_error%p.log -jar /project/JavaNativeUtilsTest/target/JavaNativeUtilsTest-*-jar-with-dependencies.jar