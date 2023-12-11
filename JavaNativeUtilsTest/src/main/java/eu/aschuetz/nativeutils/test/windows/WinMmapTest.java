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

import eu.aschuetz.nativeutils.api.*;
import eu.aschuetz.nativeutils.api.exceptions.InvalidFileDescriptorException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.test.common.MemTest;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;

import java.io.SyncFailedException;
import java.util.UUID;

public class WinMmapTest extends MemTest {

    private long hdl;
    private long hdl2;

    private NativeMemory view2;
    @Before
    public void before() throws Throwable {
        final WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        UUID uuid = UUID.randomUUID();
        hdl = wnu.CreateFileMappingA(wnu.INVALID_HANDLE_VALUE(), 0, WinConst.PAGE_READWRITE, 0, 4096, uuid.toString());


        long ptr1 = wnu.MapViewOfFileEx(hdl, WinConst.FILE_MAP_ALL_ACCESS, 0, 0, 4096, 0);

        final PointerHandler handler = new PointerHandler() {
            @Override
            public void handleClose(long ptr, long size) {
                try {
                    wnu.UnmapViewOfFile(ptr);
                } catch (UnknownNativeErrorException e) {
                    throw new IllegalStateException(""+e.intCode());
                }
            }

            @Override
            public void handleSync(long ptr, long size, long offset, long length, boolean invalidate) throws SyncFailedException {

            }
        };

        memory = wnu.pointer(ptr1, 4096, handler);

        hdl2 = wnu.OpenFileMappingA(WinConst.FILE_MAP_ALL_ACCESS, false, uuid.toString());

        long ptr2 = wnu.MapViewOfFileEx(hdl2, WinConst.FILE_MAP_ALL_ACCESS, 0, 0, 4096, 0);
        view2 = wnu.pointer(ptr2, 4096, handler);

        rng.setSeed(0);
        memory.zero();
    }

    @After
    public void after() throws Throwable {
        WindowsNativeUtil wnu = NativeUtils.getWindowsUtil();
        byte[] bufA = new byte[4096];
        byte[] bufB = new byte[4096];
        memory.read(0, bufA);
        view2.read(0, bufB);
        Assert.assertArrayEquals(bufA, bufB);

        memory.close();
        wnu.CloseHandle(hdl);
        view2.close();
        wnu.CloseHandle(hdl2);
    }
}
