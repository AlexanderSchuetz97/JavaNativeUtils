package eu.aschuetz.nativeutils.test.posix;

import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.structs.Utsname;
import org.junit.Assert;
import org.junit.Test;

public class UnameTest {

    @Test
    public void testuname() {
        Utsname uts = NativeUtils.getPosixUtil().uname();
        Assert.assertNotNull(uts);
        System.out.println(uts);
    }
}
