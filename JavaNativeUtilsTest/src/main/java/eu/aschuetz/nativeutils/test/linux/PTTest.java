package eu.aschuetz.nativeutils.test.linux;

import eu.aschuetz.nativeutils.api.*;
import eu.aschuetz.nativeutils.api.exceptions.InconsistentMutexException;
import eu.aschuetz.nativeutils.api.exceptions.QuotaExceededException;
import eu.aschuetz.nativeutils.api.exceptions.UnknownNativeErrorException;
import eu.aschuetz.nativeutils.api.exceptions.UnrecoverableMutexException;
import org.junit.*;

import java.io.*;
import java.nio.file.Files;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.UUID;
import java.util.concurrent.*;

public class PTTest {

    private static ExecutorService ex;

    @BeforeClass
    public static void b4() {
        ex = Executors.newCachedThreadPool();
    }

    @AfterClass
    public static void after() {
        ex.shutdownNow();
    }

    @Test
    public void test() throws UnknownNativeErrorException, QuotaExceededException, InconsistentMutexException, UnrecoverableMutexException {
        LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        NativeMemory mem = lnu.malloc(4096);
        long mutex_attr = mem.getNativePointer(0);
        long mutex = mem.getNativePointer(lnu.sizeof_pthread_condattr_t());

        lnu.pthread_mutexattr_init(mutex_attr);
        lnu.pthread_mutex_init(mutex, mutex_attr);
        lnu.pthread_mutex_lock(mutex);
        lnu.pthread_mutex_unlock(mutex);
        lnu.pthread_mutex_destroy(mutex);
        lnu.pthread_mutexattr_destroy(mutex_attr);
    }

    @Test
    public void test2() throws UnknownNativeErrorException, QuotaExceededException, ExecutionException, InterruptedException, TimeoutException, InconsistentMutexException, UnrecoverableMutexException {
        final LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        NativeMemory mem = lnu.malloc(4096);
        final long mutex_attr = mem.getNativePointer(0);
        final long mutex = mem.getNativePointer(lnu.sizeof_pthread_condattr_t());
        final long cond_attr = mem.getNativePointer(lnu.sizeof_pthread_condattr_t() + lnu.sizeof_pthread_mutex_t());
        final long cond = mem.getNativePointer(lnu.sizeof_pthread_condattr_t() + lnu.sizeof_pthread_mutex_t() + lnu.sizeof_pthread_condattr_t());


        lnu.pthread_mutexattr_init(mutex_attr);
        lnu.pthread_mutex_init(mutex, mutex_attr);
        lnu.pthread_condattr_init(cond_attr);
        lnu.pthread_cond_init(cond, cond_attr);

        lnu.pthread_mutex_lock(mutex);
        Future<?> t = ex.submit(new Callable<Object>() {
            @Override
            public Object call() throws Exception{
                lnu.pthread_mutex_lock(mutex);
                lnu.pthread_cond_wait(cond, mutex);
                lnu.pthread_mutex_unlock(mutex);
                return null;
            }
        });
        try {
            t.get(1000, TimeUnit.MILLISECONDS);
            Assert.fail("Exception expected");
        } catch (TimeoutException e) {

        }


        lnu.pthread_mutex_unlock(mutex);
        Thread.sleep(1000);
        lnu.pthread_mutex_lock(mutex);
        try {
            t.get(1000, TimeUnit.MILLISECONDS);
            Assert.fail("Exception expected");
        } catch (TimeoutException e) {

        }
        lnu.pthread_cond_broadcast(cond);
        lnu.pthread_mutex_unlock(mutex);
        t.get(1000, TimeUnit.MILLISECONDS);
        lnu.pthread_cond_destroy(cond);
        lnu.pthread_condattr_destroy(cond_attr);
        lnu.pthread_mutex_destroy(mutex);
        lnu.pthread_mutexattr_destroy(mutex_attr);
        mem.close();
    }

