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
package eu.aschuetz.nativeutils.api;

import java.lang.reflect.InvocationTargetException;

/**
 * Interface for a java method referenced by native code.
 * Note that any incompatible calls (for example calling a static void method with CallVoidMethod will lead to a IllegalArgumentException)
 * If a method throws an exception then the thrown exception is propagated as is even tho none of the "Call" Methods declare any checked exceptions.
 * This essentially hides checked exceptions from the caller.
 * The caller has to ensure that checked exceptions are caught by catching "Exception" or "Throwable".
 * The "invoke" will wrap any Throwable thrown into a InvocationTargetException just like Reflection does.
 *
 * @param <R> return type
 * @param <D> declaring type (instance type or declaring class if static)
 */
public interface NativeMethod<R, D> {

    /**
     * Name of the method
     */
    String getName();

    /**
     * Method parameter.
     * The array is not a copy for performance reasons. Do not mutate the array or the JVM may crash upon the next call.
     */
    Class[] getParameterTypes();

    /**
     * is the method static?
     */
    boolean isStatic();

    /**
     * returns the class/interface the method is declared in.
     */
    Class<D> getDeclaringClass();

    /**
     * gets the return type or "void.class" if the method is a void method.
     * This never returns null.
     */
    Class<R> getReturnType();

    /**
     * returns true if the method is a void method.
     */
    boolean isVoidMethod();

    /**
     * returns true if the method returns a primitive type (byte, char, short, int, long, float, double)
     */
    boolean isPrimitiveMethod();

    /**
     * returns true if the method refers to a constructor.
     */
    boolean isConstructor();

    /**
     * This method behaves like {@link java.lang.reflect.Method#invoke(Object, Object...)}
     */
    R invoke(D instance, Object... args) throws InvocationTargetException;

    /**
     * This method behaves like {@link java.lang.reflect.Method#invoke(Object, Object...)} but hides the
     * exception type from the caller.
     */
    R CallAnyMethod(D instance, Object... args);

    /**
     * Special method to call a constructor of an already existing object.
     * instance MUST NOT BE NULL, may be created by {@link JVMNativeUtil#AllocObject} or can be used to recall the constructor of an object.
     */
    void CallConstructor(D instance, Object... args);

    /**
     * Call a non-static method that returns a Object.
     */
    R CallObjectMethod(D instance, Object... args);

    /**
     * Call a non-static void method
     */
    void CallVoidMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a long.
     */
    long CallLongMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a int.
     */
    int CallIntMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a short.
     */
    short CallShortMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a byte.
     */
    byte CallByteMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a char.
     */
    char CallCharMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a boolean.
     */
    boolean CallBooleanMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a float.
     */
    float CallFloatMethod(D instance, Object... args);

    /**
     * Call a non-static method that returns a double.
     */
    double CallDoubleMethod(D instance, Object... args);

    /**
     * Call a static method that returns a object.
     */
    R CallStaticObjectMethod(Object... args);

    /**
     * Call a static void method.
     */
    void CallStaticVoidMethod(Object... args);

    /**
     * Call a static method that returns a long.
     */
    long CallStaticLongMethod(Object... args);

    /**
     * Call a static method that returns a int.
     */
    int CallStaticIntMethod(Object... args);

    /**
     * Call a static method that returns a short.
     */
    short CallStaticShortMethod(Object... args);

    /**
     * Call a static method that returns a byte.
     */
    byte CallStaticByteMethod(Object... args);

    /**
     * Call a static method that returns a char.
     */
    char CallStaticCharMethod(Object... args);

    /**
     * Call a static method that returns a boolean.
     */
    boolean CallStaticBooleanMethod(Object... args);

    /**
     * Call a static method that returns a float.
     */
    float CallStaticFloatMethod(Object... args);

    /**
     * Call a static method that returns a double.
     */
    double CallStaticDoubleMethod(Object... args);

}
