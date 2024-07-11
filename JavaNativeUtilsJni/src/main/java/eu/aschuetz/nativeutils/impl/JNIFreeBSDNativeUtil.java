package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.FreeBSDNativeUtil;

public class JNIFreeBSDNativeUtil extends JNIPosixNativeUtil implements FreeBSDNativeUtil {
    @Override
    public boolean isWindows() {
        return false;
    }

    @Override
    public boolean isLinux() {
        return false;
    }

    @Override
    public boolean isFreeBSD() {
        return true;
    }
}
