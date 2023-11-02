//
// Copyright Alexander Schütz, 2023
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
 * Thrown when a robust Mutex in an unrecoverable state.
 * This exception is only thrown for robust mutexes where pthread_mutex_consistent was not called before unlocking when InconsistentMutexException was thrown.
 *
 * The only valid operation for such a mutex is pthread_mutex_destroy.
 */
public class UnrecoverableMutexException extends Exception {
    public UnrecoverableMutexException() {

    }
}
