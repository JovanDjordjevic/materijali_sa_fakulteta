package RM_4I_2020_SEP1;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.Scanner;

//nedovrsen zadatak, nisam znao kako sa klijentske strane da posaljem podatke

public class zadatak_1_client {

    public static void main(String[] args) {

        try(SocketChannel client = SocketChannel.open(new InetSocketAddress("localhost", 7337));
            Scanner sc = new Scanner(System.in);
           ){

            client.configureBlocking(true);
            int x = sc.nextInt();
            int y = sc.nextInt();
            int r = sc.nextInt();

            ByteBuffer.allocate(12);


        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
