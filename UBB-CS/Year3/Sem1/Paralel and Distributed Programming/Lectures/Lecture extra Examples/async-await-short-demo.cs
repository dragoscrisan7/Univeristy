// A server that accepts pairs of numbers, transmitted as text and separated by whitespace, and sends back their sums

using System;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Threading.Tasks;

class Client
{

    static void Sleep()
    {
        System.Console.WriteLine("Before sleep");
        Thread.Sleep(2000);
        System.Console.WriteLine("After sleep");
    }
    static Task Wait1()
    {
        System.Console.WriteLine("Before StartNew()");
        Task ret = Task.Factory.StartNew(() => Sleep());
        System.Console.WriteLine("After StartNew()");
        return ret;
    }

    static async Task Wait2()
    {
        System.Console.WriteLine("Before1");
        await Wait1();
        System.Console.WriteLine("After1");
    }

    public static void Main(string[] args)
    {
        Task t = Wait2();//Task.Factory.StartNew(Wait2).Unwrap();
        System.Console.WriteLine("Before");
        t.Wait();
        System.Console.WriteLine("After");
    }
}