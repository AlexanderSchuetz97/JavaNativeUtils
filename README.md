l# JavaNativeUtils
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
    <groupId>eu.aschuetz</groupId>
    <artifactId>JavaNativeUtilsApi</artifactId>
    <version>4.6</version>
</dependency>
<dependency>
    <groupId>eu.aschuetz</groupId>
    <artifactId>JavaNativeUtilsJni</artifactId>
    <version>4.6</version>
</dependency>
````
Note: for versions older than 4.0 use groupId io.github.alexanderschuetz97 artifactId JavaNativeUtils

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

if (NativeUtils.isFreeBSD()) {
    FreeBSDNativeUtil util = NativeUtils.getFreeBSDUtil()
    System.out.println(util.stat("/tmp"));
    return;
}

````

## List of supported Syscalls
#### Linux
* malloc & free
* open
* fcntl
* ioctl
* symlink
* link
* unlink
* stat
* statvfs
* fstat
* lstat
* chdir
* strerror_r
* socket
* connect
* read
* write
* fsync
* getsockopt
* setsockopt
* close
* recvfrom
* recvmsg (includes CMSG HDR parsing)
* sendmsg
* mmap
* msync
* munmap
* mkfifo
* getpagesize
* __get_cpuid_count (from cpuid.h)
* if_nametoindex
* if_indextoname
* sem_open
* sem_close
* sem_unlink
* sem_init
* sem_destroy
* sem_post
* sem_wait
* sem_getvalue
* sem_trywait
* sem_timedwait
* shm_open
* shm_unlink
* ftruncate
* truncate
* memfd_create
* malloc_trim (only glibc)
* madvise
* pthread_condattr_destroy
* pthread_condattr_init
* pthread_mutexattr_destroy
* pthread_mutexattr_init
* pthread_condattr_getpshared
* pthread_condattr_setpshared
* pthread_mutexattr_setpshared
* pthread_mutexattr_getpshared
* pthread_mutexattr_settype
* pthread_mutexattr_gettype
* pthread_mutexattr_getrobust
* pthread_mutexattr_setrobust
* pthread_mutex_consistent
* pthread_mutex_init
* pthread_mutex_destroy
* pthread_mutex_lock
* pthread_mutex_trylock
* pthread_mutex_unlock
* pthread_mutex_timedlock
* pthread_cond_broadcast
* pthread_cond_signal
* pthread_cond_wait
* pthread_cond_timedwait
* pthread_cond_destroy
* pthread_cond_init

#### Windows
* malloc & free
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
* OpenEventA
* ResetEvent
* SetEvent
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
* CreateFileMappingA
* OpenFileMappingA
* MapViewOfFileEx
* UnmapViewOfFile
* GetIpForwardTable2
* CreateIpForwardEntry2
* ConvertInterfaceIndexToLuid
* ConvertInterfaceLuidToIndex
* ConvertInterfaceLuidToNameA
* ConvertInterfaceNameToLuidA
* ConvertInterfaceLuidToAlias
* CreateNamedPipeA
* ConnectNamedPipe
* WaitNamedPipeA
* DisconnectNamedPipe
* FlushFileBuffers
* ReleaseSemaphore
* CreateSemaphoreExA
* SetupComm
* SetCommTimeouts
* WaitCommEvent
* TransmitCommChar
* SetDefaultCommConfigA
* SetCommState
* SetCommMask
* SetCommConfig
* SetCommBreak
* PurgeComm
* GetDefaultCommConfigA
* GetCommTimeouts
* GetCommState
* GetCommProperties
* GetCommModemStatus
* GetCommMask
* GetCommConfig
* EscapeCommFunction
* ClearCommError
* ClearCommBreak

#### FreeBSD
* malloc & free
* stat
* symlink
* unlink

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

Only amd64 architecture is tested!

#### Linux

GLIBC 2.17 or newer:
* i386
* amd64
* armel
* armhf
* aarch64
* riscv64
* mips64el
* ppc64le
* s390x

musl libc (Alpine Linux):
* amd64

Only amd64 i386 armhf aarch64 and riscv64 architecture is tested with real hardware!
The others are only tested using qemu usermode emulation.

#### FreeBSD (14.1)
* amd64

INFO: FreeBSD support in this library is pretty rudimentary. In its current state it is mainly useful for access to 
the JNI Reflection. I may port over some posix compliant syscalls from the linux specific implementation 
to freebsd in the future, should I require them for my future projects. 
For my current needs the JNI Reflection is sufficient.

I currently use freebsd 14.1 to cross compile and test. 
The library may or may not work with earlier or later versions of freebsd.

### Unsupported OS

If an unsupported operating system or processor architecture is used then getWindowsUtil() getLinuxUtil() or getFreeBSDUtil() throws an exception.
To check if the current system supports linux or windows syscalls use the isLinux() isWindows() of isFreeBSD() method.

### INFO: Linux using pthread_mutex and pthread_cond for IPC with a C Program
Note that pthread_mutex and pthread_cond in shared memory for IPC with a C program will only work
if the C Program uses the same or a similar enough version of the C library.

