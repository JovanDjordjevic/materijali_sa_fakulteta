package RM_4I_2020_JAN2;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.Set;


//dobijam buffer overflow exception, ne radim nesto dobro tu ali ne vidim sta


public class zadatak_1_server {

    public static String getCurrentTime(){
        Calendar date = Calendar.getInstance();
        String data = Integer.toString(date.get(Calendar.DAY_OF_MONTH)) + "." + (date.get(Calendar.MONTH)+1) + "." + Integer.toString(date.get(Calendar.YEAR)) + " | "
                + Integer.toString(date.get(Calendar.HOUR_OF_DAY)) + ":" + Integer.toString(date.get(Calendar.MINUTE)) + ":" + Integer.toString(date.get(Calendar.SECOND)) + "\r\n";
        //System.out.println(data);
        return data;
    }

    public static void main(String[] args) {

        System.out.println("[Start]");

        try (ServerSocketChannel serverChannel = ServerSocketChannel.open();
             Selector selector = Selector.open();
            ){

            if(!serverChannel.isOpen() || !selector.isOpen()){
                System.err.println("error when opening");
                System.exit(1);
            }

            serverChannel.bind(new InetSocketAddress(12345));
            serverChannel.configureBlocking(false);

            serverChannel.register(selector, SelectionKey.OP_ACCEPT);

            long startSendTime = Calendar.getInstance().getTimeInMillis();

            while(true){

                long currentSendTime = Calendar.getInstance().getTimeInMillis();
                if(currentSendTime - startSendTime > 5000){
                    startSendTime = currentSendTime;

                    selector.select();
                    Set<SelectionKey> readyKeys = selector.selectedKeys();
                    Iterator<SelectionKey> it = readyKeys.iterator();
                    while(it.hasNext()){
                        SelectionKey key = it.next();
                        it.remove();
                        try{
                            if(key.isAcceptable()){
                                ServerSocketChannel server = (ServerSocketChannel)key.channel();
                                SocketChannel client = server.accept();
                                System.out.println("Accepted client");

                                client.configureBlocking(false);
                                SelectionKey clientKey = client.register(selector, SelectionKey.OP_WRITE);

                                byte[] currentTime = getCurrentTime().getBytes();
                                ByteBuffer buffer = ByteBuffer.allocate(currentTime.length);
                                buffer.put(currentTime);
                                buffer.flip();
                                clientKey.attach(buffer);
                            }
                            else if (key.isReadable()){

                            }
                            else if (key.isWritable()){
                                SocketChannel client = (SocketChannel)key.channel();
                                ByteBuffer buff = (ByteBuffer)key.attachment();
                                if(!buff.hasRemaining()){
                                    buff.rewind();
                                    buff.put(getCurrentTime().getBytes());
                                    buff.flip();
                                }
                                System.out.println("Serving time....");
                                client.write(buff);
                            }
                        }
                        catch (IOException e){
                            System.out.println("Client disconnected");
                            key.cancel();
                            key.channel().close();

                        }
                    }
                }



            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


}
