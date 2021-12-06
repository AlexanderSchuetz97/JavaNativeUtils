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
package io.github.alexanderschuetz97.nativeutils.api;

import java.lang.reflect.Field;

public interface NativeReflection extends NativeUtil {

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
