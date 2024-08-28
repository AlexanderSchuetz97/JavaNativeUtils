package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.NetBSDNativeUtil;

public class JNINetBSDNativeUtil extends JNIPosixNativeUtil implements NetBSDNativeUtil {
    @Override
    public boolean isLinux() {
        return false;
    }

    @Override
    public boolean isFreeBSD() {
        return false;
    }

    @Override
    public boolean isNetBSD() {
        return true;
    }
}
