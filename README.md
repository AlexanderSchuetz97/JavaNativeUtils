# JavaNativeUtils
JavaNativeUtils is a library containing a jni wrapper for various operating system specific syscalls.
Purpose of this library is to allow for direct interaction with the operating system from Java 
without having to write a JNI wrapper every single time.


## License
JavaNativeUtils is released under the GNU Lesser General Public License Version 3. <br>
A copy of the GNU Lesser General Public License Version 3 can be found in the COPYING & COPYING.LESSER files.<br>

## Usage
Maven:
````
<dependency>
    <groupId>io.github.alexanderschuetz97</groupId>
    <artifactId>JavaNativeUtils</artifactId>
    <version>2.0</version>
</dependency>
````

Java:
````
if (NativeUtils.isLinux()) {
    LinuxNativeUtil util = NativeUtils.getLinuxUtil()
    System.out.println(util.stat("/tmp"));
    return;
}

if (NativeUtils.isWindows()) {
    WindowsNativeUtil util = NativeUtils.getWindowsUtil()
    System.out.println(util._stat64("C:\\Windows"));
    return;
}
````

## List of supported Syscalls
#### Linux
* open
* fcntl
* ioctl
* symlink
* link
* stat
* fstat
* lstat
* chdir
* strerror_r
* socket
* connect
* read
* write
* getsockopt
* setsockopt
* close
* recvfrom
* recvmsg (includes CMSG HDR parsing)
* sendmsg
* mmap
* msync
* munmap
* getpagesize
* __get_cpuid_count (from cpuid.h)
* if_nametoindex
* if_indextoname


#### Windows
* _locking
* _stat64
* LockFileEx
* UnlockFileEx
* GetFileAttributesEx
* CreateSymbolicLinkA
* CreateHardLinkA
* CreateFileA
* CloseHandle
* GetFileAttributesA
* SetFileAttributesA
* ExpandEnvironmentStringsA
* SetEnvironmentVariableA
* GetEnvironmentVariableA
* GetModuleFileNameA
* GetVolumePathNameW
* strerror_s
* FormatMessageA
* SetupDiGetClassDevsA
* SetupDiEnumDeviceInterfaces
* SetupDiGetDeviceInterfaceDetail
* SetupDiDestroyDeviceInfoList
* DeviceIoControl
* CreateEventA
* ResetEvent
* WaitForSingleObject
* WaitForMultipleObjects
* GetOverlappedResult
* GetFriendlyIfIndex
* GetAdapterIndex
* GetAdaptersAddresses
* GetCurrentThread
* GetCurrentProcess
* DuplicateHandle
* CancelIo
* CancelIoEx
* CancelSynchronousIo
* __get_cpuid_count (from cpuid.h)
* RegOpenKeyExA
* RegCloseKey
* RegQueryValueExA
* GetTokenInformation
* OpenProcessToken
* ShellExecuteA

### List of exposed JNI Functions (All OS)
### Reflection
Reason: In newer Java Versions (17+) Reflection was gutted and is no longer able to access private Fields. <br>
All those methods are also available in sun.misc.Unsafe. <br>
Accessing sun.misc.Unsafe is also non-trivial in newer Java Versions depending on how your application/library is deployed/used.

(X) is a substitute for this set "Object, Long, Int, Short, Char, Byte, Float, Double"

* FromReflectedField
* GetFieldID
* Get(X)Field
* GetStatic(X)Field
* Set(X)Field
* SetStatic(X)Field
* FromReflectedMethod
* GetMethodID
* GetStaticMethodID
* Call(X)Method
* CallStatic(X)Method
### Other JNI Methods
* AllocObject
* DefineClass
* MonitorEnter
* MonitorExit
* Throw
* NewGlobalRef
* DeleteGlobalRef
* NewLocalRef
* NewDirectByteBuffer
* GetDirectBufferAddress


## Dependencies
* Java 7 or newer

### Supported Operating Systems / Architectures
#### Windows (Vista or newer)
* i386 
* amd64
#### Linux
* i386 (GLIBC 2.17 or newer)
* amd64 (GLIBC 2.17 or newer)
* armhf (GLIBC 2.17 or newer)
* aarch64 (GLIBC 2.17 or newer) (untested, automatic loading may not work since there is no documentation what "os.arch" is on aarch64)

If an unsupported operating system or processor architecture is used then getWindowsUtil() or getLinuxUtil() throws an exception.
To check if the current system supports linux or windows syscalls use the isLinux() or isWindows() method.

## Building
#### Windows:
Building JavaNativeUtils on Windows is currently not possible.
#### Linux:
Requirements:
* bash
* docker
* docker-compose
* jdk 8
  * Note: for various reasons you must use a JDK 8 to compile... 
  * The compiled library will work when used by any java version between including java 7 and including java 18.

Building for the first time will build the docker image to compile the native libraries. 
This will take a few minutes depending on your internet connection speed. You will only have to do this once
unless you delete/remove the containers/images.

To build:
1. clone the git repository
2. run:
````
maven -Dmaven.test.skip=true -Dgpg.skip clean install
````
