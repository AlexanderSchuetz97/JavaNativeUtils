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
package eu.aschuetz.nativeutils;

import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.WinConst;
import eu.aschuetz.nativeutils.api.WindowsNativeUtil;
import eu.aschuetz.nativeutils.api.exceptions.InvalidFileDescriptorException;
import eu.aschuetz.nativeutils.api.exceptions.ShellExecuteException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;

import java.io.IOException;
import java.lang.annotation.Native;
import java.util.Arrays;
import java.util.List;
import java.util.Random;

public class JavaNativeUtilsStandaloneTest {

    public static void main(String[] args) throws Throwable {

        if (args.length == 0) {
            System.out.println("no such test 'null'");
            System.exit(-1);
            return;
        }

        switch (args[0]) {
            case("osenv"):
                System.out.println("os.arch: " + System.getProperty("os.arch"));
                System.out.println("os.name: " + System.getProperty("os.name"));
                return;
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
            case("pipC"):
                pipeClientWin(args[1]);
                return;
            case("pipS"):
                pipeServerWin(args[1]);
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
            case("mmapWinW"):
                mmapWinW(args[1]);
                return;
            case("mmapWinR"):
                mmapWinR(args[1]);
                return;
            case("openEvent"):
                openEvent();
                return;
            case("checkLinux"):
                if (args.length == 2) {
                    System.load(args[1]);
                }
                checkLinux();
                return;
            case("GetIpForwardTable2"):
                GetIpForwardTable2();
                return;
            default:
                System.out.println("no such test " + args[0]);
                System.exit(-1);
                return;
        }
    }

    private static void pipeClientWin(String name) {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        try (NativeMemory nmem = wnu.malloc(4)){
            nmem.zero();
            long hdl = wnu.CreateFileA(name, WinConst.FILE_READ_ACCESS | WinConst.FILE_WRITE_ACCESS, false, true, true, WindowsNativeUtil.CreateFileA_createMode.OPEN_EXISTING, 0);
            try {
                while(true) {
                    wnu.WriteFile(hdl, nmem, 0, 4);
                    wnu.ReadFile(hdl, nmem, 0, 4);
                    System.out.println(nmem.readInt(0));
                }


            } finally {
                wnu.CloseHandle(hdl);
            }
        } catch (UnknownNativeErrorException e) {
            e.printStackTrace();
            System.out.println(wnu.FormatMessageA(e.intCode()));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void pipeServerWin(String name) {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        try (NativeMemory nmem = wnu.malloc(4)){

            long hdl = wnu.CreateNamedPipeA(name, WinConst.PIPE_ACCESS_DUPLEX | WinConst.FILE_FLAG_OVERLAPPED, WinConst.PIPE_TYPE_BYTE, 255, 0x1000, 0x1000, 10000, 0);

            long event = wnu.CreateEventA(0, false, false, null);

            long overlap = wnu.ConnectNamedPipe(hdl, event);
            System.out.println("ConnectNamedPipe " + overlap);
            if (wnu.WaitForSingleObject(event, 10000)) {
                System.out.println("GOT PIPE");
            } else {
                System.out.println("Timeout");
                System.exit(-1);
            }
            System.out.println("OVL Bytes " + wnu.GetOverlappedResult(hdl, overlap, true));
            System.out.println("GetOverlappedResult");
            while(true) {
                overlap = wnu.ReadFile(hdl, nmem, 0, 4, overlap, event);
                System.out.println("OVL Bytes " + wnu.GetOverlappedResult(hdl, overlap, true));
                System.out.println(nmem.readInt(0));
                nmem.writeInt(0,nmem.readInt(0)+1);
                overlap = wnu.WriteFile(hdl, nmem, 0, 4, overlap, event);
                System.out.println("OVL Bytes " + wnu.GetOverlappedResult(hdl, overlap, true));
                System.out.println("OVERLAP " + overlap);
                if (nmem.readInt(0) > 100) {
                    break;
                }
                Thread.sleep(200);
            }

            wnu.free(overlap);
            wnu.CloseHandle(event);
            wnu.FlushFileBuffers(hdl);
            wnu.DisconnectNamedPipe(hdl);
            wnu.CloseHandle(hdl);
        } catch (UnknownNativeErrorException e) {
            System.out.println(wnu.FormatMessageA(e.intCode()));
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void mmapWinW(String name) {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        try {
            System.out.println(wnu.INVALID_HANDLE_VALUE());
            long hmap = wnu.CreateFileMappingA(wnu.INVALID_HANDLE_VALUE(), 0, WinConst.PAGE_READWRITE, 0, 4096, name);
            System.out.println(hmap);
            NativeMemory mem = wnu.MapViewOfFileEx(hmap, WinConst.FILE_MAP_ALL_ACCESS, 0, 0, 4096, 0);
            long l = new Random().nextLong();
            mem.writeLong(0, l);
            System.out.println("WROTE " + l);
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            mem.close();
            wnu.CloseHandle(hmap);
            System.out.println("DONE");
        } catch (UnknownNativeErrorException e) {
            System.out.println(wnu.FormatMessageA(e.intCode()));
            e.printStackTrace();
        } catch (InvalidFileDescriptorException e) {
            e.printStackTrace();
        }
    }

    private static void mmapWinR(String name) {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        try {
            long hmap = wnu.OpenFileMappingA(WinConst.FILE_MAP_ALL_ACCESS, false, name);
            NativeMemory mem = wnu.MapViewOfFileEx(hmap, WinConst.FILE_MAP_ALL_ACCESS, 0, 0, 4096, 0);

            long l = mem.readLong(0);
            System.out.println("READ " + l);
            try {
                Thread.sleep(10000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            l = mem.readLong(0);
            System.out.println("READ " + l);

            mem.close();
            wnu.CloseHandle(hmap);
        } catch (UnknownNativeErrorException e) {
            System.out.println(wnu.FormatMessageA(e.intCode()));
            e.printStackTrace();
        } catch (InvalidFileDescriptorException e) {
            e.printStackTrace();
        }
    }


    private static void GetIpForwardTable2() {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        try {
            List<MibIpForwardRow2> mib = wnu.GetIpForwardTable2(WinConst.AF_INET);
            System.out.println("MIB_TABLE");
            System.out.println(mib);
        } catch (UnknownNativeErrorException e) {
            System.out.println(wnu.FormatMessageA(e.intCode()));
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static void checkLinux() {
        try {
            System.out.println(NativeUtils.getLinuxUtil().stat("/tmp"));
        } catch (UnknownNativeErrorException e) {
            e.printStackTrace();
            System.out.println(NativeUtils.getLinuxUtil().strerror_r(e.intCode()));
        } catch (IOException e) {
            e.printStackTrace();
        }
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
