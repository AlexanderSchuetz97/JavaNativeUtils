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
package io.github.alexanderschuetz97.nativeutils.api;

import io.github.alexanderschuetz97.nativeutils.api.exceptions.*;
import io.github.alexanderschuetz97.nativeutils.api.structs.*;

import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.nio.ByteBuffer;
import java.nio.file.FileAlreadyExistsException;
import java.util.Collection;

public interface WindowsNativeUtil extends NativeUtil {

    /**
     * see https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/locking?view=msvc-170
     */
    enum _locking_Mode {
        _LK_LOCK, // tries to lock for 10s and then gives up.
        _LK_NBLCK, // tries once and then gives up.
        _LK_UNLCK // unlock/remove the lock
    }

    /**
     * Returns the int based file descriptor of the given java FileDescriptor or -1 if it is invalid.
     */
    int getFD(FileDescriptor fd);

    /**
     * Returns the HANDLE (void *) based file descriptor of the given java FileDescriptor or -1 (INVALID_HANDLE_VALUE) if it is invalid.
     */
    long getHandle(FileDescriptor fd);

    /**
     * Returns size of void* or windows HANDLE datatype in bytes. Either 4 or 8 bytes.
     * The returned value is constant.
     */
    int getPointerSize();

    /**
     * queries the cpu for info.<br>
     *
     * the returned int[] is null if the requested code/subcode is not supported by the cpu otherwise
     * it has the length of 4 and contains the registers in this oder: <br>
     * 0 -> EAX <br>
     * 1 -> EBX <br>
     * 2 -> ECX <br>
     * 3 -> EDX <br>
     *
     * Note: on non X86/AMD64 this will always return null.
     */
    int[] __get_cpuid_count(int code, int subcode);

    /**
     * Returns the CPU Model string.
     * Example for Intel CPU's would be "GenuineIntel"
     */
    String __get_cpuid_count_model();

    /**
     * returns true if successful false if not.
     * <p>
     * In detail:
     * true if _locking() returns true.
     * false if _locking() returns false and errno is set to EACCES.
     * any other errno leads to UnknownNativeErrorException.
     * <p>
     * The start position the lock has will always be the current position in the file.
     * Meaning if you want to unlock a lock you will HAVE TO move it back to position it was in when you made the lock.
     * You have to use methods like RandomAccessFiles.seek() to accomplish this.
     * <p>
     */
    boolean _locking(int fd, _locking_Mode mode, long len) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    /**
     * returns true if successful false if not.
     */
    boolean LockFileEx(long handle, boolean exclusive, boolean failImmediately, long start, long len) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    /**
     * returns true if successful false if not.
     */
    boolean UnlockFileEx(long handle, long start, long len) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    /**
     * Allocates a new pointer of the given size
     * @throws OutOfMemoryError if malloc returns NULL
     * @throws IllegalArgumentException if size is <= 0
     */
    NativeMemory malloc(long size) throws OutOfMemoryError, IllegalArgumentException;

    /**
     * Calls free on a pointer.
     * @param ptr the pointer.
     */
    void free(long ptr);

    /**
     * Any calls to the resulting NativeMemory may cause the JVM to die due to a SEGFAULT is size is not specified correctly.
     * the close() and sync() methods are noops.
     *
     * @param ptr pointer to the data
     * @param size -1 if unknown.
     */
    NativeMemory pointer(long ptr, long size, PointerHandler handler) throws NullPointerException;


    Stat _stat64(String path) throws UnknownNativeErrorException, FileNotFoundException, IllegalArgumentException;



    /**
     * Returns file attributes.
     * Never returns null.
     */
    Win32FileAttributeData GetFileAttributesEx(String path) throws UnknownNativeErrorException;

    /**
     * Makes a symbolic link.
     * https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createsymboliclinka
     * @param lpSymlinkFileName The name of the symbolic link. This is where the acutal link is created
     * @param lpTargetFileName This is the name of the target where the link points to.
     * @param targetIsDir if true flag =| 0x1 is performed -> SYMBOLIC_LINK_FLAG_DIRECTORY
     * @param isDevMode if true flag =| 0x2 is poformed -> SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE
     *                  according to microsoft this only works when "Developer Mode" is enabled.
     */
    void CreateSymbolicLinkA(String lpSymlinkFileName, String lpTargetFileName, boolean targetIsDir, boolean isDevMode) throws UnknownNativeErrorException;

