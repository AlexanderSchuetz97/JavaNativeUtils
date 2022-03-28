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
package io.github.alexanderschuetz97.nativeutils.api.exceptions;

/**
 * This exception signals the occurance of a native error with a given code.
 * The meaning of the code depends on the context and OS of the syscall made.
 */
public class UnknownNativeErrorException extends Exception {

    private long code;

    public UnknownNativeErrorException() {
        this(-1);
    }

    /**
     * This code has a different meaning for every function call.
     */
    public UnknownNativeErrorException(long code) {
        super(Long.toString(code));
        this.code = code;
    }

    public long getCode() {
        return code;
    }

    public int intCode() {
        return (int) getCode();
    }
}
