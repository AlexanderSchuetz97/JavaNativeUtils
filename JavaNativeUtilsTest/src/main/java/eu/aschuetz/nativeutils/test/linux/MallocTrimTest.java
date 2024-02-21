package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.NativeUtils;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.util.List;
import java.util.concurrent.ConcurrentLinkedQueue;

public class MallocTrimTest {

    @Test
    public void test() {
        LinuxNativeUtil linuxUtil = NativeUtils.getLinuxUtil();
        try {
            Assert.assertTrue(linuxUtil.malloc_trim(0));
        } catch (UnsupportedOperationException uoe) {
            //LIBC MUSL
            Assert.assertEquals("malloc_trim not supported by current libc", uoe.getMessage());
            return;
        }
    }

    //@Test
    public void testManually() {
        ConcurrentLinkedQueue q = new ConcurrentLinkedQueue();
        while(true) {
            try {
                q.add(new byte[4096]);
            } catch (OutOfMemoryError oom) {
                break;
            }
        }
        q = null;
        System.gc();



        LinuxNativeUtil linuxUtil = NativeUtils.getLinuxUtil();
        System.out.println(getMem());
        for (int i = 0; i < 512; i++) {
            System.out.println(i +":");
            NativeMemory malloc = linuxUtil.malloc(512_000_000);
            malloc.zero();
            //System.out.println(getMem());
            malloc.close();
            System.out.println(getMem());
        }
        try {
            Assert.assertTrue(linuxUtil.malloc_trim(0));
        } catch (UnsupportedOperationException uoe) {
            //LIBC MUSL
            Assert.assertEquals("malloc_trim not supported by current libc", uoe.getMessage());
            return;
        }

        for (int i = 0; i < 64; i++) {
            linuxUtil.malloc_trim(0);
        }

        System.out.println(getMem());
    }

    public static String getMem() {
        File f = new File("/proc/self/status");
        if (!f.exists()) {
            return "RUN THIS TEST ON LINUX";
        }

        List<String> lines;
        try {
            System.gc();
            lines = Files.readAllLines(f.toPath(), StandardCharsets.UTF_8);
        } catch (IOException e) {
            return "";
        }

        for (String s : lines) {
            if (s.startsWith("RssAnon:")) {
                s = s.replace(" ", "");
                s = s.replace("\t", "");
                s = s.replace("RssAnon:", "");
                s = s.replace("kB", "");
                return s;
            }
        }

        return "";
    }

}
