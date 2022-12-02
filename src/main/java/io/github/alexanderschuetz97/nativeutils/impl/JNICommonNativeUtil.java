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
package io.github.alexanderschuetz97.nativeutils.impl;

import io.github.alexanderschuetz97.nativeutils.api.NativeField;
import io.github.alexanderschuetz97.nativeutils.api.NativeMemory;
import io.github.alexanderschuetz97.nativeutils.api.JVMNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeMethod;
import io.github.alexanderschuetz97.nativeutils.api.PointerHandler;

import java.io.SyncFailedException;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.lang.reflect.Modifier;
import java.nio.ByteBuffer;
import java.nio.charset.StandardCharsets;
import java.util.Objects;

public abstract class JNICommonNativeUtil implements JVMNativeUtil {

    public int getPointerSize() {
        return _getPointerSize();
    }

    native static int _getPointerSize();

    @Override
    public boolean isJVM() {
        return true;
    }

    @Override
    public boolean isNoop() {
        return false;
    }

    public native void MonitorEnter(Object obj);

    public native void MonitorExit(Object obj);

    @Override
    public native Class<?> DefineClass(String name, ClassLoader loader, byte[] bytes, int off, int len);

    @Override
    public NativeField FromReflectedField(Field field) {
        if (field == null) {
            throw new NullPointerException("field is null");
        }

        long ref = _FromReflectedField(field);

        return new JNINativeField(field.getDeclaringClass(), field.getType(), field.getName(), ref, Modifier.isStatic(field.getModifiers()));
    }

    public native int[] __get_cpuid_count(int code, int subcode);

    public String __get_cpuid_count_model() {
        int[] model = __get_cpuid_count(0, 0);
        return model == null ? null : new String(new byte[] {
                (byte)  (model[1] >> 0),
                (byte) (model[1] >> 8),
                (byte) (model[1] >> 16),
                (byte) (model[1] >>> 24),
                (byte) (model[3] >> 0),
                (byte) (model[3] >> 8),
                (byte) (model[3] >> 16),
                (byte) (model[3] >> 24),
                (byte) (model[2] >> 0),
                (byte) (model[2] >> 8),
                (byte) (model[2] >> 16),
                (byte) (model[2] >> 24),
        }, StandardCharsets.UTF_8);
    }

    @Override
    public NativeMemory GetDirectBufferAddress(ByteBuffer buffer, int off, int size) {
        if (!buffer.isDirect()) {
            throw new IllegalArgumentException("Not a direct buffer");
        }

        if (buffer.capacity() <= off+size) {
            throw new IllegalArgumentException("Offsets out of bounds");
        }

        long addr = GetDirectBufferAddress(buffer);
        if (addr == 0) {
            throw new IllegalArgumentException("Not a direct buffer");
        }

        if (off != 0) {
            addr = pointerAdd(addr, off);
        }

        return new JNINativeMemory(addr, size, true, !buffer.isReadOnly(), new BufferPointerHandler(buffer));
    }

    protected static class BufferPointerHandler implements PointerHandler {

        protected ByteBuffer buffer;

        public BufferPointerHandler(ByteBuffer buffer) {
            this.buffer = buffer;
        }

        @Override
        public void handleClose(long ptr, long size, boolean read, boolean write) {
            buffer = null;
        }

        @Override
        public void handleSync(long ptr, long size, boolean read, boolean write, long offset, long length, boolean invalidate) throws SyncFailedException {
            //NOOP
        }
    }

    native long _FromReflectedField(Field field);

    native Field _ToReflectedField(Class declaring, long field, boolean isStatic);

    native long _GetFieldID(Class clazz, String fieldName, String signature);

    native long _GetStaticFieldID(Class clazz, String fieldName, String signature);

    native long _FromReflectedMethod(Object method);

    native Object _ToReflectedMethod(Class declaring, long field, boolean isStatic);

    native long _GetMethodID(Class clazz, String fieldName, String signature);

    native long _GetStaticMethodID(Class clazz, String fieldName, String signature);

    @Override
    public native RuntimeException Throw(Throwable throwable);

    static native Object _AllocObject(Class clazz);

    @Override
    public native long NewGlobalRef(Object obj);

    @Override
    public native void DeleteGlobalRef(long ref);

    @Override
    public native <T> T NewLocalRef(long ref);

    @Override
    public <T> T AllocObject(Class<T> clazz) {
        if (clazz.isPrimitive()) {
            throw new IllegalArgumentException("cannot allocate object from primitive class");
        }

        return (T) _AllocObject(clazz);
    }

    @Override
    public <R> NativeMethod<R, R> FromReflectedMethod(Constructor<R> method) {
        long id = _FromReflectedMethod(Objects.requireNonNull(method));
        if (id == 0) {
            return null;
        }

        return new JNINativeMethod("<init>", method.getDeclaringClass(), id, method.getParameterTypes(), Modifier.isStatic(method.getModifiers()), method.getDeclaringClass());
    }