    /**
     * Makes a hard link.
     * This does not work with directories.
     * https://docs.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createhardlinka
     * @param lpFileName The name of the hard link. This is where the acutal link is created
     * @param lpExistingFileName This is the name of the target where the link points to.
     */
    void CreateHardLinkA(String lpFileName, String lpExistingFileName) throws UnknownNativeErrorException;

    enum CreateFileA_createMode {
        CREATE_NEW,
        CREATE_ALWAYS,
        OPEN_ALWAYS,
        OPEN_EXISTING,
        TRUNCATE_EXISTING
    }

    /**
     * opens a windows handle for a given path.
     * @param lpFileName the path to the file
     * @param access flag integer for meaning of bits see https://docs.microsoft.com/en-us/windows/win32/secauthz/access-mask
     * @param allowDelete allow another process to delete the file while it is opened by this process
     * @param allowRead allow another process to read the file while it is opened by this process
     * @param allowWrite allow another process to write the file while it is opened by this process
     * @param openMode defines how the file is opened
     * @param attributes flag integer for meaning of bits see https://docs.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants
     * @return valid windows HANDLE never returns INVALID_HANDLE
     * @throws FileAlreadyExistsException CREATE_ALWAYS when the file already exists
     */
    long CreateFileA(String lpFileName, int access, boolean allowDelete, boolean allowRead, boolean allowWrite, CreateFileA_createMode openMode, int attributes) throws FileAlreadyExistsException, SharingViolationException, UnknownNativeErrorException;

    /**
     * opens a windows handle for a given path.
     * @param lpFileName the path to the file
     * @param access flag integer for meaning of bits see https://docs.microsoft.com/en-us/windows/win32/secauthz/access-mask
     * @param allowDelete allow another process to delete the file while it is opened by this process
     * @param allowRead allow another process to read the file while it is opened by this process
     * @param allowWrite allow another process to write the file while it is opened by this process
     * @param openMode defines how the file is opened
     * @param attributes flag integer for meaning of bits see https://docs.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants
     * @return valid windows HANDLE never returns INVALID_HANDLE
     * @throws FileAlreadyExistsException CREATE_ALWAYS when the file already exists
     */
    long CreateFileW(String lpFileName, int access, boolean allowDelete, boolean allowRead, boolean allowWrite, CreateFileA_createMode openMode, int attributes) throws FileAlreadyExistsException, SharingViolationException, UnknownNativeErrorException;

    /**
     * Closes a windows handle. I do NOT recommend calling this with a handle that you did not create.
     * This holds especially true for a HANDLE aquired by calling #getHandle
     */
    void CloseHandle(long handle) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    /**
     * Convenience method that uses the SetupDiGetClassDevsA+SetupDiEnumDeviceInterfaces+SetupDiGetDeviceInterfaceDetail
     * Syscalls to provide the return value of SetupDiGetDeviceInterfaceDetail into a iterable for easier use.
     *
     * @param deviceClass for SetupDiGetClassDevsA, can be null
     * @param enumerator for SetupDiGetClassDevsA, can be null
     * @param flags for SetupDiGetClassDevsA
     * @param interfaceClass for SetupDiEnumDeviceInterfaces, can NOT be null
     */
    Iterable<String> iterateDeviceInterfaces(GUID deviceClass, String enumerator, int flags, GUID interfaceClass) throws UnknownNativeErrorException;

    /**
     * Create a device enumeration for connected hardware devices.
     * Returns a HANDLE to the enumeration that must be destroyed by calling SetupDiDestroyDeviceInfoList
     * @param hwndParent set to '0' for absence of a parent device class
     * @param Enumerator can be null
     * @param ClassGuid can be null
     */
    long SetupDiGetClassDevsA(GUID ClassGuid, String Enumerator, long hwndParent, int flags) throws UnknownNativeErrorException;

    /**
     * Get a device element from the device set.
     *
     * @param DeviceInfoSet obtained from SetupDiGetClassDevsA
     * @param DeviceInfoData can be null (the syscall that returns this is not yet implemented)
     * @param InterfaceClassGuid can NOT be null
     * @param index index from the set. Starts at 0, increment to iterate over the devices.
     * @return an element from the set or null if there is no more data.
     */
    SpDeviceInterfaceData SetupDiEnumDeviceInterfaces(long DeviceInfoSet, SpDeviceInfoData DeviceInfoData, GUID InterfaceClassGuid, int index) throws UnknownNativeErrorException;

