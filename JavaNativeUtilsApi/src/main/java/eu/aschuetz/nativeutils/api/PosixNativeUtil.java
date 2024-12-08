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
package eu.aschuetz.nativeutils.api;

import eu.aschuetz.nativeutils.api.consts.PosixConstProvider;
import eu.aschuetz.nativeutils.api.exceptions.*;
import eu.aschuetz.nativeutils.api.structs.Stat;
import eu.aschuetz.nativeutils.api.structs.Utsname;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.file.*;

public interface PosixNativeUtil extends NativeUtil {


    /**
     * Gets a constant provider for the current OS.
     * Some OS/Cpu architectures use different numeric values for the same constants.
     */
    PosixConstProvider getPosixConstProvider();

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
     * Unlinks a link
     *
     * @param path specifies the path to the link to unlink.
     * @throws IOException If an IOError occurs when unlinking
     * @throws AccessDeniedException If EACCESS occurs
     * @throws ResourceBusyException if EBUSY occurs
     * @throws FileIsDirectoryException If path is a directory and not a symlink (Linux Only)
     * @throws FileSystemLoopException If the path contains a loop of symbolic links
     * @throws ReadOnlyFileSystemException If the file system is read only
     */
    void unlink(String path) throws IOException, AccessDeniedException, ResourceBusyException, FileIsDirectoryException, FileSystemLoopException, ReadOnlyFileSystemException;



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
     * Note: on non X86/AMD64 this will always return null.
     */
    String __get_cpuid_count_model();

    /**
     * gets information about the unix system.
     */
    Utsname uname();

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

    /**
     * Close a file descriptor
     */
    void close(int fd) throws InvalidFileDescriptorException, IOException;

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

}
