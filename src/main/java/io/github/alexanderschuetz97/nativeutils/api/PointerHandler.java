package io.github.alexanderschuetz97.nativeutils.api;

import java.io.SyncFailedException;

/**
 * Interface for handler to close/sync pointers of native memory.
 */
public interface PointerHandler {

    /**
     * Close or free the resource associated with the pointer.
     *
     * @param ptr the pointer
     * @param size the size of the pointer if known. Long.MAX_VALUE if not known.
     * @param read is the pointer marked for reading.
     * @param write is the pointer marked for writing.
     */
    void handleClose(long ptr, long size, boolean read, boolean write);

    /**
     * Flush changes made to the pointer to disk/device.
     * This may be a noop.
     *
     * @param ptr the pointer
     * @param size size of the pointer.
     * @param read is the pointer marked for reading.
     * @param write is the pointer marked for writing.
     * @param offset offset of the region to flush changes
     * @param length length of the region to flush changes
     * @param invalidate invalidate all caches
     */
    void handleSync(long ptr, long size, boolean read, boolean write, long offset, long length, boolean invalidate) throws SyncFailedException;
}
