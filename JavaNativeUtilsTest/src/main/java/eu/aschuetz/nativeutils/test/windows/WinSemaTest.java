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
import org.junit.Assert;
import org.junit.Test;

import java.util.UUID;
import java.util.concurrent.*;

public class WinSemaTest {

    @Test
    public void test() throws Exception {
        final WindowsNativeUtil win = NativeUtils.getWindowsUtil();
        UUID uuid = UUID.randomUUID();
        final long sema = win.CreateSemaphoreExA(0, 1, 255, uuid.toString(), WinConst.SYNCHRONIZE | WinConst.SEMAPHORE_ALL_ACCESS);
        Assert.assertTrue(win.WaitForSingleObject(sema, 5000));
        ExecutorService ex = Executors.newSingleThreadExecutor();
        Future<?> f = ex.submit(new Callable<Object>() {
            @Override
            public Object call() throws Exception {
                return win.WaitForSingleObject(sema, 1000);
            }
        });

        Assert.assertEquals(Boolean.FALSE, f.get(2000, TimeUnit.MILLISECONDS));

        f = ex.submit(new Callable<Object>() {
            @Override
            public Object call() throws Exception {
                return win.WaitForSingleObject(sema, 5000);
            }
        });

        Thread.sleep(500);
        win.ReleaseSemaphore(sema, 1);
        Assert.assertEquals(Boolean.TRUE, f.get(2000, TimeUnit.MILLISECONDS));

        ex.shutdownNow();
        win.CloseHandle(sema);
    }

}
