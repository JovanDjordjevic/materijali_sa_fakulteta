package RM_4I_2020_SEP2;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
import java.nio.channels.SocketChannel;
import java.nio.channels.WritableByteChannel;
import java.util.Scanner;

//nedovrsen

public class zadatak_1_client {

    public static void main(String[] args) {
        try(SocketChannel clientChannel = SocketChannel.open(new InetSocketAddress("localhost", 12221));
            Scanner sc = new Scanner(System.in);
            WritableByteChannel out = Channels.newChannel(System.out);
           ){

            clientChannel.configureBlocking(true);
            System.out.println("Unesi broj racuna");
            //pretpostavljamo da je broj racuna int
            int accountNumber = sc.nextInt();

            Socket client = clientChannel.socket();
            ReadableByteChannel clientIn = Channels.newChannel(client.getInputStream());
            WritableByteChannel clientOut = Channels.newChannel(client.getOutputStream());

            ByteBuffer request = ByteBuffer.allocate(4).putInt(accountNumber);
            clientChannel.write(request);

            ByteBuffer response = ByteBuffer.allocate(4);
            clientIn.read(response);
            while(response.hasRemaining()){
                response.flip();
                out.write(response);
                response.clear();
            }

            System.out.println("unesi broj racuna i iznos za transfer");
            int account = sc.nextInt();
            int amount = sc.nextInt();

            ByteBuffer transferRequest = ByteBuffer.allocate(8).putInt(account).putInt(amount);
            clientOut.write(transferRequest);

            //odgovor servera

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
