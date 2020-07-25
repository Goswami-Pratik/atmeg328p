using System;
using System.IO.Ports;
using System.Threading;

namespace aa
{
    class Program
    {
        static void Main(string[] args)
        {
            SerialPort port = new SerialPort();

            port.BaudRate = 9600;
            port.Parity = Parity.None;
            port.StopBits = StopBits.One;
            port.PortName = "COM5";
            port.DataBits = 8;
            port.Handshake = Handshake.None;
            port.RtsEnable = true;
            port.DtrEnable = true;

            port.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);

            port.Open();

            while (true)
            {
                string c = Console.ReadLine();
                port.WriteLine(c);
            }
        }

        private static void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            SerialPort sp = (SerialPort)sender;
            string indata = sp.ReadExisting();
            Console.Write(indata);
        }
    }
}
