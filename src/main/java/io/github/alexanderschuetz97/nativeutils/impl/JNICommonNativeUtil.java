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
import io.github.alexanderschuetz97.nativeutils.api.NativeReflection;
import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.util.Objects;

public class JNICommonNativeUtil implements NativeReflection {

    @Override
    public boolean isWindows() {
        return false;
    }

    @Override
    public boolean isLinux() {
        return false;
    }

    @Override
    public NativeField FromReflectedField(Field field) {
        if (field == null) {
            throw new NullPointerException("field is null");
        }

        long ref = _FromReflectedField(field);

        return new JNINativeField(field.getDeclaringClass(), field.getType(), field.getName(), ref, Modifier.isStatic(field.getModifiers()));
    }

    native long _FromReflectedField(Field field);

    native Field _ToReflectedField(Class declaring, long field, boolean isStatic);

    native long _GetFieldID(Class clazz, String fieldName, String signature);

    native long _GetStaticFieldID(Class clazz, String fieldName, String signature);

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


}
