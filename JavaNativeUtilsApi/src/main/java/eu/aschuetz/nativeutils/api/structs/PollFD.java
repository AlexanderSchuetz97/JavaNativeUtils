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
package eu.aschuetz.nativeutils.api.structs;

import java.util.EnumSet;
import java.util.Objects;

/**
 * Struct that represents a java value of the native struct pollfd.
 * This object can be reused.
 */
public class PollFD {

    private final int fd;
    private final EnumSet<PollEvent> events;
    private final EnumSet<PollEvent> revents;

    /**
     * Construct a new pollfd.
     * @param fd the file descriptor
     * @param events the events we would like to poll the file descriptor about
     */
    public PollFD(int fd, EnumSet<PollEvent> events) {
        this.fd = fd;
        this.events = Objects.requireNonNull(events);
        this.revents = EnumSet.noneOf(PollEvent.class);
    }

    public int getFd() {
        return fd;
    }

    /**
     * Returns the events that this poller polls the file descriptor about.
     * The returned Set is mutable.
     */
    public EnumSet<PollEvent> getEvents() {
        return events;
    }

    /**
     * Returns the events that this poll was notified about.
     * The returned Set is mutable but any changes will be overwritten by the next call to poll.
     */
    public EnumSet<PollEvent> getREvents() {
        return revents;
    }

    /**
     * Check if the poller is positive for a given event.
     */
    public boolean test(PollEvent event) {
        return event != null && revents.contains(event);
    }

    /**
     * Event Enum constants for poll call
     */
    public enum PollEvent {
        /**
         * FD can be read from
         */
        POLLIN,

        /**
         * FD has urgent data to be read (TCP urgent data for example)
         */
        POLLPRI,

        /**
         * FD can be written to
         */
        POLLOUT,

        /**
         * same as POLLIN
         */
        POLLRDNORM,

        /**
         * same as POLLPRI
         */
        POLLRDBAND,

        /**
         * same as POLLOUT
         */
        POLLWRNORM,

        /**
         * FD is ready for writing urgent data (TCP urgent data for example)
         */
        POLLWRBAND,

        /**
         * unused in Linux
         */
        POLLMSG,

        /**
         * Special.
         */
        POLLREMOVE,

        /**
         * FD's Stream socket peer has closed his writing connection. Aka there will not be any more data to read
         */
        POLLRDHUP,

        /**
         * FD has errored, This is ignored in input events and only returned in output events.
         */
        POLLERR,

        /**
         * FD's Stream socket peer has closed his reading connection
         */
        POLLHUP,

        /**
         * The FD is invalid. This is ignored in input events and only returned in output events.
         */
        POLLNVAL,
    }
}
