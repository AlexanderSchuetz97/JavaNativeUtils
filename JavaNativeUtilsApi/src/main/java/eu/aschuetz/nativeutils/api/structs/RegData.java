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

import java.util.Arrays;
import java.util.Objects;

public class RegData {

    public enum RegType {
        REG_BINARY,
        REG_DWORD,
        REG_EXPAND_SZ,
        REG_LINK,
        REG_MULTI_SZ,
        REG_NONE,
        REG_QWORD,
        REG_SZ
    }

    private final RegType type;

    private final Object value;

    public RegData(int value) {
        this.type = RegType.REG_DWORD;
        this.value = value;
    }

    public RegData(long value) {
        this.type = RegType.REG_QWORD;
        this.value = value;
    }

    public RegData(Object data, Object type) {
        this.type = (RegType) type;
        this.value = data;
    }

    public RegType type() {
        return type;
    }

    public Object value() {
        return value;
    }

    public Number number() {
        return (Number) value;
    }

    public int asInt() {
        return number().intValue();
    }

    public long asLong() {
        return number().longValue();
    }

    public byte[] binary() {
        return (byte[]) value;
    }

    public String string() {
        return (String) value;
    }

    public String[] strings() {
        return (String[]) value;
    }

    /**
     * for debug purposes only
     */
    @Override
    public String toString() {
        String vString;
        if (value instanceof byte[]) {
            vString = Arrays.toString((byte[]) value);
        } else if (value instanceof String[]) {
            StringBuilder sb = new StringBuilder();
            boolean f = false;
            for (String s : (String[]) value) {
                if (f) {
                    sb.append(",");
                }
                f = true;
                sb.append(s);
            }
            vString = sb.toString();
        } else {
            vString = Objects.toString(value);
        }

        return  type + " | " + vString;
    }
}
