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

public class CommProp {
    int wPacketLength;
    int wPacketVersion;
    long dwServiceMask;
    long dwReserved1;
    long dwMaxTxQueue;
    long dwMaxRxQueue;
    long dwMaxBaud;
    long dwProvSubType;
    long dwProvCapabilities;
    long dwSettableParams;
    long dwSettableBaud;
    int wSettableData;
    int wSettableStopParity;
    long dwCurrentTxQueue;
    long dwCurrentRxQueue;
    long dwProvSpec1;
    long dwProvSpec2;
    char[] wcProvChar;

    public int getwPacketLength() {
        return wPacketLength;
    }

    public void setwPacketLength(int wPacketLength) {
        this.wPacketLength = wPacketLength;
    }

    public int getwPacketVersion() {
        return wPacketVersion;
    }

    public void setwPacketVersion(int wPacketVersion) {
        this.wPacketVersion = wPacketVersion;
    }

    public long getDwServiceMask() {
        return dwServiceMask;
    }

    public void setDwServiceMask(long dwServiceMask) {
        this.dwServiceMask = dwServiceMask;
    }

    public long getDwReserved1() {
        return dwReserved1;
    }

    public void setDwReserved1(long dwReserved1) {
        this.dwReserved1 = dwReserved1;
    }

    public long getDwMaxTxQueue() {
        return dwMaxTxQueue;
    }

    public void setDwMaxTxQueue(long dwMaxTxQueue) {
        this.dwMaxTxQueue = dwMaxTxQueue;
    }

    public long getDwMaxRxQueue() {
        return dwMaxRxQueue;
    }

    public void setDwMaxRxQueue(long dwMaxRxQueue) {
        this.dwMaxRxQueue = dwMaxRxQueue;
    }

    public long getDwMaxBaud() {
        return dwMaxBaud;
    }

    public void setDwMaxBaud(long dwMaxBaud) {
        this.dwMaxBaud = dwMaxBaud;
    }

    public long getDwProvSubType() {
        return dwProvSubType;
    }

    public void setDwProvSubType(long dwProvSubType) {
        this.dwProvSubType = dwProvSubType;
    }

    public long getDwProvCapabilities() {
        return dwProvCapabilities;
    }

    public void setDwProvCapabilities(long dwProvCapabilities) {
        this.dwProvCapabilities = dwProvCapabilities;
    }

    public long getDwSettableParams() {
        return dwSettableParams;
    }

    public void setDwSettableParams(long dwSettableParams) {
        this.dwSettableParams = dwSettableParams;
    }

    public long getDwSettableBaud() {
        return dwSettableBaud;
    }

    public void setDwSettableBaud(long dwSettableBaud) {
        this.dwSettableBaud = dwSettableBaud;
    }

    public int getwSettableData() {
        return wSettableData;
    }

    public void setwSettableData(int wSettableData) {
        this.wSettableData = wSettableData;
    }

    public int getwSettableStopParity() {
        return wSettableStopParity;
    }

    public void setwSettableStopParity(int wSettableStopParity) {
        this.wSettableStopParity = wSettableStopParity;
    }

    public long getDwCurrentTxQueue() {
        return dwCurrentTxQueue;
    }

    public void setDwCurrentTxQueue(long dwCurrentTxQueue) {
        this.dwCurrentTxQueue = dwCurrentTxQueue;
    }

    public long getDwCurrentRxQueue() {
        return dwCurrentRxQueue;
    }

    public void setDwCurrentRxQueue(long dwCurrentRxQueue) {
        this.dwCurrentRxQueue = dwCurrentRxQueue;
    }

    public long getDwProvSpec1() {
        return dwProvSpec1;
    }

    public void setDwProvSpec1(long dwProvSpec1) {
        this.dwProvSpec1 = dwProvSpec1;
    }

    public long getDwProvSpec2() {
        return dwProvSpec2;
    }

    public void setDwProvSpec2(long dwProvSpec2) {
        this.dwProvSpec2 = dwProvSpec2;
    }

    public char[] getWcProvChar() {
        return wcProvChar;
    }

    public void setWcProvChar(char[] wcProvChar) {
        this.wcProvChar = wcProvChar;
    }
}
