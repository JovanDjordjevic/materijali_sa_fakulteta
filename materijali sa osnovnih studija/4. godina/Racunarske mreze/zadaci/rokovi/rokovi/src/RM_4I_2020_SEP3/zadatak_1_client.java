package RM_4I_2020_SEP3;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class zadatak_1_client {
    public static void main(String[] args) {
        try(Socket client = new Socket("localhost", 12321);
            BufferedReader networkIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter networkOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
            Scanner sc = new Scanner(System.in);
           ){

            System.out.println("Unesi nickname");
            String nickname = sc.next();

            networkOut.write(nickname);
            networkOut.newLine();
            networkOut.flush();

            System.out.println(networkIn.readLine());

            while (true){
                String firstLine = networkIn.readLine();
                if(firstLine.contains("zavrsen")){
                    String line;
                    while((line = networkIn.readLine()) != null){
                        System.out.println(line);
                    }
                    break;
                }
                else {
                    System.out.println(firstLine);
                    System.out.println(networkIn.readLine());
                    System.out.println(networkIn.readLine());
                    System.out.println(networkIn.readLine());
                    System.out.println(networkIn.readLine());

                    String odgovor = sc.next();
                    networkOut.write(odgovor);
                    networkOut.newLine();
                    networkOut.flush();

                    System.out.println(networkIn.readLine());
                }
            }

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
