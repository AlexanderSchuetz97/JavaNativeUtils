#!/usr/bin/env bash

set -e

/usr/bin/env java -Xmx32m -XX:ErrorFile=/project/java_error%p.log -jar /project/JavaNativeUtilsTest/target/JavaNativeUtilsTest-*-jar-with-dependencies.jar