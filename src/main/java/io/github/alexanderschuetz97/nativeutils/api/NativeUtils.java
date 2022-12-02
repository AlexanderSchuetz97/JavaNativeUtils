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
package io.github.alexanderschuetz97.nativeutils.api;

import io.github.alexanderschuetz97.nativeutils.impl.NativeLibraryLoaderHelper;
import io.github.alexanderschuetz97.nativeutils.impl.NoopNativeUtil;
import io.github.alexanderschuetz97.nativeutils.impl.JNILinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.impl.JNIWindowsNativeUtil;

import java.util.Map;

public final class NativeUtils {

    private static NativeUtil instance;

    /**
     * Useful for testing/debugging.
     */
    public static void set(NativeUtil instance) {
        NativeUtils.instance = instance;
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
    /**
     * Gets the current instance of NativeUtil
     */
    public static NativeUtil get() {
        //I know we may make multiple instances if this is called in multi threading but no one cares about that.
        if (instance != null) {
            return instance;
        }

        try {
            NativeLibraryLoaderHelper.loadNativeLibraries();
        } catch (LinkageError err) {
            System.err.println("Failed to load native library for NativeUtils.");
            err.printStackTrace();
            instance = new NoopNativeUtil();
            return instance;
        }


        String tempOS = System.getProperty("os.name");
        if (tempOS == null) {
            instance = new NoopNativeUtil();
            return instance;
        }

        tempOS = tempOS.toLowerCase();

        if (tempOS.contains("linux")) {
            instance = new JNILinuxNativeUtil();
        } else if (tempOS.contains("windows")) {
           instance = new JNIWindowsNativeUtil();
        } else {
           instance = new NoopNativeUtil();
        }

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
        return NativeLibraryLoaderHelper.getNativeLibraryBinaries();
    }


}

