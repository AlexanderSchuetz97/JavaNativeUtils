package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.*;
import eu.aschuetz.nativeutils.api.consts.DefaultLinuxConstProvider;
import eu.aschuetz.nativeutils.api.consts.LinuxConstProvider;

import java.util.Map;

public class JNINativeUtilsProvider implements NativeUtilsProvider {


    @Override
    public Map<String, byte[]> getNativeLibraryBinaries() {
        return NativeLibraryLoaderHelper.getNativeLibraryBinaries();
    }

    @Override
    public NativeUtil get() {
        try {
            NativeLibraryLoaderHelper.loadNativeLibraries();
        } catch (LinkageError err) {
            System.err.println("Failed to load native library for NativeUtils.");
            err.printStackTrace();
            return new NoopNativeUtil();
        }


        String tempOS = System.getProperty("os.name");
        if (tempOS == null) {
            System.err.println("System property os.name is null");
            return new NoopNativeUtil();
        }

        tempOS = tempOS.toLowerCase();

        if (tempOS.contains("linux")) {
            return new JNILinuxNativeUtil();

        } else if (tempOS.contains("windows")) {
            return new JNIWindowsNativeUtil();
        } else if ("freebsd".equalsIgnoreCase(tempOS)) {
            return new JNIFreeBSDNativeUtil();
        } else {
            return new NoopNativeUtil();
        }
    }

    @Override
    public boolean isEnabled() {
        if ("true".equals(System.getProperty("eu.aschuetz.nativeutils.impl.JNINativeUtilsProvider.disable"))) {
            return false;
        }
        return true;
    }
}
