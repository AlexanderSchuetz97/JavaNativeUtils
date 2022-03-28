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
package io.github.alexanderschuetz97.nativeutils.api;

import io.github.alexanderschuetz97.nativeutils.api.exceptions.InvalidFileDescriptorException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.OperationInProgressException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.PermissionDeniedException;
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

public interface LinuxNativeUtil extends NativeUtil {


    enum fnctl_F_SETLK_Mode {
        F_RDLCK, // read lock
        F_WRLCK, // write lock
        F_UNLCK // unlock/remove the lock
    }

    int getFD(FileDescriptor fd);

    /**
     * Returns size of void* datatype in bytes. Either 4 or 8 bytes.
     * The returned value is constant.
     */
    int getPointerSize();

    /**
     * queries the cpu for info.<br>
     *
     * the returned int[] is null if the requested code/subcode is not supported by the cpu otherwise
     * it has the length of 4 and contains the registers in this oder: <br>
     * 0 -> EAX <br>
     * 1 -> EBX <br>
     * 2 -> ECX <br>
     * 3 -> EDX <br>
     *
     * Note: on non X86/AMD64 this will always return null.
     */
    int[] __get_cpuid_count(int code, int subcode);

    /**
     * Returns the CPU Model string.
     * Example for Intel CPU's would be "GenuineIntel"
     */
    String __get_cpuid_count_model();

    /**
     * returns the fd.
     * -1 is only returned if the flag O_NONBLOCK is set and the operation would block.
     */
    int open(String path, int flags) throws AccessDeniedException, QuotaExceededException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, ReadOnlyFileSystemException, UnknownNativeErrorException;

    /**
     * returns the fd.
     * -1 is only returned if the flag O_NONBLOCK is set and the operation would block.
     */
    int open(String path, int flags, int mode) throws AccessDeniedException, QuotaExceededException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, ReadOnlyFileSystemException, UnknownNativeErrorException;

    enum lseek_whence {
        SEEK_SET,
        SEEK_CUR,
        SEEK_END
    }
    long lseek(int fd, long off, lseek_whence whence) throws IOException, InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Converts a time value in milliseconds to a native timeval.
     */
    byte[] to_struct_timeval(long milliseconds);

    /**
     * Converts a native timeval to a long (milliseconds)
     * @throws NullPointerException if the array is null
     * @throws ArrayIndexOutOfBoundsException if the array is too small.
     */
    long from_struct_timeval(byte[] timeval);


    /**
     * returns a native struct sockaddr_in or sockaddr_in6 for the given address
     *
     * @throws IllegalArgumentException if the address returns invalid/null/non ipv4|6 values for port or address.
     */
    Sockaddr to_sockaddr_in(InetSocketAddress address) throws IllegalArgumentException;

    /**
     * returns a {@link InetSocketAddress} for the given native socket address
     * @throws IllegalArgumentException if Sockaddr is not AF_INET or AF_INET6 or {@link Sockaddr#address} has wrong length for its respective protocol.
     */
    InetSocketAddress from_sockaddr_in(Sockaddr sockaddr) throws IllegalArgumentException;

    /**
     * returns native struct sockaddr_un for given path.
     *
     * @throws IllegalArgumentException if path is too long (>107 characters)
     */
    Sockaddr to_sockaddr_un(String path) throws IllegalArgumentException;

    /**
     * returns the String path from a native unix socket address.
     * @throws IllegalArgumentException if Sockaddr is not AF_UNIX, has invalid size or last byte in address is not 0.
     */
    String from_sockaddr_un(Sockaddr sockaddr) throws IllegalArgumentException;

    /**
     * See man socket for information on the parameters.
     * THIS METHOD WILL BLOCK FOR EVER IF THE TARGET IP DOES NOT RESPOND UNLESS A TIMEOUT HAS BEEN SPECIFIED VIA setsockopt.
     *
     * @throws IllegalArgumentException if the arguments are invalid
     * @throws UnsupportedOperationException if the protocol or address family is not supported by the operating system.
     * @throws AccessDeniedException if the process does not have permission to create a socket of the requested type.
     * @throws QuotaExceededException if the limit of file descriptors/sockets has been reached for the process/system
     * @throws UnknownNativeErrorException protocol specific errors depends on input parameters.
     * @throws OperationInProgressException if a timeout has been specified.
     *       call poll with POLLOUT+POLLERR to check if it is done
     *       or call close() to cancel.
     */
    int socket(int domain, int type, int protocol)  throws IllegalArgumentException, UnsupportedOperationException, AccessDeniedException, QuotaExceededException, UnknownNativeErrorException;

