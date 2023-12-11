#!/usr/bin/env bash
ssh $1 "rm -rf /tmp/jnu-code"
ssh $1 "mkdir /tmp/jnu-code"
scp -r ./JavaNativeUtilsTest/target/JavaNativeUtilsTest-4.2-jar-with-dependencies.jar $1:/tmp/jnu-code
ssh $1 "java -jar /tmp/jnu-code/JavaNativeUtilsTest-4.2-jar-with-dependencies.jar"
