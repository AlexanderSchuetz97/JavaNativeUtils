//
// Copyright Alexander Schütz, 2021-2024
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
package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;

import java.io.IOException;
import java.io.OutputStream;

class LinuxOutputStream extends OutputStream {

    private final LinuxNativeUtil util;
    private final int fd;
    private final boolean close;
    private volatile boolean closed;

    private final byte[] oneByte = new byte[1];
    LinuxOutputStream(LinuxNativeUtil util, int fd, boolean close) {
        this.util = util;
        this.fd = fd;
        this.close = close;
    }

    @Override
    public synchronized void write(byte[] b, int off, int len) throws IOException {
        if (closed) {
            throw new IOException("closed");
        }
        if (len == 0) {
            return;
        }
        try {
            int data = util.write(fd, b, off, len);
            if (data == 0) {
                throw new IOException("non blocking fd");
            }
        } catch (UnknownNativeErrorException e) {
            throw new IOException(util.strerror_r(e.intCode()));
        }
    }

    @Override
    public synchronized void flush() throws IOException {
        if (closed) {
            throw new IOException("closed");
        }
        util.fsync(fd);
    }

    @Override
    public synchronized void close() throws IOException {
        if (close) {
            if (closed) {
                return;
            }
             closed = true;
            util.close(fd);
        }
        closed = true;
    }

    @Override
    public synchronized void write(int b) throws IOException {
        if (closed) {
            throw new IOException("closed");
        }
        oneByte[0] = (byte) b;
        try {
            int data = util.write(fd, oneByte, 0, 1);
            if (data == 0) {
                throw new IOException("non blocking fd");
            }
        } catch (UnknownNativeErrorException e) {
            throw new IOException(util.strerror_r(e.intCode()));
        }
    }
}
