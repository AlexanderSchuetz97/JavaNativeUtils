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
package eu.aschuetz.nativeutils.api.structs;

public class CommConfig {

    long dwSize;
    int wVersion;
    DCB dcb;
    long dwProviderSubType;
    private byte[] wcProviderData;

    public byte[] getWcProviderData() {
        return wcProviderData;
    }

    public void setWcProviderData(byte[] wcProviderData) {
        this.wcProviderData = wcProviderData;
    }

    public long getDwSize() {
        return dwSize;
    }

    public void setDwSize(long dwSize) {
        this.dwSize = dwSize;
    }

    public int getwVersion() {
        return wVersion;
    }

    public void setwVersion(int wVersion) {
        this.wVersion = wVersion;
    }

    public DCB getDcb() {
        return dcb;
    }

    public void setDcb(DCB dcb) {
        this.dcb = dcb;
    }

    public long getDwProviderSubType() {
        return dwProviderSubType;
    }

    public void setDwProviderSubType(long dwProviderSubType) {
        this.dwProviderSubType = dwProviderSubType;
    }
}
