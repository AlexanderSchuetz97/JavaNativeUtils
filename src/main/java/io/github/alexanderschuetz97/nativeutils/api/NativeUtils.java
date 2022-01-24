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


}

