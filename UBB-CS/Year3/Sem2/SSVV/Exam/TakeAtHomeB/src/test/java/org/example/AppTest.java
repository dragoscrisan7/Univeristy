package org.example;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertArrayEquals;

public class AppTest
    extends TestCase
{
    public AppTest( String testName )
    {
        super( testName );
    }

    public static Test suite()
    {
        return new TestSuite( AppTest.class );
    }

    public void testFindPairNoPairs() {
        int[] animals = {1, 3, 4, 1, 3, 4};
        List<Integer> result = App.findPair(animals);
        assertTrue(result.isEmpty());
    }

    public void testFindPairOneMouseCat() {
        int[] animals = {1, 2, 4, 3};
        List<Integer> result = App.findPair(animals);
        assertEquals(1, result.size());
        assertEquals(Integer.valueOf(1), result.get(0));
    }

    public void testFindPairOneCatDog() {
        int[] animals = {2, 3, 4, 1};
        List<Integer> result = App.findPair(animals);
        assertEquals(1, result.size());
        assertEquals(Integer.valueOf(1), result.get(0));
    }

    public void testFindPairMultiplePairs() {
        int[] animals = {1, 2, 3, 2, 1, 2, 2};
        List<Integer> result = App.findPair(animals);
        assertEquals(5, result.size());
        assertEquals(Integer.valueOf(1), result.get(0));
        assertEquals(Integer.valueOf(2), result.get(1));
        assertEquals(Integer.valueOf(3), result.get(2));
        assertEquals(Integer.valueOf(4), result.get(3));
        assertEquals(Integer.valueOf(5), result.get(4));
    }

    public void testFindPairEmptyArray() {
        int[] animals = {};
        List<Integer> result = App.findPair(animals);
        assertTrue(result.isEmpty());
    }

    public void testFindPairSingleElement() {
        int[] animals = {1};
        List<Integer> result = App.findPair(animals);
        assertTrue(result.isEmpty());
    }

    public void testFindPairTwoElements() {
        int[] animals = {1, 2};
        List<Integer> result = App.findPair(animals);
        assertEquals(1, result.size());
        assertEquals(Integer.valueOf(1), result.get(0));
    }

    public void testFindPairBoundaryStart() {
        int[] animals = {1, 2, 4, 4, 1};
        List<Integer> result = App.findPair(animals);
        assertEquals(1, result.size());
        assertEquals(Integer.valueOf(1), result.get(0));
    }

    public void testFindPairBoundaryEnd() {
        int[] animals = {3, 4, 1, 2};
        List<Integer> result = App.findPair(animals);
        assertEquals(1, result.size());
        assertEquals(Integer.valueOf(3), result.get(0));
    }

    public void testInsertCowStart() {
        int[] animals = {1, 2, 3};
        int[] result = App.insertCow(animals, 0);
        int[] expected = {4, 1, 2, 3};
        assertArrayEquals(expected, result);
    }
    public void testInsertCowMiddle() {
        int[] animals = {1, 2, 3};
        int[] result = App.insertCow(animals, 1);
        int[] expected = {1, 4, 2, 3};
        assertArrayEquals(expected, result);
    }

    public void testInsertCowEnd() {
        int[] animals = {1, 2, 3};
        int[] result = App.insertCow(animals, 2);
        int[] expected = {1, 2, 4, 3};
        assertArrayEquals(expected, result);
    }

    public void testInsertCowEmptyArray() {
        int[] animals = {};
        int[] result = App.insertCow(animals, 0);
        int[] expected = {4};
        assertArrayEquals(expected, result);
    }

    public void testInsertCowSingleElement() {
        int[] animals = {1};
        int[] result = App.insertCow(animals, 1);
        int[] expected = {1, 4};
        assertArrayEquals(expected, result);
    }

    public void testInsertCowSingleElementStart() {
        int[] animals = {1};
        int[] result = App.insertCow(animals, 0);
        int[] expected = {4, 1};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsNoPairs() {
        int[] animals = {1, 3, 4, 1, 3, 4};
        int[] result = App.beFriends(animals);
        int[] expected = {1, 3, 4, 1, 3, 4};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsOnePair() {
        int[] animals = {1, 2, 4, 3};
        int[] result = App.beFriends(animals);
        int[] expected = {1, 4, 2, 4, 3};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsMultiplePairs() {
        int[] animals = {1, 2, 3, 2, 1, 2, 2};
        int[] result = App.beFriends(animals);
        int[] expected = {1, 4, 2, 4, 3, 4, 2, 4, 1, 4, 2, 2};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsEmptyArray() {
        int[] animals = {};
        int[] result = App.beFriends(animals);
        int[] expected = {};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsSingleElement() {
        int[] animals = {1};
        int[] result = App.beFriends(animals);
        int[] expected = {1};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsTwoElements() {
        int[] animals = {1, 2};
        int[] result = App.beFriends(animals);
        int[] expected = {1, 4, 2};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsBoundaryStart() {
        int[] animals = {1, 2, 4, 4, 1};
        int[] result = App.beFriends(animals);
        int[] expected = {1, 4, 2, 4, 4, 1};
        assertArrayEquals(expected, result);
    }

    public void testBeFriendsBoundaryEnd() {
        int[] animals = {3, 4, 1, 2};
        int[] result = App.beFriends(animals);
        int[] expected = {3, 4, 1, 4, 2};
        assertArrayEquals(expected, result);
    }

    public void testApp()
    {
        assertTrue( true );
    }
}
