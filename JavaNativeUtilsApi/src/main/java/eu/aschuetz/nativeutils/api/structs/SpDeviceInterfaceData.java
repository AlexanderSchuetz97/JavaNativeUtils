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
package eu.aschuetz.nativeutils.api.structs;

/**
 * This data structure is used for several syscalls in the setupapi.h
 * Its meaning changes depending on what syscall returned it or takes it as an input.
 */
public class SpDeviceInterfaceData {
    int cbSize;
    GUID InterfaceClassGuid = new GUID();
    int flags;

    //Reserved by os to store some info
    long ptr;

    private SpDeviceInterfaceData() {
        //Called from c
    }

    public SpDeviceInterfaceData(int cbSize, GUID guid, int flags) {
        this.cbSize = cbSize;
        this.InterfaceClassGuid = guid.clone();
        this.flags = flags;
        this.ptr = 0;
    }

    public int getCbSize() {
        return cbSize;
    }

    public GUID getInterfaceClassGuid() {
        return InterfaceClassGuid.clone();
    }

    public int getFlags() {
        return flags;
    }

    public long getPtr() {
        return ptr;
    }

    @Override
    public String toString() {
        return "SpDeviceInterfaceData{" +
                "cbSize=" + cbSize +
                ", InterfaceClassGuid=" + InterfaceClassGuid +
                ", flags=" + flags +
                ", ptr=" + ptr +
                '}';
    }
}
