// Demo for cascading futures with continuations, with additionally a ContinueWhenAll() operation.
// The program computes a sum of numbers from a vector.
// For this purpose, it creates a number of tasks, each summing up a chunk of the vector,
//    plus a final task that sums up the results of those chunks.
// The final tasks starts its execution only when all the tasks that sum up a chunk have completed

using System;
using System.Threading;
using System.Threading.Tasks;

namespace test_csharp
{
    static class Program
    {
        static int addChunk(int[] numbers, int beginIdx, int endIdx)
        {
            int sum = 0;
            for(int i= beginIdx; i< endIdx; ++i)
            {
                sum += numbers[i];
            }
            return sum;
        }

        static int add2(Task<int>[] tasks1)
        {
            int sum = 0;
            foreach(Task<int> t in tasks1)
            {
                sum += t.Result;
            }
            return sum;
        }

        static void Main(string[] args)
        {
            int nrNumbers = 10000;
            int nrAdders1 = 100;
            int[] numbers = new int[nrNumbers];
            for(int i=0; i<nrNumbers; ++i)
            {
                numbers[i] = i;
            }

            Task<int>[] tasks1 = new Task<int>[nrAdders1];
            for(int i=0; i<nrAdders1; ++i)
            {
                int begin = (numbers.Length*i)/nrAdders1;
                int end = (numbers.Length * (i+1)) / nrAdders1;
                tasks1[i] = Task.Factory.StartNew(() => addChunk(numbers, begin, end));
            }

            Task<int> taskFinal = Task.Factory.ContinueWhenAll(tasks1, add2);

            Console.WriteLine("Result={0}\n", taskFinal.Result);
        }
    }
}