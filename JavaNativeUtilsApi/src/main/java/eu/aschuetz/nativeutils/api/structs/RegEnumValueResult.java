package eu.aschuetz.nativeutils.api.structs;

public class RegEnumValueResult {
    private String name;

    private RegData data;

    public RegEnumValueResult() {

    }

    public RegEnumValueResult(String name, RegData data) {
        this.name = name;
        this.data = data;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public RegData getData() {
        return data;
    }

    public void setData(RegData data) {
        this.data = data;
    }

    @Override
    public String toString() {
        return "RegEnumValueResult{" +
                "name='" + name + '\'' +
                ", data=" + data +
                '}';
    }
}
