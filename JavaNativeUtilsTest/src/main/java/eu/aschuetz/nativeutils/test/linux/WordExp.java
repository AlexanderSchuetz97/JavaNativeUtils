//
// Copyright Alexander Schütz, 2021-2024
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

package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.util.Map;

public class WordExp {

    private LinuxNativeUtil util = NativeUtils.getLinuxUtil();

    @Test
    public void test() {
        Map.Entry<String, String> e = System.getenv().entrySet().iterator().next();
        String[] ss = util.wordexp("a $"+e.getKey()+" b", true, true, true);
        Assert.assertArrayEquals(new String[]{"a", e.getValue(), "b"}, ss);
    }
}
