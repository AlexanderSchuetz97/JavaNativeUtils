//
// Copyright Alexander Schütz, 2021
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
package io.github.alexanderschuetz97.nativeutils.impl;

import io.github.alexanderschuetz97.nativeutils.api.NativeField;

class JNINativeField implements NativeField {

    private static final String[] FIELD_TYPES = new String[] {
        "Object", "int", "long", "double", "float", "short", "char", "byte", "boolean",
        "static Object", "static int", "static long", "static double", "static float", "static short", "static char", "static byte", "static boolean"
    };

    private final boolean isStatic;
    private final long reference;
    private final Class declaring;
    private final Class returnType;
    private final int method;
    private final String name;

    JNINativeField(Class declaring, Class returnType, String name, long reference, boolean isStatic) {
        this.reference = reference;
        this.isStatic = isStatic;
        this.declaring = declaring;
        this.returnType = returnType;
        this.name = name;
        int m = 0;
        if (!returnType.isPrimitive()) {
            m = 0;
        } else if (returnType == int.class) {
            m = 1;
        } else if (returnType == long.class) {
            m = 2;
        } else if (returnType == double.class) {
            m = 3;
        } else if (returnType == float.class) {
            m = 4;
        } else if (returnType == short.class) {
            m = 5;
        } else if (returnType == char.class) {
            m = 6;
        } else if (returnType == byte.class) {
            m = 7;
        } else if (returnType == boolean.class) {
            m = 8;
        } else {
            throw new IllegalStateException("Unknown primitve type");
        }

        if (isStatic) {
            m+=9;
        }

        method = m;
    }


    @Override
    public Class getDeclaringClass() {
        return declaring;
    }


    @Override
    public Class getType() {
        return returnType;
    }

    @Override
    public boolean isStatic() {
        return isStatic;
    }

    @Override
    public boolean isPrimitive() {
        return method != 0 && method != 9;
    }

    private void checkType(int type) {
        if (method != type) {
            throw new IllegalStateException("field type " + FIELD_TYPES[method] + "does not match method call for " + FIELD_TYPES[type]);
        }
    }

    private void checkType(int type, Object instance) {
        if (method != type) {
            throw new IllegalStateException("field type " + FIELD_TYPES[method] + "does not match method call for " + FIELD_TYPES[type]);
        }

        if (instance == null) {
            throw new NullPointerException();
        }

        if (!declaring.isInstance(instance)) {
            throw new ClassCastException(instance.getClass().getName() + " cannot be cast to " + declaring.getName());
        }
    }


    @Override
    public String getName() {
        return name;
    }

    @Override
    public Object get(Object instance) {
        switch (method) {
            case(0):
                return GetObjectField(instance);
            case(1):
                return GetIntField(instance);
            case(2):
                return GetLongField(instance);
            case(3):
                return GetDoubleField(instance);
            case(4):
                return GetFloatField(instance);
            case(5):
                return GetShortField(instance);
            case(6):
                return GetCharField(instance);
            case(7):
                return GetByteField(instance);
            case(8):
                return GetBooleanField(instance);
            case(9):
                return GetStaticObjectField();
            case(10):
                return GetStaticIntField();
            case(11):
                return GetStaticLongField();
            case(12):
                return GetStaticDoubleField();
            case(13):
                return GetStaticFloatField();
            case(14):
                return GetStaticShortField();
            case(15):
                return GetStaticCharField();
            case(16):
                return GetStaticByteField();
            case(17):
                return GetStaticBooleanField();
            default:
                throw new IllegalStateException("Unknown method " + method);
        }
    }

