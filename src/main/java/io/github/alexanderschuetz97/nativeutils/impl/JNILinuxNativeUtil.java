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

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.InvalidFileDescriptorException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;

import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.InvalidPathException;
import java.nio.file.NotDirectoryException;
import java.nio.file.ReadOnlyFileSystemException;

public class JNILinuxNativeUtil extends JNICommonNativeUtil implements LinuxNativeUtil {

    @Override
    public boolean isWindows() {
        return false;
    }

    @Override
    public boolean isLinux() {
        return true;
    }

    @Override
    public native int getFD(FileDescriptor fd);

    @Override
    public native boolean fnctl_F_SETLK(int fd, fnctl_F_SETLK_Mode mode, long start, long end) throws InvalidFileDescriptorException, UnknownNativeErrorException;;

    @Override
    public native void fnctl_F_SETLKW(int fd, fnctl_F_SETLK_Mode mode, long start, long end) throws InvalidFileDescriptorException, UnknownNativeErrorException;;

    @Override
    public native int fnctl_F_GETLK(int fd, boolean exclusive, long start, long end) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public native void chdir(String path) throws FileNotFoundException, NotDirectoryException, InvalidPathException, AccessDeniedException, FileSystemLoopException, IOException, UnknownNativeErrorException;

    @Override
    public native void symlink(String targetPath, String sourcePath) throws IOException, UnknownNativeErrorException;

    @Override
    public native void link(String target, String linkpath) throws IOException, InvalidPathException, ReadOnlyFileSystemException, AccessDeniedException, FileAlreadyExistsException, UnknownNativeErrorException;

    @Override
    public native Stat stat(String path);

    @Override
    public native Stat fstat(int descriptor) throws InvalidFileDescriptorException;

    @Override
    public native String strerror_r(int errno);

    @Override
    public native Stat lstat(String path) throws InvalidFileDescriptorException;

}