    /**
     * Get detailed info from a device.
     *
     * @param DeviceInfoSet obtained from SetupDiGetClassDevsA
     * @param DeviceInterfaceData obtained from SetupDiEnumDeviceInterfaces
     * @param outputData may be null if not needed. Output parameter
     *
     * @return return device path as String.
     */
    String SetupDiGetDeviceInterfaceDetail(long DeviceInfoSet, SpDeviceInterfaceData DeviceInterfaceData, SpDeviceInfoData outputData);

    /**
     * Destroys a handle created by SetupDiGetClassDevsA
     */
    void SetupDiDestroyDeviceInfoList(long handle) throws UnknownNativeErrorException;

    /**
     * Sends a control code directly to a specified device driver, causing the corresponding device to perform the corresponding operation.
     *
     * @param hDevice device handle, probably obtained from CreateFileA with
     * @param dwIoControlCode device specific code of the operation
     * @param inBuffer input buffer, can be null
     * @param outBuffer output buffer, can be null
     * @return returns the amount of bytes filled into outBuffer
     */
    int DeviceIoControl(long hDevice, int dwIoControlCode, byte[] inBuffer, int inOff, int inLen, byte[] outBuffer, int outOff, int outLen) throws UnknownNativeErrorException;

    /**
     * Sends a control code directly to a specified device driver, causing the corresponding device to perform the corresponding operation.
     *
     * @param hDevice device handle, probably obtained from CreateFileA with
     * @param dwIoControlCode device specific code of the operation
     * @param inBuffer input buffer memory, can be null
     * @param outBuffer output buffer memory, can be null
     * @return returns the amount of bytes filled into outBuffer
     */
    int DeviceIoControl(long hDevice, int dwIoControlCode, NativeMemory inBuffer, long inOff, int inLen, NativeMemory outBuffer, long outOff, int outLen) throws UnknownNativeErrorException;

    /**
     * Helper function for CTL_CODE macro that can be used to generate the dwIoControlCode for the DeviceIoControl function.
     * The return value of this method is constant.
     */
    int CTL_CODE(int DeviceType, int Function, int Method, int Access);

    /**
     * Returns a newly created event handle from the OS.
     * CloseHandle destroys this handle.
     *
     * @param lpEventAttributes pointer treated as LPSECURITY_ATTRIBUTES
     * @param manualReset if true then the event must be manually reset by calling ResetEvent
     * @param initialState if true then the event is initally set and must be first manually reset using ResetEvent
     * @param name name of the event, may be null.
     * @return the handle to the event.
     */
    long CreateEventA(long lpEventAttributes, boolean manualReset, boolean initialState, String name) throws UnknownNativeErrorException;


    long OpenEventA(int desiredAccess, boolean inheritHandle, String name) throws UnknownNativeErrorException;

    /**
     * Sets a event identified by the handle
     * @param handle
     * @return
     */
    void SetEvent(long handle) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    /**
     * Resets the given event handle.
     */
    void ResetEvent(long handle) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    /**
     * Waits for a single event handle. Be aware that Java has no way to interrupt this call.
     * @param handle the handle
     * @param millis timeout in millis
     * @return true if the wait was successfull false on timeout
     */
    boolean WaitForSingleObject(long handle, int millis) throws UnknownNativeErrorException, InvalidFileDescriptorException, MutexAbandonedException;

    /**
     * Wait for any or all event handles in a handle array. Be aware that Java has no way to interrupt this call.
     *
     * @param handles handles array. May not be null. May not be larger than 64.
     * @param millis the timeout in milliseconds.
     * @param waitAll wait for every handle in the array.
     * @return the index of the handle that was sucessfully waited on. -1 for timeout. returns 0 upon success if waitAll flag is set to true.
     */
    int WaitForMultipleObjects(long[] handles, int millis, boolean waitAll) throws UnknownNativeErrorException, InvalidFileDescriptorException, MutexAbandonedException;

    /**
     * Returns a english string repesentation of the native error code.
     * This only works for all calls to methods that start with "_" or lower case letters.
     */
    String strerror_s(int errno);

    /**
     * Returns a english string repesentation of the native error code
     * This only works for all calls to methods that start with a capital case letter.
     */
    String FormatMessageA(int lastError);

    String GetVolumePathNameW(String path) throws UnknownNativeErrorException;

    String GetModuleFileNameA(long hModule) throws UnknownNativeErrorException;

    void SetEnvironmentVariableA(String name, String value) throws UnknownNativeErrorException;

    String ExpandEnvironmentStringsA(String str) throws UnknownNativeErrorException;

    String GetEnvironmentVariableA(String name) throws UnknownNativeErrorException;

