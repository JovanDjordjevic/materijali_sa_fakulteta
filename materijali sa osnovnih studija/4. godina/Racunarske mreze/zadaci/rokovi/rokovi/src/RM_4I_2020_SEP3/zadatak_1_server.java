package RM_4I_2020_SEP3;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

//NOTE: nisam implementirao uslov za vreme kako treba

public class zadatak_1_server {

    public static Map<String, Double> users = Collections.synchronizedMap(new HashMap<String, Double>());
    public static List<Question> kviz = new ArrayList<Question>();
    public static AtomicInteger playerCount = new AtomicInteger(0);
    public static AtomicInteger finishedPlayers = new AtomicInteger(0);

    public static void main(String[] args) {

        try(ServerSocket server = new ServerSocket(12321);
            Scanner sc = new Scanner(System.in)){

            System.out.println("Unesi putanju do fajla sa pitanjima:");
            String path = sc.next();

            ucitajFajl(path);
            System.out.println("Pitanja ucitana");


            while(true){
                    Socket client = server.accept();
                    (new UserThread(client)).start();
            }


        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public static void ucitajFajl(String path){
        try(Scanner file = new Scanner(new File(path))){

            while (file.hasNext()){
                String question = file.nextLine();
                String ans_1 = file.nextLine();
                String ans_2 = file.nextLine();
                String ans_3 = file.nextLine();
                String ans_4 = file.nextLine();
                String correct_ans = "A";
                if(ans_1.contains("*")){
                    ans_1 = ans_1.replace('*', ' ').trim();
                } else if(ans_2.contains("*")){
                ans_2 = ans_2.replace('*', ' ').trim();
                correct_ans = "B";
                } else if(ans_3.contains("*")){
                    ans_3 = ans_3.replace('*', ' ').trim();
                    correct_ans = "C";
                } else if(ans_4.contains("*")){
                    ans_4 = ans_4.replace('*', ' ').trim();
                    correct_ans = "D";
                } else {
                    System.out.println("Nesto nije u redu u fajlu");
                    System.exit(1);
                }

                kviz.add(new Question(question, ans_1, ans_2, ans_3, ans_4, correct_ans));
            }

            /*for(Question q : kviz){
                System.out.println(q.toString());
            }*/

        } catch (FileNotFoundException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }

    public static class Question{
        public String question;
        public String ans_1;
        public String ans_2;
        public String ans_3;
        public String ans_4;
        public String correct_ans;
        Question(String question, String ans_1, String ans_2, String ans_3, String ans_4, String correct_ans){
            this.question = question;
            this.ans_1 = ans_1;
            this.ans_2 = ans_2;
            this.ans_3 = ans_3;
            this.ans_4 = ans_4;
            this.correct_ans = correct_ans;
        }
        @Override
        public String toString(){
            return question + "\n" + ans_1 + "\n" + ans_2 + "\n" + ans_3 + "\n" + ans_4;
        }
    }

    public static class UserThread extends Thread{
        private Socket client;
        UserThread(Socket client) {this.client = client;}

        @Override
        public void run() {
            try(BufferedReader userIn = new BufferedReader(new InputStreamReader(client.getInputStream()));
                BufferedWriter userOut = new BufferedWriter(new OutputStreamWriter(client.getOutputStream()))
               ){

                String nickaname = userIn.readLine().trim();
                users.put(nickaname, 0.0);
                playerCount.incrementAndGet();

                System.out.println("Waiting for 5 players to join");
                synchronized (playerCount){
                    while(playerCount.get()<5){
                        try{
                            playerCount.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                    playerCount.notifyAll();
                }

                userOut.write("Kviz pocinje sada. Srecno!");
                userOut.newLine();
                userOut.flush();

                for( int i = 0; i<kviz.size(); i++){
                    //System.out.println(kviz.get(i));
                    userOut.write(kviz.get(i).question); userOut.newLine(); userOut.flush();
                    userOut.write(kviz.get(i).ans_1); userOut.newLine();    userOut.flush();
                    userOut.write(kviz.get(i).ans_2); userOut.newLine();    userOut.flush();
                    userOut.write(kviz.get(i).ans_3); userOut.newLine();    userOut.flush();
                    userOut.write(kviz.get(i).ans_4); userOut.newLine();    userOut.flush();

                    System.out.println("question sent");

                    String userResponse = userIn.readLine();
                    System.out.println("user response recieved");

                    long questionStartTime = Calendar.getInstance().getTimeInMillis();

                    if(userResponse.equalsIgnoreCase(kviz.get(i).correct_ans)){
                        long questionAnsTime = Calendar.getInstance().getTimeInMillis();
                        if(questionAnsTime - questionStartTime > 10000){
                            userOut.write("Niste odgovorili na vreme");
                            userOut.newLine();
                            userOut.flush();
                        }
                        userOut.write("Tacan odgovor. Osvojili ste poen");
                        userOut.newLine();
                        userOut.flush();
                        double newVal = users.get(nickaname)+1;
                        users.put(nickaname, newVal);
                    }else{
                        long questionAnsTime = Calendar.getInstance().getTimeInMillis();
                        if(questionAnsTime - questionStartTime > 10000){
                            userOut.write("Niste odgovorili na vreme");
                            userOut.newLine();
                            userOut.flush();
                        }
                        userOut.write("Netacan odgovor. Izgubili ste 0.5 poena");
                        userOut.newLine();
                        userOut.flush();
                        double newVal = users.get(nickaname)-0.5;
                        users.put(nickaname, newVal);
                    }

                    System.out.println("response to user sent");
                }

                userOut.write("Kviz je zavrsen");
                finishedPlayers.incrementAndGet();

                synchronized (finishedPlayers){
                    while(finishedPlayers.get() != playerCount.get()){
                        try {
                            finishedPlayers.wait();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                    finishedPlayers.notifyAll();
                }

                userOut.newLine();
                userOut.flush();

                List<Map.Entry<String, Double>> entries = new ArrayList<>(users.entrySet());
                Collections.sort(entries, new Comparator<Map.Entry<String, Double>>() {
                    @Override
                    public int compare(Map.Entry<String, Double> o1, Map.Entry<String, Double> o2) {
                        return Double.compare(o2.getValue(), o1.getValue());
                    }
                });

                for(var entry : entries){
                    String response = entry.getKey() + " " + entry.getValue();
                    userOut.write(response);
                    userOut.newLine();
                    userOut.flush();
                }

            } catch (IOException e) {
                e.printStackTrace();
            }finally {
                try {
                    client.close();
                    playerCount.decrementAndGet();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

}
