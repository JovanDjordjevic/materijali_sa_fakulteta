package RM_4R_2020_JUN2;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;

//nedovrsen i netacan

public class zadatak_3_server {

    public static void main(String[] args) {

        System.out.println("starting server");

        try(ServerSocketChannel serverChannel = ServerSocketChannel.open();
            Selector selector = Selector.open();
           ){

            serverChannel.bind(new InetSocketAddress(12345));
            serverChannel.configureBlocking(false);
            serverChannel.register(selector, SelectionKey.OP_ACCEPT);

            while(true){

                selector.select();
                Iterator<SelectionKey> it = selector.selectedKeys().iterator();

                while(it.hasNext()){
                    SelectionKey key = it.next();
                    it.remove();
                    try {
                        if (key.isAcceptable()) {
                            ServerSocketChannel server = (ServerSocketChannel)key.channel();
                            SocketChannel client = server.accept();
                            client.configureBlocking(false);
                            SelectionKey clientKey = client.register(selector, SelectionKey.OP_READ);

                            ByteBuffer buf = ByteBuffer.allocate(128);
                            client.read(buf);
                            String username = new String(buf.array(), 0, buf.position());

                            System.out.println("Client " + username +" accepted");
                        } else if (key.isReadable()) {
                            SocketChannel client = (SocketChannel) key.channel();
                            ByteBuffer buf = (ByteBuffer)key.attachment();
                            if(buf == null){
                                //ako prvi put citamo od klijenta to je sigurno username
                                buf = ByteBuffer.allocate(128);
                                key.attach(buf);
                                client.read(buf);
                                String username = new String(buf.array(), 0, buf.position());
                                System.out.println(username);
                            }else {
                                //neki drugi request
                                client.read(buf);
                            }
                        } else if (key.isWritable()) {
                            SocketChannel client = (SocketChannel) key.channel();

                        }
                    }catch (Exception e){
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
