package io.github.alexanderschuetz97.nativeutils.api.structs;

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
}