    enum Path_VolumeName {
        VOLUME_NAME_DOS,
        VOLUME_NAME_GUID,
        VOLUME_NAME_NT,
        VOLUME_NAME_NONE,
    }

    String GetFinalPathNameByHandleA(long handle, boolean normalize, Path_VolumeName volumeName) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    String GetFinalPathNameByHandleW(long handle, boolean normalize, Path_VolumeName volumeName) throws UnknownNativeErrorException, InvalidFileDescriptorException;

    int GetFileAttributesA(String str) throws UnknownNativeErrorException;

    void SetFileAttributesA(String str, int attr) throws UnknownNativeErrorException;

    long RegOpenKeyExA(long hkey, String subKey, int options, int sam) throws UnknownNativeErrorException;

    void RegCloseKey(long hkey) throws UnknownNativeErrorException;

    /**
     * Read a registry value.
     *
     * @param hkey the hkey obtained from RegOpenKeyExA
     * @param valueName the name of the value to read
     * @return the value of the key
     * @throws UnknownNativeErrorException
     */
    RegData RegQueryValueExA(long hkey, String valueName) throws UnknownNativeErrorException;

    /**
     * Get information about a registry key.
     */
    RegQueryInfoKeyResult RegQueryInfoKeyA(long hkey) throws UnknownNativeErrorException;

    /**
     * Enumerate subkeys of a registry key.
     *
     * @param index the index of the key in the enumeration
     *              microsofts documentation states that this starts at 0
     *              and should ALWAYS be enumerated until the end
     *              (i.e. always increment this until this function returns null)
     * @param maxSubKeyLen obtained from RegQueryInfoKeyA field maxSubKeyLen
     *             If set to <= 0 then a call to RegQueryInfoKeyResult
     *             will be made internally to determine the size.
     * @param maxClassLen obtained from RegQueryInfoKeyA field maxClassLen
     *             If set to <= 0 then a call to RegQueryInfoKeyResult
     *             will be made internally to determine the size.
     * @return info about the next subkey or null if there are no more subkeys.
     */
    RegEnumKeyExResult RegEnumKeyExA(long hkey, int index, int maxSubKeyLen, int maxClassLen) throws UnknownNativeErrorException;

    /**
     * Convenience method that returns an iterable over all subkeys of a hkey.
     */
    Iterable<RegEnumKeyExResult> iterateRegistrySubKeys(long hkey) throws UnknownNativeErrorException;

    /**
     * Returns a pseudo Thread handle that always means current thread. This handle cannot identify the current thread to another thread.
     * call duplicate handle with the result of this call to get an actual thread handle!
     */
    long GetCurrentThread();

    /**
     * Returns a pseudo handle to the current process.
     */
    long GetCurrentProcess();

    /**
     *
     * @param srcProcess source process, most likely return value of {@link #GetCurrentProcess()}
     * @param handle the source handle to duplicate
     * @param targetProcess target process, most likely return value of {@link #GetCurrentProcess()}
     * @param access desired access flags, completely ignored if sameAccess is true
     * @param inheritHandle should child process inherit the duplicated handle?
     * @param closeSource close the source handle when "duplicating" the handle?
     * @param sameAccess use the same access flags as the source handle? true means access parameter is completely ignored.
     * @return the duplicated handle
     */
    long DuplicateHandle(long srcProcess, long handle, long targetProcess, int access, boolean inheritHandle, boolean closeSource, boolean sameAccess);

    void CancelIo(long handle) throws UnknownNativeErrorException;

    void CancelIoEx(long handle, long overlapped) throws UnknownNativeErrorException;

    void CancelSynchronousIo(long threadHandle) throws UnknownNativeErrorException;