    @Test
    public void test3() throws UnknownNativeErrorException, QuotaExceededException, ExecutionException, InterruptedException, TimeoutException, InconsistentMutexException, UnrecoverableMutexException {

        final LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        NativeMemory mem = lnu.malloc(4096);
        final long mutex_attr = mem.getNativePointer(0);
        final long mutex = mem.getNativePointer(lnu.sizeof_pthread_condattr_t());
        final long cond_attr = mem.getNativePointer(lnu.sizeof_pthread_condattr_t() + lnu.sizeof_pthread_mutex_t());
        final long cond = mem.getNativePointer(lnu.sizeof_pthread_condattr_t() + lnu.sizeof_pthread_mutex_t() + lnu.sizeof_pthread_condattr_t());


        lnu.pthread_mutexattr_init(mutex_attr);
        lnu.pthread_mutexattr_setrobust(mutex_attr, LinuxConst.PTHREAD_MUTEX_ROBUST);
        lnu.pthread_mutex_init(mutex, mutex_attr);


        lnu.pthread_condattr_init(cond_attr);
        lnu.pthread_cond_init(cond, cond_attr);

        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    lnu.pthread_mutex_lock(mutex);
                    System.out.println("LOCKED");
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
        thread.join(5000);
        Thread.sleep(5000);
        try {
            if (!lnu.pthread_mutex_timedlock(mutex, 5000)) {
                //BUG in qemu+debian?
                Assume.assumeFalse("aarch64".equalsIgnoreCase(System.getenv("QARCH")));
                Assume.assumeFalse("armel".equalsIgnoreCase(System.getenv("QARCH")));
                Assume.assumeFalse("armhf".equalsIgnoreCase(System.getenv("QARCH")));
                Assume.assumeFalse("mips64el".equalsIgnoreCase(System.getenv("QARCH")));
                Assume.assumeFalse("ppc64le".equalsIgnoreCase(System.getenv("QARCH")));
                Assume.assumeFalse("s390x".equalsIgnoreCase(System.getenv("QARCH")));

                Assert.fail("InconsistentMutexException expected, not locked " + thread.getState());
            }
            Assert.fail("InconsistentMutexException expected, locked");
        } catch (InconsistentMutexException e) {

        }


        lnu.pthread_mutex_consistent(mutex);
        lnu.pthread_mutex_unlock(mutex);
        lnu.pthread_mutex_lock(mutex);
        lnu.pthread_mutex_unlock(mutex);

        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    lnu.pthread_mutex_lock(mutex);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
        thread.join(5000);
        Thread.sleep(5000);
        try {
            lnu.pthread_mutex_timedlock(mutex, 5000);
            Assert.fail("InconsistentMutexException expected");
        } catch (InconsistentMutexException e) {

        }

        lnu.pthread_mutex_unlock(mutex);
        try {
            lnu.pthread_mutex_lock(mutex);
            Assert.fail("UnrecoverableMutexException expected");
        } catch (UnrecoverableMutexException e) {

        }

        lnu.pthread_mutex_destroy(mutex);
        lnu.pthread_mutexattr_destroy(mutex_attr);


        mem.close();
    }

    @Test
    public void shmem() throws Throwable {
        final LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        UUID uuid = UUID.randomUUID();
        int i = lnu.shm_open(uuid.toString(), LinuxConst.O_RDWR | LinuxConst.O_CREAT, 0777);
        lnu.ftruncate(i, 4096);
        long mmap = lnu.mmap(i, 4096, LinuxConst.MAP_SHARED, true, true, 0);
        final PointerHandler ptr = new PointerHandler() {
            @Override
            public void handleClose(long ptr, long size) {
                try {
                    lnu.munmap(ptr, size);
                } catch (UnknownNativeErrorException e) {
                    //DONT CARE
                }
            }

            @Override
            public void handleSync(long ptr, long size,long offset, long length, boolean invalidate) throws SyncFailedException {

            }
        };

        NativeMemory mem = lnu.pointer(mmap, 4096, ptr);
        final long mutex_attr = mem.getNativePointer(0);
        final long mutex = mem.getNativePointer(lnu.sizeof_pthread_condattr_t());

        try {
            lnu.pthread_mutexattr_init(mutex_attr);
            lnu.pthread_mutexattr_setrobust(mutex_attr, LinuxConst.PTHREAD_MUTEX_ROBUST);
            lnu.pthread_mutexattr_settype(mutex_attr, LinuxConst.PTHREAD_MUTEX_ERRORCHECK);
            lnu.pthread_mutexattr_setpshared(mutex_attr, LinuxConst.PTHREAD_PROCESS_SHARED);
            try {
                lnu.pthread_mutex_init(mutex, mutex_attr);
            } catch (UnsupportedOperationException e) {
                Assert.assertEquals("The operating system does not support creating a mutex with the desired characteristics", e.getMessage());
                //RISCV64 as emulated by QEMU doesn't support this
                if (!"riscv64".equalsIgnoreCase(System.getenv("QARCH"))) {
                    throw e;
                }
                lnu.pthread_mutexattr_setrobust(mutex_attr, LinuxConst.PTHREAD_MUTEX_STALLED);
                lnu.pthread_mutex_init(mutex, mutex_attr);
            }



            int x = lnu.shm_open(uuid.toString(), LinuxConst.O_RDWR, 0777);
            mmap = lnu.mmap(x, 4096, LinuxConst.MAP_SHARED, true, true, 0);
            lnu.shm_unlink(uuid.toString());

            NativeMemory mem2 = lnu.pointer(mmap, 4096, ptr);
            final long mutex_attr2 = mem2.getNativePointer(0);
            final long mutex2 = mem2.getNativePointer(lnu.sizeof_pthread_condattr_t());

            lnu.pthread_mutex_lock(mutex2);
            Object o = ex.submit(new Callable<Object>() {
                @Override
                public Object call() throws Exception {
                    return lnu.pthread_mutex_trylock(mutex);
                }
            }).get(5000, TimeUnit.MILLISECONDS);

            Assert.assertEquals(Boolean.FALSE, o);
            Assert.assertNotEquals(mem.getNativePointer(), mem2.getNativePointer());
            lnu.pthread_mutex_unlock(mutex2);
            o = ex.submit(new Callable<Object>() {
                @Override
                public Object call() throws Exception {
                    boolean b =  lnu.pthread_mutex_trylock(mutex);
                    if (b) {
                        lnu.pthread_mutex_unlock(mutex);
                    }

                    return b;
                }
            }).get(5000, TimeUnit.MILLISECONDS);

            Assert.assertEquals(Boolean.TRUE, o);
            mem.close();
            mem2.close();
            lnu.close(i);
            lnu.close(x);

        } catch (UnknownNativeErrorException e) {
            throw new RuntimeException(lnu.strerror_r(e.intCode()), e);
        }
    }

