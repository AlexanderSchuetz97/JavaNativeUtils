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
package io.github.alexanderschuetz97.nativeutils.impl;

import io.github.alexanderschuetz97.nativeutils.api.NativeMemory;
import io.github.alexanderschuetz97.nativeutils.api.WindowsNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.GUID;
import io.github.alexanderschuetz97.nativeutils.api.structs.SpDeviceInfoData;
import io.github.alexanderschuetz97.nativeutils.api.structs.SpDeviceInterfaceData;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;
import io.github.alexanderschuetz97.nativeutils.api.structs.Win32FileAttributeData;

import java.io.FileDescriptor;
import java.util.Collection;
import java.util.LinkedList;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class JNIWindowsNativeUtil extends JNICommonNativeUtil implements WindowsNativeUtil {

    @Override
    public native boolean LockFileEx(long fd, boolean exclusive, boolean failImmediately, long start, long len);

    @Override
    public native boolean UnlockFileEx(long fd, long start, long len);

    @Override
    public native int getFD(FileDescriptor fd);

    @Override
    public native long getHandle(FileDescriptor fd);

    @Override
    public native boolean _locking(int fd, _locking_Mode mode, long len);

    @Override
    public native Stat _stat64(String path);

    @Override
    public native Win32FileAttributeData GetFileAttributesEx(String path) throws UnknownNativeErrorException;

    @Override
    public native void CreateSymbolicLinkA(String lpSymlinkFileName, String lpTargetFileName, boolean targetIsDir, boolean isDevMode) throws UnknownNativeErrorException;

    @Override
    public native void CreateHardLinkA(String lpFileName, String lpExistingFileName) throws UnknownNativeErrorException;

    @Override
    public native long CreateFileA(String lpFileName, int access, boolean allowDelete, boolean allowRead, boolean allowWrite, CreateFileA_createMode openMode, int attributes) throws UnknownNativeErrorException;

    @Override
    public native void CloseHandle(long handle) throws UnknownNativeErrorException;

    @Override
    public Iterable<String> iterateDeviceInterfaces(GUID deviceClass, String enumerator, int flags, GUID interfaceClass) throws UnknownNativeErrorException {
        if (interfaceClass == null) {
            throw new NullPointerException("interfaceClass");
        }

        long handle = SetupDiGetClassDevsA(deviceClass, enumerator, 0, flags);
        Collection<String> strCol = new LinkedList<>();
        int i = 0;
        while(true) {
            SpDeviceInterfaceData spi = SetupDiEnumDeviceInterfaces(handle, null, interfaceClass, i++);
            if (spi == null) {
                break;
            }
            strCol.add(SetupDiGetDeviceInterfaceDetail(handle, spi, null));
        }


        return strCol;
    }

    @Override
    public native long SetupDiGetClassDevsA(GUID ClassGuid, String Enumerator, long hwndParent, int flags) throws UnknownNativeErrorException;

    @Override
    public native SpDeviceInterfaceData SetupDiEnumDeviceInterfaces(long DeviceInfoSet, SpDeviceInfoData DeviceInfoData, GUID InterfaceClassGuid, int index) throws UnknownNativeErrorException;

    @Override
    public native String SetupDiGetDeviceInterfaceDetail(long DeviceInfoSet, SpDeviceInterfaceData DeviceInterfaceData, SpDeviceInfoData output);

    @Override
    public native void SetupDiDestroyDeviceInfoList(long handle) throws UnknownNativeErrorException;

    @Override
    public native int DeviceIoControl(long hDevice, int dwIoControlCode, byte[] inBuffer, int inOff, int inLen, byte[] outBuffer, int outOff, int outLen) throws UnknownNativeErrorException;

    @Override
    public int DeviceIoControl(long hDevice, int dwIoControlCode, NativeMemory inBuffer, long inOff, int inLen, NativeMemory outBuffer, long outOff, int outLen) throws UnknownNativeErrorException {
        long inB = 0;
        long outB = 0;
        ReentrantReadWriteLock.ReadLock inBL = null;
        ReentrantReadWriteLock.ReadLock outBL = null;
        try {
            if (inBuffer != null) {
                inBL = inBuffer.readLock();
                inBL.lock();
                if (inOff < 0 || inLen < 0) {
                    throw new IllegalArgumentException("inBuffer offset/length");
                }
                if (!inBuffer.isReadable() || !inBuffer.isValid(inOff, inLen)) {
                    throw new IllegalArgumentException("inBuffer offset/length out of bounds or not readable");
                }


                inB = inBuffer.getNativePointer();
            }

            if (outBuffer != null) {
                outBL = outBuffer.readLock();
                outBL.lock();
                if (inOff < 0 || inLen < 0) {
                    throw new IllegalArgumentException("outBuffer offset/length");
                }
                if (!outBuffer.isWriteable() || !outBuffer.isValid(inOff, inLen)) {
                    throw new IllegalArgumentException("outBuffer offset/length out of bounds or not writeable");
                }


                outB = outBuffer.getNativePointer();
            }

            return DeviceIoControl(hDevice, dwIoControlCode, inB, inOff, inLen, outB, outOff, outLen);
        } finally {
            if (inBL != null) {
                inBL.unlock();
            }

            if (outBL != null) {
                outBL.unlock();
            }
        }
    }

    protected static native int DeviceIoControl(long hDevice, int dwIoControlCode, long inBuffer, long inOff, int inLen, long outBuffer, long outOff, int outLen) throws UnknownNativeErrorException;

    @Override
    public int CTL_CODE(int DeviceType, int Function, int Method, int Access) {
        //NO need to jni for this.
        return (DeviceType << 16) | (Access << 14) | (Function << 2) | (Method);
    }

    @Override
    public native long CreateEventA(long lpEventAttributes, boolean manualReset, boolean initalState, String name) throws UnknownNativeErrorException;

    @Override
    public native void ResetEvent(long handle) throws UnknownNativeErrorException;

    @Override
    public native boolean WaitForSingleObject(long handle, int millis) throws UnknownNativeErrorException;

    @Override
    public native int WaitForMultipleObjects(long[] handles, int millis, boolean waitAll) throws UnknownNativeErrorException;


    @Override
    public native String strerror_s(int errno);

    @Override
    public native String FormatMessageA(int lastError);

    @Override
    public boolean isWindows() {
        return true;
    }

    @Override
    public boolean isLinux() {
        return false;
    }


}