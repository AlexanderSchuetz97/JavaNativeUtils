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

import eu.aschuetz.nativeutils.api.consts.DefaultLinuxConstProvider;
import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.consts.LinuxConstProvider;
import eu.aschuetz.nativeutils.api.exceptions.*;
import eu.aschuetz.nativeutils.api.structs.*;

import java.io.*;
import java.net.ConnectException;
import java.net.InetSocketAddress;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.InvalidPathException;
import java.nio.file.NotDirectoryException;
import java.nio.file.NotLinkException;
import java.nio.file.ReadOnlyFileSystemException;
import java.util.Collection;

public class JNILinuxNativeUtil extends JNIPosixNativeUtil implements LinuxNativeUtil {

    public static native void _getConst(DefaultLinuxConstProvider provider);

    private final DefaultLinuxConstProvider theConst = new DefaultLinuxConstProvider();

    public JNILinuxNativeUtil() {
        _getConst(theConst);
    }

    @Override
    public LinuxConstProvider getLinuxConstProvider() {
        return theConst;
    }



    @Override
    public boolean isLinux() {
        return true;
    }

    @Override
    public boolean isFreeBSD() {
        return false;
    }

    @Override
    public boolean isNetBSD() {
        return false;
    }

    @Override
    public boolean isOpenBSD() {
        return false;
    }

    @Override
    public native int getFD(FileDescriptor fd);

    @Override
    public InputStream inputStreamFromFD(int fd, boolean close) {
        return new LinuxInputStream(this, fd, close);
    }

    @Override
    public OutputStream outputStreamFromFD(int fd, boolean close) {
        return new LinuxOutputStream(this, fd, close);
    }

    @Override
    public native int if_nametoindex(String name) throws UnknownNativeErrorException;

    @Override
    public native String if_indextoname(int index) throws UnknownNativeErrorException;

    @Override
    public native Collection<IfNameIndex> if_nameindex() throws UnknownNativeErrorException;

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
    public native void fsync(int fd) throws InvalidFileDescriptorException, IOException, ReadOnlyFileSystemException;

    @Override
    public native int recvfrom(int fd, byte[] buffer, int off, int len, int flags, Sockaddr sockaddr);

    @Override
    public native int recvmsg(int fd, Msghdr msghdr, int flags);

    @Override
    public native int sendmsg(int fd, Msghdr msghdr, int flags) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, ConnectException, UnknownNativeErrorException;

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
    public native void bind(int fd, Sockaddr sockaddr) throws InvalidFileDescriptorException, IllegalArgumentException, SocketException, AccessDeniedException, FileSystemLoopException, NotDirectoryException, ReadOnlyFileSystemException, IOException, UnknownNativeErrorException;

    @Override
    public native void getsockname(int fd, Sockaddr sockaddr) throws InvalidFileDescriptorException, IllegalArgumentException, UnknownNativeErrorException;

    @Override
    public native int getsockopt(int fd, int level, int optname);

    @Override
    public native byte[] getsockopt(int fd, int level, int optname, int payloadSize);


    @Override
    public native void setsockopt(int fd, int level, int optname, int payload);

    @Override
    public native void setsockopt(int fd, int level, int optname, byte[] payload);

    @Override
    public native void chdir(String path) throws FileNotFoundException, NotDirectoryException, InvalidPathException, AccessDeniedException, FileSystemLoopException, IOException, UnknownNativeErrorException;

    @Override
    public native void link(String target, String linkpath) throws IOException, InvalidPathException, ReadOnlyFileSystemException, AccessDeniedException, FileAlreadyExistsException, UnknownNativeErrorException;

    @Override
    public native Statvfs statvfs(String path) throws AccessDeniedException, IOException, FileSystemLoopException, FileNotFoundException, UnknownNativeErrorException;

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
    public native long geteuid();

    @Override
    public native String getlogin_r();

    @Override
    public native long[] getgrouplist(String user, long group);

    @Override
    public native Group getgrgid_r(long group);

    @Override
    public native Passwd getpwnam_r(String user);

    @Override
    public native Passwd getpwuid_r(long id);

    @Override
    public native long getuid();

    @Override
    public native String readlink(String path) throws NotLinkException;

    @Override
    public native String realpath(String path) throws AccessDeniedException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, NotDirectoryException;

    @Override
    public native void chmod(String path, int mode) throws AccessDeniedException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, NotDirectoryException;

    @Override
    public native void fchmod(int fd, int mode);

    @Override
    public native void chown(String path, int uid, int gid);

    @Override
    public native void fchown(int fd, int uid, int gid);

    @Override
    public native void lchown(String path, int uid, int gid);

    @Override
    public native int ioctl(int fd, int code);

    @Override
    public native int ioctl(int fd, int code, byte[] buf, int off);

    @Override
    public native int ioctl(int fd, int code, long ptr);

    @Override
    public int ioctl(int fd, int code, NativeMemory mem, long off) {
        long p =  mem.getNativePointer(off);
        if (p == 0) {
            throw new NullPointerException();
        }
        return ioctl(fd, code, p);
    }

