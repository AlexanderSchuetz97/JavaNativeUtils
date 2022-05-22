package io.github.alexanderschuetz97.nativeutils.api.structs;

public class IfNameIndex {

    private int index;
    private String name;

    public IfNameIndex(int index, String name) {
        this.index = index;
        this.name = name;
    }

    public int getIndex() {
        return index;
    }

    public String getName() {
        return name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        IfNameIndex that = (IfNameIndex) o;

        if (index != that.index) return false;
        return name != null ? name.equals(that.name) : that.name == null;
    }

    @Override
    public int hashCode() {
        int result = index;
        result = 31 * result + (name != null ? name.hashCode() : 0);
        return result;
    }
}
