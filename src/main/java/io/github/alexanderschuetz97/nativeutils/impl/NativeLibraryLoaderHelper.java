//
// Copyright Alexander Schütz, 2021
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
package io.github.alexanderschuetz97.nativeutils.impl;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * Utility to load the native libraries. It can be used to unpack the .so/.dll files from the jar and load them into the jvm.
 * If you wish to manually load the native libraries by other means then don't use it otherwise call loadNativeLibraries before
 * using JavaNativeUtils.
 */
public class NativeLibraryLoaderHelper {

    private static final int EXPECTED_NATIVE_LIB_VERSION = 0;

    /**
     * Flag to indicate if already loaded.
     */
    private static volatile boolean loaded = false;

    /**
     * Will load the native libraries if necessary.
     * If the loading fails then a LinkageError is thrown.
     * This method will use the temporary directory to unpack the .dll/.so files (this is necessary as native libraries
     * cannot be loaded from inside the jar) On Windows this is %TEMP% on linux this is /tmp.
     *
     * @throws LinkageError
     */
    public static void loadNativeLibraries() throws LinkageError {
        loadNativeLibraries(System.getProperty("java.io.tmpdir"));
    }

    /**
     * Will load the native libraries if necessary.
     * If the loading fails then a LinkageError is thrown.
     * The given path will be used as a directory to unpack the native libraries to.
     * If the directory at the given path does not exist it will be created.
     * If that fails that fails a LinkageError is thrown.
     *
     * @throws LinkageError
     */
    public synchronized static void loadNativeLibraries(String aPath) throws LinkageError {
        if (loaded) {
            return;
        }

        boolean tempSuccess = false;
        long tempVersion = -1;

        try {
            tempVersion = getNativeLibVersion();
            tempSuccess = true;
        } catch (UnsatisfiedLinkError err) {

        }

        if (tempSuccess && tempVersion == EXPECTED_NATIVE_LIB_VERSION) {
            loaded = true;
            return;
        }

        if (tempSuccess && tempVersion != EXPECTED_NATIVE_LIB_VERSION) {
            throw new UnsatisfiedLinkError("Wrong java_native_utils lib version was loaded expected " + EXPECTED_NATIVE_LIB_VERSION + " got " + tempVersion);
        }

        if (aPath == null) {
            throw new UnsatisfiedLinkError("Temporary file path to unpack native libraries to is null!");
        }

        File tempFile = new File(aPath);

        if (!tempFile.exists()) {
            tempFile.mkdirs();
        }

        if (!tempFile.exists() || !tempFile.isDirectory()) {
            throw new UnsatisfiedLinkError("Temporary file path doesnt exist and cannot be created! Path: " + tempFile.getAbsolutePath());
        }

        String tempArch = System.getProperty("os.arch");

        if (tempArch == null) {
            throw new UnsatisfiedLinkError("Cannot load native libraries because the processor architecture couldn't be detected!");
        }

        tempArch = tempArch.toLowerCase();

        if (tempArch.equals("arm")) {
            tempArch = "armhf";
        }

        String tempOS = System.getProperty("os.name");
        if (tempOS == null) {
            throw new UnsatisfiedLinkError("Cannot load native libraries because the operating system couldn't be detected!");
        }

        tempOS = tempOS.toLowerCase();
        try {
            if (tempOS.contains("linux")) {
                if (!"i386".equals(tempArch) && !"amd64".equals(tempArch) && !"armhf".equals(tempArch) && !"aarch64".equals(tempArch)) {
                    throw new UnsatisfiedLinkError("Processor architecture is not i386 amd64 or armhf and thus not supported! Value: " + tempArch);
                }
                loadLib(tempFile, "java_native_utils_" + tempArch + ".so");
            } else if (tempOS.contains("windows")) {
                if (!"i386".equals(tempArch) && !"amd64".equals(tempArch)) {
                    throw new UnsatisfiedLinkError("Processor architecture is not i386 amd64 and thus not supported! Value: " + tempArch);
                }
                loadLib(tempFile, "java_native_utils_" + tempArch + ".dll");
            } else {
                throw new UnsatisfiedLinkError("Operating system is not windows or linux and thus not supported!");
            }
        } catch (IOException e) {
            throw new LinkageError("IO Error while writing native library to a temporary file!", e);
        } catch (Exception e) {
            throw new LinkageError("Error while loading native library!", e);
        }

        tempVersion = getNativeLibVersion();
        if (tempVersion != EXPECTED_NATIVE_LIB_VERSION) {
            throw new UnsatisfiedLinkError("Wrong java_native_utils lib version was loaded expected " + EXPECTED_NATIVE_LIB_VERSION + " got " + tempVersion);
        }

        loaded = true;
    }


    private static void loadLib(File aBase, String aLibName) throws IOException {
        File tempLibFile = new File(aBase, aLibName);
        StringBuilder tempBuilder = new StringBuilder();
        while (tempLibFile.exists()) {
            tempBuilder.append('X');
            tempLibFile = new File(aBase, tempBuilder.toString() + aLibName);
        }

        if (!tempLibFile.createNewFile()) {
            throw new IOException("Could not createOrOpen temporary library file!");
        }

        tempLibFile.deleteOnExit();

        FileOutputStream tempFaos = new FileOutputStream(tempLibFile);

        byte[] tempBuf = new byte[512];

        InputStream tempInput = NativeLibraryLoaderHelper.class.getResourceAsStream("/" + aLibName);
        if (tempInput == null) {
            throw new IOException("The shared library file " + aLibName + " was not found by getResourceAsStream " +
                    "its either not there or this class was loaded by a classloader that doesnt support resources well!");
        }
        int i = 0;
        while (i != -1) {
            i = tempInput.read(tempBuf);
            if (i > 0) {
                tempFaos.write(tempBuf, 0, i);
            }
        }

        tempFaos.flush();
        tempFaos.close();
        tempInput.close();

        System.load(tempLibFile.getAbsolutePath());
        tempLibFile.delete();
    }

    static native long getNativeLibVersion();
}
