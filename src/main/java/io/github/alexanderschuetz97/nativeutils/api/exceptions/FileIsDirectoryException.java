package io.github.alexanderschuetz97.nativeutils.api.exceptions;

import java.nio.file.FileSystemException;

public class FileIsDirectoryException extends FileSystemException {
    public FileIsDirectoryException(String file) {
        super(file);
    }
}
