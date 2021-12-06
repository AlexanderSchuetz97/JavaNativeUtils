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

import io.github.alexanderschuetz97.nativeutils.api.NativeField;
import io.github.alexanderschuetz97.nativeutils.api.WindowsNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;
import io.github.alexanderschuetz97.nativeutils.api.structs.Win32FileAttributeData;

import java.io.FileDescriptor;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.Objects;

public class JNIWindowsNativeUtil extends JNICommonNativeUtil implements WindowsNativeUtil {

    @Override
    public native boolean LockFileEx(long fd, boolean exclusive, boolean failImmediately, long start, long len);

    @Override
    public native boolean UnlockFileEx(long fd, long start, long len);

    @Override
    public native int getFD(FileDescriptor fd);

    @Override
    public native long getHandle(FileDescriptor fd);

    @Override
    public native boolean _locking(int fd, _locking_Mode mode, long len);

    @Override
    public native Stat _stat64(String path);

    @Override
    public native Win32FileAttributeData GetFileAttributesEx(String path) throws UnknownNativeErrorException;

    @Override
    public native void CreateSymbolicLinkA(String lpSymlinkFileName, String lpTargetFileName, boolean targetIsDir, boolean isDevMode) throws UnknownNativeErrorException;

    @Override
    public native void CreateHardLinkA(String lpFileName, String lpExistingFileName) throws UnknownNativeErrorException;

    @Override
    public native long CreateFileA(String lpFileName, int access, boolean allowDelete, boolean allowRead, boolean allowWrite, CreateFileA_createMode openMode, int attributes) throws UnknownNativeErrorException;

    @Override
    public native void CloseHandle(long handle) throws UnknownNativeErrorException;

    @Override
    public native String strerror_s(int errno);

    @Override
    public native String FormatMessageA(int lastError);

    @Override
    public boolean isWindows() {
        return true;
    }

    @Override
    public boolean isLinux() {
        return false;
    }


}