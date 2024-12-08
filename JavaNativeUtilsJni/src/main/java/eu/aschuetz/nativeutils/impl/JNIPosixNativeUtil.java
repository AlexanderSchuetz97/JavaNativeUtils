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

import eu.aschuetz.nativeutils.api.PosixNativeUtil;
import eu.aschuetz.nativeutils.api.consts.DefaultLinuxConstProvider;
import eu.aschuetz.nativeutils.api.consts.DefaultPosixConstProvider;
import eu.aschuetz.nativeutils.api.consts.PosixConstProvider;
import eu.aschuetz.nativeutils.api.exceptions.FileIsDirectoryException;
import eu.aschuetz.nativeutils.api.exceptions.QuotaExceededException;
import eu.aschuetz.nativeutils.api.exceptions.ResourceBusyException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.Stat;
import eu.aschuetz.nativeutils.api.structs.Utsname;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.InvalidPathException;
import java.nio.file.ReadOnlyFileSystemException;

public abstract class JNIPosixNativeUtil extends JNICommonNativeUtil implements PosixNativeUtil {

    public static native void _getConst(DefaultPosixConstProvider provider);

    private final DefaultPosixConstProvider theConst = new DefaultPosixConstProvider();

    protected JNIPosixNativeUtil() {
        _getConst(theConst);
    }

    @Override
    public boolean isPosix() {
        return true;
    }

    @Override
    public boolean isWindows() {
        return false;
    }

    @Override
    public PosixConstProvider getPosixConstProvider() {
        return theConst;
    }

    @Override
    public native Stat stat(String path);

    @Override
    public native void symlink(String targetPath, String sourcePath) throws IOException, UnknownNativeErrorException;

    @Override
    public native void unlink(String path) throws IOException, AccessDeniedException, ResourceBusyException, FileIsDirectoryException, FileSystemLoopException, ReadOnlyFileSystemException;

    @Override
    public native Utsname uname();

    @Override
    public native int open(String path, int flags) throws AccessDeniedException, QuotaExceededException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, ReadOnlyFileSystemException, UnknownNativeErrorException;

    @Override
    public native int open(String path, int flags, int mode) throws AccessDeniedException, QuotaExceededException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, ReadOnlyFileSystemException, UnknownNativeErrorException;

    @Override
    public native void close(int fd);
}
