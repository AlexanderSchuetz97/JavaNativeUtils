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

/**
 * This file contains some constants from the windows header files.
 */
public interface WinConst {

    //winsock2.h
    int AF_INET = 2;
    int AF_INET6 = 23; //NOT THE SAME AS LINUX!

    ////
    // CreateFileA attributes
    ////

    int FILE_FLAG_WRITE_THROUGH = 0x80000000;
    int FILE_FLAG_OVERLAPPED = 0x40000000;
    int FILE_FLAG_NO_BUFFERING = 0x20000000;
    int FILE_FLAG_RANDOM_ACCESS = 0x10000000;
    int FILE_FLAG_SEQUENTIAL_SCAN = 0x8000000;
    int FILE_FLAG_DELETE_ON_CLOSE = 0x4000000;
    int FILE_FLAG_BACKUP_SEMANTICS = 0x2000000;
    int FILE_FLAG_POSIX_SEMANTICS = 0x1000000;
    int FILE_FLAG_SESSION_AWARE = 0x800000;
    int FILE_FLAG_OPEN_REPARSE_POINT = 0x200000;
    int FILE_FLAG_OPEN_NO_RECALL = 0x100000;
    int FILE_FLAG_FIRST_PIPE_INSTANCE = 0x80000;

    ////
    // File Attributes for Get/SetFileAttributesA
    ////

    int FILE_ATTRIBUTE_READONLY = 0x00000001;
    int FILE_ATTRIBUTE_HIDDEN = 0x00000002;
    int FILE_ATTRIBUTE_SYSTEM = 0x00000004;
    int FILE_ATTRIBUTE_DIRECTORY = 0x00000010;
    int FILE_ATTRIBUTE_ARCHIVE = 0x00000020;
    int FILE_ATTRIBUTE_DEVICE = 0x00000040;
    int FILE_ATTRIBUTE_NORMAL = 0x00000080;
    int FILE_ATTRIBUTE_TEMPORARY = 0x00000100;
    int FILE_ATTRIBUTE_SPARSE_FILE = 0x00000200;
    int FILE_ATTRIBUTE_REPARSE_POINT = 0x00000400;
    int FILE_ATTRIBUTE_COMPRESSED = 0x00000800;
    int FILE_ATTRIBUTE_OFFLINE = 0x00001000;
    int FILE_ATTRIBUTE_NOT_CONTENT_INDEXED = 0x00002000;
    int FILE_ATTRIBUTE_ENCRYPTED = 0x00004000;
    int FILE_ATTRIBUTE_VIRTUAL = 0x00010000;

    ////
    // Flags for SetupDiGetClassDevsW
    ///

    int DIGCF_DEFAULT = 1;
    int DIGCF_PRESENT = 2;
    int DIGCF_ALLCLASSES = 4;
    int DIGCF_PROFILE = 8;
    int DIGCF_DEVICEINTERFACE = 16;

    // DeviceIoControl Flags
    int FILE_DEVICE_UNKNOWN = 0x00000022;
    int METHOD_BUFFERED = 0;
    int METHOD_IN_DIRECT = 1;
    int METHOD_OUT_DIRECT = 2;
    int METHOD_NEITHER = 3;
    int FILE_ANY_ACCESS = 0;
    int FILE_READ_ACCESS = 1;
    int FILE_WRITE_ACCESS = 2;

