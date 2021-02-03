package RM_4R_2020_SEP2;

//zadatak 1 i 2 su isti kao na sep2 roku na I smeru

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class zadatak_3 {

    public static List<Double> numbers = Collections.synchronizedList(new ArrayList<>());
    public static double[] sortedNumbers;

    public static void main(String[] args) {

        try (Scanner sc = new Scanner(System.in)){

            System.out.println("Unesi putanju do fajla");
            //String filePath = sc.nextLine();
            String filePath = "/home/student/Desktop/rokovi/test/test3.txt";

            //pretpostavio sam da su svi brojevi u jednoj liniji
            try(Scanner file = new Scanner(new File(filePath))){
                String[] nums = file.nextLine().split(" ");
                for(String n : nums){
                    //System.out.println(n);
                    numbers.add(Double.parseDouble(n));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }

            System.out.println(numbers.size());
            sortedNumbers = new double[numbers.size()];

            long sortStartTime = System.currentTimeMillis();

            List<NumberThread> threads = new ArrayList<>();
            for(Double d : numbers){
                NumberThread t = new NumberThread(d);
                t.start();
                threads.add(t);
            }
            for(NumberThread nt : threads){
                nt.join();
            }

            long sortEndTime = System.currentTimeMillis();

            System.out.println(Arrays.toString(sortedNumbers));
            System.out.println("Sorranje je trajalo: " + (sortEndTime-sortStartTime) + " milisekundi");


        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }


    public static class NumberThread extends Thread{
        private double num;
        private int index = 0;
        private int equalNumbers = 0;
        NumberThread(double num) {this.num = num;}

        @Override
        public void run() {
            for(Double n : numbers){
                if(n !=this.num && n < this.num){
                    index++;
                }else if(n == this.num){
                    equalNumbers++;
                }
            }

            synchronized (sortedNumbers){
                //sortedNumbers[index] = this.num;
                if(sortedNumbers[index] == this.num){
                    for(int i = 0 ; i<equalNumbers; i++){
                        if(sortedNumbers[index + i] == this.num){
                            continue;
                        }else{
                            sortedNumbers[index + i] = this.num;
                            break;
                        }
                    }
                }else{
                    sortedNumbers[index] = this.num;
                }
            }

        }
    }

}