This means that if you use JavaNativeUtils with a glibc jvm to perform IPC with a
C program that was statically compiled against libc-musl then pthread_mutex
pthread_cond will not be compatible.

If the C Program uses glibc then it may not use a glibc version older than 2.3.2 (released ~2003) 
if you intend to use pthread_cond. pthread_mutex "should" always work.

Please keep in mind that glibc may decide to "change" pthread_cond or pthread_mutex in a future release.
Should this happen, then the C Program must not be linked against that new version if you want to do IPC communication with it.
The build environment for JavaNativeUtils will always use glibc version 2.2.5 for pthread_mutex and
glibc version 2.3.2 for pthread_cond.

All information regarding glibc versions was only verified for the amd64 architecture. If you
intend to use the other architectures then you will have to use objdump to verify that
the symbols for pthread_cond and pthread_mutex are the same on the c program and the respective shared object file
of JavaNativeUtils.


## Building and Development
#### Windows:
Building JavaNativeUtils on Windows is currently not possible.
#### Linux:
Requirements:
* bash
* docker
* docker-compose
* jdk 8
  * Note: for various reasons you must use a JDK 8 to compile... 
  * The compiled library will work when used by any java version between including java 7 and including java 21.

Building for the first time will build the docker image to compile the native libraries. 
This will take a few minutes depending on your internet connection speed. You will only have to do this once
unless you delete/remove the containers/images.

To build:
1. clone the git repository
2. run:
````
maven -Dmaven.test.skip=true -Dgpg.skip clean install
````

### How to run foreign architecture tests using QEMU+docker+binfmt_misc
To run non amd64 tests you may use the run bash script dockertest.sh in the repository root.
1. build the entire project and run amd64 tests (clean install)
2. install qemu-user-static so that for example /usr/bin/qemu-riscv64-static exists, repeat for all architectures
3. setup binfmt_misc so that the linux kernel knows how to execute elf binaries of foreign architecture 
   - ls /proc/sys/fs/binfmt_misc/ should contain 1 qemu file per architecture
4. configure your docker daemon to allow foreign architectures
   - "docker run --rm -it arm64v8/debian:bookworm" is a good way to test this.
5. run dockertest.sh (exit code 0 = no error)

### How to debug the native part
1. Edit the makefile and uncomment `#DEBUG_FLAGS=-ggdb -g3` and comment the `DEBUG_FLAGS=-g0` line underneath.
2. Start the jvm with gdbserver and a java remote debugger in attach mode, suspend=y is recommended.
3. Connect your native remote debugger (I use CLion)
4. Place a java breakpoint in a java IDE (Eclipse or IntelliJ will work) after the call to System.load in NativeLibraryLoaderHelper
5. Connect your java remote debugger
6. You might have to instruct gdb to NOT stop on SIGSEGV and possibly other signals too as the JVM uses this signal internally for garbage collection
7. Wait until the java breakpoint is hit
8. Your should now be able to place your native breakpoints in the native debugger as the shared object should now have been loaded.
9. Hit resume in your java debugger. After this you can detatch the java debugger.
10. Wait until your native breakpoints are hit.

#### Further debugging tips

You can preempt NativeLibraryLoaderHelper by calling System.load to your debug so/dll before the first
usage of NativeUtils in your program. This allows for easy debugging of the native part without
recompiling your program with a custom .jar of JavaNativeUtils. This is especially useful if you 
cannot compile JavaNativeUtils locally for whatever reason, since you can just compile a debug so/dll
in a Virtual Machine and just "move" a single shared object file to your actual development machine.

For debugging the windows native part I use gdbserver.exe to start the jvm. It should also be possible to attach 
proprietary debuggers on windows or build a PDB for them by adjusting the makefile 
and building a custom debug dll manually. I have never compiled JavaNativeUtils with anything 
other than Clang or GCC, using for example the MSVC may work, 
but will probably require significant modification of the makefile.

## Will this library be obsoleted by the Java FFI Interface (Project Panama)
Probably yes. The Java FFI Interface allows a Java developer to perform most of the actions
that this library permits without writing C code. The only exception would be bypassing the "Reflection" checks. 
It will however require a significant amount of Java code to be written by the developer 
to perform the same things this library does. 
The main advantage of the FFI Interface vs this library is probably going to be that it can work with any .dll/.so file
and on any CPU architecture.

My conclusion from looking at early benchmarks of the Java FFI Interface vs JNI is that the FFI interface
appears to be somewhat slower than JNI.

In addition to that, the FFI Interface is still a "preview" feature in Java 21 (LTS) and therefore not enabled by
default. A lot of applications still rely on java 8, and I personally doubt that java 8, 11 and 17 (even 21)
will disappear in the next 10 years. Just for those versions alone I intend to keep working on this library.
I also do not expect major adoption of the first LTS release after 21 that will presumably contain the "full" FFI 
to happen in the next 6 years.