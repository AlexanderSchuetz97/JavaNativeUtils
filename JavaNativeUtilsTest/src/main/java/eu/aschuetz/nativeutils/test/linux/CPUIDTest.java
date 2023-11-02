package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.CpuConst;
import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;

public class CPUIDTest {


    private final LinuxNativeUtil util = NativeUtils.getLinuxUtil();

    @Ignore
    @Test
    public void testCMP() {
        int[] ab = util.__get_cpuid_count(1, 0);
        Assert.assertEquals(true, (ab[2] & CpuConst.CPUID_FEAT_ECX_CX16) == CpuConst.CPUID_FEAT_ECX_CX16);
    }

    @Ignore
    @Test
    public void testModel() {
        String str = util.__get_cpuid_count_model();
        System.out.println(str);
        Assert.assertTrue(str != null);
    }
}
