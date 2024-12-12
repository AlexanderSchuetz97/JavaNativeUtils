package eu.aschuetz.nativeutils.api.consts;

public class DefaultPosixConstProvider implements PosixConstProvider {

    int O_ACCMODE = 0003;
    int O_RDONLY = 00;
    int O_WRONLY = 01;
    int O_RDWR = 02;
    int O_CREAT = 0100;
    int O_EXCL = 0200;
    int O_NOCTTY = 0400;
    int O_TRUNC = 01000;
    int O_APPEND = 02000;
    int O_NONBLOCK = 04000;
    int O_NDELAY = O_NONBLOCK;
    int O_SYNC = 04010000;
    int O_ASYNC = 020000;
    int O_DIRECTORY = 0200000;
    int O_NOFOLLOW = 0400000;
    int O_CLOEXEC = 02000000;
    int O_DSYNC = 010000;

    int S_IRUSR = 0400;
    int S_IWUSR = 0200;
    int S_IXUSR = 0100;
    int S_IRGRP = S_IRUSR >> 3;
    int S_IWGRP = S_IWUSR >> 3;
    int S_IXGRP = S_IXUSR >> 3;
    int S_IROTH = S_IRGRP >> 3;
    int S_IWOTH = S_IWGRP >> 3;
    int S_IXOTH = S_IXGRP >> 3;
    int S_IRWXU = S_IRUSR | S_IWUSR | S_IXUSR;
    int S_IRWXG = S_IRWXU >> 3;
    int S_IRWXO = S_IRWXG >> 3;

    int MAP_SHARED = 1;
    int MAP_PRIVATE = 2;

    @Override
    public int O_ACCMODE() {
        return O_ACCMODE;
    }

    @Override
    public int O_RDONLY() {
        return O_RDONLY;
    }

    @Override
    public int O_WRONLY() {
        return O_WRONLY;
    }

    @Override
    public int O_RDWR() {
        return O_RDWR;
    }

    @Override
    public int O_CREAT() {
        return O_CREAT;
    }

    @Override
    public int O_EXCL() {
        return O_EXCL;
    }

    @Override
    public int O_NOCTTY() {
        return O_NOCTTY;
    }

    @Override
    public int O_TRUNC() {
        return O_TRUNC;
    }

    @Override
    public int O_APPEND() {
        return O_APPEND;
    }

    @Override
    public int O_NONBLOCK() {
        return O_NONBLOCK;
    }

    @Override
    public int O_NDELAY() {
        return O_NDELAY;
    }

    @Override
    public int O_SYNC() {
        return O_SYNC;
    }

    @Override
    public int O_ASYNC() {
        return O_ASYNC;
    }

    @Override
    public int O_DIRECTORY() {
        return O_DIRECTORY;
    }

    @Override
    public int O_NOFOLLOW() {
        return O_NOFOLLOW;
    }

    @Override
    public int O_CLOEXEC() {
        return O_CLOEXEC;
    }

    @Override
    public int O_DSYNC() {
        return O_DSYNC;
    }

    @Override
    public int S_IRUSR() {
        return S_IRUSR;
    }

    @Override
    public int S_IWUSR() {
        return S_IWUSR;
    }

    @Override
    public int S_IXUSR() {
        return S_IXUSR;
    }

    @Override
    public int S_IRGRP() {
        return S_IRGRP;
    }

    @Override
    public int S_IWGRP() {
        return S_IWGRP;
    }

    @Override
    public int S_IXGRP() {
        return S_IXGRP;
    }

    @Override
    public int S_IROTH() {
        return S_IROTH;
    }

    @Override
    public int S_IWOTH() {
        return S_IWOTH;
    }

    @Override
    public int S_IXOTH() {
        return S_IXOTH;
    }

    @Override
    public int S_IRWXU() {
        return S_IRWXU;
    }

    @Override
    public int S_IRWXG() {
        return S_IRWXG;
    }

    @Override
    public int S_IRWXO() {
        return S_IRWXO;
    }

    @Override
    public int MAP_SHARED() {
        return MAP_SHARED;
    }

    @Override
    public int MAP_PRIVATE() {
        return MAP_PRIVATE;
    }
}
