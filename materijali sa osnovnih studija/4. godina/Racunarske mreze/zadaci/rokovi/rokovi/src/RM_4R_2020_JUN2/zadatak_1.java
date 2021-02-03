package RM_4R_2020_JUN2;

import java.io.File;
import java.io.FileNotFoundException;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

//ne uspevam da lepo ucitam matrice

public class zadatak_1 {

    public static void main(String[] args) {
        try(Scanner sc = new Scanner(System.in)){
            System.out.println("Unesi putanju do fajla");
            //String path = sc.nextLine();
            String path = "/home/student/Desktop/rokovi/test/matrice.txt";

            try (Scanner file = new Scanner(new File(path))
                ){

                while(file.hasNext()){
                    String line;
                    List<int[]> matrix = new ArrayList<>();
                    while (!(line = file.nextLine().trim()).equalsIgnoreCase("")){
                        String[] numbers = line.split(" ");
                        //System.out.println(Arrays.deepToString(numbers));
                        int[] nums = new int[numbers.length];
                        for(int i = 0; i<numbers.length; i++){
                            nums[i] = Integer.parseInt(numbers[i]);
                        }
                        matrix.add(nums);
                    }

                    for(int i = 0; i<matrix.size(); i++){
                        System.out.println(Arrays.toString(matrix.get(i)));
                        /*for(int j = 0; j<matrix.get(i).length; j++){
                            System.out.println(matrix.get(i)[j] + " ");
                        }*/
                        System.out.println();
                    }

                }

            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
        }
    }

}
