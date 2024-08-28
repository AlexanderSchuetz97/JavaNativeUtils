package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.PosixNativeUtil;
import eu.aschuetz.nativeutils.api.exceptions.FileIsDirectoryException;
import eu.aschuetz.nativeutils.api.exceptions.ResourceBusyException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.Stat;
import eu.aschuetz.nativeutils.api.structs.Utsname;

import java.io.IOException;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileSystemLoopException;
import java.nio.file.ReadOnlyFileSystemException;

public abstract class JNIPosixNativeUtil extends JNICommonNativeUtil implements PosixNativeUtil {

    @Override
    public native Stat stat(String path);

    @Override
    public native void symlink(String targetPath, String sourcePath) throws IOException, UnknownNativeErrorException;

    @Override
    public native void unlink(String path) throws IOException, AccessDeniedException, ResourceBusyException, FileIsDirectoryException, FileSystemLoopException, ReadOnlyFileSystemException;

    @Override
    public native Utsname uname();

    @Override
    public boolean isPosix() {
        return true;
    }

    @Override
    public boolean isWindows() {
        return false;
    }

}