    private static void runCFile(String cfileName, String... args) throws Exception {
        File tdir = Files.createTempDirectory("").toFile();
        File cfile = new File(tdir, cfileName);
        cfile.createNewFile();
        try(InputStream input = PTTest.class.getResourceAsStream("/" + cfileName)) {
            try(FileOutputStream faos = new FileOutputStream(cfile, false)) {
                byte[] buf = new byte[4096];
                int x = 0;
                while(x != -1) {
                    x = input.read(buf);
                    if (x > 0) {
                        faos.write(buf, 0, x);
                    }
                }
            }
        }

        int r = new ProcessBuilder("gcc", cfileName, "-lpthread", "-lrt").inheritIO().directory(tdir).start().waitFor();
        Assert.assertEquals(0, r);
        System.out.println("RUNNING C PROGRAM " + cfileName + " " + Arrays.toString(args));
        List<String> str = new ArrayList<>();
        str.add(new File(tdir, "a.out").getAbsolutePath());
        str.addAll(Arrays.asList(args));
        int r2 = new ProcessBuilder(str).directory(tdir).inheritIO().start().waitFor();
        Assert.assertEquals(0, r2);
        System.out.println("C PROGRAM " + cfileName + " DONE");

        for (File f : tdir.listFiles()) {
            f.delete();
        }

        tdir.delete();
    }

    @Test
    public void testSharedGCC() throws Exception {
        final LinuxNativeUtil lnu = NativeUtils.getLinuxUtil();
        final UUID uuid = UUID.randomUUID();
        int i = lnu.shm_open(uuid.toString(), LinuxConst.O_RDWR | LinuxConst.O_CREAT, 0777);
        lnu.ftruncate(i, 4096);
        long mmap = lnu.mmap(i, 4096, LinuxConst.MAP_SHARED, true, true, 0);
        final PointerHandler ptr = new PointerHandler() {
            @Override
            public void handleClose(long ptr, long size) {
                try {
                    lnu.munmap(ptr, size);
                } catch (UnknownNativeErrorException e) {
                    //DONT CARE
                }
            }

            @Override
            public void handleSync(long ptr, long size, long offset, long length, boolean invalidate) throws SyncFailedException {

            }
        };

        NativeMemory mem = lnu.pointer(mmap, 4096, ptr);
        mem.zero();
        final long mutex_attr = mem.getNativePointer(0);
        final long mutex = mem.getNativePointer(lnu.sizeof_pthread_condattr_t());

        lnu.pthread_mutexattr_init(mutex_attr);
        if (!"riscv64".equalsIgnoreCase(System.getenv("QARCH"))) {
            lnu.pthread_mutexattr_setrobust(mutex_attr, LinuxConst.PTHREAD_MUTEX_ROBUST);
        }
        lnu.pthread_mutexattr_setpshared(mutex_attr, LinuxConst.PTHREAD_PROCESS_SHARED);
        lnu.pthread_mutex_init(mutex, mutex_attr);

        lnu.pthread_mutex_lock(mutex);
        Future<Object> submit = ex.submit(new Callable<Object>() {
            @Override
            public Object call() throws Exception {
                runCFile("mutextest.c", uuid.toString());
                return null;
            }
        });

        Thread.sleep(5000);
        if (submit.isDone()) {
            submit.get();
        }
        Assert.assertFalse(submit.isDone());
        lnu.pthread_mutex_unlock(mutex);

        submit.get(2, TimeUnit.SECONDS);
        mem.close();
    }
}
