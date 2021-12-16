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
import io.github.alexanderschuetz97.nativeutils.api.structs.PollFD;
import io.github.alexanderschuetz97.nativeutils.api.structs.Sockaddr;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;

import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetSocketAddress;
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
    public native Stat lstat(String path) throws InvalidFileDescriptorException;

}
