package RM_4I_2019_JAN2;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Random;

public class zadatak_1_server {

    public static void main(String[] args) {
        try(ServerSocketChannel serverChannel = ServerSocketChannel.open();
            Selector selector = Selector.open();
            ){

            serverChannel.bind(new InetSocketAddress(12345));
            serverChannel.configureBlocking(false);
            serverChannel.register(selector, SelectionKey.OP_ACCEPT);

            while (true){
                selector.select();
                Iterator<SelectionKey> it = selector.selectedKeys().iterator();

                while(it.hasNext()){
                    SelectionKey key = it.next();
                    it.remove();
                    try {
                        if (key.isAcceptable()) {
                            ServerSocketChannel server = (ServerSocketChannel)key.channel();
                            SocketChannel client = server.accept();
                            System.out.println("client accepted");

                            client.configureBlocking(false);
                            SelectionKey clientKey = client.register(selector, SelectionKey.OP_WRITE);

                            ByteBuffer buf = ByteBuffer.allocate(4);
                            clientKey.attach(buf);
                        } else if (key.isWritable()) {
                            SocketChannel client = (SocketChannel)key.channel();
                            ByteBuffer buf = (ByteBuffer)key.attachment();

                            Random r = new Random();
                            int i = r.nextInt();
                            System.out.println(i);

                            if(!buf.hasRemaining()){
                                buf.rewind();
                                buf.clear();
                                buf.putInt(i);
                                buf.flip();
                            }

                            client.write(buf);
                        }
                    }catch (IOException e) {
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