    /**
     * timeout in milliseconds
     */
    int poll(PollFD[] fds, int timeout) throws IllegalArgumentException, UnknownNativeErrorException;

    /**
     * Reads from a file descriptor. Returns the number of bytes read into the buffer. Will read up to "len" bytes.
     * May return 0 for non blocking file descriptors that do not have data available.
     */
    int read(int fd, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    /**
     * Write to a file descriptor
     * returns the number of bytes written from the buffer.
     * may return 0 for non blocking file descriptors that are not ready to write data.
     */
    int write(int fd, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    /**
     * The Output parameter sockaddr may be null if you are not interested in this information.
     *
     * @param fd file descriptor to the socket.
     * @param buffer the buffer, must not be null.
     * @param off offset in the buffer
     * @param len max len of bytes to fill into buffer. If you are receiving datagrams then any excess bytes may be discarded.
     * @param flags flags for recvfrom.
     * @param sockaddr This param will contain the info from where the data was received. Pass null if you don't care about this info.
     * @return the number of bytes read. -1 is EOF. 0 is possible if the socket fd is set to be non-blocking and no data is available.
     */
    int recvfrom(int fd, byte[] buffer, int off, int len, int flags, Sockaddr sockaddr) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    /**
     * receive a message on a socket. This method can be used if data should be read from a socket into multiple segments of memory or if special metadata is needed.
     *
     * @param fd the file descriptor
     * @return the amount of bytes read into the iovecs
     */
    int recvmsg(int fd, Msghdr msghdr, int flags);

    /**
     * Returns the page size of the operating system in bytes.
     */
    int getpagesize();


    /**
     * Parse the CMSG header in the byte array.
     * @param msg_control from {@link Msghdr}
     */
    Collection<Cmsghdr> parseCMSG_HDR(byte[] msg_control, int msg_controllen);

    /**
     * Maps a file descriptor into memory.
     * Note: the native parameter addr to mmap is always 0.
     *
     * @param fd the file descriptor.
     * @param length
     * @param flags
     * @param read
     * @param write
     * @param offset file offset for the memory mapping. Only matters if the fd refers to a file.
     * @return A memory mapping that MUST BE FREED by using the cl
     */
    long mmap(int fd, long length, int flags, boolean read, boolean write, long offset) throws IllegalArgumentException, QuotaExceededException, InvalidFileDescriptorException, AccessDeniedException, IllegalStateException, UnsupportedOperationException;

    /**
     * Sync memory mapping to disk
     *
     * @param ptr pointer to the address
     * @param off offset from the pointer
     * @param len length of the memory to sync
     * @param invalidate invalidate memory mappings of other processes
     * @throws AccessDeniedException if a memory lock exists for the region and the invalidate flag is set to true.
     * @throws IllegalStateException if the memory or a part of it is not mapped by mmap
     * @throws IllegalArgumentException if ptr+off % getpagesize() != 0
     */
    void msync(long ptr, long off, long len, boolean invalidate) throws AccessDeniedException, IllegalStateException, IllegalArgumentException, UnknownNativeErrorException;

    /**
     * Unmap a pointer
     * @param ptr pointer to the address
     * @param size size of the memory mapping
     * @throws IllegalArgumentException if ptr/size do not correspond to a valid memory mapping.
     * @throws UnknownNativeErrorException
     */
    void munmap(long ptr, long size) throws UnknownNativeErrorException;

    /**
     * Allocates a new pointer of the given size
     * @throws OutOfMemoryError if malloc returns NULL
     * @throws IllegalArgumentException if size is <= 0
     */
    NativeMemory malloc(long size) throws OutOfMemoryError, IllegalArgumentException;

    /**
     * Any calls to the resulting NativeMemory may cause the JVM to die due to a SEGFAULT is size is not specified correctly.
     * the close() and sync() methods are noops.
     *
     * @param ptr pointer to the data
     * @param size -1 if unknown.
     */
    NativeMemory pointer(long ptr, long size, PointerHandler handler) throws NullPointerException;

    /**
     * calls connect using a generic socket address.
     * @param fd obtained from "socket"
     * @param sockaddr socket address to connect to.
     */
    void connect(int fd, Sockaddr sockaddr) throws InvalidFileDescriptorException, IllegalArgumentException, UnsupportedOperationException, OperationInProgressException;

    /**
     * returns a "int" socket option.
     * Most commonly used socket options are int values.
     */
    int getsockopt(int fd, int level, int optname) throws InvalidFileDescriptorException, IllegalArgumentException, UnsupportedOperationException;


    /**
     * returns a custom payload socket option.
     * @param payloadSize the maximum size of the payload. This is used to allocate a temporary buffer in native code. The actual returned payload may have a smaller size.
     */
    byte[] getsockopt(int fd, int level, int optname, int payloadSize) throws InvalidFileDescriptorException, IllegalArgumentException, UnsupportedOperationException;

    /**
     * sets a int socket option.
     * Most commonly used socket options are int values.
     */
    void setsockopt(int fd, int level, int optname, int payload) throws InvalidFileDescriptorException, IllegalArgumentException, UnsupportedOperationException;

    /**
     * Sets a custom payload socket option.
     */
    void setsockopt(int fd, int level, int optname, byte[] payload) throws InvalidFileDescriptorException, IllegalArgumentException, UnsupportedOperationException;



    /**
     * Close a file descriptor
     */
    void close(int fd) throws InvalidFileDescriptorException, IOException;

    /**
     * This call will never block. It returns true if the desired lock could be aquired, false otherwise.
     * <p>
     * NOTE: If the current process already holds a lock in the desired area the "conflicting" lock is released and replaced with the new lock.
     */
    boolean fnctl_F_SETLK(int fd, fnctl_F_SETLK_Mode mode, long start, long len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * This call will block until the desired lock on the file can be obtained.
     * This CANNOT be interrupted. Use with care.
     */
    void fnctl_F_SETLKW(int fd, fnctl_F_SETLK_Mode mode, long start, long len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * returns the pid that would prevent placement of the lock on the file.
     * returns -1 if the lock could have been placed. (Meaning either, unlocked or already locked by this process)
     * if this returns anything >= 0 then the file/region is already locked by another process.
     *
     * Note: This method cannot be used to determine if the current process has the lock.
     */
    int fnctl_F_GETLK(int fd, boolean exclusive, long start, long len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Changes the work directory of the entire jvm process.
     * The JVM does not have an internal mechanism to do this precisely because it will cause issues for most applications.
     * Use this with care, depending on the JVM version this may break things. new File(".").getAbsolutePath() may not reflect
     * the new work directory. Relative path from other c based jni libraries will use the new path.
     *
     * @throws IllegalArgumentException If path is null
     * @throws OutOfMemoryError when ENOMEM occurs -> Insufficient kernel memory was available.
     * @throws FileNotFoundException when ENOENT occurs (The path file does not exist at all)
     * @throws NotDirectoryException when ENOTDIR occurs (The path or part of it is not a directory)
     * @throws InvalidPathException if NAMETOOLONG occrus
     * @throws AccessDeniedException when EACCESS occurs (Process does not have search persmission to the given path)
     * @throws FileSystemLoopException when ELOOP occurs (The given path loops to itself with symlinks)
     * @throws IOException when EIO occurs
     * @throws UnknownNativeErrorException when an unexpected errno occurs
     */
    void chdir(String path) throws FileNotFoundException, NotDirectoryException, InvalidPathException, AccessDeniedException, FileSystemLoopException, IOException, UnknownNativeErrorException;


    /**
     * Creates a symlink pointing to target. The symlink is placed at "linkpath".
     *
     * @throws IOException If an IOError occurs when creating the symlink
     * @throws InvalidPathException If any of the two paths is invalid
     * @throws IllegalArgumentException If target or linkpath is null
     * @throws ReadOnlyFileSystemException If the file system of linkpath is read only.
     * @throws AccessDeniedException If the process lacks permission to write to linkpath. (and/or do path resolving)
     * @throws FileAlreadyExistsException If the file at "linkpath" already exists
     * @throws UnknownNativeErrorException If any unexpected native error occures.
     * @throws QuotaExceededException If any os enforced quota limit is violated by creating the link.
     */
    void symlink(String target, String linkpath) throws IOException, InvalidPathException, ReadOnlyFileSystemException, AccessDeniedException, FileAlreadyExistsException, UnknownNativeErrorException;

    /**
     * Creates a hard link pointing to target. The symlink is placed at "linkpath".
     *
     * @throws IOException If an IOError occurs when creating the symlink
     * @throws InvalidPathException If any of the two paths is invalid
     * @throws IllegalArgumentException If target or linkpath is null
     * @throws ReadOnlyFileSystemException If the file system of linkpath is read only.
     * @throws AccessDeniedException If the process lacks permission to write to linkpath. (and/or do path resolving)
     * @throws FileAlreadyExistsException If the file at "linkpath" already exists
     * @throws UnknownNativeErrorException If any unexpected native error occures.
     * @throws QuotaExceededException If any os enforced quota limit is violated by creating the link.
     */
    void link(String target, String linkpath) throws IOException, InvalidPathException, ReadOnlyFileSystemException, AccessDeniedException, FileAlreadyExistsException, UnknownNativeErrorException, QuotaExceededException;

    /**
     * Gets information about a file for a given path.
     *
     * @param path the path to the file
     * @return never null
     * @throws IllegalArgumentException If path is null
     * @throws FileNotFoundException If the file cannot be found
     * @throws FileSystemLoopException If too many sym links had to be followed to resolve the path
     * @throws InvalidPathException If the path is invalid (empty string, parent is not a directory etc)
     * @throws AccessDeniedException If the process lacks permission to resolve the path. (Parent directory does not have permission to list files for example)
     * @throws IOException If a unspecified IO error occures while reading the info from disc.
     * @throws UnknownNativeErrorException If any unexpected native error occures.
     */
    Stat stat(String path) throws FileNotFoundException, InvalidPathException, FileSystemLoopException, AccessDeniedException, UnknownNativeErrorException, IOException;


    /**
     * Identical to stat.
     * Only difference:
     * If the target file is itself a symbolic link then this does not follow the symbolic link and instead returns information about the symbolic link.
     * Normal stat would follow the link.
     *
     * @param path the path to the file/symbolic link
     * @return never null
     * @throws IllegalArgumentException If path is null
     * @throws FileNotFoundException If the file cannot be found
     * @throws FileSystemLoopException If too many sym links had to be followed to resolve the path
     * @throws InvalidPathException If the path is invalid (empty string, parent is not a directory etc)
     * @throws AccessDeniedException If the process lacks permission to resolve the path. (Parent directory does not have permission to list files for example)
     * @throws IOException If a unspecified IO error occures while reading the info from disc.
     * @throws UnknownNativeErrorException If any unexpected native error occures.
     */
    Stat lstat(String path) throws FileNotFoundException, InvalidPathException, FileSystemLoopException, AccessDeniedException, UnknownNativeErrorException, IOException;

    /**
     * Gets information about a opened file descriptor
     *
     * @return never null
     * @throws IllegalArgumentException If descriptor is null
     * @throws InvalidFileDescriptorException If the given file descriptor is invalid
     * @throws IOException If a unspecified IO error occures while reading the info from disc.
     * @throws UnknownNativeErrorException If any unexpected native error occures.
     */
    Stat fstat(int descriptor) throws InvalidFileDescriptorException, UnknownNativeErrorException, IOException;


    /**
     * Returns a english string repesentation of the native error code
     */
    String strerror_r(int errno);

    /**
     * Set an environment variable.
     * Note that the map in System.getenv() is most likely cached by the jvm at the start of the process.
     * You will need to use reflection to modify it.
     *
     * @param key name of the variable
     * @param value new value of the variable
     * @param overwrite overwrite the variable if it is present already or not.
     * @throws NullPointerException if key or value is null
     * @throws IllegalArgumentException if key contains "=" or is empty
     * @throws UnknownNativeErrorException if an unexpected error occurs.
     */
    void setenv(String key, String value, boolean overwrite) throws UnknownNativeErrorException;

    /**
     * Get an environment variable.
     *
     * @param key name of the variable
     * @return the value or null
     *
     * @throws NullPointerException if key is null
     * @throws IllegalArgumentException if key contains "=" or is empty
     * @throws UnknownNativeErrorException if an unexpected error occurs.
     */
    String getenv(String key) throws UnknownNativeErrorException;


    /**
     * removes a enviroment variable if it exists.
     * Theres no way to tell if the variable did or did not exist prior to this call.
     *
     * @throws NullPointerException if key is null
     * @throws IllegalArgumentException if key contains "=" or is empty
     * @throws UnknownNativeErrorException if an unexpected native error occurs.
     */
    void unsetenv(String key) throws  UnknownNativeErrorException;

    /**
     * performs word expansion like a posix-shell.
     * Note: This internally calls wordfree()
     * @param allowCommands if true then commands are allowed. Do not use this for untrusted user input as they can run any system command they want. example "$(ls)" would insert the output of "ls" into the result.
     * @param useStdErr if true then errors that occur during command execution are passed to stderr. if false then the errors are ignored. if allowCommands is false then this parameter is meaningless.
     * @param allowUndef if true then undefined variables are substituted with "". If false then an IllegalArgumentException is thrown when an unknown variable is encountered.
     * @throws IllegalArgumentException if the argument has invalid syntax, contains commands when not allowed or contains undefined variable when not allowed.
     */
    String[] wordexp(String expression, boolean allowCommands, boolean useStdErr, boolean allowUndef) throws IllegalArgumentException;

    /**
     * gets information about the unix system.
     */
    Utsname uname();

    /**
     * returns the resolved path of the symlink
     *
     * @param path the path of the sym link to resolve
     * @return the target of the link, never null
     * @throws NullPointerException if path is null
     * @throws NotLinkException if path exists but is not a symbolic link
     * @throws UnknownNativeErrorException if an unexpected native error occurs
     * @throws InvalidPathException if the path is invalid (too long for example)
     * @throws IOException if an io error occurs while reading the link location from the physical disk
     * @throws FileSystemLoopException if too many symlinks have to be followed to resolve components of the path
     * @throws AccessDeniedException  if the current process does not have permission to resolve the path or read the target of the link
     * @throws FileNotFoundException if the path does not exist.
     * @throws NotDirectoryException if a component of the path is not a directory (or link to a directory) but rather a file/something else.
     */
    String readlink(String path) throws NotLinkException, UnknownNativeErrorException, InvalidPathException, IOException, FileSystemLoopException, AccessDeniedException, FileNotFoundException, NotDirectoryException;

    /**
     * resolves all symbolic links in the given path.
     *
     * @param path path to be resolved
     * @return resolved path without symbolic links
     * @throws NullPointerException if path is null
     * @throws AccessDeniedException if read or search permission was denied for a component of the path prefix
     * @throws IOException If an io error occurs while reading from the file system
     * @throws FileSystemLoopException if too many symlinks have to be followed to resolve components of the path
     * @throws InvalidPathException if the path is too long
     * @throws FileNotFoundException if the file referenced by the path does not exist
     * @throws NotDirectoryException if a component of the path is not a directory
     * @throws UnknownNativeErrorException if an unexpected native error occurs
     */
    String realpath(String path) throws AccessDeniedException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, NotDirectoryException, UnknownNativeErrorException;

    /**
     * change file modifier
     *
     * @param path the path to the file
     * @param mode the new file mode
     * @throws NullPointerException if path is null
     * @throws AccessDeniedException if the process does not have permissions to resolve path
     * @throws PermissionDeniedException if the process does not have permissions the change the file mode
     * @throws IOException if an io error occurs while changing the file mode
     * @throws FileSystemLoopException if too many symlinks have to be followed to resolve components of the path
     * @throws InvalidPathException if the path is too long
     * @throws FileNotFoundException if the file does not exist
     * @throws NotDirectoryException if a component of the path is not a directory
     */
    void chmod(String path, int mode) throws AccessDeniedException, PermissionDeniedException, IOException, FileSystemLoopException, InvalidPathException, FileNotFoundException, NotDirectoryException;
}
