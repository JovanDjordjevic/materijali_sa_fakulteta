package RM_4I_2019_KOL_A;

import java.io.*;
import java.net.Socket;
import java.nio.Buffer;
import java.util.Scanner;

public class zadatak_2_client {
    public static void main(String[] args) {
        try (Socket client = new Socket("localhost", 27182);
             BufferedReader newtworkIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
             BufferedWriter networkOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
             Scanner in = new Scanner(System.in);
             ){

            System.out.println("ulaz: ");
            String path = in.next();
            double x = in.nextDouble();
            double eps = in.nextDouble();
            //System.out.println(path +" "+ x +" "+ eps);

            networkOut.write(path + " " + x + " " + eps);
            networkOut.newLine();
            networkOut.flush();

            System.out.println(newtworkIn.readLine());
            System.out.println(newtworkIn.readLine());

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
