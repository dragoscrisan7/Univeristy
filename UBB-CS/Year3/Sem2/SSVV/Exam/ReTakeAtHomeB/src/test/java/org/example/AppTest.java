package org.example;

import junit.framework.Test;
import junit.framework.TestCase;
import junit.framework.TestSuite;
import static org.junit.jupiter.api.Assertions.*;

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

    public void testApp()
    {
        assertTrue( true );
    }

    /*
    Blackbox testing

    Equivalence Classes:
    Valid Classes: Arrays with at least one 0 and arrays with no 0.
    Invalid Classes: Although not typically applicable for black-box testing of this method,
    an invalid array (e.g., null array) can be considered.

    1. Array with no failures (all elements are 1).
    2. Array with all failures (all elements are 0).
    3. Array with mixed values (some elements are 1, some are 0).
    4. Empty array.
    5. Single element array (1 or 0).

    Boundary Value Analysis:
    Boundary Values: Arrays with minimum length (0, 1) and arrays with 0 at the start, middle, and end.

    1. Array with a single element.
    2. Array with the smallest size having both 1 and 0.
    3. Large arrays to test performance.
     */

    public void testFindAFailTest_AllPass() {
        int[] testCases = {1, 1, 1, 1};
        assertEquals(-1, App.FindAFailTest(testCases));
    }

    public void testFindAFailTestAllFailures() {
        int[] testCases = {0, 0, 0, 0};
        assertEquals(0, App.FindAFailTest(testCases));
    }

    public void testFindAFailTestMixedValues() {
        int[] testCases = {1, 0, 1, 0};
        assertEquals(1, App.FindAFailTest(testCases));
    }

    public void testFindAFailTestEmptyArray() {
        int[] testCases = {};
        assertEquals(-1, App.FindAFailTest(testCases));
    }

    public void testFindAFailTestSingleElementPass() {
        int[] testCases = {1};
        assertEquals(-1, App.FindAFailTest(testCases));
    }

    public void testFindAFailTestSingleElementFail() {
        int[] testCases = {0};
        assertEquals(0, App.FindAFailTest(testCases));
    }

    public void testFindAFailTest_OneFailAtStart() {
        int[] testCases = {0, 1, 1, 1};
        assertEquals(0, App.FindAFailTest(testCases));
    }

    public void testFindAFailTest_OneFailAtEnd() {
        int[] testCases = {1, 1, 1, 0};
        assertEquals(3, App.FindAFailTest(testCases));
    }


    /*
    Whitebox testing

    Path Coverage:
    Paths for valid and invalid indices.

    1. Normal execution with index within bounds.
    2. Execution with index at the start.
    3. Execution with index at the end.
    4. Execution with index out of bounds (negative and greater than array length).

    Decision/Condition Coverage:
    Ensure all branches (if conditions) are tested.

    1. Test true/false outcomes for if (i != index).
    2. Test the condition if (index < 0 || index >= testCases.length).

    Loop Coverage:
    Single iteration, multiple iterations, zero iterations.

    1. Loop runs zero times (empty array).
    2. Loop runs exactly once (single element array).
    3. Loop runs multiple times (larger arrays).
     */

    public void testEliminateValidPositionStart() {
        int[] testCases = {1, 0, 1, 0};
        int[] expected = {0, 1, 0};
        assertArrayEquals(expected, App.EliminateAnElementOnAPosition(testCases, 0));
    }

    public void testEliminateValidPositionMiddle() {
        int[] testCases = {1, 0, 1, 0};
        int[] expected = {1, 0, 0};
        assertArrayEquals(expected, App.EliminateAnElementOnAPosition(testCases, 2));
    }

    public void testEliminateValidPositionEnd() {
        int[] testCases = {1, 0, 1, 0};
        int[] expected = {1, 0, 1};
        assertArrayEquals(expected, App.EliminateAnElementOnAPosition(testCases, 3));
    }

    public void testEliminateInvalidPositionNegative() {
        int[] testCases = {1, 0, 1, 0};
        assertThrows(IllegalArgumentException.class, () -> {
            App.EliminateAnElementOnAPosition(testCases, -1);
        });
    }

    public void testEliminateInvalidPositionOutOfBounds() {
        int[] testCases = {1, 0, 1, 0};
        assertThrows(IllegalArgumentException.class, () -> {
            App.EliminateAnElementOnAPosition(testCases, 4);
        });
    }

    public void testEliminateEmptyArray() {
        int[] testCases = {};
        assertThrows(IllegalArgumentException.class, () -> {
            App.EliminateAnElementOnAPosition(testCases, 0);
        });
    }

    public void testEliminateAnElementOnAPositionSingleElementArray() {
        int[] testCases = {1};
        int[] expected = {};
        assertArrayEquals(expected, App.EliminateAnElementOnAPosition(testCases, 0));
    }

    /*
    Integration Testing Strategy:
    Top-down Integration: Starting with TestsToSolve,
    ensure it correctly calls and integrates FindAFailTest and EliminateAnElementOnAPosition.

    Top-Down Integration Testing: Start testing from the high-level function TestsToSolve and
    integrate the lower-level functions FindAFailTest and EliminateAnElementOnAPosition step by step.

    Test Cases:

    1. Test with no passing test cases.
    2. Test with all passing test cases.
    3. Test with mixed passing and failing test cases.
    4. Test with an empty array.
    5. Test with a single element array (1 or 0).
     */

    public void testTestsToSolve_AllFail() {
        int[] testCases = {0, 0, 0, 0};
        int[] expected = {1, 2, 3, 4};
        assertArrayEquals(expected, App.TestsToSolve(testCases));
    }

    public void testTestsToSolve_AllPass() {
        int[] testCases = {1, 1, 1, 1};
        int[] expected = {};
        assertArrayEquals(expected, App.TestsToSolve(testCases));
    }

    public void testTestsToSolve_MixedCases() {
        int[] testCases = {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1};
        int[] expected = {2, 3, 4, 7, 9};
        assertArrayEquals(expected, App.TestsToSolve(testCases));
    }

    public void testTestsToSolveEmptyArray() {
        int[] testCases = {};
        int[] expected = {};
        assertArrayEquals(expected, App.TestsToSolve(testCases));
    }

    public void testTestsToSolve_SingleElementPass() {
        int[] testCases = {1};
        int[] expected = {};
        assertArrayEquals(expected, App.TestsToSolve(testCases));
    }

    public void testTestsToSolve_SingleElementFail() {
        int[] testCases = {0};
        int[] expected = {1};
        assertArrayEquals(expected, App.TestsToSolve(testCases));
    }
}
