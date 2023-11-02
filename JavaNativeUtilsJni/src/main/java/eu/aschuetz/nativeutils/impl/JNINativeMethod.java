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
package eu.aschuetz.nativeutils.impl;

import eu.aschuetz.nativeutils.api.NativeMethod;

import java.lang.reflect.InvocationTargetException;
import java.util.Objects;

public class JNINativeMethod implements NativeMethod {

    private final String name;
    private final int[] types;
    private final int type;
    private final Class[] parameterTypes;
    private final Class returnType;
    private final Class declaring;
    private final boolean isStatic;
    private final long methodID;

    private static String[] TYPE_NAME = new String[] {
            "boolean", "byte", "char", "short", "int", "long", "float", "double", "Object", "void",
            "static boolean", "static byte", "static char", "static short", "static int", "static long", "static float", "static double", "static Object", "static void", "Object constructor"
    };

    private static Class[] BOXED = new Class[] {
            Boolean.class, Byte.class, Character.class, Short.class, Integer.class, Long.class, Float.class, Double.class, Object.class, Void.class
    };

    private static int toType(Class<?> clazz) {
        if (clazz == void.class) {
            return 9;
        }

        if (!clazz.isPrimitive()) {
            return 8;
        }

        if (clazz == boolean.class) {
            return 0;
        }

        if (clazz == byte.class) {
            return 1;
        }

        if (clazz == char.class) {
            return 2;
        }

        if (clazz == short.class) {
            return 3;
        }

        if (clazz == int.class) {
            return 4;
        }

        if (clazz == long.class) {
            return 5;
        }

        if (clazz == float.class) {
            return 6;
        }

        if (clazz == double.class) {
            return 7;
        }

        throw new IllegalStateException("Unknown primitve type");
    }

