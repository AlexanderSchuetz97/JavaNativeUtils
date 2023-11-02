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

import java.util.Objects;

public class Msghdr {

    private final Iovec[] msg_iov;
    private final byte[] msg_control;

    private final Sockaddr msg_name;

    /**
     * indicates end-of-record; the data returned completed a record
     */
    private boolean complete;
    /**
     * the buffers in msg_iov were too small to hold all the data of the mssage and parts of it have been truncated
     */
    private boolean truncated;
    /**
     * is set to indicate the the msg_control buffer was too small to hold all the control data
     */
    private boolean controlDataTruncated;
    /**
     * is set to indicate that expedited or out-of-band data were received.
     */
    private boolean outOfBand;
    /**
     * indicates that no data was received but an extended error from the socket error queue.
     */
    private boolean errQueue;



    /**
     * Output parameter
     */
    private int msg_controllen;

    public Msghdr(byte[] buf, int off, int len) {
        this(new Iovec(buf, off, len));
    }

    public Msghdr(Iovec msg_iov) {
        this(new Iovec[]{msg_iov});
    }

    public Msghdr(Iovec[] msg_iov) {
        this(msg_iov, null, null);
    }

    public Msghdr(Iovec[] msg_iov, Sockaddr sockaddr) {
        this(msg_iov, sockaddr, null);
    }

    public Msghdr(Iovec[] msg_iov, byte[] msg_control) {
        this(msg_iov, null, msg_control);
    }

    public Msghdr(Iovec msg_iov,Sockaddr sockaddr, byte[] msg_control) {
        this(new Iovec[]{msg_iov}, sockaddr, msg_control);
    }

    public Msghdr(Iovec[] msg_iov, Sockaddr sockaddr, byte[] msg_control) {
        this.msg_iov = Objects.requireNonNull(msg_iov);
        this.msg_control = msg_control;
        this.msg_controllen = msg_control == null ? 0 : msg_control.length;
        this.msg_name = sockaddr;
    }

    public boolean isComplete() {
        return complete;
    }

    public boolean isTruncated() {
        return truncated;
    }

    public boolean isControlDataTruncated() {
        return controlDataTruncated;
    }

    public boolean isOutOfBand() {
        return outOfBand;
    }

    public boolean isErrQueue() {
        return errQueue;
    }

    public Iovec[] getMsg_iov() {
        return msg_iov;
    }

    public byte[] getMsg_control() {
        return msg_control;
    }

    public Sockaddr getMsg_name() {
        return msg_name;
    }

    public int getMsg_controllen() {
        return msg_controllen;
    }
}
