package eu.aschuetz.nativeutils.api;

import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.Stat;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.InvalidPathException;

public interface FreeBSDNativeUtil {

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


}
