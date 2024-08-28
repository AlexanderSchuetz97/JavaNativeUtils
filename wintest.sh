#!/usr/bin/env bash
ssh win10@192.168.100.160 "rd /s /q E:\\code\\jnu"
ssh win10@192.168.100.160 "mkdir E:\\code\\jnu"
scp -r ./JavaNativeUtilsTest/target/JavaNativeUtilsTest-4.7-jar-with-dependencies.jar win10@192.168.100.160:/E:/code/jnu
ssh win10@192.168.100.160 "java -jar E:\\code\\jnu\\JavaNativeUtilsTest-4.7-jar-with-dependencies.jar $1"
