package RM_4I_2019_KOL_B;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class zadatak_2_server_thread extends Thread{

    private Socket client;

    zadatak_2_server_thread(Socket client){
        this.client = client;
    }

    @Override
    public void run() {
        try(BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
            ) {

            String clientInput = in.readLine();
            System.out.println(clientInput);

            String filePath = "C:\\Users\\Jovan\\Desktop\\RM\\rokovi\\test\\" + clientInput;

            File file = new File(filePath);
            if(file.exists()){
                out.write("Validna putanja");
                out.newLine();
                out.flush();
            }else{
                out.write("Nije validna putanja");
                out.newLine();
                out.flush();
            }

            try(Scanner f = new Scanner(file)){

                boolean hasReals = false;
                double sum = 0.0;
                while(f.hasNextDouble()){
                    hasReals = true;
                    sum += f.nextDouble();
                }

                if(hasReals){
                    out.write(Double.toString(sum));
                    out.newLine();
                    out.flush();
                }else{
                    out.write("Nema realnih brojeva");
                    out.newLine();
                    out.flush();
                }

            }catch (FileNotFoundException e){
                out.write("Nema realnih brojeva");
                out.newLine();
                out.flush();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }finally {
            try {
                client.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }
}
