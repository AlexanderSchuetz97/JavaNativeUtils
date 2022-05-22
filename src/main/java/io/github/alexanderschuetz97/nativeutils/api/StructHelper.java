package io.github.alexanderschuetz97.nativeutils.api;

import java.nio.ByteOrder;

/**
 * Helper/Util class to help parse/create structs from byte arrays.
 * All values are automatically read/parsed in native byte order.
 */
public class StructHelper {

    private static final boolean BIG_ENDIAN = ByteOrder.nativeOrder() == ByteOrder.BIG_ENDIAN;

    public static int readInt(byte[] buf, int off) {
        return BIG_ENDIAN ?
                ((buf[off++] & 0xff) << 24) + ((buf[off++] & 0xff) << 16) + ((buf[off++] & 0xff) << 8) + ((buf[off] & 0xff) << 0)
                :
                ((buf[off++] & 0xff) << 0) + ((buf[off++] & 0xff) << 8) + ((buf[off++] & 0xff) << 16) + ((buf[off] & 0xff) << 24);
    }

    public static short readShort(byte[] buf, int off) {
        return (short) readUShort(buf, off);
    }

    public static long readLong(byte[] buf, int off) {
        return BIG_ENDIAN ?
                (((long)(buf[off++] & 0xff)) << 56) + (((long)(buf[off++] & 0xff)) << 48) + (((long)(buf[off++] & 0xff)) << 40) + (((long)(buf[off++] & 0xff)) << 32) + (((long)(buf[off++] & 0xff)) << 24) + (((long)(buf[off++] & 0xff)) << 16) + (((long)(buf[off++] & 0xff)) << 8) + (((long)(buf[off] & 0xff)) << 0)
                :
                (((long)(buf[off++] & 0xff)) << 0) + (((long)(buf[off++] & 0xff)) << 8) + (((long)(buf[off++] & 0xff)) << 16) + (((long)(buf[off++] & 0xff)) << 24) + (((long)(buf[off++] & 0xff)) << 32) + (((long)(buf[off++] & 0xff)) << 40) + (((long)(buf[off++] & 0xff)) << 48) + (((long)(buf[off] & 0xff)) << 56);
    }

    public static float readFloat(byte[] buf, int off) {
        return Float.intBitsToFloat(readInt(buf, off));
    }

    public static double readDouble(byte[] buf, int off) {
        return Double.longBitsToDouble(readLong(buf, off));
    }

    public static int readUShort(byte[] buf, int off) {
        return BIG_ENDIAN ?
                ((buf[off] & 0xff) << 8) + ((buf[off+1] & 0xff) << 0)
                :
                ((buf[off] & 0xff) << 0) + ((buf[off+1] & 0xff) << 8);
    }

    public static long readUInt(byte[] buf, int off) {
        return readInt(buf, off) & 0xffffffffL;
    }

    public static int readUByte(byte[] buf, int off) {
        return buf[off] & 0xff;
    }

    public static byte readByte(byte[] buf, int off) {
        return buf[off];
    }

    public static void writeByte(byte[] buf, int off, byte value) {
        buf[off] = value;
    }

    public static void writeByte(byte[] buf, int off, int value) {
        buf[off] = (byte) value;
    }

    public static void writeShort(byte[] buf, int off, short value) {
        writeShort(buf, off, (int) value);
    }

    public static void writeShort(byte[] buf, int off, int value) {
        if (BIG_ENDIAN) {
            buf[off++] = (byte) (value >>> 8);
            buf[off] = (byte) (value >>> 0);
            return;
        }

        buf[off++] = (byte) (value >>> 0);
        buf[off] = (byte) (value >>> 8);
    }

    public static void writeInt(byte[] buf, int off, int value) {
        if (BIG_ENDIAN) {
            buf[off++] = (byte) (value >>> 24);
            buf[off++] = (byte) (value >>> 16);
            buf[off++] = (byte) (value >>> 8);
            buf[off] = (byte) (value >>> 0);
            return;
        }

        buf[off++] = (byte) (value >>> 0);
        buf[off++] = (byte) (value >>> 8);
        buf[off++] = (byte) (value >>> 16);
        buf[off] = (byte) (value >>> 24);
    }

    public static void writeInt(byte[] buf, int off, long value) {
        writeInt(buf, off, (int) value);
    }

    public static void writeLong(byte[] buf, int off, long value) {
        if (BIG_ENDIAN) {
            buf[off++] = (byte) (value >>> 56);
            buf[off++] = (byte) (value >>> 48);
            buf[off++] = (byte) (value >>> 40);
            buf[off++] = (byte) (value >>> 32);
            buf[off++] = (byte) (value >>> 24);
            buf[off++] = (byte) (value >>> 16);
            buf[off++] = (byte) (value >>> 8);
            buf[off] = (byte) (value >>> 0);
            return;
        }

        buf[off++] = (byte) (value >>> 0);
        buf[off++] = (byte) (value >>> 8);
        buf[off++] = (byte) (value >>> 16);
        buf[off++] = (byte) (value >>> 24);
        buf[off++] = (byte) (value >>> 32);
        buf[off++] = (byte) (value >>> 40);
        buf[off++] = (byte) (value >>> 48);
        buf[off] = (byte) (value >>> 56);
    }

    public static int htonl(int num) {
        if (BIG_ENDIAN) {
            return num;
        }

        return ((num >>> 24)) | ((num >>   8) &   0xFF00) | ((num << 8) & 0xFF0000) | ((num << 24));
    }

    public static int htons(int num) {
        if (BIG_ENDIAN) {
            return num & 0xffff;
        }

        return ((num >> 8) & 0xFF) | ((num << 8) & 0xFF00);
    }

    public static int ntohl(int num) {
        if (BIG_ENDIAN) {
            return num;
        }

        return ((num >>> 24)) | ((num >>   8) &   0xFF00) | ((num << 8) & 0xFF0000) | ((num << 24));
    }

    public static int ntohs(int num) {
        if (BIG_ENDIAN) {
            return num & 0xffff;
        }

        return ((num >> 8) & 0xFF) | ((num << 8) & 0xFF00);
    }

    public static int ntohs(byte[] buf, int off) {
        return ntohs(readUShort(buf, off));
    }

    public static void htons(byte[] buf, int off, int value) {
        writeShort(buf, off, htons(value));
    }

    public static int ntohl(byte[] buf, int off) {
        return ntohs(readInt(buf, off));
    }

    public static void htonl(byte[] buf, int off, int value) {
        writeInt(buf, off, htonl(value));
    }



}
