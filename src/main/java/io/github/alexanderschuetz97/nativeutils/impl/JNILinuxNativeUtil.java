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
package io.github.alexanderschuetz97.nativeutils.impl;

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.InvalidFileDescriptorException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.QuotaExceededException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.Cmsghdr;
import io.github.alexanderschuetz97.nativeutils.api.structs.Msghdr;
import io.github.alexanderschuetz97.nativeutils.api.structs.PollFD;
import io.github.alexanderschuetz97.nativeutils.api.structs.Sockaddr;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;
import io.github.alexanderschuetz97.nativeutils.api.structs.Utsname;

import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.InvalidPathException;
import java.nio.file.NotDirectoryException;
import java.nio.file.NotLinkException;
import java.nio.file.ReadOnlyFileSystemException;
import java.util.Collection;

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
    public native int open(String path, int flags) throws AccessDeniedException, QuotaExceededException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, ReadOnlyFileSystemException, UnknownNativeErrorException;

    @Override
    public native int open(String path, int flags, int mode) throws AccessDeniedException, QuotaExceededException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, ReadOnlyFileSystemException, UnknownNativeErrorException;

    @Override
    public native long lseek(int fd, long off, lseek_whence whence);

    @Override
    public native byte[] to_struct_timeval(long timestamp);

    @Override
    public native long from_struct_timeval(byte[] timeval);

    @Override
    public native Sockaddr to_sockaddr_in(InetSocketAddress address);

    @Override
    public native InetSocketAddress from_sockaddr_in(Sockaddr sockaddr);

    @Override
    public native Sockaddr to_sockaddr_un(String path);

    @Override
    public native String from_sockaddr_un(Sockaddr sockaddr);

    @Override
    public native int socket(int domain, int type, int protocol);

    @Override
    public native int poll(PollFD[] fds, int timeout);

    @Override
    public native int read(int fd, byte[] buffer, int off, int len);

    @Override
    public native int write(int fd, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    @Override
    public native int recvfrom(int fd, byte[] buffer, int off, int len, int flags, Sockaddr sockaddr);

    @Override
    public native int recvmsg(int fd, Msghdr msghdr, int flags);

    @Override
    public native int getpagesize();

    @Override
    public native Collection<Cmsghdr> parseCMSG_HDR(byte[] msg_control, int msg_controllen);


    protected static native void _munmap(long ptr, long length) throws IllegalArgumentException, UnknownNativeErrorException;

    protected static native long _mmap(int fd, long length, int flags, boolean read, boolean write, long offset) throws IllegalArgumentException, QuotaExceededException, InvalidFileDescriptorException, AccessDeniedException, IllegalStateException, UnsupportedOperationException;

    protected static native void _msync(long ptr, long off, long len, boolean invalidate) throws AccessDeniedException, IllegalStateException, IllegalArgumentException;


    @Override
    public long mmap(int fd, final long length, int flags, boolean read, boolean write, long offset) throws IllegalArgumentException, QuotaExceededException, InvalidFileDescriptorException, AccessDeniedException, IllegalStateException, UnsupportedOperationException {
        return _mmap(fd, length, flags, read, write, offset);
    }

    @Override
    public void msync(long ptr, long off, long len, boolean invalidate) throws AccessDeniedException, IllegalStateException, IllegalArgumentException {
        if (off < 0 || len < 0) {
            throw new IllegalArgumentException("len/off");
        }

        _msync(ptr, off, len, invalidate);
    }

    @Override
    public void munmap(long ptr, long size) throws UnknownNativeErrorException {
        _munmap(ptr, size);
    }


    @Override
    public native void connect(int fd, Sockaddr sockaddr);

    @Override
    public native int getsockopt(int fd, int level, int optname);

    @Override
    public native byte[] getsockopt(int fd, int level, int optname, int payloadSize);

    @Override
    public native void setsockopt(int fd, int level, int optname, int payload);

    @Override
    public native void setsockopt(int fd, int level, int optname, byte[] payload);

    @Override
    public native void close(int fd);

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
    public native void setenv(String key, String value, boolean overwrite) throws UnknownNativeErrorException;

    @Override
    public native String getenv(String key) throws UnknownNativeErrorException;

    @Override
    public native void unsetenv(String key) throws UnknownNativeErrorException;

    @Override
    public native String[] wordexp(String expression, boolean allowCommands, boolean useStdErr, boolean allowUndef);

    @Override
    public native Utsname uname();

    @Override
    public native String readlink(String path) throws NotLinkException;

    @Override
    public native String realpath(String path) throws AccessDeniedException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, NotDirectoryException;

    @Override
    public native void chmod(String path, int mode) throws AccessDeniedException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, NotDirectoryException;
    
    @Override
    public native Stat lstat(String path) throws InvalidFileDescriptorException;

}
