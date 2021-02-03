package RM_4I_2020_SEP1;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Scanner;
import java.util.Set;

//nedovrsen zadatak, nisam znao kako sa klijentske strane da posaljem podatke

public class zadatak_1_server {

    public static void main(String[] args) {

        try(Scanner sc = new Scanner(System.in)){
            System.out.println("Unesi m i n:");
            int m = sc.nextInt();
            int n = sc.nextInt();
        }

        try(ServerSocketChannel serverChannel = ServerSocketChannel.open();
            Selector selector = Selector.open();
           ){

            serverChannel.bind(new InetSocketAddress(7337));
            serverChannel.configureBlocking(false);
            serverChannel.register(selector, SelectionKey.OP_ACCEPT);

            while (true){
                selector.select();
                Set<SelectionKey> readyKeys = selector.selectedKeys();
                Iterator<SelectionKey> it = readyKeys.iterator();
                while(it.hasNext()){
                    SelectionKey key = it.next();
                    it.remove();
                    try {
                        if (key.isAcceptable()) {
                            ServerSocketChannel server = (ServerSocketChannel) key.channel();
                            SocketChannel client = server.accept();
                            System.out.println("Accepted client");

                            server.configureBlocking(false);
                            SelectionKey clientKey = client.register(selector, SelectionKey.OP_WRITE | SelectionKey.OP_READ);

                            ByteBuffer buf = ByteBuffer.allocate(12);  //3 inta
                            //ByteBuffer bufWrite = ByteBuffer.allocate(8); //1 double

                            clientKey.attach(buf);
                        } else if (key.isReadable()) {

                        } else if (key.isWritable()) {

                        } else {
                        }
                    }catch(IOException e){
                        System.out.println("CLient disconected");
                        key.cancel();
                        key.channel().close();
                    }
                }

            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
