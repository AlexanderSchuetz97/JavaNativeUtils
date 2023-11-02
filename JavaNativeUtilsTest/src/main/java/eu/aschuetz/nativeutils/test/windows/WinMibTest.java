//
// Copyright Alexander Schütz, 2021-2023
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
import eu.aschuetz.nativeutils.api.structs.MibIpForwardRow2;
import eu.aschuetz.nativeutils.api.structs.Sockaddr;
import org.junit.Assert;
import org.junit.Test;

import java.util.Arrays;
import java.util.List;

public class WinMibTest {

    @Test
    public void testMib() throws Throwable {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        try {
            List<MibIpForwardRow2> mib = wnu.GetIpForwardTable2(WinConst.AF_INET);
            List<MibIpForwardRow2> mib6 = wnu.GetIpForwardTable2(WinConst.AF_INET6);

            Assert.assertFalse(mib.isEmpty());
            Assert.assertFalse(mib6.isEmpty());

            int i = 0;
            for (MibIpForwardRow2 mibRow : mib) {
                System.out.println("MIB_TABLE " + i++);
                String name = wnu.ConvertInterfaceLuidToNameA(mibRow.getInterfaceLuid());
                System.out.println(name);
                System.out.println(wnu.ConvertInterfaceLuidToAlias(mibRow.getInterfaceLuid()));
                Assert.assertEquals(mibRow.getInterfaceLuid(), wnu.ConvertInterfaceNameToLuidA(name));
                System.out.println(mibRow);
                System.out.println(Arrays.toString(mibRow.getDestinationPrefixAddress().getAddress()));
                System.out.println(mibRow.getDestinationPrefixAddress().getAddress().length);
                System.out.println();
            }

            for (MibIpForwardRow2 mibRow : mib6) {
                System.out.println("MIB_TABLE6 " + i++);
                String name = wnu.ConvertInterfaceLuidToNameA(mibRow.getInterfaceLuid());
                System.out.println(name);
                System.out.println(wnu.ConvertInterfaceLuidToAlias(mibRow.getInterfaceLuid()));
                Assert.assertEquals(mibRow.getInterfaceLuid(), wnu.ConvertInterfaceNameToLuidA(name));
                System.out.println(mibRow);
                System.out.println(Arrays.toString(mibRow.getDestinationPrefixAddress().getAddress()));
                System.out.println(mibRow.getDestinationPrefixAddress().getAddress().length);
                System.out.println();
            }

            MibIpForwardRow2 row = new MibIpForwardRow2();
            row.setMetric(69);
            row.setImmortal(true);
            row.setLoopback(false);
            row.setAutoconfigureAddress(false);
            row.setInterfaceIndex(mib.get(0).getInterfaceIndex());
            row.setInterfaceLuid(mib.get(0).getInterfaceLuid());
            row.setPublish(false);
            row.setValidLifetime(4294967295L);
            row.setPreferredLifetime(4294967295L);
            row.setProtocol(10006);
            row.setAge(0);
            byte[] srcRaw = new byte[]{69,0,0,0};
            byte[] bbuf = new byte[28];
            bbuf[0] = 2;
            bbuf[4] = srcRaw[0];
            bbuf[5] = srcRaw[1];
            bbuf[6] = srcRaw[2];
            bbuf[7] = srcRaw[3];

            //new byte[]{2,0,0,0, srcRaw[0], srcRaw[1], srcRaw[2], srcRaw[3]}

            Sockaddr src = new Sockaddr(WinConst.AF_INET, bbuf);
            byte[] dstRaw = mib.get(0).getNextHop().parseWin32_SOCKADDR_INET().getAddress().getAddress();

            bbuf = new byte[28];
            bbuf[0] = 2;
            bbuf[4] = dstRaw[0];
            bbuf[5] = dstRaw[1];
            bbuf[6] = dstRaw[2];
            bbuf[7] = dstRaw[3];

            Sockaddr dst = new Sockaddr(WinConst.AF_INET, bbuf);
            row.setDestinationPrefixAddress(src);
            row.setNextHop(dst);
            row.setDestinationPrefixLength(24);

            wnu.DeleteIpForwardEntry2(row);

            Assert.assertTrue(wnu.CreateIpForwardEntry2(row));

            mib = wnu.GetIpForwardTable2(WinConst.AF_INET);

            boolean found = false;
            for (MibIpForwardRow2 row4 : mib) {
                if (Arrays.equals(srcRaw, row4.getDestinationPrefixAddress().parseWin32_SOCKADDR_INET().getAddress().getAddress())) {
                    found = true;
                    break;
                }
            }

            Assert.assertTrue(wnu.DeleteIpForwardEntry2(row));
            Assert.assertTrue(found);
            mib = wnu.GetIpForwardTable2(WinConst.AF_INET);

            found = false;
            for (MibIpForwardRow2 row4 : mib) {
                if (Arrays.equals(srcRaw, row4.getDestinationPrefixAddress().parseWin32_SOCKADDR_INET().getAddress().getAddress())) {
                    found = true;
                    break;
                }
            }

            Assert.assertFalse(found);

        } catch (UnknownNativeErrorException e) {
            System.out.println(wnu.FormatMessageA(e.intCode()));
            throw e;
        }
    }
}
