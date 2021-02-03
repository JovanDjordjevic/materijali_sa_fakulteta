package RM_4R_2020_JUN1;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.DoubleBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

//NE RADI

public class zadatak_3_client {

    public static void main(String[] args) {

        try(SocketChannel clientChannel = SocketChannel.open(new InetSocketAddress("localhost", 31415));
            Scanner sc = new Scanner(System.in);
           ){

            clientChannel.configureBlocking(true);


            while (true){
                double broj = sc.nextDouble();
                ByteBuffer buffer = ByteBuffer.allocate(8).putDouble(broj);
                clientChannel.write(buffer);

                clientChannel.read(buffer);
                System.out.println(buffer.getDouble());
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
