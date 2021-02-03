package RM_4I_2019_KOL_A;

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

//nemam konkretne fajlove sa klk pa sam pretpostavio da se u fajlovima sadrze samo brojevi i nista drugo (ili su prazni)

public class zadatak_2_server_thread extends Thread{

    private Socket client;

    zadatak_2_server_thread(Socket client){
        this.client = client;
    }

    @Override
    public void run() {
        try(BufferedReader in = new BufferedReader(new InputStreamReader(this.client.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(this.client.getOutputStream()))
           ){

            String[] inputFromClient = in.readLine().split(" ");
            System.out.println(inputFromClient[0]);

            String path = inputFromClient[0];
            double x = Double.parseDouble(inputFromClient[1]);
            double eps = Double.parseDouble(inputFromClient[2]);

            String filePath = "C:\\Users\\Jovan\\Desktop\\RM\\rokovi\\test\\" + path;

            File file = new File(filePath);
            if(file.exists()){
                out.write("Validna putanja");
                out.newLine();
                out.flush();
            }else{
                out.write("Putanja nije validna");
                out.newLine();
                out.flush();
                out.write("Nema realnih brojeva");
                out.newLine();
                out.flush();
            }

            try(Scanner f = new Scanner(file);) {
                int count = 0;
                boolean hasReals = false;
                while (f.hasNext()) {
                    double tmp = f.nextDouble();
                    hasReals = true;
                    if (x - eps < tmp && tmp < x + eps) {
                        count++;
                    }
                }

                if(hasReals){
                    out.write(Integer.toString(count));
                    out.newLine();
                    out.flush();
                }else{
                    out.write("Nema realnih brojeva");
                    out.newLine();
                    out.flush();
                }

            }catch (FileNotFoundException e){

            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                client.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
