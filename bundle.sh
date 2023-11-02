#!/usr/bin/env bash
rm bundle1.jar
rm bundle2.jar
rm bundle3.jar

cd target
jar -cvf bundle1.jar JavaNative*
mv bundle1.jar ..
cd ..

cd JavaNativeUtilsApi/target/
jar -cvf bundle2.jar JavaNative*
mv bundle2.jar ../..
cd ../..


cd JavaNativeUtilsJni/target/
jar -cvf bundle3.jar JavaNative*
mv bundle3.jar ../..
cd ../..


