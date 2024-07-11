package eu.aschuetz.nativeutils.test.freebsd;

import eu.aschuetz.nativeutils.api.CpuConst;
import eu.aschuetz.nativeutils.api.FreeBSDNativeUtil;
import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Ignore;
import org.junit.Test;

public class FBSDCPUIDTest {


    private final FreeBSDNativeUtil util = NativeUtils.getFreeBSDUtil();

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
