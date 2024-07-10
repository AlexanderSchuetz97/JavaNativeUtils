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
package eu.aschuetz.nativeutils.impl;

import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.UUID;

/**
 * Utility to load the native libraries. It can be used to unpack the .so/.dll files from the jar and load them into the jvm.
 * If you wish to manually load the native libraries by other means then don't use it otherwise call loadNativeLibraries before
 * using JavaNativeUtils.
 */
public class NativeLibraryLoaderHelper {

    private static final int EXPECTED_NATIVE_LIB_VERSION = 9;

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
        loadNativeLibraries(new File(System.getProperty("java.io.tmpdir")).getAbsolutePath());
    }

    private static byte[] readLib(String name) {
        InputStream tempInput = NativeLibraryLoaderHelper.class.getResourceAsStream(name);
        if (tempInput == null) {
            return null;
        }

        ByteArrayOutputStream baos = new ByteArrayOutputStream();

        byte[] tempBuf = new byte[512];
        try {
            int i = 0;
            while (i != -1) {
                i = tempInput.read(tempBuf);
                if (i > 0) {
                    baos.write(tempBuf, 0, i);
                }
            }

            tempInput.close();
        } catch (IOException e) {
            return null;
        }

        return baos.toByteArray();
    }

    /**
     * Helper method to get all shared lib binaries in a map, so you can load them yourself more easily.
     */
    public static Map<String, byte[]> getNativeLibraryBinaries() {
        Map<String, byte[]> theMap = new HashMap<>();
        theMap.put("java_native_utils_amd64.so", readLib("/java_native_utils_amd64.so"));
        theMap.put("java_native_utils_amd64_musl.so", readLib("/java_native_utils_amd64_musl.so"));
        theMap.put("java_native_utils_i386.so", readLib("/java_native_utils_i386.so"));
        theMap.put("java_native_utils_armhf.so", readLib("/java_native_utils_armhf.so"));
        theMap.put("java_native_utils_armel.so", readLib("/java_native_utils_armel.so"));
        theMap.put("java_native_utils_aarch64.so", readLib("/java_native_utils_aarch64.so"));
        theMap.put("java_native_utils_riscv64.so", readLib("/java_native_utils_riscv64.so"));
        theMap.put("java_native_utils_mips64el.so", readLib("/java_native_utils_mips64el.so"));
        theMap.put("java_native_utils_ppc64le.so", readLib("/java_native_utils_ppc64le.so"));
        theMap.put("java_native_utils_s390x.so", readLib("/java_native_utils_s390x.so"));
        theMap.put("java_native_utils_amd64.dll", readLib("/java_native_utils_amd64.dll"));
        theMap.put("java_native_utils_i386.dll", readLib("/java_native_utils_i386.dll"));
        theMap.put("java_native_utils_amd64_freebsd.so", readLib("/java_native_utils_amd64_freebsd.so"));

        return theMap;
    }

    /**
     * Shortcut to System.load so it loads a library using JavaNativeUtils Classloader.
     */
    public synchronized static void load(String file) throws LinkageError {
        if (loaded) {
            return;
        }

        boolean succ = false;
        long v = 0;
        try {
            v = getNativeLibVersion();
            succ = true;
        } catch (UnsatisfiedLinkError error) {

        }

        if (succ) {
            if (v != EXPECTED_NATIVE_LIB_VERSION) {
                throw new UnsatisfiedLinkError("Wrong java_native_utils lib version was loaded expected " + EXPECTED_NATIVE_LIB_VERSION + " got " + v);
            }

            loaded = true;
        }

        System.load(file);
        v = getNativeLibVersion();
        if (v != EXPECTED_NATIVE_LIB_VERSION) {
            throw new UnsatisfiedLinkError("Wrong java_native_utils lib version was loaded expected " + EXPECTED_NATIVE_LIB_VERSION + " got " + v);
        }
        loaded = true;
    }

    /**
     * Will load the native libraries if necessary.
     * If the loading fails then a LinkageError is thrown.
     * The given path will be used as a directory to unpack the native libraries to.
     * If the directory at the given path does not exist it will be created.
     * If that fails a LinkageError is thrown.
     *
     * This method tries to guess the OS and architecture of your system based on System Properties.
     * Due to lack of documentation this is not perfect and may fail even tho your system would be supported.
     * In this case you may have to load the correct library by hand by calling getSharedLibraryBinaries and writing
     * your desired library to a file and calling load on it.
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

        if (tempArch.equals("arm64")) {
            tempArch = "aarch64";
        }

        if (tempArch.equals("x86")) {
            tempArch = "i386";
        }

        if (tempArch.equals("x64") || tempArch.equals("x86_64")) {
            tempArch = "amd64";
        }

        String tempOS = System.getProperty("os.name");
        if (tempOS == null) {
            throw new UnsatisfiedLinkError("Cannot load native libraries because the operating system couldn't be detected!");
        }

        tempOS = tempOS.toLowerCase();
        try {
            if (tempOS.contains("linux")) {
                switch(tempArch) {
                    case("armhf"):
                        try {
                            loadLib(tempFile, "java_native_utils_armhf.so");
                        } catch (Throwable e) {
                            //ARMEL Fallback as both architectures have same os.arch
                            loadLib(tempFile, "java_native_utils_armel.so");
                        }
                        break;
                    case("amd64"):
                        try {
                            //Check if we are on musl...
                            if (new File("/lib/libc.musl-x86_64.so.1").exists()) {
                                loadLib(tempFile, "java_native_utils_amd64_musl.so");
                                break;
                            }
                        } catch (Throwable e) {
                            //Fallback to GLIBC
                            loadLib(tempFile, "java_native_utils_amd64.so");
                            break;
                        }

                        try {
                            //TRY GLIBC
                            loadLib(tempFile, "java_native_utils_amd64.so");
                        } catch (Throwable e) {
                            //MUSL as fallback
                            loadLib(tempFile, "java_native_utils_amd64_musl.so");
                        }
                        break;
                    case("armel"):
                    case("i386"):
                    case("aarch64"):
                    case("riscv64"):
                    case("ppc64le"):
                    case("mips64el"):
                    case("s390x"):
                        loadLib(tempFile, "java_native_utils_" + tempArch + ".so");
                        break;
                    default:
                        throw new UnsatisfiedLinkError("Processor architecture is not supported on Linux! Value: " + tempArch);
                }
            } else if (tempOS.contains("windows")) {
                if (!"i386".equals(tempArch) && !"amd64".equals(tempArch)) {
                    throw new UnsatisfiedLinkError("Processor architecture is not supported on Windows! Value: " + tempArch);
                }
                loadLib(tempFile, "java_native_utils_" + tempArch + ".dll");
            } else if ("freebsd".equalsIgnoreCase(tempOS)) {
                if (!"amd64".equals(tempArch)) {
                    throw new UnsatisfiedLinkError("Processor architecture is not supported on FreeBSD! Value: " + tempArch);
                }

                loadLib(tempFile, "java_native_utils_amd64_freebsd.so");
            } else {
                throw new UnsatisfiedLinkError("Operating system is not windows, linux or freebsd and thus not supported! Value: " + tempOS);
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
        //System.out.println("loading lib " + aLibName);
        MessageDigest md5;
        try {
            md5 = MessageDigest.getInstance("MD5");
        } catch (NoSuchAlgorithmException e) {
            throw new IOException("MD5 MessageDigest not found", e);
        }


        Random rng = new Random();
        File extractionFile;
        File loadingFile = null;
        do {
            extractionFile = new File(aBase, "X" + new UUID(rng.nextLong(), rng.nextLong()).toString().replace("-","") + aLibName);
        } while (extractionFile.exists());

        if (!extractionFile.createNewFile()) {
            throw new IOException("Could not call createNewFile on temporary library file!");
        }


        try {
            InputStream tempInput = null;

            try(FileOutputStream tempFaos = new FileOutputStream(extractionFile)) {
                byte[] tempBuf = new byte[512];
                tempInput = NativeLibraryLoaderHelper.class.getResourceAsStream("/" + aLibName);
                if (tempInput == null) {
                    throw new IOException("The shared library file " + aLibName + " was not found by getResourceAsStream " +
                            "its either not there or this class was loaded by a classloader that doesn't support resources well!");
                }

                int i = 0;
                while (i != -1) {
                    i = tempInput.read(tempBuf);
                    if (i > 0) {
                        md5.update(tempBuf, 0, i);
                        tempFaos.write(tempBuf, 0, i);
                    }
                }

                tempFaos.flush();
            } finally {
                try {
                    if (tempInput != null) {
                        tempInput.close();
                    }
                } catch (IOException e) {
                    //DC
                }
            }

            String dig = toHexString(md5.digest());
            loadingFile = new File(aBase, dig + aLibName);

            //On windows this call will fail on the second run but it will not matter as the last run already extracted it...
            extractionFile.renameTo(loadingFile);

            //We just check if its actually there and then load it...
            if (!loadingFile.exists()) {
                throw new IOException("Could not rename temporary file " + extractionFile.getAbsolutePath() +  " to " + loadingFile.getAbsolutePath());
            }

            try {
                System.load(loadingFile.getAbsolutePath());
            } catch (Throwable t) {
                throw t;

            }

        } finally {
            //This will only delete something on windows, on linux the file is already renamed and gone...
            extractionFile.delete();
        }
    }

    private static String toHexString(byte[] digest) {
        StringBuilder sb = new StringBuilder(digest.length << 1);
        for (byte b : digest) {
            String hx = Integer.toHexString(b & 0XFF);
            if (hx.length() == 1) {
                sb.append('0');
            }
            sb.append(hx);
        }

        return sb.toString();
    }

    static native long getNativeLibVersion();
}
