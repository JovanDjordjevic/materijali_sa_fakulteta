package RM_4I_2020_JUN1;

import java.io.*;
import java.net.Socket;
import java.util.List;
import java.util.Map;

//nisam implementirao da li je validan format zahteva
//nisma implementirao da moze vise reci da cini content i title

public class zadatak_1_server_thread implements Runnable{

    private Socket client;
    private Map<Integer, zadatak_1_server.ForumTopic> forum;

    zadatak_1_server_thread(Socket client){
        this.client = client;
        this.forum = zadatak_1_server.forum;
    }

    @Override
    public void run() {
        try(BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            BufferedWriter out = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()));
           ){

            System.out.println("Pristigao client: " + client.getInetAddress().getHostName());

            while(true) {
                String line = in.readLine();
                String[] params = line.split(" ");

                if (params[0].equalsIgnoreCase("bye")){
                    System.out.println(client.getInetAddress().getHostName() + "disconnected");
                    break;
                }else if(params[0].equalsIgnoreCase("list")){
                    synchronized (forum){
                        for( Integer id : forum.keySet()){
                            out.write( id + ": " + forum.get(id).topic );
                            out.newLine();
                            out.flush();
                            List<String> replies = forum.get(id).getAllContent();
                            for(String r : replies){
                                out.write(r);
                                out.newLine();
                                out.flush();
                            }
                        }
                    }
                }
                else if(params[0].equalsIgnoreCase("reply")){
                    int id = Integer.parseInt(params[1]);
                    String content = params[2];
                    synchronized (forum) {
                        forum.get(id).addContent("\t- " + content);
                    }
                    out.write("reply " + id + " " + content);
                    out.newLine();
                    out.flush();
                }
                else if(params[0].equalsIgnoreCase("post")){
                    String title = params[1];
                    String content = params[2];
                    synchronized (forum) {
                        forum.put(zadatak_1_server.getNextAvailableId(),
                                new zadatak_1_server.ForumTopic(title, "\t# " + content));
                    }
                    out.write("post je uspesno izvrsen");
                    out.newLine();
                    out.flush();
                }

            }

        } catch (IOException e) {
            e.printStackTrace();
        }finally {
            try {
                this.client.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
