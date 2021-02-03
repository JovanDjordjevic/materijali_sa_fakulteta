package RM_4R_2020_JUN2;

import java.io.IOException;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.SocketChannel;
import java.nio.channels.WritableByteChannel;
import java.util.Scanner;

//nedovrsen i netacan

public class zadatak_3_client {

    public static void main(String[] args) {

        try(SocketChannel clientChannel = SocketChannel.open(new InetSocketAddress("localhost", 12345));
            Scanner sc = new Scanner(System.in);
            WritableByteChannel out = Channels.newChannel(System.out);
           ){
            System.out.println("Unesi ime");
            byte[] imeCimera = sc.nextLine().getBytes();
            ByteBuffer request = ByteBuffer.allocate(imeCimera.length).put(imeCimera);
            clientChannel.write(request);

            while(true){
                System.out.println("Unesi komandu");
                String line = sc.nextLine();

                try{
                    int broj = Integer.parseInt(line);
                    ByteBuffer buf = ByteBuffer.allocate(4).putInt(broj);
                    clientChannel.write(buf);

                }catch (NumberFormatException e){
                    //invalid number
                    continue;
                }

                if(line.trim().equalsIgnoreCase("kraj")){
                    break;
                }else if(line.trim().equalsIgnoreCase("stanje")){
                    byte[] content = line.getBytes();
                    System.out.println(content.length);
                    ByteBuffer buf = ByteBuffer.allocate(content.length).put(content);
                    clientChannel.write(buf);

                    //odgovor od servera
                    ByteBuffer responseBuf = ByteBuffer.allocate(128);
                    while(clientChannel.read(responseBuf) != -1){
                        responseBuf.flip();
                        out.write(responseBuf);
                        responseBuf.clear();
                    }

                }else{
                    continue;
                }
            }

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
