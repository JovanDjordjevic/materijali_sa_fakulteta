package RM_4I_2020_JAN2;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.Channel;
import java.nio.channels.Channels;
import java.nio.channels.SocketChannel;
import java.nio.channels.WritableByteChannel;
import java.util.Scanner;

public class zadatak_1_client {

    public static boolean shouldStop = false;

    public static void main(String[] args) {

        System.out.println("[Start]");
        System.out.println("Connecting...");

        try(SocketChannel client = SocketChannel.open(new InetSocketAddress("localhost", 12345));
            Scanner sc = new Scanner(System.in);){

            System.out.println("Starting thread");
            Thread t = new Thread(new UserThread(client));
            t.start();
            System.out.println("Thread started");

            String signal = sc.next();
            if(signal.equalsIgnoreCase("stop")){
                //ovo daje asynchronous close exception, nemam bolji nacin
                shouldStop = true;
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    private static class UserThread implements Runnable{

        private SocketChannel client;
        private boolean shouldStop;

        UserThread(SocketChannel client){
            this.client = client;
        }

        @Override
        public void run() {
            ByteBuffer buffer = ByteBuffer.allocate(22);
            WritableByteChannel out = Channels.newChannel(System.out);

            try {
                while (client.read(buffer) != -1) {
                    buffer.flip();
                    out.write(buffer);
                    buffer.clear();
                }
            }catch (IOException e){
                e.printStackTrace();
            }

            if(shouldStop) return;
        }
    }


}
