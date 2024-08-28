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
import java.io.InputStream;

class LinuxInputStream extends InputStream {

    private final LinuxNativeUtil util;
    private final int fd;
    private final boolean close;
    private volatile boolean closed;

    private final byte[] oneByte = new byte[1];
    LinuxInputStream(LinuxNativeUtil util, int fd, boolean close) {
        this.util = util;
        this.fd = fd;
        this.close = close;
    }

    @Override
    public synchronized int read() throws IOException {
        try {
            if (closed) {
                throw new IOException("closed");
            }
            int x = util.read(fd, oneByte, 0, 1);
            if (x != 0) {
                return oneByte[0] & 0xFF;
            }

            return -1;
        } catch (UnknownNativeErrorException e) {
            throw new IOException(util.strerror_r(e.intCode()));
        }
    }

    @Override
    public synchronized int read(byte[] b, int off, int len) throws IOException {
        try {
            if (closed) {
                throw new IOException("closed");
            }
            int x = util.read(fd, b, off, len);
            if (x != 0) {
                return x;
            }

            return -1;
        } catch (UnknownNativeErrorException e) {
            throw new IOException(util.strerror_r(e.intCode()));
        }
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
}
