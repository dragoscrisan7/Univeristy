package org.example;

import java.util.ArrayList;
import java.util.List;

public class App
{
    public static void main( String[] args )
    {
        int[] animals = {1, 2, 3, 4, 3, 2, 1, 1, 2, 3, 1};
        int[] result = beFriends(animals);

        for(int animal : result) {
            System.out.print(animal + " ");
        }
    }

    // Method to find pairs
    public static List<Integer> findPair(int[] animals) {
        List<Integer> pairs = new ArrayList<>();
        for (int i = 0; i < animals.length - 1; i++) {
            if ((animals[i] == 1 && animals[i + 1] == 2) ||
                    (animals[i] == 2 && animals[i + 1] == 3) ||
                    (animals[i] == 2 && animals[i + 1] == 1) ||
                    (animals[i] == 3 && animals[i + 1] == 2)) {
                pairs.add(i + 1);
            }
        }
        return pairs;
    }

    // Method to insert cow at a specific position
    public static int[] insertCow(int[] animals, int index) {
        int[] newAnimals = new int[animals.length + 1];
        boolean cowInserted = false;
        for (int i = 0, j = 0; i < animals.length; i++, j++) {
            if (i == index && !cowInserted) {
                newAnimals[j++] = 4; // Insert cow (4)
                cowInserted = true;
            }
            newAnimals[j] = animals[i];
        }
        if (!cowInserted) {
            newAnimals[animals.length] = 4;
        }
        return newAnimals;
    }

    // Method to solve the problem
    public static int[] beFriends(int[] animals) {
        List<Integer> pairs = findPair(animals);
        int offset = 0;
        for (int index : pairs) {
            animals = insertCow(animals, index + offset);
            offset++;
        }
        return animals;
    }
}