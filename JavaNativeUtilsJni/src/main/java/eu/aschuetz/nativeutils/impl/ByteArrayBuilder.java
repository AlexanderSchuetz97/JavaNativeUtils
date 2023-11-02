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

package eu.aschuetz.nativeutils.impl;

import java.util.Arrays;

/**
 * Poor man's StringBuilder
 */
class ByteArrayBuilder {

    protected byte buf[] = new byte[64];

    protected int nextIndex;

    private void ensureSize(int index) {
        if (buf.length > index) {
            return;
        }

        int cap = buf.length << 1;
        if (cap - index < 0) {
            cap = index;
        }

        buf = Arrays.copyOf(buf, cap);
    }

    public void append(int by) {
        ensureSize(nextIndex);
        buf[nextIndex++] = (byte) by;
    }

    public int getCount() {
        return nextIndex;
    }

    public byte[] getBuffer() {
        return buf;
    }
}
