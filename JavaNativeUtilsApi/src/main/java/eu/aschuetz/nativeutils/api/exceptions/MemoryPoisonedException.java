package eu.aschuetz.nativeutils.api.exceptions;

public class MemoryPoisonedException extends MemoryFaultException {

    public MemoryPoisonedException(String what) {
        super(what);
    }
}
