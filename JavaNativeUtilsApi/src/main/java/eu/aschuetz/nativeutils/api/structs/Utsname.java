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
package eu.aschuetz.nativeutils.api.structs;

import java.util.Objects;

public class Utsname {

    private Utsname() {
        //Called from c
    }

    private String sysname;
    private String nodename;
    private String release;
    private String version;
    private String machine;

    public String getSysname() {
        return sysname;
    }

    public String getNodename() {
        return nodename;
    }

    public String getRelease() {
        return release;
    }

    public String getVersion() {
        return version;
    }

    public String getMachine() {
        return machine;
    }

    @Override
    public String toString() {
        return "Utsname{" +
                "sysname='" + sysname + '\'' +
                ", nodename='" + nodename + '\'' +
                ", release='" + release + '\'' +
                ", version='" + version + '\'' +
                ", machine='" + machine + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Utsname utsname = (Utsname) o;
        return Objects.equals(sysname, utsname.sysname) && Objects.equals(nodename, utsname.nodename) && Objects.equals(release, utsname.release) && Objects.equals(version, utsname.version) && Objects.equals(machine, utsname.machine);
    }

    @Override
    public int hashCode() {
        return Objects.hash(sysname, nodename, release, version, machine);
    }
}
