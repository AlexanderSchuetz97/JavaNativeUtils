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

import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.PosixNativeUtil;
import eu.aschuetz.nativeutils.api.consts.DefaultLinuxConstProvider;
import eu.aschuetz.nativeutils.api.consts.DefaultPosixConstProvider;
import eu.aschuetz.nativeutils.api.consts.PosixConstProvider;
import eu.aschuetz.nativeutils.api.exceptions.*;
import eu.aschuetz.nativeutils.api.structs.Stat;
import eu.aschuetz.nativeutils.api.structs.Utsname;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.ByteBuffer;
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
    public native int read(int fd, byte[] buffer, int off, int len);

    protected native int read(int fd, long ptr, int len);

    @Override
    public int read(int fd, NativeMemory mem, long off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException {
        if (!mem.isValid(off, len)) {
            throw new IllegalArgumentException("out of bounds");
        }

        return read(fd, mem.getNativePointer(off), len);
    }

    @Override
    public int read(int fd, ByteBuffer buf, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException {
        if (buf.isReadOnly()) {
            throw new IllegalArgumentException("buffer is read only");
        }

        if (len < 0) {
            throw new IllegalArgumentException("len < 0");
        }
        if (len == 0) {
            return 0;
        }

        if (buf.remaining() < len) {
            throw new IllegalArgumentException("buffer.remaining() < len");
        }

        if (!buf.isDirect()) {
            if (!buf.hasArray()) {
                byte[] bbuf = new byte[len];
                int x = read(fd, bbuf, 0, len);
                if (x > 0) {
                    buf.put(bbuf, 0, x);
                }

                return x;
            }

            byte[] bbuf = buf.array();
            int x = read(fd, bbuf, buf.position(), len);
            if (x > 0) {
                buf.position(buf.position() + x);
            }
            return x;

        }

        long addr = GetDirectBufferAddress(buf);
        if (addr == 0) {
            throw new IllegalStateException("Not a direct buffer even tho buffer.isDirect() returned true");
        }

        int pos = buf.position();
        if (pos > 0) {
            addr = pointerAdd(addr, pos);
        }
        int r = read(fd, addr, len);
        if (r > 0) {
            buf.position(buf.position() + r);
        }
        return r;
    }


    @Override
    public native int write(int fd, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    @Override
    public int write(int fd, ByteBuffer buf, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException {
        if (buf.remaining() < len) {
            throw new IllegalArgumentException("buffer.remaining() < len");
        }

        if (len < 0) {
            throw new IllegalArgumentException("len < 0");
        }
        if (len == 0) {
            return 0;
        }

        if (!buf.isDirect()) {
            if (!buf.hasArray()) {
                byte[] bbuf = new byte[len];
                int pos = buf.position();
                buf.get(bbuf);
                buf.position(pos);
                int x = write(fd, bbuf, 0, len);

                if (x > 0) {
                    buf.position(pos+x);
                }

                return x;
            }

            byte[] bbuf = buf.array();
            int x = write(fd, bbuf, buf.position(), len);
            if (x > 0) {
                buf.position(buf.position() + x);
            }
            return x;

        }

        long addr = GetDirectBufferAddress(buf);
        if (addr == 0) {
            throw new IllegalStateException("Not a direct buffer even tho buffer.isDirect() returned true");
        }

        int pos = buf.position();
        if (pos > 0) {
            addr = pointerAdd(addr, pos);
        }
        int r = write(fd, addr, len);
        if (r > 0) {
            buf.position(buf.position() + r);
        }
        return r;
    }

    protected native int write(int fd, long ptr, int len);

    @Override
    public int write(int fd, NativeMemory mem, long off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException {
        if (!mem.isValid(off, len)) {
            throw new IllegalArgumentException("out of bounds");
        }

        return write(fd, mem.getNativePointer(off), len);
    }

    @Override
    public native void close(int fd);
}
