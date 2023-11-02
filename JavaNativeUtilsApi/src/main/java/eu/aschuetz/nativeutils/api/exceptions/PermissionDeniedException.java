package eu.aschuetz.nativeutils.api.exceptions;

import java.io.IOException;

public class PermissionDeniedException extends IOException {

    public PermissionDeniedException(String file) {
        super(file);
    }

    public PermissionDeniedException(String file, String reason) {
        this(file + " " + reason);
    }

}
