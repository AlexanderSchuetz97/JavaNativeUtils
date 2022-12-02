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

package io.github.alexanderschuetz97.nativeutils.api.structs;

import java.util.List;
import java.util.Objects;

public class Group {

    private int gr_gid;

    private String gr_name;
    private String gr_passwd;
    private List<String> gr_mem;

    public String getGr_name() {
        return gr_name;
    }

    public int getGr_gid() {
        return gr_gid;
    }

    public void setGr_gid(int gr_gid) {
        this.gr_gid = gr_gid;
    }

    public void setGr_name(String gr_name) {
        this.gr_name = gr_name;
    }

    public String getGr_passwd() {
        return gr_passwd;
    }

    public void setGr_passwd(String gr_passwd) {
        this.gr_passwd = gr_passwd;
    }

    public List<String> getGr_mem() {
        return gr_mem;
    }

    public void setGr_mem(List<String> gr_mem) {
        this.gr_mem = gr_mem;
    }

    @Override
    public String toString() {
        return "Group{" +
                "gr_gid=" + gr_gid +
                ", gr_name='" + gr_name + '\'' +
                ", gr_passwd='" + gr_passwd + '\'' +
                ", gr_mem=" + gr_mem +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Group group = (Group) o;
        return gr_gid == group.gr_gid && Objects.equals(gr_name, group.gr_name) && Objects.equals(gr_passwd, group.gr_passwd) && Objects.equals(gr_mem, group.gr_mem);
    }

    @Override
    public int hashCode() {
        return Objects.hash(gr_gid, gr_name, gr_passwd, gr_mem);
    }
}
