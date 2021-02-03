package RM_4I_2020_JUN1;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

public class zadatak_1_server {

    public static Map<Integer, ForumTopic> forum = Collections.synchronizedMap(new HashMap<Integer, ForumTopic>());
    public static int nextAvailableId = 0;

    public static void main(String[] args) {
        try(ServerSocket server = new ServerSocket(7337);
           ){

            while(true){
                Socket client = server.accept();
                new Thread(new zadatak_1_server_thread(client)).start();
            }



        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int getNextAvailableId(){
        nextAvailableId++;
        return nextAvailableId;
    }



    public static class ForumTopic{
        public String topic;
        private List<String> allContent = new ArrayList<>();
        ForumTopic(String topic, String content){
            this.topic = topic;
            this.allContent.add(content);
        }
        public void addContent(String content){
            this.allContent.add(content);
        }
        public List<String> getAllContent(){
            return this.allContent;
        }
    }

}
