package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.FreeBSDNativeUtil;
import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtil;

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