    @Override
    public native int fcntl(int fd, int code) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public native int fcntl(int fd, int code, int param) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public native int fcntl(int fd, int code, long param) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public native int fcntl(int fd, int code, byte[] param, int off) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public int fcntl(int fd, int code, NativeMemory mem, long off) throws InvalidFileDescriptorException, UnknownNativeErrorException {
        long p =  mem.getNativePointer(off);
        if (p == 0) {
            throw new NullPointerException();
        }
        return fcntl(fd, code, p);
    }

    @Override
    public native long sem_open(String name, int oflags) throws AccessDeniedException, QuotaExceededException, FileNotFoundException, FileAlreadyExistsException, UnknownNativeErrorException;

    @Override
    public native long sem_open(String name, int oflags, int mode, int value) throws AccessDeniedException, QuotaExceededException, FileNotFoundException, FileAlreadyExistsException, UnknownNativeErrorException;

    @Override
    public native void sem_close(long sem) throws UnknownNativeErrorException;

    @Override
    public native void sem_unlink(String name) throws AccessDeniedException, FileNotFoundException, UnknownNativeErrorException;
    @Override
    public native int sem_t_size();
    @Override
    public native void sem_init(long sem, boolean interprocess, int value) throws UnknownNativeErrorException;

    @Override
    public native void sem_destroy(long sem) throws UnknownNativeErrorException;

    @Override
    public native void sem_post(long sem) throws UnknownNativeErrorException;

    @Override
    public native void sem_wait(long sem) throws UnknownNativeErrorException;

    @Override
    public native int sem_getvalue(long sem) throws UnknownNativeErrorException;

    @Override
    public native boolean sem_trywait(long sem) throws UnknownNativeErrorException;

    @Override
    public native boolean sem_timedwait(long sem, long timeoutInMillis) throws UnknownNativeErrorException;

    @Override
    public native int shm_open(String name, int oflag, int mode);

    @Override
    public native void shm_unlink(String name);

    @Override
    public native void ftruncate(int fd, long len);

    @Override
    public native void truncate(String name, long len);

    @Override
    public native void mkfifo(String name, int mode) throws AccessDeniedException, QuotaExceededException, FileAlreadyExistsException, FileNotFoundException, NotDirectoryException, ReadOnlyFileSystemException;

    @Override
    public native long sizeof_pthread_mutex_t();

    @Override
    public native long sizeof_pthread_mutexattr_t();

    @Override
    public native long sizeof_pthread_cond_t();

    @Override
    public native long sizeof_pthread_condattr_t();

    @Override
    public native void pthread_condattr_destroy(long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_condattr_init(long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutexattr_destroy(long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutexattr_init(long attributes) throws UnknownNativeErrorException;

    @Override
    public native int pthread_condattr_getpshared(long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_condattr_setpshared(long attributes, int value) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutexattr_setpshared(long attributes, int value) throws UnknownNativeErrorException;

    @Override
    public native int pthread_mutexattr_getpshared(long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutexattr_setrobust(long attributes, int value) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutex_consistent(long mutex) throws UnknownNativeErrorException;

    @Override
    public native int pthread_mutexattr_getrobust(long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutexattr_settype(long attributes, int value) throws UnknownNativeErrorException;

    @Override
    public native int pthread_mutexattr_gettype(long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutex_init(long mutex, long attributes) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutex_destroy(long mutex) throws UnknownNativeErrorException;

    @Override
    public native void pthread_mutex_lock(long mutex) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    @Override
    public native boolean pthread_mutex_trylock(long mutex) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    @Override
    public native void pthread_mutex_unlock(long mutex) throws UnknownNativeErrorException;

    @Override
    public native boolean pthread_mutex_timedlock(long mutex, long timeout) throws UnknownNativeErrorException;

    @Override
    public native void pthread_cond_broadcast(long condition) throws UnknownNativeErrorException;

    @Override
    public native void pthread_cond_signal(long condition) throws UnknownNativeErrorException;

    @Override
    public native void pthread_cond_wait(long condition, long mutex)  throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    @Override
    public native boolean pthread_cond_timedwait(long condition, long mutex, long timeout) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    @Override
    public native void pthread_cond_destroy(long condition) throws UnknownNativeErrorException;

    @Override
    public native void pthread_cond_init(long condition, long attributes) throws UnknownNativeErrorException;

    @Override
    public native int memfd_create(String name, int flags) throws QuotaExceededException, PermissionDeniedException, UnknownNativeErrorException;

    @Override
    public native boolean malloc_trim(long pad);

    @Override
    public native void madvise(long ptr, long length, int advice) throws UnknownNativeErrorException, AccessDeniedException, IOException, PermissionDeniedException, ResourceTemporarilyUnavailableException, ResourceBusyException, MemoryFaultException;

    @Override
    public native Stat lstat(String path) throws InvalidFileDescriptorException;



}
