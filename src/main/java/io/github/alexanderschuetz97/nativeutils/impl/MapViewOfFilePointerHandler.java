package io.github.alexanderschuetz97.nativeutils.impl;

import io.github.alexanderschuetz97.nativeutils.api.PointerHandler;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;

import java.io.SyncFailedException;

class MapViewOfFilePointerHandler implements PointerHandler {

    static MapViewOfFilePointerHandler INSTANCE = new MapViewOfFilePointerHandler();

    @Override
    public void handleClose(long ptr, long size, boolean read, boolean write) {
        if (ptr != 0) {
            try {
                JNIWindowsNativeUtil._UnmapViewOfFile(ptr);
            } catch (UnknownNativeErrorException e) {
                throw new RuntimeException(e);
            }
        }
    }

    @Override
    public void handleSync(long ptr, long size, boolean read, boolean write, long offset, long length, boolean invalidate) throws SyncFailedException {
        //NOOP
    }
}
