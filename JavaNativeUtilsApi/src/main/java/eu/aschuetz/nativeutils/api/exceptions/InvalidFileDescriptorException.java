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
 * This exception is thrown when a passed file descriptor has been detected to be invalid.
 * This is usally the case when errno EBADF occurs or FileDescriptor.fd is -1.
 * On windows this occurs when FileDescriptor.handle is INVALID_HANDLE_VALUE (-1).
 */
public class InvalidFileDescriptorException extends IOException {

}
