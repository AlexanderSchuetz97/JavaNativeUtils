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
package io.github.alexanderschuetz97.nativeutils.api.structs;

public final class Win32FileAttributeData {

    private Win32FileAttributeData() {
        //called from c
    }

    private long dwFileAttributes;
    private long nFileSizeLow;
    private long nFileSizeHigh;
    private long ftLastAccessTimeLow;
    private long ftLastAccessTimeHigh;
    private long ftLastWriteTimeHigh;
    private long ftLastWriteTimeLow;
    private long ftCreationTimeHigh;
    private long ftCreationTimeLow;

    public long getDwFileAttributes() {
        return dwFileAttributes;
    }

    public long getnFileSizeLow() {
        return nFileSizeLow;
    }

    public long getnFileSizeHigh() {
        return nFileSizeHigh;
    }

    public long getFtLastAccessTimeLow() {
        return ftLastAccessTimeLow;
    }

    public long getFtLastAccessTimeHigh() {
        return ftLastAccessTimeHigh;
    }

    public long getFtLastWriteTimeHigh() {
        return ftLastWriteTimeHigh;
    }

    public long getFtLastWriteTimeLow() {
        return ftLastWriteTimeLow;
    }

    public long getFtCreationTimeHigh() {
        return ftCreationTimeHigh;
    }

    public long getFtCreationTimeLow() {
        return ftCreationTimeLow;
    }
}
