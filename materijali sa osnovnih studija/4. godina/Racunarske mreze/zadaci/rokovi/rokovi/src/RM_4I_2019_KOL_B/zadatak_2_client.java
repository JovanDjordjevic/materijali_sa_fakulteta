package RM_4I_2019_KOL_B;

import java.io.*;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class zadatak_2_client {

    public static void main(String[] args) {
        try(Socket  client = new Socket("localhost", 31415);
            BufferedReader networkIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter networkOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
            Scanner sc = new Scanner(System.in);
           ){

            System.out.println("enter path relative to test folder");
            String path = sc.next();

            networkOut.write(path);
            networkOut.newLine();
            networkOut.flush();

            System.out.println(networkIn.readLine());
            System.out.println(networkIn.readLine());

        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
