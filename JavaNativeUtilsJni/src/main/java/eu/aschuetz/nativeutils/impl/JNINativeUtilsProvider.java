//
// Copyright Alexander Schütz, 2021-2024
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
        } else if ("netbsd".equalsIgnoreCase(tempOS)) {
            return new JNINetBSDNativeUtil();
        } else if ("openbsd".equalsIgnoreCase(tempOS)) {
            return new JNIOpenBSDNativeUtil();
        } else if ("mac os x".equalsIgnoreCase(tempOS)) {
            return new JNIMacOSNativeUtil();
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
