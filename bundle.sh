#!/usr/bin/env bash
VERSION=$1

# Fucking maven plugin no longer makes this shit, and the "new" plugin doesnt work fuck, there was no need to change this shit ffs
cd target
rm *.md5
rm *.sha1
md5sum JavaNativeUtils-$VERSION.pom | awk '{print $1}' > JavaNativeUtils-$VERSION.pom.md5
sha1sum JavaNativeUtils-$VERSION.pom | awk '{print $1}' > JavaNativeUtils-$VERSION.pom.sha1

cd ..
cd JavaNativeUtilsJni/target
rm *.md5
rm *.sha1
md5sum JavaNativeUtilsJni-$VERSION.pom | awk '{print $1}' > JavaNativeUtilsJni-$VERSION.pom.md5
sha1sum JavaNativeUtilsJni-$VERSION.pom | awk '{print $1}' > JavaNativeUtilsJni-$VERSION.pom.sha1

md5sum JavaNativeUtilsJni-$VERSION.jar | awk '{print $1}' > JavaNativeUtilsJni-$VERSION.jar.md5
sha1sum JavaNativeUtilsJni-$VERSION.jar | awk '{print $1}' > JavaNativeUtilsJni-$VERSION.jar.sha1

md5sum JavaNativeUtilsJni-$VERSION-sources.jar | awk '{print $1}' > JavaNativeUtilsJni-$VERSION-sources.jar.md5
sha1sum JavaNativeUtilsJni-$VERSION-sources.jar | awk '{print $1}' > JavaNativeUtilsJni-$VERSION-sources.jar.sha1

md5sum JavaNativeUtilsJni-$VERSION-javadoc.jar | awk '{print $1}' > JavaNativeUtilsJni-$VERSION-javadoc.jar.md5
sha1sum JavaNativeUtilsJni-$VERSION-javadoc.jar | awk '{print $1}' > JavaNativeUtilsJni-$VERSION-javadoc.jar.sha1

cd ../..

cd JavaNativeUtilsApi/target
rm *.md5
rm *.sha1
md5sum JavaNativeUtilsApi-$VERSION.pom | awk '{print $1}' > JavaNativeUtilsApi-$VERSION.pom.md5
sha1sum JavaNativeUtilsApi-$VERSION.pom | awk '{print $1}' > JavaNativeUtilsApi-$VERSION.pom.sha1

md5sum JavaNativeUtilsApi-$VERSION.jar | awk '{print $1}' > JavaNativeUtilsApi-$VERSION.jar.md5
sha1sum JavaNativeUtilsApi-$VERSION.jar | awk '{print $1}' > JavaNativeUtilsApi-$VERSION.jar.sha1

md5sum JavaNativeUtilsApi-$VERSION-sources.jar | awk '{print $1}' > JavaNativeUtilsApi-$VERSION-sources.jar.md5
sha1sum JavaNativeUtilsApi-$VERSION-sources.jar | awk '{print $1}' > JavaNativeUtilsApi-$VERSION-sources.jar.sha1

md5sum JavaNativeUtilsApi-$VERSION-javadoc.jar | awk '{print $1}' > JavaNativeUtilsApi-$VERSION-javadoc.jar.md5
sha1sum JavaNativeUtilsApi-$VERSION-javadoc.jar | awk '{print $1}' > JavaNativeUtilsApi-$VERSION-javadoc.jar.sha1
cd ../..

rm -rf deploy
mkdir -p deploy/eu/aschuetz/JavaNativeUtils/$VERSION
cp target/JavaNative* deploy/eu/aschuetz/JavaNativeUtils/$VERSION/

mkdir -p deploy/eu/aschuetz/JavaNativeUtilsApi/$VERSION
cp JavaNativeUtilsApi/target/JavaNative* deploy/eu/aschuetz/JavaNativeUtilsApi/$VERSION/

mkdir -p deploy/eu/aschuetz/JavaNativeUtilsJni/$VERSION
cp JavaNativeUtilsJni/target/JavaNative* deploy/eu/aschuetz/JavaNativeUtilsJni/$VERSION/

cd deploy
zip -r b.zip eu