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
import io.github.alexanderschuetz97.nativeutils.api.exceptions.InvalidFileDescriptorException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.ShellExecuteException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.GUID;
import io.github.alexanderschuetz97.nativeutils.api.structs.RegData;
import io.github.alexanderschuetz97.nativeutils.api.structs.RegEnumKeyExResult;
import io.github.alexanderschuetz97.nativeutils.api.structs.SpDeviceInfoData;
import io.github.alexanderschuetz97.nativeutils.api.structs.SpDeviceInterfaceData;

import java.util.Arrays;

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
            case("reg"):
                if (args.length != 3)  {
                    System.out.println("reg key query");
                    System.exit(-1);
                    return;
                }

                reg(args[1], args[2]);
                return;
            case("lsreg"):
                if (args.length != 2)  {
                    System.out.println("lsreg key");
                    System.exit(-1);
                    return;
                }

                lsreg(args[1]);
                return;
            case("isadmin"):
                isAdmin();
                return;
            case("admincmd"):
                admincmd(args);
                return;
            case("createEvent"):
                createEvent();
                return;
            case("openEvent"):
                openEvent();
                return;
            case("checkLinux"):
                checkLinux();
                return;
            default:
                System.out.println("no such test " + args[0]);
                System.exit(-1);
                return;
        }
    }

    public static void checkLinux() {
        NativeUtils.getLinuxUtil();
    }
    public static void openEvent() {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        long l;
        try {
            l = wnu.OpenEventA(WinConst.SYNCHRONIZE | WinConst.EVENT_MODIFY_STATE, true, "Global\\Test");

            try {
                wnu.SetEvent(l);
                Thread.sleep(4000);
                System.out.println("WFSO 60s!");
                wnu.WaitForSingleObject(l, 60000);
                System.out.println("SUCCESS!");
            } finally {
                wnu.CloseHandle(l);
            }
        } catch (InterruptedException | InvalidFileDescriptorException e) {
            throw new RuntimeException(e);
        } catch (UnknownNativeErrorException e) {
            System.out.println(wnu.FormatMessageA(e.intCode()));
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void createEvent() {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        long l;
        try {
            l = wnu.CreateEventA(0, true, false, "Global\\Test");

            try {
                System.out.println("WFSO 60s!");
                wnu.WaitForSingleObject(l, 60000);
                wnu.ResetEvent(l);
                Thread.sleep(1000);
                wnu.SetEvent(l);
                System.out.println("SUCCESS!");
            } finally {
                wnu.CloseHandle(l);
            }
        } catch (InterruptedException | InvalidFileDescriptorException e) {
            throw new RuntimeException(e);
        } catch (UnknownNativeErrorException e) {
            System.out.println(wnu.FormatMessageA(e.intCode()));
            e.printStackTrace();
            System.exit(-1);
        }
    }

    public static void admincmd(String[] args) {
        WindowsNativeUtil util = NativeUtils.getWindowsUtil();
        try {
            util.ShellExecuteA(Integer.parseInt(args[1]), "runas", args[2], null, null, Integer.parseInt(args[3]));
        } catch (ShellExecuteException e) {
            System.out.println(e.getHinstance());
            System.out.println(util.FormatMessageA(e.intCode()));
            e.printStackTrace();
        }
    }

    public static void isAdmin() {
        WindowsNativeUtil util = NativeUtils.getWindowsUtil();
        long procID = util.GetCurrentProcess();
        try {
            long token = util.OpenProcessToken(procID, WinConst.TOKEN_QUERY);
            try {
                byte[] tk = util.GetTokenInformation(token, WinConst.TokenElevation);
                System.out.println(Arrays.toString(tk));
            } finally {
                util.CloseHandle(token);
            }

        } catch (InvalidFileDescriptorException e) {
            e.printStackTrace();
            System.exit(-1);
        } catch (UnknownNativeErrorException e) {
            System.out.println(util.FormatMessageA(e.intCode()));
            e.printStackTrace();
            System.exit(-1);
        }


    }

    public static void lsreg(String key) {
        WindowsNativeUtil wni = NativeUtils.getWindowsUtil();
        try {
            long hkey = wni.RegOpenKeyExA(WinConst.HKEY_LOCAL_MACHINE, key, 0, WinConst.KEY_ALL_ACCESS);
            try {
                for (RegEnumKeyExResult res : wni.iterateRegistrySubKeys(hkey)) {
                    System.out.println(res);
                }
            } finally {
                wni.RegCloseKey(hkey);
            }
        } catch (UnknownNativeErrorException e) {
            System.out.println(wni.FormatMessageA(e.intCode()));
            e.printStackTrace();
            System.exit(-1);
        }

    }

    public static void reg(String key, String value) {
        WindowsNativeUtil wni = NativeUtils.getWindowsUtil();
        try {
            long hkey = wni.RegOpenKeyExA(WinConst.HKEY_LOCAL_MACHINE, key, 0, WinConst.KEY_QUERY_VALUE);
            try {
                RegData rd = wni.RegQueryValueExA(hkey, value);
                System.out.println(rd);
            } finally {
                wni.RegCloseKey(hkey);
            }
        } catch (UnknownNativeErrorException e) {
            System.out.println(wni.FormatMessageA(e.intCode()));
            System.exit(-1);
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
