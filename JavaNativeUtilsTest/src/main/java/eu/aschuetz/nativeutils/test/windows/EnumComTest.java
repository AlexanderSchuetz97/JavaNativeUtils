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
package eu.aschuetz.nativeutils.test.windows;

import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.WinConst;
import eu.aschuetz.nativeutils.api.WindowsNativeUtil;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.CommTimeouts;
import eu.aschuetz.nativeutils.api.structs.DCB;
import eu.aschuetz.nativeutils.api.structs.RegEnumKeyExResult;
import eu.aschuetz.nativeutils.api.structs.RegEnumValueResult;
import org.junit.Assert;
import org.junit.Test;

import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class EnumComTest {

    @Test
    public void test() throws Exception {
        Set<String> ports = new LinkedHashSet<>();
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        try {
            long hkey = wnu.RegOpenKeyExA(WinConst.HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM", 0, WinConst.KEY_READ | WinConst.KEY_QUERY_VALUE);
            try {
                int i = 0;
                while(true) {
                    RegEnumValueResult regEnumValueResult = wnu.RegEnumValueA(hkey, i++);
                    if (regEnumValueResult == null) {
                        break;
                    }

                    ports.add(regEnumValueResult.getData().string());
                }

            } finally {
                wnu.RegCloseKey(hkey);
            }
        } catch (UnknownNativeErrorException e) {
            e.printStackTrace();
            Assert.fail(wnu.FormatMessageA(e.intCode()));
        }

        Thread.sleep(200);

        for (String port : ports) {
            try {
                long l = wnu.CreateFileA(port, WinConst.FILE_READ_ACCESS | WinConst.FILE_WRITE_ACCESS, true, true, true, WindowsNativeUtil.CreateFileA_createMode.OPEN_EXISTING, 0);

                try {
                    DCB dcb = wnu.GetCommState(l);
                    System.out.println("DCB " + port + " " + dcb);
                    dcb.setBaudRate(9600);
                    wnu.SetCommState(l, dcb);
                    dcb = wnu.GetCommState(l);
                    System.out.println("DCB2 " + port + " " + dcb);
                    Assert.assertEquals(dcb.getBaudRate(), 9600);
                    CommTimeouts timeouts = wnu.GetCommTimeouts(l);
                    System.out.println("TIMEOUTS " + port + " " + timeouts);
                    timeouts.setReadTotalTimeoutConstant(5000);
                    wnu.SetCommTimeouts(l, timeouts);
                    timeouts = wnu.GetCommTimeouts(l);
                    System.out.println("TIMEOUTS2 " + port + " " + timeouts);
                    Assert.assertEquals(timeouts.getReadTotalTimeoutConstant(), 5000);

                    byte[] buf = new byte[256];
                    long b4 = System.currentTimeMillis();
                    int i = wnu.ReadFile(l, buf, 0, buf.length);
                    Assert.assertEquals(0, i);
                    long after = System.currentTimeMillis();
                    Assert.assertTrue(after-b4 > 4000);

                    //wnu.SetCommTimeouts(l, timeouts);


                } finally {
                    wnu.CloseHandle(l);
                }
            } catch (UnknownNativeErrorException e) {
                e.printStackTrace();
                Assert.fail(wnu.FormatMessageA(e.intCode()));

            }

        }
   }
}
