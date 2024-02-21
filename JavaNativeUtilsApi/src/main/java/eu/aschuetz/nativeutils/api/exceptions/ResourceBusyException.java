package eu.aschuetz.nativeutils.api.exceptions;

import java.io.IOException;

public class ResourceBusyException extends IOException {

    public ResourceBusyException(String what) {
        super(what);
    }
}