    @Override
    public void set(Object instance, Object value) {
        switch (method) {
            case(0):
                SetObjectField(instance, value);
                return;
            case(1):
                SetIntField(instance, (Integer) value);
                return;
            case(2):
                SetLongField(instance, (Long) value);
                return;
            case(3):
                SetDoubleField(instance, (Double) value);
                return;
            case(4):
                SetFloatField(instance, (Float) value);
                return;
            case(5):
                SetShortField(instance, (Short) value);
                return;
            case(6):
                SetCharField(instance, (Character) value);
                return;
            case(7):
                SetByteField(instance, (Byte) value);
                return;
            case(8):
                SetBooleanField(instance, (Boolean) value);
                return;
            case(9):
                SetStaticObjectField(value);
                return;
            case(10):
                SetStaticIntField((Integer) value);
                return;
            case(11):
                SetStaticLongField((Long) value);
                return;
            case(12):
                SetStaticDoubleField((Double) value);
                return;
            case(13):
                SetStaticFloatField((Float) value);
                return;
            case(14):
                SetStaticShortField((Short) value);
                return;
            case(15):
                SetStaticCharField((Character) value);
                return;
            case(16):
                SetStaticByteField((Byte) value);
                return;
            case(17):
                SetStaticBooleanField((Boolean) value);
                return;
            default:
                throw new IllegalStateException("Unknown method " + method);
        }
    }

    @Override
    public Object GetObjectField(Object instance) {
        checkType(0, instance);
        return _GetObjectField(reference, instance);
    }

    @Override
    public Object GetStaticObjectField() {
        checkType(9);
        return _GetStaticObjectField(reference, declaring);
    }

    @Override
    public int GetIntField(Object instance) {
        checkType(1, instance);
        return _GetIntField(reference, instance);
    }

    @Override
    public int GetStaticIntField() {
        checkType(10);
        return _GetStaticIntField(reference, declaring);
    }

    @Override
    public long GetLongField(Object instance) {
        checkType(2, instance);
        return _GetLongField(reference, instance);
    }

    @Override
    public long GetStaticLongField() {
        checkType(11);
        return _GetStaticLongField(reference, declaring);
    }

    @Override
    public double GetDoubleField(Object instance) {
        checkType(3);
        return _GetDoubleField(reference, instance);
    }

    @Override
    public double GetStaticDoubleField() {
        checkType(12);
        return _GetStaticDoubleField(reference, declaring);
    }

    @Override
    public float GetFloatField(Object instance) {
        checkType(4);
        return _GetFloatField(reference, instance);
    }

    @Override
    public float GetStaticFloatField() {
        checkType(13);
        return _GetStaticFloatField(reference, declaring);
    }

    @Override
    public short GetShortField(Object instance) {
        checkType(5);
        return _GetShortField(reference, instance);
    }

    @Override
    public short GetStaticShortField() {
        checkType(14);
        return _GetStaticShortField(reference, declaring);
    }

    @Override
    public char GetCharField(Object instance) {
        checkType(6);
        return _GetCharField(reference, instance);
    }

    @Override
    public char GetStaticCharField() {
        checkType(15);
        return _GetStaticCharField(reference, declaring);
    }

    @Override
    public byte GetByteField(Object instance) {
        checkType(7);
        return _GetByteField(reference, instance);
    }

    @Override
    public byte GetStaticByteField() {
        checkType(15);
        return _GetStaticByteField(reference, declaring);
    }

    @Override
    public boolean GetBooleanField(Object instance) {
        checkType(8);
        return _GetBooleanField(reference, instance);
    }

    @Override
    public boolean GetStaticBooleanField() {
        checkType(15);
        return _GetStaticBooleanField(reference, declaring);
    }

    @Override
    public void SetObjectField(Object instance, Object value) {
        checkType(0, instance);
        if (value != null && !returnType.isInstance(value)) {
            throw new ClassCastException("cannot cast " + value.getClass() + " to " + returnType.getName());
        }
        _SetObjectField(reference, instance, value);
    }

    @Override
    public void SetStaticObjectField(Object value) {
        checkType(9);
        if (value != null && !returnType.isInstance(value)) {
            throw new ClassCastException("cannot cast " + value.getClass() + " to " + returnType.getName());
        }
        _SetStaticObjectField(reference, declaring, value);
    }

    @Override
    public void SetIntField(Object instance, int value) {
        checkType(1, instance);
        _SetIntField(reference, instance, value);
    }

    @Override
    public void SetStaticIntField(int value) {
        checkType(10);
        _SetStaticIntField(reference, declaring, value);
    }

    @Override
    public void SetLongField(Object instance, long value) {
        checkType(2, instance);
        _SetLongField(reference, instance, value);
    }

