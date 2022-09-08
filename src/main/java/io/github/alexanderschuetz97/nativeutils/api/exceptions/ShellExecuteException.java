package io.github.alexanderschuetz97.nativeutils.api.exceptions;

public class ShellExecuteException extends UnknownNativeErrorException {

    private final long hinstance;

    public ShellExecuteException(long code, long hinstance) {
        super(code);
        this.hinstance = hinstance;
    }

    public long getHinstance() {
        return hinstance;
    }
}
