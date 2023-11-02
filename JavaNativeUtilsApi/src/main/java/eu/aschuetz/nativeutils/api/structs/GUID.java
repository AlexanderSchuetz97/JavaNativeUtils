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
package eu.aschuetz.nativeutils.api.structs;


/**
 * See
 * https://docs.microsoft.com/en-us/windows/win32/api/guiddef/ns-guiddef-guid
 */
public class GUID {
    private int data1;
    private short data2;
    private short data3;
    private final byte[] data4 = new byte[8];

    public GUID() {

    }

    public GUID(String txt) {
        if (txt.length() != 36) {
            throw new IllegalArgumentException("Invalid GUID");
        }

        txt = txt.toUpperCase();

        for (int i = 0; i < txt.length(); i++) {
            char c = txt.charAt(i);
            if (i == 8 || i == 13 || i == 18 ||  i == 23) {
                if (c != '-') {
                    throw new IllegalArgumentException("Invalid GUID");
                }
                continue;
            }

            if (!Character.isDigit(c) && (c < 'A' || c > 'F')) {
                throw new IllegalArgumentException("Invalid GUID");
            }
        }

        try {
            data1 = (int) Long.parseLong(txt.substring(0, 0+8), 16);
            data2 = (short) Long.parseLong(txt.substring(9, 9+4), 16);
            data3 = (short) Long.parseLong(txt.substring(14, 14+4), 16);

            data4[0] = (byte) Long.parseLong(txt.substring(19, 19+2), 16);
            data4[1] = (byte) Long.parseLong(txt.substring(21, 21+2), 16);
            data4[2] = (byte) Long.parseLong(txt.substring(24, 24+2), 16);
            data4[3] = (byte) Long.parseLong(txt.substring(26, 26+2), 16);
            data4[4] = (byte) Long.parseLong(txt.substring(28, 28+2), 16);
            data4[5] = (byte) Long.parseLong(txt.substring(30, 30+2), 16);
            data4[6] = (byte) Long.parseLong(txt.substring(32, 32+2), 16);
            data4[7] = (byte) Long.parseLong(txt.substring(34, 34+2), 16);


        } catch (NumberFormatException exc) {
            //Shouldn't happen as check above is more strict than Long.parseLong
            throw new IllegalArgumentException("Invalid GUID", exc);
        }
    }

    public int getData1() {
        return data1;
    }

    public void setData1(int data1) {
        this.data1 = data1;
    }

    public short getData2() {
        return data2;
    }

    public void setData2(short data2) {
        this.data2 = data2;
    }

    public short getData3() {
        return data3;
    }

    public void setData3(short data3) {
        this.data3 = data3;
    }

    public byte[] getData4() {
        return data4;
    }

    public void setData4(byte[] data4) {
        System.arraycopy(data4, 0, this.data4, 0, 8);
    }

    public String toString() {
        String s1 = Long.toHexString(data1 & 0xffffffffL);
        String s2 = Long.toHexString(data2 & 0xffff);
        String s3 = Long.toHexString(data3 & 0xffff);
        StringBuilder s4 = new StringBuilder();

        for (int i = 0; i < data4.length;i++) {
            String s = Long.toHexString(data4[i] & 0xff);

            if (s.length() == 1) {
                s4.append("0");
            }

            s4.append(s);
        }

        while(s1.length() < 8) {
            s1 = "0" + s1;
        }
        while(s2.length() < 4) {
            s2 = "0" + s2;
        }
        while(s3.length() < 4) {
            s3 = "0" + s3;
        }

        return (s1 + "-" + s2 + "-" + s3 + "-" + s4.substring(0, 4) + "-" + s4.substring(4)).toUpperCase();
    }

    @Override
    public GUID clone() {
        GUID clone = new GUID();
        clone.data1 = data1;
        clone.data2 = data2;
        clone.data3 = data3;
        System.arraycopy(data4, 0, clone.data4, 0, 8);
        return clone;
    }



}
