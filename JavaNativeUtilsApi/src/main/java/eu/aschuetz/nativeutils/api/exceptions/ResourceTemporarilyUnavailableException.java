package eu.aschuetz.nativeutils.api.exceptions;

import java.io.IOException;

public class ResourceTemporarilyUnavailableException extends IOException {

    public ResourceTemporarilyUnavailableException(String what) {
        super(what);
    }
}
