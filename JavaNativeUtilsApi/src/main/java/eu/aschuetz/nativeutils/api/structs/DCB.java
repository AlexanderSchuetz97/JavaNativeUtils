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

public class DCB {
    long BaudRate;
    boolean fBinary;
    boolean fParity;
    boolean fOutxCtsFlow;
    boolean fOutxDsrFlow;
    long fDtrControl;
    boolean fDsrSensitivity;
    boolean fTXContinueOnXoff;
    boolean fOutX;
    boolean fInX;
    boolean fErrorChar;
    boolean fNull;
    long fRtsControl;
    boolean fAbortOnError;
    int XonLim;
    int XoffLim;
    int ByteSize;
    int Parity;
    int StopBits;
    int XonChar;
    int XoffChar;
    int ErrorChar;
    int EofChar;
    int EvtChar;

    public long getBaudRate() {
        return BaudRate;
    }

    public void setBaudRate(long baudRate) {
        BaudRate = baudRate;
    }

    public boolean isfBinary() {
        return fBinary;
    }

    public void setfBinary(boolean fBinary) {
        this.fBinary = fBinary;
    }

    public boolean isfParity() {
        return fParity;
    }

    public void setfParity(boolean fParity) {
        this.fParity = fParity;
    }

    public boolean isfOutxCtsFlow() {
        return fOutxCtsFlow;
    }

    public void setfOutxCtsFlow(boolean fOutxCtsFlow) {
        this.fOutxCtsFlow = fOutxCtsFlow;
    }

    public boolean isfOutxDsrFlow() {
        return fOutxDsrFlow;
    }

    public void setfOutxDsrFlow(boolean fOutxDsrFlow) {
        this.fOutxDsrFlow = fOutxDsrFlow;
    }

    public long getfDtrControl() {
        return fDtrControl;
    }

    public void setfDtrControl(long fDtrControl) {
        this.fDtrControl = fDtrControl;
    }

    public boolean isfDsrSensitivity() {
        return fDsrSensitivity;
    }

    public void setfDsrSensitivity(boolean fDsrSensitivity) {
        this.fDsrSensitivity = fDsrSensitivity;
    }

    public boolean isfTXContinueOnXoff() {
        return fTXContinueOnXoff;
    }

    public void setfTXContinueOnXoff(boolean fTXContinueOnXoff) {
        this.fTXContinueOnXoff = fTXContinueOnXoff;
    }

    public boolean isfOutX() {
        return fOutX;
    }

    public void setfOutX(boolean fOutX) {
        this.fOutX = fOutX;
    }

    public boolean isfInX() {
        return fInX;
    }

    public void setfInX(boolean fInX) {
        this.fInX = fInX;
    }

    public boolean isfErrorChar() {
        return fErrorChar;
    }

    public void setfErrorChar(boolean fErrorChar) {
        this.fErrorChar = fErrorChar;
    }

    public boolean isfNull() {
        return fNull;
    }

    public void setfNull(boolean fNull) {
        this.fNull = fNull;
    }

    public long getfRtsControl() {
        return fRtsControl;
    }

    public void setfRtsControl(long fRtsControl) {
        this.fRtsControl = fRtsControl;
    }

    public boolean isfAbortOnError() {
        return fAbortOnError;
    }

    public void setfAbortOnError(boolean fAbortOnError) {
        this.fAbortOnError = fAbortOnError;
    }

    public int getXonLim() {
        return XonLim;
    }

    public void setXonLim(int xonLim) {
        XonLim = xonLim;
    }

    public int getXoffLim() {
        return XoffLim;
    }

    public void setXoffLim(int xoffLim) {
        XoffLim = xoffLim;
    }

    public int getByteSize() {
        return ByteSize;
    }

    public void setByteSize(int byteSize) {
        ByteSize = byteSize;
    }

    public int getParity() {
        return Parity;
    }

    public void setParity(int parity) {
        Parity = parity;
    }

    public int getStopBits() {
        return StopBits;
    }

    public void setStopBits(int stopBits) {
        StopBits = stopBits;
    }

    public int getXonChar() {
        return XonChar;
    }

    public void setXonChar(int xonChar) {
        XonChar = xonChar;
    }

    public int getXoffChar() {
        return XoffChar;
    }

    public void setXoffChar(int xoffChar) {
        XoffChar = xoffChar;
    }

    public int getErrorChar() {
        return ErrorChar;
    }

    public void setErrorChar(int errorChar) {
        ErrorChar = errorChar;
    }

    public int getEofChar() {
        return EofChar;
    }

    public void setEofChar(int eofChar) {
        EofChar = eofChar;
    }

    public int getEvtChar() {
        return EvtChar;
    }

    public void setEvtChar(int evtChar) {
        EvtChar = evtChar;
    }

    @Override
    public String toString() {
        return "DCB{" +
                "BaudRate=" + BaudRate +
                ", fBinary=" + fBinary +
                ", fParity=" + fParity +
                ", fOutxCtsFlow=" + fOutxCtsFlow +
                ", fOutxDsrFlow=" + fOutxDsrFlow +
                ", fDtrControl=" + fDtrControl +
                ", fDsrSensitivity=" + fDsrSensitivity +
                ", fTXContinueOnXoff=" + fTXContinueOnXoff +
                ", fOutX=" + fOutX +
                ", fInX=" + fInX +
                ", fErrorChar=" + fErrorChar +
                ", fNull=" + fNull +
                ", fRtsControl=" + fRtsControl +
                ", fAbortOnError=" + fAbortOnError +
                ", XonLim=" + XonLim +
                ", XoffLim=" + XoffLim +
                ", ByteSize=" + ByteSize +
                ", Parity=" + Parity +
                ", StopBits=" + StopBits +
                ", XonChar=" + XonChar +
                ", XoffChar=" + XoffChar +
                ", ErrorChar=" + ErrorChar +
                ", EofChar=" + EofChar +
                ", EvtChar=" + EvtChar +
                '}';
    }
}
