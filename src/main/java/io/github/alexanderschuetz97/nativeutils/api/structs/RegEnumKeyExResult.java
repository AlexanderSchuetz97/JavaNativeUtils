package io.github.alexanderschuetz97.nativeutils.api.structs;

public class RegEnumKeyExResult {

    private String name;
    private String className;
    private long lastWriteTime;

    private RegEnumKeyExResult() {
        //called from c
    }

    public String getName() {
        return name;
    }

    public String getClassName() {
        return className;
    }

    public long getLastWriteTime() {
        return lastWriteTime;
    }

    @Override
    public String toString() {
        return "SubKey " + name + " : " + className + " @ " + lastWriteTime;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        RegEnumKeyExResult that = (RegEnumKeyExResult) o;

        if (lastWriteTime != that.lastWriteTime) return false;
        if (name != null ? !name.equals(that.name) : that.name != null) return false;
        return className != null ? className.equals(that.className) : that.className == null;
    }

    @Override
    public int hashCode() {
        int result = name != null ? name.hashCode() : 0;
        result = 31 * result + (className != null ? className.hashCode() : 0);
        result = 31 * result + (int) (lastWriteTime ^ (lastWriteTime >>> 32));
        return result;
    }
}