    JNINativeMethod(String name, Class<?> declaring, long methodID, Class[] parameterTypes, boolean isStatic, Class<?> returnType) {
        this.name = Objects.requireNonNull(name);
        this.declaring = Objects.requireNonNull(declaring);
        this.methodID = methodID;
        this.parameterTypes = Objects.requireNonNull(parameterTypes);
        this.isStatic = isStatic;
        this.returnType = Objects.requireNonNull(returnType);

        int mType = toType(returnType);
        this.types = new int[parameterTypes.length];
        for (int i = 0; i < types.length; i++) {
            this.types[i] = toType(Objects.requireNonNull(parameterTypes[i]));
        }

        if (isStatic) {
            mType+=10;
        }

        if (name.equals("<init>")) {
            //CONSTRUCTOR
            mType = 20;
        }

        type = mType;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public Class[] getParameterTypes() {
        return parameterTypes;
    }

    @Override
    public boolean isStatic() {
        return isStatic;
    }

    @Override
    public Class getDeclaringClass() {
        return declaring;
    }

    @Override
    public Class<?> getReturnType() {
        return returnType;
    }

    @Override
    public boolean isVoidMethod() {
        return type == 9;
    }

    @Override
    public boolean isPrimitiveMethod() {
        return type != 8 && type != 18;
    }

    @Override
    public boolean isConstructor() {
        return type==20;
    }

    private void checkType(int t, Object[] args, Object instance) {
        if (instance == null) {
            throw new NullPointerException();
        }

        declaring.cast(instance);

        if (t != type) {
            throw new IllegalStateException("return type " + TYPE_NAME[type] + " does not match method call for " + TYPE_NAME[t]);
        }

        checkArgs(args);
    }

    private void checkType(int t, Object[] args) {
        if (t != type) {
            throw new IllegalStateException("return type " + TYPE_NAME[type] + " does not match method call for " + TYPE_NAME[t]);
        }
        checkArgs(args);
    }

    private void checkArgs(Object[] args) {
        if (args.length != parameterTypes.length) {
            throw new IllegalArgumentException("argument count mismatch");
        }

        for (int i = 0; i < args.length; i++) {
            Object arg = args[i];
            if (arg == null) {
                if (types[i] == 8) {
                    continue;
                }

                //8->Object everything else is primitive
                throw new ClassCastException("argument #" + (i+1) + " is null and cannot be cast to " + TYPE_NAME[types[i]]);
            }

            Class pType = parameterTypes[i];

            if (pType.isPrimitive()) {
                Class<?> boxed = BOXED[types[i]];
                if (boxed.isInstance(arg)) {
                    continue;
                }

                throw new ClassCastException("argument #" + (i+1) + " " + arg.getClass().getName() + " cannot be cast to " + boxed.getName() + " for unboxing to " + pType.getName());
            }

            if (pType.isInstance(arg)) {
                continue;
            }

            throw new ClassCastException("argument #" + (i+1) + " " + arg.getClass().getName() + " cannot be cast to " + pType.getName());
        }
    }

    @Override
    public Object invoke(Object instance, Object... args) throws InvocationTargetException {
        if (!isStatic()) {
            if (!isConstructor()) {
                if (instance == null) {
                    throw new NullPointerException();
                }

                declaring.cast(instance);
            } else {
                if (instance != null && instance != declaring) {
                    declaring.cast(instance);
                }
            }
        }

        checkArgs(args);

        try {
            switch (type) {
                case(0):
                    return _CallBooleanMethod(instance, methodID, types, args);
                case(1):
                    return _CallByteMethod(instance, methodID, types, args);
                case(2):
                    return _CallCharMethod(instance, methodID, types, args);
                case(3):
                    return _CallShortMethod(instance, methodID, types, args);
                case(4):
                    return _CallIntMethod(instance, methodID, types, args);
                case(5):
                    return _CallLongMethod(instance, methodID, types, args);
                case(6):
                    return _CallFloatMethod(instance, methodID, types, args);
                case(7):
                    return _CallDoubleMethod(instance, methodID, types, args);
                case(8):
                    return _CallObjectMethod(instance, methodID, types, args);
                case(9):
                    _CallVoidMethod(instance, methodID, types, args);
                    return null;
                case(10):
                    return _CallStaticBooleanMethod(declaring, methodID, types, args);
                case(11):
                    return _CallStaticByteMethod(declaring, methodID, types, args);
                case(12):
                    return _CallStaticCharMethod(declaring, methodID, types, args);
                case(13):
                    return _CallStaticShortMethod(declaring, methodID, types, args);
                case(14):
                    return _CallStaticIntMethod(declaring, methodID, types, args);
                case(15):
                    return _CallStaticLongMethod(declaring, methodID, types, args);
                case(16):
                    return _CallStaticFloatMethod(declaring, methodID, types, args);
                case(17):
                    return _CallStaticDoubleMethod(declaring, methodID, types, args);
                case(18):
                    return _CallStaticObjectMethod(declaring, methodID, types, args);
                case(19):
                    _CallStaticVoidMethod(declaring, methodID, types, args);
                    return null;
                case(20):
                    if (instance != null && instance != declaring) {
                        _CallVoidMethod(instance, methodID, types, args);
                        return null;
                    }
                    return _NewObject(declaring, methodID, types, args);
                default:
                    break;
            }
        } catch (Throwable t) {
            throw new InvocationTargetException(t);
        }

        throw new IllegalStateException("invalid type");
    }

    @Override
    public Object CallAnyMethod(Object instance, Object... args) {
        switch (type) {
            case(0):
                return CallBooleanMethod(instance, args);
            case(1):
                return CallByteMethod(instance, args);
            case(2):
                return CallCharMethod(instance, args);
            case(3):
                return CallShortMethod(instance, args);
            case(4):
                return CallIntMethod(instance, args);
            case(5):
                return CallLongMethod(instance, args);
            case(6):
                return CallFloatMethod(instance, args);
            case(7):
                return CallDoubleMethod(instance, args);
            case(8):
                return CallObjectMethod(instance, args);
            case(9):
                CallVoidMethod(instance, args);
                return null;
            case(10):
                return CallStaticBooleanMethod(args);
            case(11):
                return CallStaticByteMethod(args);
            case(12):
                return CallStaticCharMethod(args);
            case(13):
                return CallStaticShortMethod(args);
            case(14):
                return CallStaticIntMethod(args);
            case(15):
                return CallStaticLongMethod(args);
            case(16):
                return CallStaticFloatMethod(args);
            case(17):
                return CallStaticDoubleMethod(args);
            case(18):
                return CallStaticObjectMethod(args);
            case(19):
                CallStaticVoidMethod(args);
                return null;
            case(20):
                if (instance != null && instance != declaring) {
                    CallConstructor(instance, args);
                    return null;
                }
                return NewObject(args);
            default:
                break;
        }

        throw new IllegalStateException("invalid type");
    }

    @Override
    public void CallConstructor(Object instance, Object... args) {
        checkType(20, args, instance);
        _CallVoidMethod(instance, methodID, types, args);
    }

    public Object NewObject(Object... args) {
        checkType(20, args);
        return _NewObject(declaring, methodID, types, args);
    }

    @Override
    public Object CallObjectMethod(Object instance, Object... args) {
        checkType(8, args, instance);
        return _CallObjectMethod(instance, methodID, types, args);
    }


    @Override
    public void CallVoidMethod(Object instance, Object... args) {
        checkType(9, args, instance);
        _CallVoidMethod(instance, methodID, types, args);
    }

    @Override
    public long CallLongMethod(Object instance, Object... args) {
        checkType(5, args, instance);
        return _CallLongMethod(instance, methodID, types, args);
    }

    @Override
    public int CallIntMethod(Object instance, Object... args) {
        checkType(4, args, instance);
        return _CallIntMethod(instance, methodID, types, args);
    }

    @Override
    public short CallShortMethod(Object instance, Object... args) {
        checkType(3, args, instance);
        return _CallShortMethod(instance, methodID, types, args);
    }

    @Override
    public byte CallByteMethod(Object instance, Object... args) {
        checkType(1, args, instance);
        return _CallByteMethod(instance, methodID, types, args);
    }

    public char CallCharMethod(Object instance, Object... args) {
        checkType(2, args, instance);
        return _CallCharMethod(instance, methodID, types, args);
    }

    @Override
    public boolean CallBooleanMethod(Object instance, Object... args) {
        checkType(0, args, instance);
        return _CallBooleanMethod(instance, methodID, types, args);
    }

    @Override
    public float CallFloatMethod(Object instance, Object... args) {
        checkType(6, args, instance);
        return _CallFloatMethod(instance, methodID, types, args);
    }

    @Override
    public double CallDoubleMethod(Object instance, Object... args) {
        checkType(7, args, instance);
        return _CallDoubleMethod(instance, methodID, types, args);
    }

    @Override
    public Object CallStaticObjectMethod(Object... args) {
        checkType(18, args);
        return _CallStaticObjectMethod(declaring, methodID, types, args);
    }

    @Override
    public void CallStaticVoidMethod(Object... args) {
        checkType(19, args);
        _CallStaticVoidMethod(declaring, methodID, types, args);
    }

    @Override
    public long CallStaticLongMethod(Object... args) {
        checkType(15, args);
        return _CallStaticLongMethod(declaring, methodID, types, args);
    }

    @Override
    public int CallStaticIntMethod(Object... args) {
        checkType(14, args);
        return _CallStaticIntMethod(declaring, methodID, types, args);
    }

    @Override
    public short CallStaticShortMethod(Object... args) {
        checkType(13, args);
        return _CallStaticShortMethod(declaring, methodID, types, args);
    }

    @Override
    public byte CallStaticByteMethod(Object... args) {
        checkType(11, args);
        return _CallStaticByteMethod(declaring, methodID, types, args);
    }

    @Override
    public char CallStaticCharMethod(Object... args) {
        checkType(12, args);
        return _CallStaticCharMethod(declaring, methodID, types, args);
    }

    @Override
    public boolean CallStaticBooleanMethod(Object... args) {
        checkType(10, args);
        return _CallStaticBooleanMethod(declaring, methodID, types, args);
    }

    @Override
    public float CallStaticFloatMethod(Object... args) {
        checkType(16, args);
        return _CallStaticFloatMethod(declaring, methodID, types, args);
    }

    @Override
    public double CallStaticDoubleMethod(Object... args) {
        checkType(17, args);
        return _CallStaticDoubleMethod(declaring, methodID, types, args);
    }


    static native Object _NewObject(Class clazz, long methodID, int[] types, Object[] args);

    static native Object _CallObjectMethod(Object instance,long methodID, int[] types, Object[] args);

    static native void _CallVoidMethod(Object instance,long methodID, int[] types, Object[] args);

    static native long _CallLongMethod(Object instance,long methodID, int[] types, Object[] args);

    static native int _CallIntMethod(Object instance,long methodID, int[] types, Object[] args);

    static native short _CallShortMethod(Object instance,long methodID, int[] types, Object[] args);

    static native char _CallCharMethod(Object instance,long methodID, int[] types, Object[] args);

    static native byte _CallByteMethod(Object instance,long methodID, int[] types, Object[] args);

    static native boolean _CallBooleanMethod(Object instance,long methodID, int[] types, Object[] args);

    static native float _CallFloatMethod(Object instance,long methodID, int[] types, Object[] args);

    static native double _CallDoubleMethod(Object instance,long methodID, int[] types, Object[] args);

    static native Object _CallStaticObjectMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native void _CallStaticVoidMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native long _CallStaticLongMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native int _CallStaticIntMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native short _CallStaticShortMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native byte _CallStaticByteMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native char _CallStaticCharMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native boolean _CallStaticBooleanMethod(Class clazz,long methodID, int[] types, Object[] args);

    static native float _CallStaticFloatMethod(Class clazz, long methodID, int[] types, Object[] args);

    static native double _CallStaticDoubleMethod(Class clazz, long methodID, int[] types, Object[] args);

}
