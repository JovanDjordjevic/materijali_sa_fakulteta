package RM_4R_2020_JUN1;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Iterator;
import java.util.Set;

//NE RADI

public class zadatak_3_server {

    public static void main(String[] args) {

        try(ServerSocketChannel serverChannel = ServerSocketChannel.open();
            Selector selector = Selector.open();
           ){

            serverChannel.bind(new InetSocketAddress(31415));
            serverChannel.configureBlocking(false);
            serverChannel.register(selector, SelectionKey.OP_ACCEPT);

            while (true){

                selector.select();
                Set<SelectionKey> selectedKeys = selector.selectedKeys();
                Iterator<SelectionKey> it = selectedKeys.iterator();

                while(it.hasNext()){
                    SelectionKey key = it.next();
                    it.remove();

                    try {
                        if (key.isAcceptable()) {
                            ServerSocketChannel server = (ServerSocketChannel) key.channel();
                            SocketChannel client = server.accept();
                            client.configureBlocking(false);
                            client.register(selector, SelectionKey.OP_READ);
                            System.out.println("client accepted");
                        } else if  (key.isReadable()){
                            SocketChannel client = (SocketChannel)key.channel();

                            System.out.println("reading from client");
                            ByteBuffer buf = ByteBuffer.allocate(8);
                            key.attach(buf);
                            client.read(buf);

                            double radius = buf.getDouble();
                            double povrsina = radius * radius * Math.PI;

                            ByteBuffer res = ByteBuffer.allocate(8).putDouble(povrsina);
                            key.attach(res);
                            key.interestOps(SelectionKey.OP_WRITE);

                        }else if (key.isWritable()){
                            SocketChannel client = (SocketChannel)key.channel();
                            ByteBuffer out = (ByteBuffer) key.attachment();

                            if(out.hasRemaining()){
                                System.out.println("writing to cient");
                                client.write(out);
                            }else{
                                System.out.println("finished writing");
                                client.register(selector, SelectionKey.OP_READ);
                            }
                        }
                    }catch (IOException e){
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
