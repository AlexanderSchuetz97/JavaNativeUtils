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
package io.github.alexanderschuetz97.nativeutils.api;

import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.nio.ByteBuffer;

public interface JVMNativeUtil extends NativeUtil {


    /**
     * Defines a class in the given classloader.
     * @param name MUST BE IN JNI NOTATION. for example "org.example.MyClass" would be "org/example/MyClass"
     * @return the defined class
     *
     * @throws ClassFormatError if the bytes in buf are not a valid class
     * @throws ClassCircularityError if the class would be its own superclass
     * @throws SecurityException if name starts with "java."
     */
    Class<?> DefineClass(String name, ClassLoader loader, byte[] bytes, int off, int len) throws ClassFormatError, ClassCircularityError, SecurityException;

    /**
     * Enter a monitor. This is equivalent to the beginning of a synchronized block/method.
     */
    void MonitorEnter(Object obj);

    /**
     * Exit from a monitor entered by MonitorEnter. This MUST NOT be used to leave a monitor acquired by a synchronized block/method.
     */
    void MonitorExit(Object obj);

    /**
     * returns the native address of a direct byte buffer.
     */
    long GetDirectBufferAddress(ByteBuffer buffer);

    /**
     * returns a direct byte buffer using the given pointer and capacity.
     */
    ByteBuffer NewDirectByteBuffer(long ptr, long capacity);

    /**
     * Returns a NativeMemory object that uses the direct byte buffer object as backing.
     * This method ensures that the buffer object is not garbage collected until the close() method of the NativeMemory
     * object is called. The resulting NativeMemory Object does not modify the buffer position.
     * The resulting NativeMemory Object is bound by off and size.
     * Off is relative to the start of the buffer not the current position of the buffer.
     */
    NativeMemory GetDirectBufferAddress(ByteBuffer buffer, int off, int size);

    /**
     * creates a instance of a object without calling a constructor.
     */
    <T> T AllocObject(Class<T> clazz);

    /**
     * returns a global reference that can be stored to a java object.
     * The given java object will not be garbage collected/finalized unless DeleteGlobalRef is called with the returned value
     * @throws NullPointerException if obj is null
     * @return opaque native reference long. This value must NEVER be modified or the DeleteGlobalRef/NewLocalRef method will crash the jvm if a modified value is used.
     */
    long NewGlobalRef(Object obj);

    /**
     * Deletes a global ref. After deletion the ref must no longer be used. if the Object referred to by the given ref
     * is no longer referenced elsewhere it will be garbage collected.
     *
     * If a "ref" long value is used after calling DeleteGlobalRef the jvm may crash.
     */
    void DeleteGlobalRef(long ref);

    /**
     * Resolves a Global ref into a "object".
     * Note: you can safely use the object even after DeleteGlobalRef has already been called on the ref passed to this method.
     */
    <T> T NewLocalRef(long ref);

    /**
     * This method allows throwing of checked exceptions in methods that do not declare them as checked exceptions.
     * @throws NullPointerException if the given throwable is null
     * @throws Throwable the given throwable
     * @return never returns without throwing an exception. Return type RuntimeException only exists to trick compiler to allow for "throw util.Throw(...)" pattern
     */
    RuntimeException Throw(Throwable throwable);


    /*
     * How to type Signature:
     * boolean -> Z
     * byte -> B
     * char -> C
     * short -> S
     * int -> I
     * long -> J
     * float -> F
     * double -> D
     * Class -> Lmy/package/ClassName;
     * Array -> [TYPE [ex: int[] -> [I ex2: String[] -> [Ljava/lang/String;)
     * 2D Array -> [[TYPE (ex int[][] -> [[I
     * ND Array -> N times [ followed by TYPE
     */

    /**
     * reflection method to native method.
     */
    NativeMethod FromReflectedMethod(Method method);

    /**
     * reflection constructor to native method.
     */
    <R> NativeMethod<R, R> FromReflectedMethod(Constructor<R> method);


    /**
     * Get non static native method by signature
     */
    <R, D> NativeMethod<R, D> GetMethodID(Class<D> declaring, String name, String signature);

    /**
     * Get static native method by signature
     */
    <R, D> NativeMethod<R, D> GetStaticMethodID(Class<D> declaring, String name, String signature);

    /**
     * Gets a native reference to a java field from a given Reflection field.
     */
    NativeField FromReflectedField(Field field);

    /**
     * Gets a native reference to a java field.
     *
     * @param clazz the class the field is in
     * @param fieldName the field name
     * @param signature the signature of the field type<br>

     * @return null if the field was not found.
     */
    <T, X> NativeField<T, X> GetFieldID(Class<T> clazz, String fieldName, String signature);

    /**
     * Gets a native reference to a java field.
     *
     * @param clazz the class the field is in
     * @param fieldName the field name
     * @param signature the signature of the field type
     * @return null if the field was not found.
     */
    <T, X> NativeField<T, X> GetStaticFieldID(Class<T> clazz, String fieldName, String signature);
}
