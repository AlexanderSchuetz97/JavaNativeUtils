#!/usr/bin/env bash
ssh -p 9922 $1 "rm -rf /tmp/jnu-code"
ssh -p 9922 $1 "mkdir /tmp/jnu-code"
scp -P 9922 -r ./JavaNativeUtilsTest/target/JavaNativeUtilsTest-4.6-jar-with-dependencies.jar $1:/tmp/jnu-code
ssh -p 9922 $1 "java -jar -Xmx128M /tmp/jnu-code/JavaNativeUtilsTest-4.6-jar-with-dependencies.jar $2"
