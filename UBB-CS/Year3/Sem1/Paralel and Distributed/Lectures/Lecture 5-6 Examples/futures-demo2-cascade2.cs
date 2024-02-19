// Demo for cascading futures with continuations.
// The program computes a sum of numbers.
// For this purpose, it creates one task for each number. The task gets the result from the previous
//    task and adds the current number.
// Unlike the other example, the computation actual execution is deliberately postponed until after
//    is fully set up.

using System;
using System.Threading;
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
            TaskCompletionSource<int> start = new TaskCompletionSource<int>();
            Task<int> t = start.Task;
            foreach(int v in numbers)
            {
                t = t.ContinueWith((a) => add(a, v));
            }

            // Up to here, the computation set up is done
            Console.WriteLine("Before starting");
            Thread.Sleep(TimeSpan.FromSeconds(3));
            start.SetResult(0); // this actually starts the computation
            Console.WriteLine("Result={0}\n", t.Result);
        }
    }
}