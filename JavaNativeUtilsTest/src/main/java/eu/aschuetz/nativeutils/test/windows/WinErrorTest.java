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
            String s = windowsUtil.FormatMessageA(2, 1033);
            Assert.assertNotNull(s);
            Assert.assertFalse(s, s.contains("FormatMessageA"));
        }
    }

    @Test
    public void testEnglish() {
        WindowsNativeUtil windowsUtil = NativeUtils.getWindowsUtil();
        String s = windowsUtil.FormatMessageA(2, 1033);
        Assert.assertEquals("The system cannot find the file specified.\r\n", s);
    }

    @Test
    public void testShitty() {
        WindowsNativeUtil windowsUtil = NativeUtils.getWindowsUtil();
        String s = windowsUtil.FormatMessageA(2, 5168546);
        //System.out.println(s);
        Assert.assertEquals("Failed to call FormatMessageA with dwMessageId='2' dwLanguageId='5168546' because of GetLastError='15105'", s);
    }

    @Test
    public void testShitty2() {
        WindowsNativeUtil windowsUtil = NativeUtils.getWindowsUtil();
        String s = windowsUtil.FormatMessageA(5168546, 1033);
        System.out.println(s);
        Assert.assertEquals("Failed to call FormatMessageA with dwMessageId='5168546' dwLanguageId='1033' because of GetLastError='317'", s);
    }

    @Test
    public void testValidLanguageButNotFound() {
        //1080=Faroe island language of some island of denmark, that I do not have installed for sure.
        //This shit used to be a bug that caused a crash with access violation....
        WindowsNativeUtil windowsUtil = NativeUtils.getWindowsUtil();
        String s = windowsUtil.FormatMessageA(2, 1080);
        System.out.println(s);
        Assert.assertEquals("Failed to call FormatMessageA with dwMessageId='2' dwLanguageId='1080' because of GetLastError='15100'", s);
    }
}
