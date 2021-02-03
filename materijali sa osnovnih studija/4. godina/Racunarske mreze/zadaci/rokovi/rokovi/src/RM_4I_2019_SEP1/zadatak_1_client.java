package RM_4I_2019_SEP1;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class zadatak_1_client {

    public static void main(String[] args) {

        try(Socket client = new Socket("localhost", 12345);
            BufferedReader networkIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter networkOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
            Scanner sc = new Scanner(System.in);
        ){

            System.out.println("input path");
            String inputPath = sc.nextLine();

            networkOut.write(inputPath);
            networkOut.newLine();
            networkOut.flush();

            byte indicator;
            indicator = (byte) networkIn.read();
            if(indicator == 0){
                System.out.println("output path");
                String outputPath = sc.nextLine();
                FileOutputStream fos = new FileOutputStream(outputPath);
                BufferedWriter fileOut = new BufferedWriter(new OutputStreamWriter(fos));
                String line;
                while( (line = networkIn.readLine()) != null){
                    line += '\n';
                    fos.write(line.getBytes());
                }
            }else if(indicator == 1){
                System.out.println("invalid file");
            }else {
                System.out.println("server misbehaving");
            }

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

}
