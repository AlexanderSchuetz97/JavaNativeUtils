package eu.aschuetz.nativeutils.api.exceptions;

import java.io.IOException;

public class MemoryFaultException extends IOException {
    public MemoryFaultException(String what) {
        super(what);
    }
}
