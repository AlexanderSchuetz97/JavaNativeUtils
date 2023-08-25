package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeMemory;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.QuotaExceededException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.*;

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
    public void test() throws UnknownNativeErrorException, QuotaExceededException {
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
    public void test2() throws UnknownNativeErrorException, QuotaExceededException, ExecutionException, InterruptedException, TimeoutException {
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
    }
}
