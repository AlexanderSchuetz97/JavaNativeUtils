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

import java.io.IOException;

/**
 * Exception thrown when an operation that is still running and being attempted in the background took longer to complete
 * than some timeout value. The status of the background operation has to be retrieved by some other syscall depending on the syscall that caused this exception to be thrown.
 */
public class OperationInProgressException extends IOException {
    public OperationInProgressException() {
        super();
    }

    public OperationInProgressException(String message) {
        super(message);
    }
}
