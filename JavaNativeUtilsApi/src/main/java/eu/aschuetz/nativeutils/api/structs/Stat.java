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
package eu.aschuetz.nativeutils.api.structs;

import java.util.Date;
import java.util.concurrent.TimeUnit;

/**
 * See https://linux.die.net/man/2/stat for the meaning behind each of the fields in this data container.
 *
 * Some values in this data container class are unsigned. This means the value can be bigger than javas Long.MAX_VALUE.
 * If you need to have a numerical representation of this value then convert it to for example a BigInteger.
 * This is not done automatically to not waste cpu time since you may not even care about a certain value,
 * or you may be fine with a signed representation of a unsigned number for your use case.
 * FYI: "simple and slow" single line to convert a long to a unsigned BigInteger:
 * new BigInteger(Long.toHexString(VALUE), 16);
 *
 */
public final class Stat {

    private Stat() {
        //called from c
    }

    private long dev;
    private long ino;
    private long mode;
    private long nlink;
    private long uid;
    private long gid;
    private long rdev;
    private long size;
    private long blksize;
    private long blocks;
    private long atime;
    private long mtime;
    private long ctime;

    /**
     * unsigned number
     */
    public long getDev() {
        return dev;
    }

    /**
     * unsigned number
     */
    public long getIno() {
        return ino;
    }

    /**
     * unsigned number
     */
    public long getMode() {
        return mode;
    }

    //Yes those are octal integer bit masks see stat.h search for S_IFDIR to find them.

    public boolean isDir() {
        return (mode & 0040000) == 0040000;
    }

    public boolean isCharacterDevice() {
        return (mode & 0020000) == 0020000;
    }

    public boolean isBlockDevice() {
        return (mode & 0060000) == 0060000;
    }

    public boolean isRegularFile() {
        return (mode & 0100000) == 0100000;
    }

    public boolean isFIFO() {
        return (mode & 0010000) == 0010000;
    }

    public boolean isSymbolicLink() {
        return (mode & 0120000) == 0120000;
    }

    public boolean isSocket() {
        return (mode & 0140000) == 0140000;
    }

    private static final int OR = 0400;
    private static final int OW = 0200;
    private static final int OE = 0100;
    private static final int GR = OR >> 3;
    private static final int GW = OW >> 3;
    private static final int GE = OE >> 3;
    private static final int ER = GR >> 3;
    private static final int EW = GW >> 3;
    private static final int EE = GE >> 3;


    public boolean canOwnerRead() {
        return (mode & OR) == OR;
    }

    public boolean canOwnerWrite() {
        return (mode & OW) == OW;
    }

    public boolean canOwnerExecute() {
        return (mode & OE) == OE;
    }

    public boolean canGroupRead() {
        return (mode & GR) == GR;
    }

    public boolean canGroupWrite() {
        return (mode & GW) == GW;
    }

    public boolean canGroupExecute() {
        return (mode & GE) == GE;
    }

    public boolean canOthersRead() {
        return (mode & ER) == ER;
    }

    public boolean canOthersWrite() {
        return (mode & EW) == EW;
    }

    public boolean canOthersExecute() {
        return (mode & EE) == EE;
    }

    public String getPermissions() {
        StringBuilder sb = new StringBuilder(9);
        sb.append(canOwnerRead() ? 'r' : '-');
        sb.append(canOwnerWrite() ? 'w' : '-');
        sb.append(canOwnerExecute() ? 'x' : '-');
        sb.append(canGroupRead() ? 'r' : '-');
        sb.append(canGroupWrite() ? 'w' : '-');
        sb.append(canGroupExecute() ? 'x' : '-');
        sb.append(canOthersRead() ? 'r' : '-');
        sb.append(canOthersWrite() ? 'w' : '-');
        sb.append(canOthersExecute() ? 'x' : '-');
        return sb.toString();
    }

    /**
     * unsigned number
     */
    public long getNlink() {
        return nlink;
    }

    /**
     * unsigned number
     */
    public long getUid() {
        return uid;
    }

    /**
     * unsigned number
     */
    public long getGid() {
        return gid;
    }

    /**
     * unsigned number
     */
    public long getRdev() {
        return rdev;
    }

    /**
     * signed number
     */
    public long getSize() {
        return size;
    }

    /**
     * signed number
     */
    public long getBlksize() {
        return blksize;
    }

    /**
     * signed number
     */
    public long getBlocks() {
        return blocks;
    }

    /**
     * signed number
     */
    public long getAtime() {
        return atime;
    }

    /**
     * signed number
     */
    public long getMtime() {
        return mtime;
    }

    /**
     * signed number
     */
    public long getCtime() {
        return ctime;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("       Type: ");
        if (isSymbolicLink()) {
            sb.append("link");
        } else if (isDir()) {
            sb.append("directory");
        } else if (isRegularFile()) {
            sb.append("file");
        } else if (isCharacterDevice()) {
            sb.append("character device");
        } else if (isBlockDevice()) {
            sb.append("block device");
        } else if (isFIFO()) {
            sb.append("pipe");
        } else if (isSocket()) {
            sb.append("socket");
        } else {
            sb.append("other");
        }
        sb.append("\n");
        sb.append("       Size: ");
        sb.append(size);
        sb.append("\n");
        sb.append("        UID: ");
        sb.append(getUid());
        sb.append("\n");
        sb.append("        GID: ");
        sb.append(getGid());
        sb.append("\n");
        sb.append("Permissions: ");
        sb.append(getPermissions());
        sb.append("\n");
        sb.append("     Access: ");
        sb.append(new Date(TimeUnit.SECONDS.toMillis(getAtime())));
        sb.append("\n");
        sb.append("     Modify: ");
        sb.append(new Date(TimeUnit.SECONDS.toMillis(getMtime())));
        sb.append("\n");
        sb.append("     Change: ");
        sb.append(new Date(TimeUnit.SECONDS.toMillis(getCtime())));
        sb.append("\n");
        sb.append("     Blocks: ");
        sb.append(blocks);
        sb.append("\n");
        sb.append(" Block Size: ");
        sb.append(blksize);
        sb.append("\n");
        sb.append("     Device: ");
        sb.append(getDev());
        sb.append("\n");
        sb.append("      Inode: ");
        sb.append(getIno());
        sb.append("\n");
        sb.append("      Links: ");
        sb.append(getNlink());

        return sb.toString();
    }
}