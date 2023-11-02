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
package eu.aschuetz.nativeutils.api;

/**
 * This interface is a wrapper for all field access methods from the jni interface.
 * It is not a good idea to expose the jfieldID directly to any java application because calling the wrong jni method directly will crash the entire jvm without any real way of finding out why.
 * The impl of this interface is always a reference to a specific field and does any necesarry checks before calling the J́NI methods to prevent a JVM crash.
 * Expect to get:
 * IllegalStateException when calling the wrong method (for the wrong field type).
 * ClassCastException when calling with wrong objects.
 * NullPointerException when trying to get a non static field with null instance.
 * @param <T> Type where the field is declared in
 * @param <F> Type of the field.
 */
public interface NativeField<T, F> {

    /**
     * Returns the class the field is in.
     */
    Class<T> getDeclaringClass();

    /**
     * Returns the type of the class the field is in.
     */
    Class<F> getType();

    /**
     * is the field static?
     */
    boolean isStatic();

    /**
     * is the field primitive?
     */
    boolean isPrimitive();

    /**
     * field name
     */
    String getName();

    /**
     * This method  automatically calls the correct get method but does autoboxing.
     * For static fields instance parameter is completely ignored.
     * This method does autoboxing of primitives
     */
    F get(T instance);
    /**
     * This method automatically calls the correct set method but does autoboxing.
     * For static fields instance parameter is completely ignored.
     * This method does autoboxing
     * @throws NullPointerException if the field a primitive and value is null
     */
    void set(T instance, F value);

    //These methods pretty much do what you expect them to do...

    /**
     * Does NOT do autoboxing. Will fail with IllegalStateException if for example called with to get "int".
     */
    F GetObjectField(T instance);

    /**
     * Does NOT do autoboxing. Will fail with IllegalStateException if for example called with to get "int".
     */
    F GetStaticObjectField();
    int GetIntField(T instance);
    int GetStaticIntField();
    long GetLongField(T instance);
    long GetStaticLongField();
    double GetDoubleField(T instance);
    double GetStaticDoubleField();
    float GetFloatField(T instance);
    float GetStaticFloatField();
    short GetShortField(T instance);
    short GetStaticShortField();
    char GetCharField(T instance);
    char GetStaticCharField();
    byte GetByteField(T instance);
    byte GetStaticByteField();
    boolean GetBooleanField(T instance);
    boolean GetStaticBooleanField();

    /**
     * Does NOT do autoboxing. Will fail with IllegalStateException if for example called with Integer to set "int".
     */
    void SetObjectField(T instance, F value);

    /**
     * Does NOT do autoboxing. Will fail with IllegalStateException if for example called with Integer to set "int".
     */
    void SetStaticObjectField(T value);
    void SetIntField(T instance, int value);
    void SetStaticIntField(int value);
    void SetLongField(T instance, long value);
    void SetStaticLongField(long value);
    void SetDoubleField(T instance, double value);
    void SetStaticDoubleField(double value);
    void SetFloatField(T instance, float value);
    void SetStaticFloatField(float value);
    void SetShortField(T instance, short value);
    void SetStaticShortField(short value);
    void SetCharField(T instance, char value);
    void SetStaticCharField(char value);
    void SetByteField(T instance, byte value);
    void SetStaticByteField(byte value);
    void SetBooleanField(T instance, boolean value);
    void SetStaticBooleanField(boolean value);

}
