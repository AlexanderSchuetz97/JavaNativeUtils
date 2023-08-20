package io.github.alexanderschuetz97.nativeutils.api.structs;

public class Statvfs {
    
    private long f_bsize;    /* Filesystem block size */
    private long  f_frsize;   /* Fragment size */
    private long f_blocks;   /* Size of fs in f_frsize units */
    private long f_bfree;    /* Number of free blocks */
    private long f_bavail;   /* Number of free blocks for
                                             unprivileged users */
    private long f_files;    /* Number of inodes */
    private long f_ffree;    /* Number of free inodes */
    private long f_favail;   /* Number of free inodes for
                                             unprivileged users */
    private long f_fsid;     /* Filesystem ID */
    private long f_flag;     /* Mount flags */
    private long f_namemax;  /* Maximum filename length */

    public long getF_bsize() {
        return f_bsize;
    }

    public void setF_bsize(long f_bsize) {
        this.f_bsize = f_bsize;
    }

    public long getF_frsize() {
        return f_frsize;
    }

    public void setF_frsize(long f_frsize) {
        this.f_frsize = f_frsize;
    }

    public long getF_blocks() {
        return f_blocks;
    }

    public void setF_blocks(long f_blocks) {
        this.f_blocks = f_blocks;
    }

    public long getF_bfree() {
        return f_bfree;
    }

    public void setF_bfree(long f_bfree) {
        this.f_bfree = f_bfree;
    }

    public long getF_bavail() {
        return f_bavail;
    }

    public void setF_bavail(long f_bavail) {
        this.f_bavail = f_bavail;
    }

    public long getF_files() {
        return f_files;
    }

    public void setF_files(long f_files) {
        this.f_files = f_files;
    }

    public long getF_ffree() {
        return f_ffree;
    }

    public void setF_ffree(long f_ffree) {
        this.f_ffree = f_ffree;
    }

    public long getF_favail() {
        return f_favail;
    }

    public void setF_favail(long f_favail) {
        this.f_favail = f_favail;
    }

    public long getF_fsid() {
        return f_fsid;
    }

    public void setF_fsid(long f_fsid) {
        this.f_fsid = f_fsid;
    }

    public long getF_flag() {
        return f_flag;
    }

    public void setF_flag(long f_flag) {
        this.f_flag = f_flag;
    }

    public long getF_namemax() {
        return f_namemax;
    }

    public void setF_namemax(long f_namemax) {
        this.f_namemax = f_namemax;
    }

    @Override
    public String toString() {
        return "Statvfs{" +
                "f_bsize=" + f_bsize +
                ", f_frsize=" + f_frsize +
                ", f_blocks=" + f_blocks +
                ", f_bfree=" + f_bfree +
                ", f_bavail=" + f_bavail +
                ", f_files=" + f_files +
                ", f_ffree=" + f_ffree +
                ", f_favail=" + f_favail +
                ", f_fsid=" + f_fsid +
                ", f_flag=" + f_flag +
                ", f_namemax=" + f_namemax +
                '}';
    }
}
