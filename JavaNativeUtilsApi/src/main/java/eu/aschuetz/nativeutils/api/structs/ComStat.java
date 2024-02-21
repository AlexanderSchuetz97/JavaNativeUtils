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

public class ComStat {
    long fCtsHold;
    long fDsrHold;
    long fRlsdHold;
    long fXoffHold;
    long fXoffSent;
    long fEof;
    long fTxim;
    long cbInQue;
    long cbOutQue;

    public long getfCtsHold() {
        return fCtsHold;
    }

    public void setfCtsHold(int fCtsHold) {
        this.fCtsHold = fCtsHold;
    }

    public long getfDsrHold() {
        return fDsrHold;
    }

    public void setfDsrHold(int fDsrHold) {
        this.fDsrHold = fDsrHold;
    }

    public long getfRlsdHold() {
        return fRlsdHold;
    }

    public void setfRlsdHold(int fRlsdHold) {
        this.fRlsdHold = fRlsdHold;
    }

    public long getfXoffHold() {
        return fXoffHold;
    }

    public void setfXoffHold(int fXoffHold) {
        this.fXoffHold = fXoffHold;
    }

    public long getfXoffSent() {
        return fXoffSent;
    }

    public void setfXoffSent(int fXoffSent) {
        this.fXoffSent = fXoffSent;
    }

    public long getfEof() {
        return fEof;
    }

    public void setfEof(int fEof) {
        this.fEof = fEof;
    }

    public long getfTxim() {
        return fTxim;
    }

    public void setfTxim(int fTxim) {
        this.fTxim = fTxim;
    }
    public long getCbInQue() {
        return cbInQue;
    }

    public void setCbInQue(long cbInQue) {
        this.cbInQue = cbInQue;
    }

    public long getCbOutQue() {
        return cbOutQue;
    }

    public void setCbOutQue(long cbOutQue) {
        this.cbOutQue = cbOutQue;
    }
}