    /**
     * Reads bytes from a handle into a buffer.
     *
     * @param handle file handle
     * @param buffer data goes here
     * @param off offset in the buffer
     * @param len maximum bytes to read
     *
     * @return number of bytes read
     */
    int ReadFile(long handle, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Reads bytes from a handle into a buffer.
     *
     * @param handle file handle
     * @param buffer data goes here
     * @param len maximum bytes to read
     *
     * @return number of bytes read
     */
    int ReadFile(long handle, ByteBuffer buffer, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Reads bytes from a handle into a buffer.
     *
     * @param handle file handle
     * @param buffer data goes here
     * @param off offset in the buffer
     * @param len maximum bytes to read
     *
     * @return number of bytes read
     */
    int ReadFile(long handle, NativeMemory buffer, long off, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * reads using overlapped mechanism. returns an overlapped pointer that must be feed by calling {@link #free(long)} after it has been confirmed that the async READ is done by calling GetOverlappedResult.
     *
     * @param event created by CreateEventA
     */
    long ReadFile(long handle, NativeMemory buffer, long off, int len, long event) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Writes bytes from a Buffer into a handle.
     *
     * @param handle file handle
     * @param buffer data from here
     * @param off offset of data
     * @param len maximum bytes to read
     *
     * @return number of bytes read
     */
    int WriteFile(long handle, byte[] buffer, int off, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Writes bytes from a Buffer into a handle.
     *
     * @param handle file handle
     * @param buffer data from here
     * @param len maximum bytes to read
     *
     * @return number of bytes read
     */
    int WriteFile(long handle, ByteBuffer buffer, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Writes bytes from a Buffer into a handle.
     *
     * @param handle file handle
     * @param buffer data from here
     * @param off offset of data
     * @param len maximum bytes to read
     *
     * @return number of bytes read
     */
    int WriteFile(long handle, NativeMemory buffer, long off, int len) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * writes using overlapped mechanism. returns an overlapped pointer that must be feed by calling {@link #free(long)} after it has been confirmed that the async WRITE is done by calling GetOverlappedResult.
     *
     * @param event created by CreateEventA
     */
    long WriteFile(long handle, NativeMemory buffer, long off, int len, long event) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Gets the result from an async io operation on a handle.
     *
     * @param handle handle on which the async operation is performed.
     * @param overlapped overlapped pointer returned by the call that started the async operation.
     * @param wait wait until the async operation is completed before return. false means return immediately.
     * @return  -1 if the async operation is not yet completed. (only if wait=false) otherwise number of bytes transfered is returned.
     */
    int GetOverlappedResult(long handle, long overlapped, boolean wait) throws InvalidFileDescriptorException, UnknownNativeErrorException;

    /**
     * Returns a friendly adapter index.
     * Sidenote: javas {@link java.net.NetworkInterface} class uses the friendly index for its byIndex method.
     * @param index the "unfriendly" adapter index
     */
    int GetFriendlyIfIndex(long index);

    /**
     * returns a unfriendly adapter index based on adapter name (GUID).
     * @param adapterName this is a GUID. YOU DO NOT SEE THIS NAME ANYWHERE OUTSIDE THE WINDOWS REGISTRY!
     *                    for example: Computer\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Class\{4d36e972-e325-11ce-bfc1-08002be10318}\0000->NetCfgInstanceId
     *                    would hold this GUID. Ex value would be "{4E27A816-B07C-48E3-9453-6145B1BFFB51}"
     * @throws UnknownNativeErrorException
     */
    long GetAdapterIndex(String adapterName) throws UnknownNativeErrorException;

    /**
     * Returns adapter addresses.
     */
    Collection<IpAdapterAddresses> GetAdaptersAddresses(long family, long flags) throws UnknownNativeErrorException;

    /**
     * Opens a process token handle.
     *
     * @return the token handle that must be closed with CloseHandle
     */
    long OpenProcessToken(long ProcessHandle, int DesiredAccess) throws UnknownNativeErrorException;

    /**
     * Gets information about a token
     * @param TokenHandle obtained from {@link #OpenProcessToken(long, int)}
     * @param TokenInformationClass int constants from {@link WinConst}, all valid values start with "Token"
     * @return binary struct that has to be parsed. Length/Meaning depends on TokenInformationClass
     */
    byte[] GetTokenInformation(long TokenHandle, int TokenInformationClass) throws UnknownNativeErrorException;


    /**
     * Performs an operation on a specified file.
     * @param hwnd handle to parent window. 0 is a possible value.
     * @param lpOperation operation to perform. This is a string enum. noteable values are "runas" "open" "print" and "explore"
     * @param lpFile the file to perform the operation on
     * @param lpParameters dependant on verb. on "runas" for example this would be parameters to the program pointed to by lpFile
     * @param lpDirectory defines the working directory for the action
     * @param nShowCmd defines how to action is displayed to the user value from 0 to 11 are valid
     */
    long ShellExecuteA(long hwnd, String lpOperation, String lpFile, String lpParameters, String lpDirectory, int nShowCmd) throws ShellExecuteException;




    //TODO
    //long CreateIpForwardEntry(MibIpForwardRow pRoute) throws UnknownNativeErrorException;

    //long DeleteIpForwardEntry(MibIpForwardRow pRoute) throws UnknownNativeErrorException;

}
