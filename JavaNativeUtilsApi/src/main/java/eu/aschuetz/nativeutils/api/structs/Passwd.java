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

import java.util.Objects;

public class Passwd {

    String pw_name;
    String pw_passwd;
    int pw_uid;
    int pw_gid;
    String pw_gecos;
    String pw_dir;
    String pw_shell;

    public String getPw_name() {
        return pw_name;
    }

    public void setPw_name(String pw_name) {
        this.pw_name = pw_name;
    }

    public String getPw_passwd() {
        return pw_passwd;
    }

    public void setPw_passwd(String pw_passwd) {
        this.pw_passwd = pw_passwd;
    }

    public int getPw_uid() {
        return pw_uid;
    }

    public void setPw_uid(int pw_uid) {
        this.pw_uid = pw_uid;
    }

    public int getPw_gid() {
        return pw_gid;
    }

    public void setPw_gid(int pw_gid) {
        this.pw_gid = pw_gid;
    }

    public String getPw_gecos() {
        return pw_gecos;
    }

    public void setPw_gecos(String pw_gecos) {
        this.pw_gecos = pw_gecos;
    }

    public String getPw_dir() {
        return pw_dir;
    }

    public void setPw_dir(String pw_dir) {
        this.pw_dir = pw_dir;
    }

    public String getPw_shell() {
        return pw_shell;
    }

    public void setPw_shell(String pw_shell) {
        this.pw_shell = pw_shell;
    }

    @Override
    public String toString() {
        return "Passwd{" +
                "pw_name='" + pw_name + '\'' +
                ", pw_passwd='" + pw_passwd + '\'' +
                ", pw_uid=" + pw_uid +
                ", pw_gid=" + pw_gid +
                ", pw_gecos='" + pw_gecos + '\'' +
                ", pw_dir='" + pw_dir + '\'' +
                ", pw_shell='" + pw_shell + '\'' +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Passwd passwd = (Passwd) o;
        return pw_uid == passwd.pw_uid && pw_gid == passwd.pw_gid && Objects.equals(pw_name, passwd.pw_name) && Objects.equals(pw_passwd, passwd.pw_passwd) && Objects.equals(pw_gecos, passwd.pw_gecos) && Objects.equals(pw_dir, passwd.pw_dir) && Objects.equals(pw_shell, passwd.pw_shell);
    }

    @Override
    public int hashCode() {
        return Objects.hash(pw_name, pw_passwd, pw_uid, pw_gid, pw_gecos, pw_dir, pw_shell);
    }
}
