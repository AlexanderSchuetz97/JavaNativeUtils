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
package eu.aschuetz.nativeutils.api.structs;

import java.util.Objects;

public class Iovec {

    private final byte[] payload;
    private final int off;
    private final int len;

    /**
     * Output variable only. How many bytes of payload at off were used
     */
    private int size = 0;

    public Iovec(int size) {
        this(new byte[size]);
    }

    public Iovec(byte[] payload) {
        this.payload = Objects.requireNonNull(payload);
        this.off = 0;
        this.len = payload.length;
    }

    public Iovec(byte[] paylaod, int off, int len) {
        this.payload = Objects.requireNonNull(paylaod);
        this.off = off;
        this.len = len;
    }

    public int getOff() {
        return off;
    }

    public int getLen() {
        return len;
    }

    public byte[] getPayload() {
        return payload;
    }


    public int getSize() {
        return size;
    }

}
