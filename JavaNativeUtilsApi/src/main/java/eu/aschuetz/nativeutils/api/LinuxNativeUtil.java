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

public interface LinuxNativeUtil extends NativeUtil {


    int getFD(FileDescriptor fd);

    /**
     * Returns size of void* datatype in bytes. Either 4 or 8 bytes.
     * The returned value is constant.
     */
    int getPointerSize();

    /**
     * Returns a input stream that will read bytes from the filedescriptor by calling the read method.
     * This method exists for convinience.
     * Closing the returned InputStream will only call the close() method if the close flag is set to true.
     * Otherwise, closeing the stream is a noop.
     */
    InputStream inputStreamFromFD(int fd, boolean close);

    /**
     * Returns a output stream that will write bytes to the filedescriptor by calling the write method.
     * This method exists for convinience.
     * Closing the returned OutputStream will only call the close() method if the close flag is set to true.
     * Otherwise, closeing the stream is a noop.
     */
    OutputStream outputStreamFromFD(int fd, boolean close);

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
     * returns the interface index or 0 if the interface is not found
     */
    int if_nametoindex(String name) throws UnknownNativeErrorException;

    /**
     * Returns the interface name as a string or null if the index is not found.
     */
    String if_indextoname(int index) throws UnknownNativeErrorException;