    //Registry constants
    long HKEY_CLASSES_ROOT = 0x80000000;
    long HKEY_CURRENT_USER = 0x80000001;
    long HKEY_LOCAL_MACHINE = 0x80000002;
    long HKEY_USERS = 0x80000003;
    long HKEY_PERFORMANCE_DATA = 0x80000004;
    long HKEY_PERFORMANCE_TEXT = 0x80000050;
    long HKEY_PERFORMANCE_NLSTEXT = 0x80000060;
    long HKEY_CURRENT_CONFIG = 0x80000005;
    long HKEY_DYN_DATA = 0x80000006;
    int KEY_QUERY_VALUE = 0x0001;
    int KEY_SET_VALUE = 0x0002;
    int KEY_CREATE_SUB_KEY = 0x0004;
    int KEY_ENUMERATE_SUB_KEYS = 0x0008;
    int KEY_NOTIFY = 0x0010;
    int KEY_CREATE_LINK = 0x0020;
    int KEY_WOW64_64KEY = 0x0100;
    int KEY_WOW64_32KEY = 0x0200;
    int KEY_WOW64_RES = 0x0300;
    int KEY_ALL_ACCESS = 0xF003F;
    int KEY_EXECUTE = 0x20019;
    int KEY_READ = 0x20019;
    int KEY_WRITE = 0x20006;

    //Access flags
    int STANDARD_RIGHTS_ALL = 0x001F0000;
    int READ_CONTROL = 0x00020000;
    int STANDARD_RIGHTS_READ = READ_CONTROL;
    int STANDARD_RIGHTS_WRITE = READ_CONTROL;
    int STANDARD_RIGHTS_EXECUTE = READ_CONTROL;
    int SPECIFIC_RIGHTS_ALL = 0x0000FFFF;
    int STANDARD_RIGHTS_REQUIRED = 0x000F0000;


    int TOKEN_ASSIGN_PRIMARY = 0x0001;
    int TOKEN_DUPLICATE = 0x0002;
    int TOKEN_IMPERSONATE = 0x0004;
    int TOKEN_QUERY = 0x0008;
    int TOKEN_QUERY_SOURCE = 0x0010;
    int TOKEN_ADJUST_PRIVILEGES = 0x0020;
    int TOKEN_ADJUST_GROUPS = 0x0040;
    int TOKEN_ADJUST_DEFAULT = 0x0080;
    int TOKEN_ADJUST_SESSIONID = 0x0100;

    //TOKEN_INFORMATION_CLASS
    int TokenUser = 1;
    int TokenGroups = 2;
    int TokenPrivileges = 3;
    int TokenOwner = 4;
    int TokenPrimaryGroup = 5;
    int TokenDefaultDacl = 6;
    int TokenSource = 7;
    int TokenType = 8;
    int TokenImpersonationLevel = 9;
    int TokenStatistics = 10;
    int TokenRestrictedSids = 11;
    int TokenSessionId = 12;
    int TokenGroupsAndPrivileges = 13;
    int TokenSessionReference = 14;
    int TokenSandBoxInert = 15;
    int TokenAuditPolicy = 16;
    int TokenOrigin = 17;
    int TokenElevationType = 18;
    int TokenLinkedToken = 19;
    int TokenElevation = 20;
    int TokenHasRestrictions = 21;
    int TokenAccessInformation = 22;
    int TokenVirtualizationAllowed = 23;
    int TokenVirtualizationEnabled = 24;
    int TokenIntegrityLevel = 25;
    int TokenUIAccess = 26;
    int TokenMandatoryPolicy = 27;
    int TokenLogonSid = 28;
    int TokenIsAppContainer = 29;
    int TokenCapabilities = 30;
    int TokenAppContainerSid = 31;
    int TokenAppContainerNumber = 32;
    int TokenUserClaimAttributes = 33;
    int TokenDeviceClaimAttributes = 34;
    int TokenRestrictedUserClaimAttributes = 35;
    int TokenRestrictedDeviceClaimAttributes = 36;
    int TokenDeviceGroups = 37;
    int TokenRestrictedDeviceGroups = 38;
    int TokenSecurityAttributes = 39;
    int TokenIsRestricted = 40;
    int TokenProcessTrustLevel = 41;
    int TokenPrivateNameSpace = 42;
    int TokenSingletonAttributes = 43;
    int TokenBnoIsolation = 44;
    int TokenChildProcessFlags = 45;
    int TokenIsLessPrivilegedAppContainer = 46;
    int TokenIsSandboxed = 47;
    int TokenIsAppSilo = 48;
    int MaxTokenInfoClass = 49;
}

