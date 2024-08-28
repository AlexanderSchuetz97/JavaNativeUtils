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

public interface NativeUtil {

    /**
     * Returns true if this NativeUtil is instanceof {@link WindowsNativeUtil} and supports the Windows API functions.
     */
    boolean isWindows();

    /**
     * Returns true if this NativeUtil is instanceof {@link LinuxNativeUtil} and supports the Linux API functions.
     */
    boolean isLinux();

    /**
     * Returns true if this NativeUtil is instanceof {@link JVMNativeUtil} and supports the JVM/JNI API functions.
     */
    boolean isJVM();


    /**
     * Returns true if this NativeUtil does not implement any useful functions.
     * This indicates a jvm running on a platform not supported by JavaNativeUtils. (Apple OSX for example)
     * or a failure to load the native libraries in which case taking a look at {@link NativeUtils#getNativeLibraryBinaries()} may help.
     */
    boolean isNoop();

    /**
     * returns true if this NativeUtil is instanceof {@link FreeBSDNativeUtil}  and supports the FreeBSD API functions.
     */
    boolean isFreeBSD();

    /**
     * returns true if this NativeUtil is instanceof {@link NetBSDNativeUtil}  and supports the NetBSD API functions.
     */
    boolean isNetBSD();

    /**
     * returns true if this NativeUtil is instanceof {@link PosixNativeUtil}  and supports the POSIX API functions.
     */
    boolean isPosix();
}
