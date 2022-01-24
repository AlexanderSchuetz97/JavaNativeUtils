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
package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.NativeMemory;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import io.github.alexanderschuetz97.nativeutils.api.WinConst;
import io.github.alexanderschuetz97.nativeutils.api.WindowsNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.GUID;
import io.github.alexanderschuetz97.nativeutils.api.structs.SpDeviceInfoData;
import io.github.alexanderschuetz97.nativeutils.api.structs.SpDeviceInterfaceData;

public class JavaNativeUtilsStandaloneTest {

    public static void main(String[] args) throws Throwable {

        if (args.length == 0) {
            System.out.println("no such test 'null'");
            System.exit(-1);
            return;
        }

        switch (args[0]) {
            case("lsivshmem"):
               lsivshmem();
               return;
            case("lsdev"):
                if (args.length != 2)  {
                    System.out.println("lsdev <device-guid>");
                    System.exit(-1);
                    return;
                }
                listDevices(args[1]);
                return;
            default:
                System.out.println("no such test " + args[0]);
                System.exit(-1);
                return;
        }
    }

    public static void listDevices(String guid) throws Throwable {
        WindowsNativeUtil wni = NativeUtils.getWindowsUtil();

        try {
            for (String dev : wni.iterateDeviceInterfaces(null, null, WinConst.DIGCF_PRESENT | WinConst.DIGCF_ALLCLASSES | WinConst.DIGCF_DEVICEINTERFACE, new GUID(guid))) {
                System.out.println(dev);
            }
        } catch (UnknownNativeErrorException e) {
            System.out.println(wni.FormatMessageA((int) e.getCode()));
        }

        System.out.println("END");
    }

    public static void lsivshmem() throws Throwable {
        WindowsNativeUtil wni = NativeUtils.getWindowsUtil();
        try {
            GUID guid = new GUID("DF576976-569D-4672-95A0-F57E4EA0B210");


            long handle = wni.SetupDiGetClassDevsA(null, null, 0, WinConst.DIGCF_PRESENT | WinConst.DIGCF_ALLCLASSES | WinConst.DIGCF_DEVICEINTERFACE);

            int i = 0;
            while(true) {
                SpDeviceInterfaceData spi = wni.SetupDiEnumDeviceInterfaces(handle, null, guid, i);

                if (spi == null) {
                    System.out.println("NO_MORE_ITEMS");
                    break;
                }

                SpDeviceInfoData spdevInfo = new SpDeviceInfoData();
                String path = wni.SetupDiGetDeviceInterfaceDetail(handle, spi, spdevInfo);
                System.out.println(path);

                long devHandle = wni.CreateFileA(path, 0, false, false, false, WindowsNativeUtil.CreateFileA_createMode.OPEN_EXISTING, 0);
                long size = 0;
                try (NativeMemory buf = wni.malloc(8)) {
                    int len = wni.DeviceIoControl(devHandle, wni.CTL_CODE(WinConst.FILE_DEVICE_UNKNOWN, 0x801, WinConst.METHOD_BUFFERED, WinConst.FILE_ANY_ACCESS),  null, 0, 0, buf, 0, 8);
                    size = len == 4 ? buf.readUnsignedInt(0) : buf.readLong(0);
                }
                System.out.println("SIZE = " + size);

                System.out.println();
                wni.CloseHandle(devHandle);
                i++;
            }

            wni.SetupDiDestroyDeviceInfoList(handle);
            System.out.println("END");
        } catch (UnknownNativeErrorException e) {
            System.out.println(wni.FormatMessageA((int) e.getCode()));
        }

    }
}
