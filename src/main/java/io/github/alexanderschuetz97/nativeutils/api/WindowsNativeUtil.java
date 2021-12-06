//
// Copyright Alexander Schütz, 2021
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

import io.github.alexanderschuetz97.nativeutils.api.exceptions.InvalidFileDescriptorException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.SharingViolationException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.Stat;
import io.github.alexanderschuetz97.nativeutils.api.structs.Win32FileAttributeData;

import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.nio.file.FileAlreadyExistsException;

public interface WindowsNativeUtil extends NativeReflection {

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
     * Closes a windows handle. I do NOT recommend calling this with a handle that you did not create.
     * This holds especially true for a HANDLE aquired by calling #getHandle
     */
    void CloseHandle(long handle) throws UnknownNativeErrorException, InvalidFileDescriptorException;

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
}
