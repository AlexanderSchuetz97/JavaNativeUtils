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


import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.StructHelper;
import eu.aschuetz.nativeutils.api.WinConst;

import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.util.Arrays;
import java.util.Objects;

/**
 * Java representation of native struct sockaddr in its many varieties (such as sockaddr_in for example)
 */
public class Sockaddr {

    private static final byte[] EMPTY = new byte[0];

    /**
     * Address family usually equal to first field in native struct for accessible from java for convenience.
     */
    private int addressFamily;

    /**
     * Holds the native struct
     */
    private byte[] address;

    /**
     * Use this constructor for creating objects to call {@link LinuxNativeUtil#recvfrom(int, byte[], int, int, int, Sockaddr)}
     * and similar methods that want to output a socket address. Be aware that such syscalls may mutate the address array if the size fits the desired size.
     * You should in general copy the address array if you need to store it before reusing a {@link Sockaddr} Object as an output
     */
    public Sockaddr() {
        this(-1, EMPTY);
    }

    /**
     * Constructs new native representation of a socket address.
     *
     * You do not need to call this constructor this manually for AF_UNIX, AF_INET and AF_INET6 as there
     * are conversion methods available to in the LinuxNativeUtils to handle this job for you this
     *
     * @param addressFamily constant address family value. This is the first field within address.
     * @param address binary value of the respective struct sockaddr. This must include the addressFamily.
     *                If you construct this value manually then the size must match the native structs size or syscalls using this address may fail because of it.
     *                The size for certain addresses may be dependent on the CPU architecture.
     *
     */
    public Sockaddr(int addressFamily, byte[] address) {
        this.addressFamily = addressFamily;
        this.address = Objects.requireNonNull(address);
    }

    public Sockaddr(Sockaddr other) {
        this(-1, EMPTY);
        other.copyTo(this);
    }

    /**
     * Returns the Address family of this socket address in a easy to understand format for java.
     * This value should be always duplicated inside the first bytes of address.
     */
    public int getAddressFamily() {
        return addressFamily;
    }

    /**
     * IF you need to store the returned array copy it as it is mutable.
     */
    public byte[] getAddress() {
        return address;
    }

    @Override
    public Sockaddr clone()  {
       return new Sockaddr(addressFamily, Arrays.copyOf(address, address.length));
    }

    /**
     * Copy this address to the other address object.
     * The address array of the other array will be mutated if the size is the same otherwise the array is cloned.
     */
    public void copyTo(Sockaddr other) {
        other.addressFamily = addressFamily;
        if (other.address.length == address.length) {
            System.arraycopy(address, 0, other.address, 0 , address.length);
            return;
        }

        other.address = Arrays.copyOf(address, address.length);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Sockaddr sockaddr = (Sockaddr) o;
        return addressFamily == sockaddr.addressFamily && Arrays.equals(address, sockaddr.address);
    }

    @Override
    public int hashCode() {
        int result = Objects.hash(addressFamily);
        result = 31 * result + Arrays.hashCode(address);
        return result;
    }

    /**
     * Parses the Sockaddr as a Win32 SOCKADDR_INET.
     * Returns null if the Sockaddr is not parsable.
     */
    public InetSocketAddress parseWin32_SOCKADDR_INET() {
        if (address == null) {
            return null;
        }

        if (addressFamily == WinConst.AF_INET && address.length >= 8) {
            int port = StructHelper.readUShort(address, 2);
            try {
                return new InetSocketAddress(InetAddress.getByAddress(new byte[]{address[4], address[5], address[6], address[7]}), port);
            } catch (UnknownHostException e) {
                //WONT HAPPEN
                return null;
            }
        }

        //TODO verify this shit
        if (addressFamily == WinConst.AF_INET6 && address.length >= 24) {
            int port = StructHelper.readUShort(address, 2);
            byte[] addr = new byte[16];
            System.arraycopy(address, 8, addr, 0, 16);
            try {
                return new InetSocketAddress(InetAddress.getByAddress(addr), port);
            } catch (UnknownHostException e) {
                //WONT Happen
                return null;
            }
        }

        return null;
    }

    @Override
    public String toString() {
        return "Sockaddr{" +
                "addressFamily=" + addressFamily +
                ", address=" + Arrays.toString(address) +
                '}';
    }
}
