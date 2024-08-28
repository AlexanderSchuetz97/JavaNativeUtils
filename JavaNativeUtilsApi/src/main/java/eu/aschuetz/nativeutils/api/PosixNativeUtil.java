package eu.aschuetz.nativeutils.api;

import eu.aschuetz.nativeutils.api.exceptions.FileIsDirectoryException;
import eu.aschuetz.nativeutils.api.exceptions.QuotaExceededException;
import eu.aschuetz.nativeutils.api.exceptions.ResourceBusyException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.Stat;
import eu.aschuetz.nativeutils.api.structs.Utsname;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.*;

public interface PosixNativeUtil extends NativeUtil {

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
}
