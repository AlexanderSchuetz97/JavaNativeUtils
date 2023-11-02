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
package eu.aschuetz.nativeutils.api.exceptions;

/**
 * WaitForMultipleObjects & WaitForSingleObject when they return WAIT_ABANDONED/WAIT_ABANDONED_0
 */
public class MutexAbandonedException extends RuntimeException {

    private final long handle;

    public MutexAbandonedException(long handle) {
        this.handle = handle;
    }

    /**
     * May be -1 if the handle could not be determined due to calling WaitForMultipleObjects with waitAll set to true
     */
    public long getHandle() {
        return handle;
    }
}
