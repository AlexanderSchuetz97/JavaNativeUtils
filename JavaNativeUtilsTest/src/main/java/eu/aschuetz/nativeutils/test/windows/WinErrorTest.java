package eu.aschuetz.nativeutils.test.windows;

import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.WindowsNativeUtil;
import org.junit.Assert;
import org.junit.Test;

public class WinErrorTest {

    @Test
    public void test() {
        WindowsNativeUtil windowsUtil = NativeUtils.getWindowsUtil();
        for (int i = 0; i < 128; i++) {
            String s = windowsUtil.FormatMessageA(2);
            Assert.assertNotNull(s);
            Assert.assertFalse(s, s.contains("FormatMessageA"));
        }
    }
}
