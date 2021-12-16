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
    <version>1.2</version>
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
* fnctl F_GETLK
* fnctl F_SETLK
* fnctl F_SETLKW
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
* strerror_s
* FormatMessageA

### List of exposed JNI Functions (All OS)
### Reflection
Reason: In newer Java Versions (17+) Reflection was gutted and is no longer able to access private Fields. <br>
All those methods are also availabe in sun.misc.Unsafe. <br>
Accessing sun.misc.Unsafe is also non-trivial in newer Java Versions depending on how your application/library is deployed/used.
* FromReflectedField
* GetFieldID
* GetObjectField
* GetStaticObjectField
* GetIntField
* GetStaticIntField
* GetLongField
* GetStaticLongField
* GetDoubleField
* GetStaticDoubleField
* GetFloatField
* GetStaticFloatField
* GetShortField
* GetStaticShortField
* GetCharField
* GetStaticCharField
* GetByteField
* GetStaticByteField
* GetBooleanField
* GetStaticBooleanField
* SetObjectField
* SetStaticObjectField
* SetIntField
* SetStaticIntField
* SetLongField
* SetStaticLongField
* SetDoubleField
* SetStaticDoubleField
* SetFloatField
* SetStaticFloatField
* SetShortField
* SetStaticShortField
* SetCharField
* SetStaticCharField
* SetByteField
* SetStaticByteField
* SetBooleanField
* SetStaticBooleanField


## Dependencies
* Java 7 or newer

### Supported Operating Systems / Architectures
#### Windows (Vista or newer)
* i386 
* amd64
#### Linux
* i386 (GLIBC 2.3.4 or newer)
* amd64 (GLIBC 2.3.4 or newer)
* armhf (GLIBC 2.4 or newer)
* aarch64 (GLIBC 2.17 or newer) (untested, automatic loading may not work since its no where documented what "os.arch" is on aarch64)

If an unsupported operating system or processor architecture is used then getWindowsUtil() or getLinuxUtil() throws an exception.
To check if the current system supports linux or windows syscalls use the isLinux() or isWindows() method.

## Building
#### Windows:
Building JavaNativeUtils on Windows is currently not possible.
#### Linux:
Requirements:
* mingw-cross (x86)
* mingw-cross (i386)
* gcc compiler (x86)
* gcc compiler (i386)
* gcc compiler (armhf)
* gcc compiler (aarch64)
* make
* bash
* linux JDK 7 or newer
* Windows JDK 7 or newer (only for headers, optional you can skip this requirement by adjusting config)

JDK 7 (Oracle), 8 (OpenJDK) and 11 (OpenJDK) were tested.
On a 64 bit Ubuntu 20.04 all requirements for building can be installed by running:
````
sudo apt-get install build-essential gcc-mingw-w64 openjdk-8-jdk gcc-mingw-w64-i686 gcc-mingw-w64-x86-64 gcc-i686-linux-gnu gcc-arm-linux-gnueabihf gcc-aarch64-linux-gnu 
````
You may have to adjust this command if you desire a different JDK version.

To get the Windows JDK either copy the JDK home directory from a Windows installation or use other means
(such as msiextract or unzip) to extract the JDK home directory from a Windows setup file.

It is not required to run anything using the Windows JDK. The only relevant files for JavaNativeUtils
are inside the "include" folder. You can safely delete everything else as long as you do not change the folder structure.
It is recommended but not required to use the same JDK version for Windows and Linux because the
JNI headers for Windows are generated using the Linux JDK's javah command to avoid having to run a Windows binary.

To build:
1. clone the git repository
2. run:
````
bash compile_native.sh
````
3. edit the newly created config.sh file and enter the paths for your Windows JDK home and Linux JDK home.
4. (optional) Adjust the build targets to for example disable windows building or use a different compiler
5. run:
````
maven -Dmaven.test.skip=true -Dgpg.skip clean install
````