    /**
     * returns all network interface indices
     */
    Collection<IfNameIndex> if_nameindex() throws UnknownNativeErrorException;

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
     * Reads from a file descriptor. Returns the number of bytes read into the buffer. Will read up to "len" bytes.
     * May return 0 for non blocking file descriptors that do not have data available.
     */
    int read(int fd, NativeMemory mem, long off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    /**
     * Reads from a file descriptor. Returns the number of bytes read into the buffer. Will read up to "len" bytes.
     * May return 0 for non blocking file descriptors that do not have data available.
     */
    int read(int fd, ByteBuffer buf, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;


    void fsync(int fd) throws InvalidFileDescriptorException, IOException, ReadOnlyFileSystemException;

    /**
     * Write to a file descriptor
     * returns the number of bytes written from the buffer.
     * may return 0 for non blocking file descriptors that are not ready to write data.
     */
    int write(int fd, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    /**
     * Write to a file descriptor
     * returns the number of bytes written from the buffer.
     * may return 0 for non blocking file descriptors that are not ready to write data.
     */
    int write(int fd, NativeMemory mem, long off, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

    /**
     * Write to a file descriptor
     * returns the number of bytes written from the buffer.
     * may return 0 for non blocking file descriptors that are not ready to write data.
     */
    int write(int fd, ByteBuffer buf, int len) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, UnknownNativeErrorException;

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
    int recvmsg(int fd, Msghdr msghdr, int flags) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, ConnectException, UnknownNativeErrorException;

    /**
     * send a message on a socket.
     */
    int sendmsg(int fd, Msghdr msghdr, int flags) throws InvalidFileDescriptorException, IllegalArgumentException, IOException, ConnectException, UnknownNativeErrorException;


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
     * Binds a socket to a address.
     * @param fd socket fd
     * @param sockaddr the address to bind to
     * @throws InvalidFileDescriptorException if fd is not valid or not a socket
     * @throws IllegalArgumentException if sockaddr is not valid
     * @throws SocketException if the address is already in use
     * @throws AccessDeniedException if the address cannot be accessed
     * @throws FileSystemLoopException (AF_UNIX) if too many symbolic links were encountered when resolving the path
     * @throws NotDirectoryException (AF_UNIX) if a component of the path is not a directory
     * @throws ReadOnlyFileSystemException (AF_UNIX) the file system where the socket should be bound to is read only
     * @throws IOException if the requested address cannot be assigned for various other reasons
     * @throws UnknownNativeErrorException if anything else goes wrong
     */
    void bind(int fd, Sockaddr sockaddr) throws InvalidFileDescriptorException, IllegalArgumentException, SocketException, AccessDeniedException, FileSystemLoopException, NotDirectoryException, ReadOnlyFileSystemException, IOException, UnknownNativeErrorException;

    /**
     * Writes the socket address the socket is bound to into the given Sockaddr object.
     *
     * @param fd socket fd
     * @param sockaddr output porameter.
     * @throws InvalidFileDescriptorException if the fd is not valid
     * @throws IllegalArgumentException if the fd does not refer to a socket
     * @throws UnknownNativeErrorException if anything else goes wrong
     */
    void getsockname(int fd, Sockaddr sockaddr) throws InvalidFileDescriptorException, IllegalArgumentException, UnknownNativeErrorException;

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

    Statvfs statvfs(String path) throws AccessDeniedException, IOException, FileSystemLoopException, FileNotFoundException, UnknownNativeErrorException;

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
     * returns the effective uid of the user running the process.
     */
    long geteuid();

    /**
     * Returns the username of the current user
     * @throws IOException if an IOError occurs while gathering infos (syscall queries a buch of files)
     * @throws UnknownNativeErrorException If something enexpected occurs
     * @throws IllegalStateException If ENOTTY/ENXIO occurs
     */
    String getlogin_r() throws IOException, UnknownNativeErrorException, IllegalStateException;

    /**
     * Returns group list for given username
     * @param user the username
     * @param group the first group of the user. (This is usually equal to the UID but call getpwnam to be safe)
     * @return a int[] containing all gids the user is in. If the user is not found a array only containing the "group" parameter is returned as this function does not disclose if the user exists or not.
     */
    long[] getgrouplist(String user, long group);

    /**
     * Returns info about a group.
     * Returns null if the group was not found.
     * @param group groupid
     */
    Group getgrgid_r(long group);

    /**
     * Returns user information about a given user.
     * Returns null if the user was not found
     */
    Passwd getpwnam_r(String user);

    /**
     * Returns user information about a given user by uid
     */
    Passwd getpwuid_r(long id);

    /**
     * returns the real uid of the user running the process.
     */
    long getuid();

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

    void fchmod(int fd, int mode);

    void chown(String path, int uid, int gid);

    void fchown(int fd, int uid, int gid);

    void lchown(String path, int uid, int gid);

    /**
     * trigger an ioctl with a device.
     *
     * @param fd the file descriptor to the device
     * @param code the device specific request code
     */
    int ioctl(int fd, int code) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * trigger an ioctl with a device.
     *
     * @param fd the file descriptor to the device
     * @param code the device specific request code
     * @param buf the buffer
     * @param off offset in the buffer.
     *            Warning: ioctl may overflow the buffer and corrupt heap!
     *            Using too small a buffer may cause the memory corruption and result in undefined behavior of the VM.
     */
    int ioctl(int fd, int code, byte[] buf, int off) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * trigger an ioctl with a device.
     *
     * @param fd the file descriptor to the device
     * @param code the device specific request code
     * @param param the param to ioctl. Will be cast to void* but does not have to be a pointer.
     */
    int ioctl(int fd, int code, long param) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * trigger an ioctl with a device.
     *
     * @param fd filedescriptor
     * @param code ioctl request code
     * @param mem memory to pass to ioctl
     * @param off offset in the memory
     */
    int ioctl(int fd, int code, NativeMemory mem, long off) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    int fcntl(int fd, int code) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    int fcntl(int fd, int code, int param) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    int fcntl(int fd, int code, long param) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    int fcntl(int fd, int code, byte[] param, int off) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    int fcntl(int fd, int code, NativeMemory param, long off) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    long sem_open(String name, int oflags) throws AccessDeniedException, QuotaExceededException, FileNotFoundException, FileAlreadyExistsException, UnknownNativeErrorException;

    long sem_open(String name, int oflags, int mode, int value) throws AccessDeniedException, QuotaExceededException, FileNotFoundException, FileAlreadyExistsException, UnknownNativeErrorException;

    void sem_close(long sem) throws UnknownNativeErrorException;

    void sem_unlink(String name) throws AccessDeniedException, FileNotFoundException, UnknownNativeErrorException;

    /**
     * Returns the size of sem_t in bytes.
     * This value changes depending on CPU and JVM architecture.
     */
    int sem_t_size();

    /**
     * Initializes an unnamed semaphore.
     *
     * @param sem ptr to allocated memory. This memory must be able to hold sem_t_size bytes.
     * @param interprocess should the semaphore be interprocess? (ptr must reside in shared memory)
     * @param value initial value of the semaphore.
     */
    void sem_init(long sem, boolean interprocess, int value) throws UnknownNativeErrorException;

    void sem_destroy(long sem) throws UnknownNativeErrorException;

    void sem_post(long sem) throws UnknownNativeErrorException;

    void sem_wait(long sem) throws UnknownNativeErrorException;

    int sem_getvalue(long sem) throws UnknownNativeErrorException;

    boolean sem_trywait(long sem) throws UnknownNativeErrorException;

    boolean sem_timedwait(long sem, long timeoutInMillis) throws UnknownNativeErrorException;

    int shm_open(String name, int oflag, int mode) throws FileAlreadyExistsException, FileNotFoundException, UnknownNativeErrorException, AccessDeniedException, QuotaExceededException;

    void shm_unlink(String name) throws FileNotFoundException, AccessDeniedException, UnknownNativeErrorException;

    void ftruncate(int fd, long len);

    void truncate(String name, long len);

    void mkfifo(String name, int mode) throws AccessDeniedException, QuotaExceededException, FileAlreadyExistsException, FileNotFoundException, NotDirectoryException, ReadOnlyFileSystemException;

    long sizeof_pthread_mutex_t();
    long sizeof_pthread_mutexattr_t();

    long sizeof_pthread_cond_t();
    long sizeof_pthread_condattr_t();

    void pthread_condattr_destroy(long attributes) throws UnknownNativeErrorException;

    void pthread_condattr_init(long attributes) throws UnknownNativeErrorException;

    void pthread_mutexattr_destroy(long attributes) throws UnknownNativeErrorException;

    void pthread_mutexattr_init(long attributes) throws UnknownNativeErrorException;

    int pthread_condattr_getpshared(long attributes) throws UnknownNativeErrorException;

    void pthread_condattr_setpshared(long attributes, int value) throws UnknownNativeErrorException;

    void pthread_mutexattr_setpshared(long attributes, int value) throws UnknownNativeErrorException;

    int pthread_mutexattr_getpshared(long attributes) throws UnknownNativeErrorException;

    int pthread_mutexattr_getrobust(long attributes) throws UnknownNativeErrorException;

    void pthread_mutexattr_setrobust(long attributes, int value) throws UnknownNativeErrorException;

    void pthread_mutex_consistent(long mutex) throws UnknownNativeErrorException;

    void pthread_mutexattr_settype(long attributes, int value) throws UnknownNativeErrorException;

    int pthread_mutexattr_gettype(long attributes) throws UnknownNativeErrorException;

    void pthread_mutex_init(long mutex, long attributes) throws UnknownNativeErrorException, QuotaExceededException;

    void pthread_mutex_destroy(long mutex) throws UnknownNativeErrorException;

    void pthread_mutex_lock(long mutex) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    boolean pthread_mutex_trylock(long mutex) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    void pthread_mutex_unlock(long mutex) throws UnknownNativeErrorException;

    boolean pthread_mutex_timedlock(long mutex, long timeout) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    void pthread_cond_broadcast(long condition) throws UnknownNativeErrorException;

    void pthread_cond_signal(long condition) throws UnknownNativeErrorException;

    void pthread_cond_wait(long condition, long mutex) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    boolean pthread_cond_timedwait(long condition, long mutex, long timeout) throws UnknownNativeErrorException, InconsistentMutexException, UnrecoverableMutexException;

    void pthread_cond_destroy(long condition) throws UnknownNativeErrorException;

    void pthread_cond_init(long condition, long attributes) throws UnknownNativeErrorException;

}
