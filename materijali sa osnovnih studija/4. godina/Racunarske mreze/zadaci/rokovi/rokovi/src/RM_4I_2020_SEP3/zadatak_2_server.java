package RM_4I_2020_SEP3;

import java.io.File;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.nio.charset.StandardCharsets;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Scanner;

//ne radi mi lepo vracanje podatka korisniku ako je pos1 validan a pos2 nije, mrzi me da popravljam

public class zadatak_2_server {

    public static String folderPath;

    public static void main(String[] args) {
        try(DatagramSocket server = new DatagramSocket(12121);
            Scanner sc = new Scanner(System.in)){

            System.out.println("Unesi naziv foldera iz kog klijent moze da trazi fajlove");
            folderPath = sc.nextLine();
            //folderPath = "/home/student/Desktop/rokovi/test";

            int datagramIndex = 1;

            while(true) {
                try {
                    DatagramPacket request = new DatagramPacket(new byte[1024], 1024);
                    server.receive(request);

                    System.out.println("Datagram arrived. Index: " + datagramIndex + " User: " + request.getAddress());
                    datagramIndex++;

                    byte[] requestBuf = request.getData();
                    String[] requestContent = new String(requestBuf, 0, request.getLength(), StandardCharsets.US_ASCII).split(" ");
                    String fileName = requestContent[0];
                    int pos1 = Integer.parseInt(requestContent[1]);
                    int pos2 = Integer.parseInt(requestContent[2]);
                    //System.out.println(fileName + " " + pos1 + " " + pos2);

                    byte[] responseBuf = formResponse(fileName, pos1, pos2);
                    DatagramPacket response = new DatagramPacket(responseBuf, responseBuf.length, request.getAddress(), request.getPort());
                    server.send(response);

                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    //nisam implementirao da podrzava podfoldere
    public static byte[] formResponse(String fileName, int pos1, int pos2){
        try(DirectoryStream<Path> ds = Files.newDirectoryStream(Paths.get(folderPath))){
            for(Path p : ds){
                String pName = p.getFileName().toString();
                //System.out.println(p.getFileName());
                if(pName.equalsIgnoreCase(fileName)){
                    try(Scanner sc = new Scanner(new File(p.toString()))){
                        int linesRead = 0;
                        StringBuilder responseStringBuilder = new StringBuilder();
                        boolean reached1 = false;
                        boolean reached2 = false;
                        while(sc.hasNext()){
                            String line = sc.nextLine();
                            linesRead++;
                            if(pos1 == linesRead) {reached1 = true;}
                            if(pos2 == linesRead) {reached2 = true;}
                            if(pos1 <= linesRead && pos2>=linesRead){
                                responseStringBuilder.append(line).append('\n');
                            }
                        }

                        if(reached1 && reached2){
                            String responseString = responseStringBuilder.toString();
                            return responseString.getBytes();
                        }
                        else{
                            String responseString = "Nepravilno zadata naredba\n";
                            return responseString.getBytes();
                        }
                    }
                }
            }

            //izasao iz petlje znaci nije dao odgovarajuci path
            String responseString = "Nepravilno zadata naredba\n";
            return responseString.getBytes();

        } catch (IOException e) {
            e.printStackTrace();
        }

        return new byte[1];
    }

}
