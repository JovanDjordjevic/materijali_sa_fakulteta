package RM_4I_2018_KOL_A;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

//mozda nisam lepo resio izgladnjivanje

public class zadatak_2 {

    public static List<String> allPaths = Collections.synchronizedList(new ArrayList<>());

    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        System.out.println("unesi putanju do tekstualnog fajla sa putanjama");
        //String path = sc.nextLine();
        String path = "/home/student/Desktop/rokovi/test/paths.txt";

        System.out.println();
        try (Scanner fileSc = new Scanner(new File(path));){
            while (fileSc.hasNext()){
                String line = fileSc.nextLine();
                System.out.println(line);
                allPaths.add(line);
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        System.out.println("\nUnesi rec za pretragu i broj niti");
        String word = sc.next();
        int n = sc.nextInt();

        List<WorkerThread> threads = new ArrayList<>();
        for(int i=0; i<n; i++){
            WorkerThread t = new WorkerThread(word);
            t.start();
            threads.add(t);
        }
        for(WorkerThread t : threads){
            try {
                t.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        sc.close();
    }



    public static class WorkerThread extends Thread{
        private String word;
        WorkerThread(String word){ this.word = word; }

        @Override
        public void run() {
            while(allPaths.size()>0) {
                String fileToSearch = "";
                synchronized (allPaths) {
                    //System.out.println("Thread " + Thread.currentThread().getId() + "took a file");
                    fileToSearch = allPaths.remove(0);
                }

                try {
                    Thread.sleep(2000);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                try (Scanner file = new Scanner(new File(fileToSearch));){
                    int lineCount = 0;
                    while (file.hasNext()){
                        String[] words = file.nextLine().split(" ");
                        lineCount++;
                        for(String w : words) {
                            if (w.trim().equalsIgnoreCase(this.word)) {
                                System.out.println(Thread.currentThread().getId() + " : " + fileToSearch + " : " + lineCount);
                            }
                        }
                    }
                } catch (FileNotFoundException e) {
                    continue;
                }

            }
        }

    }
}
