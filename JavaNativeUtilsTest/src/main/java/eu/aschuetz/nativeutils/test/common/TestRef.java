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

import java.util.ArrayList;

public class TestRef {

    JVMNativeUtil jvmu = NativeUtils.getJVMUtil();

    private long ngref()  {
        ArrayList<String> ar = new ArrayList();
        ar.add("bleh");
        return jvmu.NewGlobalRef(ar);
    }

    @Test
    public void test() {
        long l = ngref();
        System.gc();
        ArrayList<String> ar = jvmu.NewLocalRef(l);
        jvmu.DeleteGlobalRef(l);
        Assert.assertEquals("bleh", ar.get(0));
    }

}
