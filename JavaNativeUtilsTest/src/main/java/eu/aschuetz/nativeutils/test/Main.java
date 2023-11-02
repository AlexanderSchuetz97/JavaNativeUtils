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
package eu.aschuetz.nativeutils.test;

import eu.aschuetz.nativeutils.api.NativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.test.common.*;
import eu.aschuetz.nativeutils.test.linux.*;
import eu.aschuetz.nativeutils.test.windows.WinMibTest;
import eu.aschuetz.nativeutils.test.windows.WinMmapTest;
import eu.aschuetz.nativeutils.test.windows.WinSemaTest;
import org.junit.runner.Description;
import org.junit.runner.JUnitCore;
import org.junit.runner.Result;
import org.junit.runner.notification.Failure;
import org.junit.runner.notification.RunListener;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    private static List<Class> COMMON_TESTS = (List) Arrays.asList(
            TestLibLoad.class,
            MemTest.class,
            TestRef.class,
            TestMonitor.class,
            ReflectionTests.class);
    private static List<Class> LINUX_TESTS = (List) Arrays.asList(
            ChdirTests.class,
            ChmodTest.class,
            CPUIDTest.class,
            IfTests.class,
            LinkLinkTests.class,
            LinuxStatTest.class,
            MMapTest.class,
            PTTest.class,
            SemTest.class,
            SocketTests.class,
            StreamTest.class,
            TestConversions.class,
            TestFifo.class,
            TestMBuf.class,
            UserTest.class,
            WordExp.class);

    private static List<Class> WINDOWS_TESTS = (List) Arrays.asList(
            WinSemaTest.class,
            WinMmapTest.class,
            WinMibTest.class
    );


    public static Result runTests() {
        NativeUtil nativeUtil = NativeUtils.get();
        if (!nativeUtil.isLinux() && ! nativeUtil.isWindows()) {
            System.err.println("Lib failed to load!");
            System.exit(-1);
        }


        JUnitCore junit = new JUnitCore();
        junit.addListener(new RunListener() {

            private String name(Description description) {
                return description.getClassName().substring(description.getClassName().lastIndexOf('.')+1) + "." + description.getMethodName();
            }


            @Override
            public void testStarted(Description description) throws Exception {
                System.out.println("START  " + name(description));
            }

            @Override
            public void testFinished(Description description) throws Exception {
                System.out.println("FINISH " + name(description));
            }

            @Override
            public void testFailure(Failure failure) throws Exception {
                System.out.println("FAIL   " + name(failure.getDescription()));
                System.out.flush();
                if (failure.getException() != null) {
                    failure.getException().printStackTrace(System.out);
                    System.out.flush();
                }
            }

            @Override
            public void testIgnored(Description description) throws Exception {
                System.out.println("IGNORE " + description);
            }
        });
        Result result = null;

        if (nativeUtil.isLinux()) {
            System.out.println("LINUX");
            ArrayList<Class> ar = new ArrayList();
            ar.addAll(COMMON_TESTS);
            ar.addAll(LINUX_TESTS);

            result = junit.run(ar.toArray(new Class[0]));
        }

        if (nativeUtil.isWindows()) {
            System.out.println("WINDOWS");
            ArrayList<Class> ar = new ArrayList();
            ar.addAll(COMMON_TESTS);
            ar.addAll(WINDOWS_TESTS);

            result = junit.run(ar.toArray(new Class[0]));
        }

        return result;
    }

    public static void main(String[] args) {
        Result result = runTests();

        if (result.getFailureCount() != 0) {
            System.err.println("FAILURES " + result.getFailureCount());
            System.exit(-1);
        } else {
            System.out.println("NO FAILURES");
            System.exit(0);
        }
    }
}