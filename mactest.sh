#!/usr/bin/env bash
ssh $1 "rm -rf /tmp/jnu-code"
ssh $1 "mkdir /tmp/jnu-code"
scp -r ./JavaNativeUtilsTest/target/JavaNativeUtilsTest-4.8-jar-with-dependencies.jar $1:/tmp/jnu-code
ssh $1 "/opt/jdk-21.0.5+11/Contents/Home/bin/java -jar -Xmx128M /tmp/jnu-code/JavaNativeUtilsTest-4.8-jar-with-dependencies.jar $2 $3"
