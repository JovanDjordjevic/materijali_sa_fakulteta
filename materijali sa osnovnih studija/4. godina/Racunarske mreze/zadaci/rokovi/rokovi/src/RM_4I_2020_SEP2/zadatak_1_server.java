package RM_4I_2020_SEP2;


import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;

//nedovrsen

public class zadatak_1_server {

    public static void main(String[] args) {

        try(ServerSocketChannel serverChannel = ServerSocketChannel.open();
            Selector selector = Selector.open();
           ){

            serverChannel.bind(new InetSocketAddress(12221));
            serverChannel.configureBlocking(false);
            serverChannel.register(selector, SelectionKey.OP_ACCEPT);

            while(true){
                selector.select();
                Iterator<SelectionKey> it = selector.selectedKeys().iterator();

                while(it.hasNext()){
                    SelectionKey key = it.next();
                    it.remove();
                    if(key.isAcceptable()){
                        ServerSocketChannel server = (ServerSocketChannel)key.channel();
                        SocketChannel client = server.accept();
                        client.configureBlocking(false);
                        SelectionKey clientKey = client.register(selector, SelectionKey.OP_READ);
                    }else if(key.isReadable()){
                        SocketChannel client = (SocketChannel)key.channel();
                        ByteBuffer buf = (ByteBuffer)key.attachment();
                        if(buf == null){
                            buf = ByteBuffer.allocate(4);
                            key.attach(buf);
                            client.read(buf);
                        }
                        System.out.println(buf.getInt());
                        key.interestOps(SelectionKey.OP_WRITE);
                    }else if(key.isWritable()){

                    }

                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
