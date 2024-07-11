package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.exceptions.FileIsDirectoryException;
import eu.aschuetz.nativeutils.api.exceptions.ResourceBusyException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.Stat;

import java.io.IOException;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.ReadOnlyFileSystemException;

public abstract class JNIPosixNativeUtil extends JNICommonNativeUtil {

    public native Stat stat(String path);

    public native void symlink(String targetPath, String sourcePath) throws IOException, UnknownNativeErrorException;

    public native void unlink(String path) throws IOException, AccessDeniedException, ResourceBusyException, FileIsDirectoryException, FileSystemLoopException, ReadOnlyFileSystemException;

}
