package org.example;

import java.util.ArrayList;
import java.util.List;

public class App {
    public static void main(String[] args) {
        int[] testCases = {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1};
        int[] result = TestsToSolve(testCases);

        for (int testCase : result) {
            System.out.print(testCase + " ");
        }
    }

    public static int FindAFailTest(int[] testCases) {
        for (int i = 0; i < testCases.length; i++) {
            if (testCases[i] == 0) {
                return i;
            }
        }
        return -1;
    }

    public static int[] EliminateAnElementOnAPosition(int[] testCases, int index) {
        if (index < 0 || index >= testCases.length) {
            throw new IllegalArgumentException("Index out of bounds");
        }
        int[] newTestCases = new int[testCases.length - 1];
        for (int i = 0, j = 0; i < testCases.length; i++) {
            if (i != index) {
                newTestCases[j++] = testCases[i];
            }
        }
        return newTestCases;
    }

    public static int[] TestsToSolve(int[] testCases) {
        List<Integer> result = new ArrayList<>();
        int[] remainingTestCases = testCases.clone();
        int failTestsFound = 0;

        while (true) {
            int failIndex = FindAFailTest(remainingTestCases);
            if (failIndex == -1) {
                break;
            }
            result.add(failTestsFound + failIndex + 1);
            failTestsFound++;
            remainingTestCases = EliminateAnElementOnAPosition(remainingTestCases, failIndex);
        }

        int[] newArray = new int[result.size()];
        for (int i = 0; i < result.size(); i++) {
            newArray[i] = result.get(i);
        }
        return newArray;
    }
}