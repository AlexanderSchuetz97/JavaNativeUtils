#!/usr/bin/env bash

set -e

/jdk/jdk-11.0.21+9/bin/java -Xmx32m -Xint -XX:ErrorFile=/project/java_error%p.log -jar /project/JavaNativeUtilsTest/target/JavaNativeUtilsTest-*-jar-with-dependencies.jar