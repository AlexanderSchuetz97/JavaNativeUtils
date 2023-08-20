package io.github.alexanderschuetz97.nativeutils.impl;

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import io.github.alexanderschuetz97.nativeutils.api.structs.PollFD;

import java.io.IOException;
import java.io.InputStream;
import java.util.EnumSet;

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
