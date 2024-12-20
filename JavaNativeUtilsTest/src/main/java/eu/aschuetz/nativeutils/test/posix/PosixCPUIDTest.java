package eu.aschuetz.nativeutils.test.posix;

import eu.aschuetz.nativeutils.api.CpuConst;
import eu.aschuetz.nativeutils.api.FreeBSDNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.PosixNativeUtil;
import org.junit.Assert;
import org.junit.Test;

public class PosixCPUIDTest {


    private final PosixNativeUtil util = NativeUtils.getPosixUtil();

    //@Ignore
    @Test //You probably need to try reasonably hard to run this teston a CPU without CPUID_FEAT_ECX_CX16.
    public void testCMP() {
        int[] ab = util.__get_cpuid_count(1, 0);
        Assert.assertEquals(true, (ab[2] & CpuConst.CPUID_FEAT_ECX_CX16) == CpuConst.CPUID_FEAT_ECX_CX16);
    }

    //@Ignore
    @Test
    public void testModel() {
        String str = util.__get_cpuid_count_model();
        System.out.println(str);
        Assert.assertTrue(str != null);
    }
}
