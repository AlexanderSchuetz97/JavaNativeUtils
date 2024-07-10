package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.structs.Stat;

public abstract class JNIPosixNativeUtil extends JNICommonNativeUtil {

    public native Stat stat(String path);
}
