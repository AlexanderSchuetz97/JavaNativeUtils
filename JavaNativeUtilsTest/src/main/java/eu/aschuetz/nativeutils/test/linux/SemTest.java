package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.LinuxConst;
import eu.aschuetz.nativeutils.api.LinuxNativeUtil;
import eu.aschuetz.nativeutils.api.NativeMemory;
import eu.aschuetz.nativeutils.api.NativeUtils;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.*;

import java.io.FileNotFoundException;
import java.util.concurrent.*;

public class SemTest {

    private static final String UUID = "/" + java.util.UUID.randomUUID().toString().replaceAll("-", "");
    private static ExecutorService ex;


    @BeforeClass
    public static void beforeCl() {
        ex = Executors.newCachedThreadPool();
    }
    @AfterClass
    public static void afterCl() {
        ex.shutdownNow();
    }

    @After
    public void after() {
        try {
            NativeUtils.getLinuxUtil().sem_unlink(UUID);
        } catch (Exception e) {
            //DONT CARE
        }
    }

    @Test
    public void test2() throws Exception {
        final LinuxNativeUtil linuxUtil = NativeUtils.getLinuxUtil();
        try {
            linuxUtil.sem_open(UUID, 0, 0777, 0);
            Assert.fail();
        } catch (FileNotFoundException e) {
            Assert.assertEquals(UUID, e.getMessage());
        }
    }

    @Test
    public void test3() throws Exception {
        final LinuxNativeUtil linuxUtil = NativeUtils.getLinuxUtil();
        try(NativeMemory nmem = linuxUtil.malloc(linuxUtil.sem_t_size())) {
            final long sem = nmem.getNativePointer(0);
            linuxUtil.sem_init(sem, false, 0);
            Assert.assertEquals(0, linuxUtil.sem_getvalue(sem));

            Future<?> f = ex.submit(new Runnable() {
                @Override
                public void run() {
                    try {
                        linuxUtil.sem_wait(sem);
                    } catch (UnknownNativeErrorException e) {
                        throw new RuntimeException(e);
                    }
                }
            });

            try {
                f.get(500, TimeUnit.MILLISECONDS);
                Assert.fail();
            } catch (TimeoutException e) {

            }

            linuxUtil.sem_post(sem);

            f.get(500, TimeUnit.MILLISECONDS);

            Assert.assertEquals(0, linuxUtil.sem_getvalue(sem));
            linuxUtil.sem_destroy(sem);
        }
    }

    @Test
    public void testTw() throws Exception {
        final LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();

        final long sem = lnu.sem_open(UUID, LinuxConst.O_CREAT | LinuxConst.O_EXCL, 0777, 0);
        Future<Boolean> f = ex.submit(new Callable<Boolean>() {
        @Override
            public Boolean call() {
                try {
                    boolean b = lnu.sem_timedwait(sem, 1000);
                    System.out.println(b);
                    return b;
                } catch (UnknownNativeErrorException e) {
                    throw new RuntimeException(e);
                }
            }
        });

        Thread.sleep(200);
        Assert.assertFalse(f.isDone());
        Assert.assertFalse(f.get(2000, TimeUnit.MILLISECONDS));

        f = ex.submit(new Callable<Boolean>() {
            @Override
            public Boolean call() {
                try {
                    return lnu.sem_timedwait(sem, 1000);
                } catch (UnknownNativeErrorException e) {
                    throw new RuntimeException(e);
                }
            }
        });

        Thread.sleep(200);
        Assert.assertFalse(f.isDone());
        lnu.sem_post(sem);
        Assert.assertTrue(f.get(2000, TimeUnit.MILLISECONDS));
    }

    @Test
    public void test() throws Exception {
        final LinuxNativeUtil linuxUtil = NativeUtils.getLinuxUtil();
        final long sem = linuxUtil.sem_open(UUID, LinuxConst.O_CREAT | LinuxConst.O_EXCL, 0777, 0);
        Assert.assertEquals(0, linuxUtil.sem_getvalue(sem));
        Future<?> f = ex.submit(new Runnable() {
            @Override
            public void run() {
                try {
                    linuxUtil.sem_wait(sem);
                } catch (UnknownNativeErrorException e) {
                    throw new RuntimeException(e);
                }
            }
        });

        try {
            f.get(500, TimeUnit.MILLISECONDS);
            Assert.fail();
        } catch (TimeoutException e) {

        }

        linuxUtil.sem_post(sem);

        f.get(500, TimeUnit.MILLISECONDS);

        Assert.assertEquals(0, linuxUtil.sem_getvalue(sem));
        linuxUtil.sem_close(sem);
        linuxUtil.sem_unlink(UUID);
    }
}
