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
package eu.aschuetz.nativeutils.test.common;

import eu.aschuetz.nativeutils.api.JVMNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.util.concurrent.*;

public class TestMonitor {

    JVMNativeUtil util = NativeUtils.getJVMUtil();

    @Test
    public void testException() {
        try {
            util.MonitorExit(new Object());
        } catch (IllegalMonitorStateException exc) {
            return;
        }
        Assert.fail();

    }

    @Test
    public void testMonitor() {
        Object o = new Object();
        util.MonitorEnter(o);
        util.MonitorExit(o);
    }

    @Test
    public void testMonitorSync() {
        Object o = new Object();
        synchronized (o) {
            util.MonitorEnter(o);
            util.MonitorExit(o);
        }
    }

    @Test
    public void testMonitorSyncOtherThread() throws Throwable{
        ExecutorService executorService = Executors.newSingleThreadExecutor();
        final Object o = new Object();
        Future<?> f;
        synchronized (o) {
             f = executorService.submit(new Runnable() {
                @Override
                public void run() {
                    util.MonitorEnter(o);
                    util.MonitorExit(o);
                }
            });

            try {
                f.get(1000, TimeUnit.MILLISECONDS);
                Assert.fail();
            } catch (TimeoutException e) {
                //expected
            }
        }
        f.get(5000, TimeUnit.MILLISECONDS);
        executorService.shutdownNow();
    }

}
