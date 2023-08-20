package io.github.alexanderschuetz97.nativeutils;

import io.github.alexanderschuetz97.nativeutils.api.LinuxNativeUtil;
import io.github.alexanderschuetz97.nativeutils.api.NativeUtils;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.QuotaExceededException;
import io.github.alexanderschuetz97.nativeutils.api.exceptions.UnknownNativeErrorException;
import org.junit.Assert;
import org.junit.Test;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.AccessDeniedException;
import java.nio.file.FileAlreadyExistsException;
import java.nio.file.NotDirectoryException;
import java.util.UUID;

public class TestFifo {

    @Test
    public void test() throws IOException, UnknownNativeErrorException {
        UUID u = UUID.randomUUID();
        LinuxNativeUtil util = NativeUtils.getLinuxUtil();
        util.mkfifo("/tmp/" + u.toString(), 0777);
        Assert.assertTrue(util.stat("/tmp/" + u.toString()).isFIFO());
        new File("/tmp/" + u.toString()).delete();

    }
}