    @Override
    public void SetStaticLongField(long value) {
        checkType(11);
        _SetStaticLongField(reference, declaring, value);
    }

    @Override
    public void SetDoubleField(Object instance, double value) {
        checkType(3, instance);
        _SetDoubleField(reference, instance, value);
    }

    @Override
    public void SetStaticDoubleField(double value) {
        checkType(11);
        _SetStaticDoubleField(reference, declaring, value);
    }

    @Override
    public void SetFloatField(Object instance, float value) {
        checkType(4, instance);
        _SetFloatField(reference, instance, value);
    }

    @Override
    public void SetStaticFloatField(float value) {
        checkType(12);
        _SetStaticFloatField(reference, declaring, value);
    }

    @Override
    public void SetShortField(Object instance, short value) {
        checkType(5, instance);
        _SetShortField(reference, instance, value);
    }

    @Override
    public void SetStaticShortField(short value) {
        checkType(13);
        _SetStaticShortField(reference, declaring, value);
    }

    @Override
    public void SetCharField(Object instance, char value) {
        checkType(6, instance);
        _SetCharField(reference, instance, value);
    }

    @Override
    public void SetStaticCharField(char value) {
        checkType(14);
        _SetStaticCharField(reference, declaring, value);
    }

    @Override
    public void SetByteField(Object instance, byte value) {
        checkType(7, instance);
        _SetByteField(reference, instance, value);
    }

    @Override
    public void SetStaticByteField(byte value) {
        checkType(15);
        _SetStaticByteField(reference, declaring, value);
    }

    @Override
    public void SetBooleanField(Object instance, boolean value) {
        checkType(8, instance);
        _SetBooleanField(reference, instance, value);
    }

    @Override
    public void SetStaticBooleanField(boolean value) {
        checkType(16);
        _SetStaticBooleanField(reference, declaring, value);
    }


    static native Object _GetObjectField(long reference, Object instance);
    static native Object _GetStaticObjectField(long reference, Class declaring);
    static native int _GetIntField(long reference, Object instance);
    static native int _GetStaticIntField(long reference, Class declaring);
    static native long _GetLongField(long reference, Object instance);
    static native long _GetStaticLongField(long reference, Class declaring);
    static native double _GetDoubleField(long reference, Object instance);
    static native double _GetStaticDoubleField(long reference, Class declaring);
    static native float _GetFloatField(long reference, Object instance);
    static native float _GetStaticFloatField(long reference, Class declaring);
    static native short _GetShortField(long reference, Object instance);
    static native short _GetStaticShortField(long reference, Class declaring);
    static native char _GetCharField(long reference, Object instance);
    static native char _GetStaticCharField(long reference, Class declaring);
    static native byte _GetByteField(long reference, Object instance);
    static native byte _GetStaticByteField(long reference, Class declaring);
    static native boolean _GetBooleanField(long reference, Object instance);
    static native boolean _GetStaticBooleanField(long reference, Class declaring);
    static native void _SetObjectField(long reference, Object instance, Object value);
    static native void _SetStaticObjectField(long reference, Class declaring, Object value);
    static native void _SetIntField(long reference, Object instance, int value);
    static native void _SetStaticIntField(long reference, Class declaring, int value);
    static native void _SetLongField(long reference, Object instance, long value);
    static native void _SetStaticLongField(long reference, Class declaring, long value);
    static native void _SetDoubleField(long reference, Object instance, double value);
    static native void _SetStaticDoubleField(long reference, Class declaring, double value);
    static native void _SetFloatField(long reference, Object instance, float value);
    static native void _SetStaticFloatField(long reference, Class declaring, float value);
    static native void _SetShortField(long reference, Object instance, short value);
    static native void _SetStaticShortField(long reference, Class declaring, short value);
    static native void _SetCharField(long reference, Object instance, char value);
    static native void _SetStaticCharField(long reference, Class declaring, char value);
    static native void _SetByteField(long reference, Object instance, byte value);
    static native void _SetStaticByteField(long reference, Class declaring, byte value);
    static native void _SetBooleanField(long reference, Object instance, boolean value);
    static native void _SetStaticBooleanField(long reference, Class declaring, boolean value);
}
