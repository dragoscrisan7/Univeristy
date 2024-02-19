// Demo for cascading futures with continuations.
// The program computes a sum of numbers.
// For this purpose, it creates one task for each number. The task gets the result from the previous
//    task and adds the current number.

using System;
using System.Threading.Tasks;

namespace test_csharp
{
    static class Program
    {
        static int add(Task<int> a, int b)
        {
            return a.Result + b;
        }

        static void Main(string[] args)
        {
            int[] numbers = { 10, 20, 30, 40};
            Task<int> t = Task.FromResult(0);
            foreach(int v in numbers)
            {
                t = t.ContinueWith((a) => add(a, v));
            }

            Console.WriteLine("Result={0}\n", t.Result);
        }
    }
}