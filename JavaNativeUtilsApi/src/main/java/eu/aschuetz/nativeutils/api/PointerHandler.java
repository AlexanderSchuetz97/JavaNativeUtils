//
// Copyright Alexander Schütz, 2021-2022
//
// This file is part of JavaNativeUtils.
//
// JavaNativeUtils is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// JavaNativeUtils is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// A copy of the GNU Lesser General Public License should be provided
// in the COPYING & COPYING.LESSER files in top level directory of JavaNativeUtils.
// If not, see <https://www.gnu.org/licenses/>.
//
package eu.aschuetz.nativeutils.api;

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
    void handleClose(long ptr, long size);

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
    void handleSync(long ptr, long size, long offset, long length, boolean invalidate) throws SyncFailedException;
}
