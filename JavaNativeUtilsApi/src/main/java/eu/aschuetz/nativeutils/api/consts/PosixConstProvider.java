package eu.aschuetz.nativeutils.api.consts;

public interface PosixConstProvider {

    /////
    // Open flags
    ////

    int O_ACCMODE() ;
    int O_RDONLY() ;
    int O_WRONLY() ;
    int O_RDWR() ;
    int O_CREAT();
    int O_EXCL();
    int O_NOCTTY();
    int O_TRUNC();
    int O_APPEND();
    int O_NONBLOCK();
    int O_NDELAY();
    int O_SYNC() ;
    int O_ASYNC();

    int O_DIRECTORY();
    int O_NOFOLLOW();
    int O_CLOEXEC();
    int O_DSYNC();

    int S_IRUSR();
    int S_IWUSR();
    int S_IXUSR();
    int S_IRGRP() ;
    int S_IWGRP() ;
    int S_IXGRP() ;
    int S_IROTH() ;
    int S_IWOTH() ;
    int S_IXOTH() ;
    int S_IRWXU() ;
    int S_IRWXG() ;
    int S_IRWXO() ;

    //FOR MMAP FLAGS
    int MAP_SHARED();
    int MAP_PRIVATE();
}
