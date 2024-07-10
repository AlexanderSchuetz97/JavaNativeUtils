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
package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.WinConst;
import eu.aschuetz.nativeutils.api.WindowsNativeUtil;
import eu.aschuetz.nativeutils.api.exceptions.InvalidFileDescriptorException;
import eu.aschuetz.nativeutils.api.exceptions.SharingViolationException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.structs.*;

import java.io.FileDescriptor;
import java.nio.ByteBuffer;
import java.nio.file.FileAlreadyExistsException;
import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;
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
    public native long CreateFileW(String lpFileName, int access, boolean allowDelete, boolean allowRead, boolean allowWrite, CreateFileA_createMode openMode, int attributes) throws FileAlreadyExistsException, SharingViolationException, UnknownNativeErrorException;

    @Override
    public native long CreateFileMappingA(long hFile, long lpFileMappingAttributes, int flProtect, int dwMaximumSizeHigh, int dwMaximumSizeLow, String lpName) throws UnknownNativeErrorException;

    @Override
    public native long OpenFileMappingA(int dwDesiredAccess, boolean bInheritHandle, String lpName) throws UnknownNativeErrorException;

    @Override
    public long MapViewOfFileEx(long hFileMappingObject, int dwDesiredAccess, int dwFileOffsetHigh, int dwFileOffsetLow, int dwNumberOfBytesToMap, long lpBaseAddress) throws UnknownNativeErrorException {
        return _MapViewOfFileEx(hFileMappingObject, dwDesiredAccess, dwFileOffsetHigh, dwFileOffsetLow, dwNumberOfBytesToMap, lpBaseAddress);
    }

    static native long _MapViewOfFileEx(long hFileMappingObject, int dwDesiredAccess, int dwFileOffsetHigh, int dwFileOffsetLow, int dwNumberOfBytesToMap, long lpBaseAddress);

    @Override
    public void UnmapViewOfFile(long address) throws UnknownNativeErrorException {
        _UnmapViewOfFile(address);
    }

    static native void _UnmapViewOfFile(long address) throws UnknownNativeErrorException;

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
        if (inBuffer != null) {
            if (inOff < 0 || inLen < 0) {
                throw new IllegalArgumentException("inBuffer offset/length");
            }
            if (!inBuffer.isValid(inOff, inLen)) {
                throw new IllegalArgumentException("inBuffer offset/length out of bounds");
            }


            inB = inBuffer.getNativePointer();
        }

        if (outBuffer != null) {
            if (inOff < 0 || inLen < 0) {
                throw new IllegalArgumentException("outBuffer offset/length");
            }
            if (!outBuffer.isValid(inOff, inLen)) {
                throw new IllegalArgumentException("outBuffer offset/length out of bounds");
            }


            outB = outBuffer.getNativePointer();
        }

        return DeviceIoControl(hDevice, dwIoControlCode, inB, inOff, inLen, outB, outOff, outLen);
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
    public native long OpenEventA(int desiredAccess, boolean inheritHandle, String name) throws UnknownNativeErrorException;

    @Override
    public native void SetEvent(long handle) throws UnknownNativeErrorException;

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
    public native String GetVolumePathNameW(String path);

    @Override
    public native String GetModuleFileNameA(long hModule) throws UnknownNativeErrorException;

    @Override
    public native void SetEnvironmentVariableA(String name, String value) throws UnknownNativeErrorException;

    @Override
    public native String ExpandEnvironmentStringsA(String str) throws UnknownNativeErrorException;

    @Override
    public native String GetEnvironmentVariableA(String name) throws UnknownNativeErrorException;

    @Override
    public native String GetFinalPathNameByHandleA(long handle, boolean normalize, Path_VolumeName volumeName) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    @Override
    public native String GetFinalPathNameByHandleW(long handle, boolean normalize, Path_VolumeName volumeName) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    @Override
    public native int GetFileAttributesA(String str) throws UnknownNativeErrorException;

    @Override
    public native void SetFileAttributesA(String str, int attr) throws UnknownNativeErrorException;

    @Override
    public native long RegOpenKeyExA(long hkey, String subKey, int options, int sam) throws UnknownNativeErrorException;

    @Override
    public native void RegCloseKey(long hkey) throws UnknownNativeErrorException;

    @Override
    public native RegData RegQueryValueExA(long hkey, String valueName) throws UnknownNativeErrorException;

    @Override
    public native RegQueryInfoKeyResult RegQueryInfoKeyA(long hkey) throws UnknownNativeErrorException;

    @Override
    public native RegEnumKeyExResult RegEnumKeyExA(long hkey, int index, int nameSize, int classSize) throws UnknownNativeErrorException;

    @Override
    public native RegEnumValueResult RegEnumValueA(long hkey, int index) throws UnknownNativeErrorException;

    @Override
    public Iterable<RegEnumKeyExResult> iterateRegistrySubKeys(long hkey) throws UnknownNativeErrorException {

        RegQueryInfoKeyResult info = RegQueryInfoKeyA(hkey);
        Collection<RegEnumKeyExResult> resultCol = new ArrayList<>(info.getSubKeys());
        int i = 0;
        while(true) {
            RegEnumKeyExResult res = RegEnumKeyExA(hkey, i++, info.getMaxSubKeyLen(), info.getMaxClassLen());
            if (res == null) {
                break;
            }

            resultCol.add(res);
        }

        return resultCol;
    }

    @Override
    public native long GetCurrentThread();

    @Override
    public native long GetCurrentProcess();

    @Override
    public native long DuplicateHandle(long srcProcess, long handle, long targetProcess, int access, boolean inheritHandle, boolean closeSource, boolean sameAccess);

    @Override
    public native void CancelIo(long handle) throws UnknownNativeErrorException;

    @Override
    public native void CancelIoEx(long handle, long overlapped) throws UnknownNativeErrorException;

    @Override
    public native void CancelSynchronousIo(long threadHandle) throws UnknownNativeErrorException;

    @Override
    public native int ReadFile(long handle, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public int ReadFile(long handle, ByteBuffer buffer, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException {
        if (buffer.isReadOnly()) {
            throw new IllegalArgumentException("buffer is read only");
        }

        if (len < 0) {
            throw new IllegalArgumentException("len < 0");
        }
        if (len == 0) {
            return 0;
        }

        if (buffer.remaining() < len) {
            throw new IllegalArgumentException("buffer.remaining() < len");
        }

        if (!buffer.isDirect()) {
            if (!buffer.hasArray()) {
                byte[] bbuf = new byte[len];
                int x = ReadFile(handle, bbuf, 0, len);

                if (x > 0) {
                    buffer.put(bbuf, 0, x);
                }

                return x;
            }

            byte[] bbuf = buffer.array();
            int x = ReadFile(handle, bbuf, buffer.position(), len);
            if (x > 0) {
                buffer.position(buffer.position() + x);
            }
            return x;

        }

        long addr = GetDirectBufferAddress(buffer);
        if (addr == 0) {
            throw new IllegalStateException("Not a direct buffer even tho buffer.isDirect() returned true");
        }

        int pos = buffer.position();
        if (pos > 0) {
            addr = pointerAdd(addr, pos);
        }
        int r = ReadFile(handle, addr, len);
        if (r > 0) {
            buffer.position(buffer.position() + r);
        }
        return r;
    }

    native int ReadFile(long handle, long ptr, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public int ReadFile(long handle, NativeMemory buffer, long off, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException {
        if (!buffer.isValid(off, len)) {
            throw new IllegalArgumentException("buffer off/len out of bounds");
        }

        return ReadFile(handle, buffer.getNativePointer(off), len);
    }

    native long ReadFile(long handle, long ptr, int len, long overlapped, long event) throws UnknownNativeErrorException;

    @Override
    public long ReadFile(long handle, NativeMemory buffer, long off, int len, long overlapped, long event) throws UnknownNativeErrorException {
        if (!buffer.isValid(off, len)) {
            throw new IllegalArgumentException("buffer off/len out of bounds");
        }

        return ReadFile(handle, buffer.getNativePointer(off), len, overlapped, event);
    }

    @Override
    public native int WriteFile(long handle, byte[] buffer, int off, int len) throws UnknownNativeErrorException;

    @Override
    public int WriteFile(long handle, ByteBuffer buffer, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException {
        if (len < 0) {
            throw new IllegalArgumentException("len < 0");
        }
        if (len == 0) {
            return 0;
        }

        if (buffer.remaining() < len) {
            throw new IllegalArgumentException("buffer.remaining() < len");
        }

        if (!buffer.isDirect()) {
            if (!buffer.hasArray()) {
                byte[] bbuf = new byte[len];
                int pos = buffer.position();
                buffer.get(bbuf);
                buffer.position(pos);
                int x = WriteFile(handle, bbuf, 0, len);
                if (x > 0) {
                    buffer.position(pos+x);
                }

                return x;
            }

            byte[] bbuf = buffer.array();
            int x = WriteFile(handle, bbuf, buffer.position(), len);
            if (x > 0) {
                buffer.position(buffer.position() + x);
            }
            return x;

        }

        long addr = GetDirectBufferAddress(buffer);
        if (addr == 0) {
            throw new IllegalStateException("Not a direct buffer even tho buffer.isDirect() returned true");
        }

        int pos = buffer.position();
        if (pos > 0) {
            addr = pointerAdd(addr, pos);
        }
        int r = WriteFile(handle, addr, len);
        if (r > 0) {
            buffer.position(buffer.position() + r);
        }
        return r;
    }

    native int WriteFile(long handle, long ptr, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    @Override
    public int WriteFile(long handle, NativeMemory buffer, long off, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException {
        if (!buffer.isValid(off, len)) {
            throw new IllegalArgumentException("buffer off/len invalid/out of bounds");
        }

        return WriteFile(handle, buffer.getNativePointer(off), len);
    }

    native long WriteFile(long handle, long ptr, int len , long overlapped, long event) throws UnknownNativeErrorException;

    @Override
    public long WriteFile(long handle, NativeMemory buffer, long off, int len, long overlapped, long event) throws UnknownNativeErrorException {
        if (!buffer.isValid(off, len)) {
            throw new IllegalArgumentException("buffer off/len invalid/out of bounds");
        }

        return WriteFile(handle, buffer.getNativePointer(off), len, overlapped, event);
    }

    @Override
    public native int GetOverlappedResult(long handle, long overlapped, boolean wait) throws UnknownNativeErrorException;

    @Override
    public native int GetFriendlyIfIndex(long index);

    @Override
    public native long GetAdapterIndex(String adapterName) throws UnknownNativeErrorException;

    @Override
    public native Collection<IpAdapterAddresses> GetAdaptersAddresses(long family, long flags) throws UnknownNativeErrorException;

    @Override
    public native long OpenProcessToken(long ProcessHandle, int DesiredAccess) throws UnknownNativeErrorException;

    @Override
    public native byte[] GetTokenInformation(long TokenHandle, int TokenInformationClass) throws UnknownNativeErrorException;

    @Override
    public native long ShellExecuteA(long hwnd, String lpOperation, String lpFile, String lpParameters, String lpDirectory, int nShowCmd);

    @Override
    public native long INVALID_HANDLE_VALUE();

    @Override
    public native long CreateNamedPipeA(String name, int dwOpenMode, int dwPipeMode, int nMaxInstances, int nOutBufferSize, int nInBufferSize, int nDefaultTimeOut, long lpSecurityAttributes) throws UnknownNativeErrorException;

    @Override
    public native void ConnectNamedPipe(long pipeHandle) throws UnknownNativeErrorException;

    @Override
    public native long ConnectNamedPipe(long pipeHandle, long eventHandle) throws UnknownNativeErrorException;

    @Override
    public native boolean WaitNamedPipeA(String name, long infinite) throws UnknownNativeErrorException;

    @Override
    public native void DisconnectNamedPipe(long pipeHandle) throws UnknownNativeErrorException;

    @Override
    public native void FlushFileBuffers(long handle)  throws UnknownNativeErrorException;

    @Override
    public native List<MibIpForwardRow2> GetIpForwardTable2(int Family) throws UnknownNativeErrorException;

    @Override
    public native boolean CreateIpForwardEntry2(MibIpForwardRow2 entry) throws UnknownNativeErrorException;

    @Override
    public native boolean DeleteIpForwardEntry2(MibIpForwardRow2 entry) throws UnknownNativeErrorException;
    @Override
    public native long ConvertInterfaceIndexToLuid(int idx) throws UnknownNativeErrorException;

    @Override
    public native int ConvertInterfaceLuidToIndex(long luid) throws UnknownNativeErrorException;

    @Override
    public native String ConvertInterfaceLuidToNameA(long luid) throws UnknownNativeErrorException;

    @Override
    public native String ConvertInterfaceLuidToAlias(long luid) throws UnknownNativeErrorException;

    @Override
    public native long ConvertInterfaceNameToLuidA(String name) throws UnknownNativeErrorException;

    @Override
    public native long CreateSemaphoreExA(long lpSemaphoreAttributes, long initialCount, long maximumCount, String name, int dwDesiredAccess) throws UnknownNativeErrorException;

    @Override
    public native long ReleaseSemaphore(long hSemaphore, long lReleaseCount) throws UnknownNativeErrorException;

    @Override
    public native void SetupComm(long handle, int dwInQueue, int dwOutQueue) throws UnknownNativeErrorException;

    @Override
    public native void SetCommTimeouts(long handle, CommTimeouts timeouts) throws UnknownNativeErrorException;

    @Override
    public native int WaitCommEvent(long handle) throws UnknownNativeErrorException;

    @Override
    public native void TransmitCommChar(long handle, byte data) throws UnknownNativeErrorException;

    @Override
    public native void SetDefaultCommConfigA(String name, CommConfig config) throws UnknownNativeErrorException;

    @Override
    public native void SetCommState(long handle, DCB dcb) throws UnknownNativeErrorException;

    @Override
    public native void SetCommMask(long handle, int mask) throws UnknownNativeErrorException;

    @Override
    public native void SetCommConfig(long handle, CommConfig config) throws UnknownNativeErrorException;

    @Override
    public native void SetCommBreak(long handle) throws UnknownNativeErrorException;

    @Override
    public native void PurgeComm(long handle, int flags) throws UnknownNativeErrorException;

    @Override
    public native CommConfig GetDefaultCommConfigA(String name) throws UnknownNativeErrorException;

    @Override
    public native CommTimeouts GetCommTimeouts(long handle) throws UnknownNativeErrorException;

    @Override
    public native DCB GetCommState(long handle) throws UnknownNativeErrorException;

    @Override
    public native CommProp GetCommProperties(long handle) throws UnknownNativeErrorException;

    @Override
    public native int GetCommModemStatus(long handle) throws UnknownNativeErrorException;

    @Override
    public native int GetCommMask(long handle) throws UnknownNativeErrorException;

    @Override
    public native CommConfig GetCommConfig(long handle) throws UnknownNativeErrorException;

    @Override
    public native void EscapeCommFunction(long handle, int func) throws UnknownNativeErrorException;

    @Override
    public int ClearCommError(long handle) throws UnknownNativeErrorException {
        return ClearCommError(handle, null);
    }

    @Override
    public native int ClearCommError(long handle, ComStat stat) throws UnknownNativeErrorException;

    @Override
    public native void ClearCommBreak(long handle) throws UnknownNativeErrorException;

    @Override
    public boolean isWindows() {
        return true;
    }

    @Override
    public boolean isLinux() {
        return false;
    }

    @Override
    public boolean isFreeBSD() {
        return false;
    }


}