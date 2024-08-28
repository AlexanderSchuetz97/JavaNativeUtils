//
// Copyright Alexander Schütz, 2021-2024
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
 * This exception is thrown by linux when the pthread implementation tries to lock a robust mutex which
 * WAS locked by another process or thread that has died before releasing the mutex.
 *
 * If this exception is thrown then the mutex is locked successfully and must call unlock.
 * However, before unlock is called the thread should call pthread_mutex_consistent if the locked data is in a consistent state.
 * If pthread_mutex_consistent is not called then after unlocking every further attempt to lock() will fail.
 *
 */
public class InconsistentMutexException extends Exception {

    public InconsistentMutexException() {

    }
}