    @Override
    public NativeMethod FromReflectedMethod(Method method) {
        long id = _FromReflectedMethod(Objects.requireNonNull(method));
        if (id == 0) {
            return null;
        }
        return new JNINativeMethod(method.getName(), method.getDeclaringClass(), id, method.getParameterTypes(), Modifier.isStatic(method.getModifiers()), method.getReturnType());
    }

    @Override
    public <R, D> NativeMethod<R, D> GetMethodID(Class<D> declaring, String methodName, String signature) {
        Objects.requireNonNull(declaring, "declaring class is null");
        if (declaring.isPrimitive()) {
            return null;
        }
        long id = _GetMethodID(declaring, Objects.requireNonNull(methodName, "methodName is null"), Objects.requireNonNull(signature, "signature is null"));
        if (id == 0) {
            return null;
        }

        Object method = _ToReflectedMethod(declaring, id, false);
        if (method instanceof Constructor) {
            Constructor<?> constructor = (Constructor<?>) method;
            return new JNINativeMethod("<init>", constructor.getDeclaringClass(), id, constructor.getParameterTypes(), Modifier.isStatic(constructor.getModifiers()), constructor.getDeclaringClass());
        }

        Method jMethod = (Method) method;
        return new JNINativeMethod(jMethod.getName(), jMethod.getDeclaringClass(), id, jMethod.getParameterTypes(), Modifier.isStatic(jMethod.getModifiers()), jMethod.getReturnType());
    }

    @Override
    public <R, D> NativeMethod<R, D> GetStaticMethodID(Class<D> declaring, String methodName, String signature) {
        Objects.requireNonNull(declaring, "declaring class is null");
        Objects.requireNonNull(methodName, "methodName is null");
        if (declaring.isPrimitive()) {
            return null;
        }
        //Static class initializer
        if ("<cinit>".equals(methodName)) {
            return null;
        }

        long id = _GetStaticMethodID(declaring, methodName, Objects.requireNonNull(signature, "signature is null"));
        if (id == 0) {
            return null;
        }
        Method method = (Method) _ToReflectedMethod(declaring, id, true);
        return new JNINativeMethod(method.getName(), method.getDeclaringClass(), id, method.getParameterTypes(), Modifier.isStatic(method.getModifiers()), method.getReturnType());
    }

    @Override
    public NativeField GetFieldID(Class clazz, String fieldName, String signature) {
        long ref = _GetFieldID(Objects.requireNonNull(clazz, "declaring class is null"), Objects.requireNonNull(fieldName, "fieldName is null"), Objects.requireNonNull(signature, "signature is null"));
        if (ref == 0) {
            return null;
        }

        Field field = _ToReflectedField(clazz, ref, false);
        return new JNINativeField(field.getDeclaringClass(), field.getType(), field.getName(), ref, false);
    }

    @Override
    public NativeField GetStaticFieldID(Class clazz, String fieldName, String signature) {
        long ref = _GetStaticFieldID(Objects.requireNonNull(clazz, "declaring class is null"), Objects.requireNonNull(fieldName, "fieldName is null"), Objects.requireNonNull(signature, "signature is null"));
        if (ref == 0) {
            return null;
        }

        Field field = _ToReflectedField(clazz, ref, false);
        return new JNINativeField(field.getDeclaringClass(), field.getType(), field.getName(), ref, true);
    }

    protected static native long _malloc(long size);

    private static final PointerHandler FREE_HANDLER = new PointerHandler() {
        @Override
        public void handleClose(long ptr, long size, boolean read, boolean write) {
            _free(ptr);
        }

        @Override
        public void handleSync(long ptr, long size, boolean read, boolean write, long offset, long length, boolean invalidate) {
            //NOOP.
        }
    };

    protected static native void _free(long ptr);



    /**
     * Any calls to the resulting NativeMemory may cause the JVM to die due to a SEGFAULT is size is not specified correctly.
     * the close() and sync() methods are noops.
     *
     * @param ptr pointer to the data
     * @param size -1 if unknown.
     */
    public NativeMemory pointer(long ptr, long size, PointerHandler handler) throws NullPointerException {
        if (size < 0) {
            size = Long.MAX_VALUE;
        }
        return new JNINativeMemory(ptr, size, true, true, handler);
    }

    public NativeMemory malloc(long size) throws OutOfMemoryError, IllegalArgumentException {
        if (size <= 0) {
            throw new IllegalArgumentException("size <= 0");
        }

        long nPtr = _malloc(size);
        return new JNINativeMemory(nPtr, size, true, true, FREE_HANDLER);
    }


    public void free(long ptr) {
        //A for effort
        if (ptr == 0) {
            throw new NullPointerException();
        }

        _free(ptr);
    }

    /**
     * returns the native address of a direct byte buffer.
     */
    public native long GetDirectBufferAddress(ByteBuffer buffer);

    static native long pointerAdd(long ptr, long increment);
    /**
     * returns a direct byte buffer using the given pointer and capacity.
     */
    public native ByteBuffer NewDirectByteBuffer(long ptr, long capacity);



}
