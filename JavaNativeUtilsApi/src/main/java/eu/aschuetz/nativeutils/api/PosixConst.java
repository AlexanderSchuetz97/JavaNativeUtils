package eu.aschuetz.nativeutils.api;

import eu.aschuetz.nativeutils.api.consts.DefaultPosixConstProvider;
import eu.aschuetz.nativeutils.api.consts.PosixConstProvider;

public class PosixConst {
    //open flags
    public static final int O_ACCMODE;
    public static final int O_RDONLY;
    public static final int O_WRONLY;
    public static final int O_RDWR;
    public static final int O_CREAT;
    public static final int O_EXCL;
    public static final int O_NOCTTY;
    public static final int O_TRUNC;
    public static final int O_APPEND;
    public static final int O_NONBLOCK;
    public static final int O_NDELAY;
    public static final int O_SYNC;
    public static final int O_ASYNC;
    public static final int O_DIRECTORY;
    public static final int O_NOFOLLOW;
    public static final int O_CLOEXEC;
    public static final int O_DSYNC;

    public static final int S_IRUSR;
    public static final int S_IWUSR;
    public static final int S_IXUSR;
    public static final int S_IRGRP;
    public static final int S_IWGRP;
    public static final int S_IXGRP;
    public static final int S_IROTH;
    public static final int S_IWOTH;
    public static final int S_IXOTH;
    public static final int S_IRWXU;
    public static final int S_IRWXG;
    public static final int S_IRWXO;

    //FOR MMAP FLAGS
    public static final int MAP_SHARED;
    public static final int MAP_PRIVATE;

    static {

        PosixConstProvider provider = null;
        try {
            NativeUtil utils = NativeUtils.get();
            if (NativeUtils.isPosix()) {
                provider = NativeUtils.getPosixUtil().getPosixConstProvider();
            } else {
                provider = new DefaultPosixConstProvider(); //fallback to Linux amd64 constants
            }
        } catch (Throwable t) {
            provider = new DefaultPosixConstProvider();
        }

        O_ACCMODE = provider.O_ACCMODE();
        O_RDONLY = provider.O_RDONLY();
        O_WRONLY = provider.O_WRONLY();
        O_RDWR = provider.O_RDWR();
        O_CREAT = provider.O_CREAT();
        O_EXCL = provider.O_EXCL();
        O_NOCTTY = provider.O_NOCTTY();
        O_TRUNC = provider.O_TRUNC();
        O_APPEND = provider.O_APPEND();
        O_NONBLOCK = provider.O_NONBLOCK();
        O_NDELAY = provider.O_NDELAY();
        O_SYNC = provider.O_SYNC();
        O_ASYNC = provider.O_ASYNC();
        O_DIRECTORY = provider.O_DIRECTORY();
        O_NOFOLLOW = provider.O_NOFOLLOW();
        O_CLOEXEC = provider.O_CLOEXEC();
        O_DSYNC = provider.O_DSYNC();
        S_IRUSR = provider.S_IRUSR();
        S_IWUSR = provider.S_IWUSR();
        S_IXUSR = provider.S_IXUSR();
        S_IRGRP = provider.S_IRGRP();
        S_IWGRP = provider.S_IWGRP();
        S_IXGRP = provider.S_IXGRP();
        S_IROTH = provider.S_IROTH();
        S_IWOTH = provider.S_IWOTH();
        S_IXOTH = provider.S_IXOTH();
        S_IRWXU = provider.S_IRWXU();
        S_IRWXG = provider.S_IRWXG();
        S_IRWXO = provider.S_IRWXO();
        MAP_PRIVATE = provider.MAP_PRIVATE();
        MAP_SHARED = provider.MAP_SHARED();
    }
}
