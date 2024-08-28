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

public class RegEnumKeyExResult {

    private String name;
    private String className;
    private long lastWriteTime;

    private RegEnumKeyExResult() {
        //called from c
    }

    public String getName() {
        return name;
    }

    public String getClassName() {
        return className;
    }

    public long getLastWriteTime() {
        return lastWriteTime;
    }

    @Override
    public String toString() {
        return "SubKey " + name + " : " + className + " @ " + lastWriteTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        RegEnumKeyExResult that = (RegEnumKeyExResult) o;

        if (lastWriteTime != that.lastWriteTime) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        return className != null ? className.equals(that.className) : that.className == null;
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + (className != null ? className.hashCode() : 0);
        result = 31 * result + (int) (lastWriteTime ^ (lastWriteTime >>> 32));
        return result;
    }
}
