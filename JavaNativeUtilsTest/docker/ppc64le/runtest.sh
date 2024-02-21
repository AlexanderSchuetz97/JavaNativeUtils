#!/usr/bin/env bash

set -e

/jdk/bin/java -Xmx32m -Xint -XX:ErrorFile=/project/java_error%p.log -jar /project/JavaNativeUtilsTest/target/JavaNativeUtilsTest-*-jar-with-dependencies.jar