import eu.aschuetz.nativeutils.test.Main;
import org.junit.Assert;

public class Test {

    @org.junit.Test
    public void run() {
        Assert.assertEquals(0, Main.runTests(null).getFailureCount());
    }
}
