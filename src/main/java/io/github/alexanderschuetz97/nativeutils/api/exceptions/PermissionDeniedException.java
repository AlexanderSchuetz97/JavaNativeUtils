package io.github.alexanderschuetz97.nativeutils.api.exceptions;

import java.io.IOException;
import java.nio.file.AccessDeniedException;

public class PermissionDeniedException extends IOException {

    public PermissionDeniedException(String file) {
        super(file);
    }

    public PermissionDeniedException(String file, String reason) {
        this(file + " " + reason);
    }

}
