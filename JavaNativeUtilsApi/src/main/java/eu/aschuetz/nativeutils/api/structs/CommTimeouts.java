//
// Copyright Alexander Schütz, 2024
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

public class CommTimeouts {

    long ReadIntervalTimeout;
    long ReadTotalTimeoutMultiplier;
    long ReadTotalTimeoutConstant;
    long WriteTotalTimeoutMultiplier;
    long WriteTotalTimeoutConstant;

    public long getReadIntervalTimeout() {
        return ReadIntervalTimeout;
    }

    public void setReadIntervalTimeout(long readIntervalTimeout) {
        ReadIntervalTimeout = readIntervalTimeout;
    }

    public long getReadTotalTimeoutMultiplier() {
        return ReadTotalTimeoutMultiplier;
    }

    public void setReadTotalTimeoutMultiplier(long readTotalTimeoutMultiplier) {
        ReadTotalTimeoutMultiplier = readTotalTimeoutMultiplier;
    }

    public long getReadTotalTimeoutConstant() {
        return ReadTotalTimeoutConstant;
    }

    public void setReadTotalTimeoutConstant(long readTotalTimeoutConstant) {
        ReadTotalTimeoutConstant = readTotalTimeoutConstant;
    }

    public long getWriteTotalTimeoutMultiplier() {
        return WriteTotalTimeoutMultiplier;
    }

    public void setWriteTotalTimeoutMultiplier(long writeTotalTimeoutMultiplier) {
        WriteTotalTimeoutMultiplier = writeTotalTimeoutMultiplier;
    }

    public long getWriteTotalTimeoutConstant() {
        return WriteTotalTimeoutConstant;
    }

    public void setWriteTotalTimeoutConstant(long writeTotalTimeoutConstant) {
        WriteTotalTimeoutConstant = writeTotalTimeoutConstant;
    }

    @Override
    public String toString() {
        return "CommTimeouts{" +
                "ReadIntervalTimeout=" + ReadIntervalTimeout +
                ", ReadTotalTimeoutMultiplier=" + ReadTotalTimeoutMultiplier +
                ", ReadTotalTimeoutConstant=" + ReadTotalTimeoutConstant +
                ", WriteTotalTimeoutMultiplier=" + WriteTotalTimeoutMultiplier +
                ", WriteTotalTimeoutConstant=" + WriteTotalTimeoutConstant +
                '}';
    }
}
