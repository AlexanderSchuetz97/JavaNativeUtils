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

public class RegQueryInfoKeyResult {

    private String keyClass;
    private int subKeys;
    private int maxSubKeyLen;
    private int maxClassLen;
    private int values;
    private int maxValueNameLen;
    private int maxValueLen;
    private int securityDescriptorSize;
    private long lastWriteTime;

    private RegQueryInfoKeyResult() {
        //called from c.
    }

    public String getKeyClass() {
        return keyClass;
    }

    public int getSubKeys() {
        return subKeys;
    }

    public int getMaxSubKeyLen() {
        return maxSubKeyLen;
    }

    public int getMaxClassLen() {
        return maxClassLen;
    }

    public int getValues() {
        return values;
    }

    public int getMaxValueNameLen() {
        return maxValueNameLen;
    }

    public int getMaxValueLen() {
        return maxValueLen;
    }

    public int getSecurityDescriptorSize() {
        return securityDescriptorSize;
    }

    public long getLastWriteTime() {
        return lastWriteTime;
    }

    @Override
    public String toString() {
        return "RegQueryInfoKeyResult{" +
                "keyClass='" + keyClass + '\'' +
                ", subKeys=" + subKeys +
                ", maxSubKeyLen=" + maxSubKeyLen +
                ", maxClassLen=" + maxClassLen +
                ", values=" + values +
                ", maxValueNameLen=" + maxValueNameLen +
                ", maxValueLen=" + maxValueLen +
                ", securityDescriptorSize=" + securityDescriptorSize +
                ", lastWriteTime=" + lastWriteTime +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        RegQueryInfoKeyResult that = (RegQueryInfoKeyResult) o;

        if (subKeys != that.subKeys) return false;
        if (maxSubKeyLen != that.maxSubKeyLen) return false;
        if (maxClassLen != that.maxClassLen) return false;
        if (values != that.values) return false;
        if (maxValueNameLen != that.maxValueNameLen) return false;
        if (maxValueLen != that.maxValueLen) return false;
        if (securityDescriptorSize != that.securityDescriptorSize) return false;
        if (lastWriteTime != that.lastWriteTime) return false;
        return keyClass != null ? keyClass.equals(that.keyClass) : that.keyClass == null;
    }

    @Override
    public int hashCode() {
        int result = keyClass != null ? keyClass.hashCode() : 0;
        result = 31 * result + (int) (subKeys ^ (subKeys >>> 32));
        result = 31 * result + (int) (maxSubKeyLen ^ (maxSubKeyLen >>> 32));
        result = 31 * result + (int) (maxClassLen ^ (maxClassLen >>> 32));
        result = 31 * result + (int) (values ^ (values >>> 32));
        result = 31 * result + (int) (maxValueNameLen ^ (maxValueNameLen >>> 32));
        result = 31 * result + (int) (maxValueLen ^ (maxValueLen >>> 32));
        result = 31 * result + (int) (securityDescriptorSize ^ (securityDescriptorSize >>> 32));
        result = 31 * result + (int) (lastWriteTime ^ (lastWriteTime >>> 32));
        return result;
    }
}
