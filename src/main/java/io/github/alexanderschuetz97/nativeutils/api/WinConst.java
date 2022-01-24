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
package io.github.alexanderschuetz97.nativeutils.api;

/**
 * This file contains some constants from the windows header files.
 */
public interface WinConst {
    ////
    // Flags for SetupDiGetClassDevsW
    ///

    int DIGCF_DEFAULT = 1;
    int DIGCF_PRESENT = 2;
    int DIGCF_ALLCLASSES = 4;
    int DIGCF_PROFILE = 8;
    int DIGCF_DEVICEINTERFACE = 16;

    // DeviceIoControl Flags
    int FILE_DEVICE_UNKNOWN = 0x00000022;
    int METHOD_BUFFERED = 0;
    int METHOD_IN_DIRECT = 1;
    int METHOD_OUT_DIRECT = 2;
    int METHOD_NEITHER = 3;
    int FILE_ANY_ACCESS = 0;
    int FILE_READ_ACCESS = 1;
    int FILE_WRITE_ACCESS = 2;
}

