//
// Copyright Alexander Schütz, 2021-2022
//
// This file is part of JavaNativeUtils.
//
// JavaNativeUtils is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JavaNativeUtils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// A copy of the GNU Lesser General Public License should be provided
// in the COPYING & COPYING.LESSER files in top level directory of JavaNativeUtils.
// If not, see <https://www.gnu.org/licenses/>.
//
package eu.aschuetz.nativeutils.api;

import java.util.*;

public final class NativeUtils {

    private static NativeUtil instance;
    private static NativeUtilsProvider provider;

    /**
     * Useful for testing/debugging.
     */
    public static void set(NativeUtil instance) {
        NativeUtils.instance = instance;
    }

    /**
     * Useful for testing/debugging.
     */
    public static void setProvider(NativeUtilsProvider instance) {
        NativeUtils.provider = instance;
        NativeUtils.instance = null;
    }


    public static boolean isWindows() {
        return get().isWindows();
    }

    public static boolean isLinux() {
        return get().isLinux();
    }

    public static boolean isJVM() {
        return get().isJVM();
    }

    public static boolean isFreeBSD() {
        return get().isFreeBSD();
    }

    public static boolean isNetBSD() {
        return get().isNetBSD();
    }

    public static boolean isPosix() {
        return get().isPosix();
    }

    public static JVMNativeUtil getJVMUtil() {
        NativeUtil util = get();
        if (util instanceof JVMNativeUtil) {
            return (JVMNativeUtil) util;
        }

        throw new UnsupportedOperationException("JVM functions not supported.");
    }

    public static LinuxNativeUtil getLinuxUtil() {
        NativeUtil util = get();
        if (util instanceof LinuxNativeUtil) {
            return (LinuxNativeUtil) util;
        }

        throw new UnsupportedOperationException("Linux functions not supported.");
    }

    public static WindowsNativeUtil getWindowsUtil() {
        NativeUtil util = get();
        if (util instanceof WindowsNativeUtil) {
            return (WindowsNativeUtil) util;
        }

        throw new UnsupportedOperationException("Windows functions not supported.");
    }

    public static FreeBSDNativeUtil getFreeBSDUtil() {
        NativeUtil util = get();
        if (util instanceof FreeBSDNativeUtil) {
            return (FreeBSDNativeUtil) util;
        }

        throw new UnsupportedOperationException("FreeBSD functions not supported.");
    }

    public static NetBSDNativeUtil getNetBSDUtil() {
        NativeUtil util = get();
        if (util instanceof NetBSDNativeUtil) {
            return (NetBSDNativeUtil) util;
        }

        throw new UnsupportedOperationException("NetBSD functions not supported.");
    }

    public static PosixNativeUtil getPosixUtil() {
        NativeUtil util = get();
        if (util instanceof PosixNativeUtil) {
            return (PosixNativeUtil) util;
        }

        throw new UnsupportedOperationException("Posix functions not supported.");
    }

    static NativeUtilsProvider getProvider() {
        if (provider != null) {
            return provider;
        }

        ClassLoader loaderToUse = Thread.currentThread().getContextClassLoader();
        if (loaderToUse == null) {
            loaderToUse = NativeUtils.class.getClassLoader();
        }

        ServiceLoader<NativeUtilsProvider> providers = ServiceLoader.load(NativeUtilsProvider.class, loaderToUse);
        List<NativeUtilsProvider> enabled = new ArrayList<>();
        for (NativeUtilsProvider provider : providers) {
            if (provider.isEnabled()) {
                enabled.add(provider);
            }
        }

        if (enabled.isEmpty()) {
            System.err.println("No NativeUtilsProvider is loaded and enabled. There is a classpath issue. Will not do anything...");
            return null;
        }

        if (enabled.size() != 1) {
            System.err.println("Multiple NativeUtilsProvider are loaded and enabled. There is a classpath issue. Will not do anything...");
            return null;
        }


        provider = enabled.get(0);
        return provider;
    }

    /**
     * Gets the current instance of NativeUtil
     */
    public static NativeUtil get() {
        //I know we may make multiple instances if this is called in multi threading but no one cares about that.
        if (instance != null) {
            return instance;
        }

        NativeUtilsProvider theProvider = getProvider();
        if (theProvider == null) {
            instance = new NoopNativeUtil();
            return instance;
        }
        NativeUtil theUtil = theProvider.get();
        if (theUtil == null) {
            System.err.println("NativeUtilsProvider.get() returned null!");
            instance = new NoopNativeUtil();
            return instance;
        }

        instance = theUtil;
        return instance;
    }

    /**
     * Helper method to get all shared lib binaries in a map.
     * If you know what platform you are developing for then you may write the byte[] to disk with the appropriate name
     * and then call {@link System#load(String)} with the absolute path to the file on the disk.
     *
     * Afterwards call {@link NativeUtils#set(NativeUtil)} with null as parameter to force it to detect the loaded library.
     *
     * Note that "loading" the library more than once will cause issues. Only do this if you know for sure that
     * the library has not been loaded automatically, or you know for sure that loading automatically has failed
     * (Can be detected by calling {@link #get()} and then checking for {@link NativeUtil#isNoop()} returns true.
     * It only returns true if automatic loading has failed. The cause for this is most likely due to running on an unsupported
     * platform such as Apple OSX. In that case this method will not help you either...
     */
    public static Map<String, byte[]> getNativeLibraryBinaries() {
        NativeUtilsProvider provider = getProvider();
        if (provider == null) {
            return Collections.emptyMap();
        }

        return provider.getNativeLibraryBinaries();
    }


}

