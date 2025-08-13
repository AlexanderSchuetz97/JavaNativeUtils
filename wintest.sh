#!/usr/bin/env bash
ssh win10@10.6.0.209 "rd /s /q E:\\code\\jnu"
ssh win10@10.6.0.209 "mkdir E:\\code\\jnu"
scp -r ./JavaNativeUtilsTest/target/JavaNativeUtilsTest-4.9-jar-with-dependencies.jar win10@10.6.0.209:/E:/code/jnu
ssh win10@10.6.0.209 "java -jar E:\\code\\jnu\\JavaNativeUtilsTest-4.9-jar-with-dependencies.jar $1"
