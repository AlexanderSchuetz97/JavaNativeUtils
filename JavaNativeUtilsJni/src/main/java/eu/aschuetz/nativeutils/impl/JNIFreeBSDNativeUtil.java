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
package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.FreeBSDNativeUtil;

public class JNIFreeBSDNativeUtil extends JNIPosixNativeUtil implements FreeBSDNativeUtil {

    @Override
    public boolean isLinux() {
        return false;
    }

    @Override
    public boolean isFreeBSD() {
        return true;
    }

    @Override
    public boolean isNetBSD() {
        return false;
    }

    @Override
    public boolean isOpenBSD() {
        return false;
    }
}
