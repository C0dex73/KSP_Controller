/*
 * Console Application developped by CODEX in 2023
 * interact with ksp from an external micro-controller
 * 
 * **************************** IMPORTANT ****************************
 * Krcp needed
 * Read commands.txt to know how to communicate with it
 * Use config.cfg or type config in the console at start to setup your environnement
 * 
 * THIS IS NOT THE MAIN PROGRAM !
 * VOID MAIN() IS IN PROGRAM.CS
 */
using KRPC.Client;
using KRPC.Client.Services.SpaceCenter;
using System.IO;
using System;
 
namespace KSP_Communication
{
    public class Config
    {
        string mainLog;
        string comPort;
        int baudRate;

        public Config(string cfgAdr)
        {
            string[] cfg = File.ReadAllLines(cfgAdr);

            mainLog = cfg[0].Split("=")[1];
            comPort = cfg[1].Split("=")[1];
            try
            {
                baudRate = int.Parse(cfg[2].Split("=")[1]);
            }
            catch(Exception e)
            {
                Console.WriteLine("Something went wrong with the baudRate conversion ! Check the baudrate value in config.cfg (must be an int).");
                Console.WriteLine("[" + e.Message + "]");
                Console.WriteLine("The baudRate is set for this runtime to the default value : 9600");
                baudRate = 9600;
            }
        }

        public void Set()
        {

        }

        public void Get()
        {

        }
    }

    class GameData
    {
        readonly public Connection connection;
        public Vessel vessel;
        public Flight flightScene;

#pragma warning disable CS8618 //can't see that it will not be null by update()
        public GameData(Connection connection)
#pragma warning restore CS8618
        {
            this.connection = connection;
            update();
        }

        //called every tick and when created, update the data
        public void update()
        {
            vessel = connection.SpaceCenter().ActiveVessel;
            flightScene = vessel.Flight(vessel.Orbit.Body.ReferenceFrame);

        }
    }
}