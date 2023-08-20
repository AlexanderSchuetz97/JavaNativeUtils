package io.github.alexanderschuetz97.nativeutils;


import io.github.alexanderschuetz97.nativeutils.api.*;

import javax.swing.*;
import java.awt.*;
import java.awt.image.*;
import java.nio.ByteBuffer;
import java.nio.IntBuffer;
import java.security.SecureRandom;
import java.util.Random;
import java.util.Vector;
import java.util.concurrent.ScheduledExecutorService;

public class TestImg {


    public static void main(String[] args) {

        LinuxNativeUtil wnu = NativeUtils.getLinuxUtil();
        JVMNativeUtil jvmu = NativeUtils.getJVMUtil();
        final NativeMemory mem = wnu.malloc(512 * 512 * 4);
        final IntBuffer direct = jvmu.NewDirectByteBuffer(mem.getNativePointer(), mem.size()).asIntBuffer();

        new Thread(new Runnable() {
            @Override
            public void run() {
                Random r = new SecureRandom();
                while(true) {
                    for (long x = 0; x < mem.size(); x++) {
                        mem.writeByte(x, r.nextInt() & 0xFF);
                    }

                    try {
                        Thread.sleep(18);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

            }
        }).start();



        BufferedImage bufI = new BufferedImage(512, 512, BufferedImage.TYPE_INT_BGR) {

            @Override
            public WritableRaster getRaster() {
                WritableRaster wr = super.getRaster();
                int[] ir = ((DataBufferInt)wr.getDataBuffer()).getData();
                direct.position(0);
                direct.get(ir);
                return wr;
            }
        };

        display(bufI, direct);
    }


    private static JFrame frame;
    public static void display(final BufferedImage image, final IntBuffer buffer) {
            frame = new JFrame();
            frame.setTitle("stained_image");
            frame.setSize(image.getWidth(), image.getHeight());
            frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
            final Canvas pane = new Canvas();
            frame.add(pane);
            frame.setVisible(true);


            final int[] dta = ((DataBufferInt) image.getRaster().getDataBuffer()).getData();

        new Thread(new Runnable() {
            @Override
            public void run() {
                Random r = new Random();
                while(true) {
                    SwingUtilities.invokeLater(new Runnable() {
                        @Override
                        public void run() {
                            long l = System.currentTimeMillis();
                            buffer.position(0);
                            buffer.get(dta);
                            System.out.println(System.currentTimeMillis()-l);
                            pane.getGraphics().drawImage(image, 0, 0, null);
                        }
                    });

                    try {
                        Thread.sleep(32);
                    } catch (InterruptedException e) {
                        throw new RuntimeException(e);
                    }
                }

            }
        }).start();
    }
}
