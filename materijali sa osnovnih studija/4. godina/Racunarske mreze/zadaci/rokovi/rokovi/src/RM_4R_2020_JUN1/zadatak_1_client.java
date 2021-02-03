package RM_4R_2020_JUN1;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class zadatak_1_client {

    public static void main(String[] args) {
        try(Socket client = new Socket("localhost", 10000);
            BufferedReader networkIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter networkOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
            Scanner sc = new Scanner(System.in);
           ){

            String line;
            Double number;
            while (true){
                line = sc.nextLine();
                if(line.equalsIgnoreCase("KRAJ")){
                    networkOut.write(line);
                    networkOut.newLine();
                    networkOut.flush();
                    break;
                } else{
                    try{
                        number = Double.parseDouble(line);
                        networkOut.write(line);
                        networkOut.newLine();
                        networkOut.flush();
                    }catch (NumberFormatException e){
                        System.out.println("Neispravan broj");
                    }
                }
            }

            //System.out.println("zavrsen input");
            System.out.println(networkIn.readLine());

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
