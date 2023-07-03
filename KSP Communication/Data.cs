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
using System.Dynamic;
using System.ComponentModel;
using System.Net;
 
namespace KSP_Communication
{
    public class Config : DynamicObject
    {
        //Class data stored in a dict
        protected readonly Dictionary<string, dynamic?> source = new() { };

        public Config(string cfgAdr)
        {
            //Read config file's lines
            foreach (string line in File.ReadAllLines(cfgAdr))
            {
                //null and commentary lines handled
                if (!line.StartsWith('#') && line != "")
                {
                    //Conversion from cfg to dict
                    try
                    {
                        //Split the line in 3 groups
                        string name = line.Split(":")[0].Replace(" ", "");
                        Type? type = Type.GetType(line.Split("=")[0].Split(":")[1].Replace(" ", ""));
                        string value = line.Split("=")[1].Replace(" ", "");

                        //Debug each processed line
                        ConsoleHandler.WriteLine("Converting " + name + line.Split("=")[0].Split(":")[1].Replace(" ", "") + value + " to an object of Config().", LogLevel.Debug, hold:true);

                        //Handle incorrect Type
                        if (type == null) { throw new Exception("Type not recognized"); }

                        //Add this line to the source dict
                        //old : source.Add(name, Convert.ChangeType(value,type));
                        source.Add(name, Conversion(type, value));
                    }
                    catch (Exception e)
                    {
                        ConsoleHandler.WriteLine("ERROR while converting config.cfg to C# class : " + e.Message + " in " + line, LogLevel.Debug, hold:true);
                    }
                }
            }
        }

        private static dynamic? Conversion(Type type, string value)
        {
            if (type.Name == "IPAddress")
            {
                return IPAddress.Parse(value);
            }
            return TypeDescriptor.GetConverter(type).ConvertFrom(value);
        }

        public override bool TryGetMember(GetMemberBinder binder, out object? result)
        {
            result = null;
            return source.TryGetValue(binder.Name, out result);
        }
    }

    public class GameData
    {
        readonly public Connection connection;
        public Vessel vessel;
        public Flight flightScene;

#pragma warning disable CS8618 //can't see that it will not be null when update() will be called
        public GameData(Connection connection)
#pragma warning restore CS8618
        {
            this.connection = connection;
            Update();
        }

        //called every tick and when created, update the data
        public void Update()
        {
            vessel = connection.SpaceCenter().ActiveVessel;
            flightScene = vessel.Flight(vessel.Orbit.Body.ReferenceFrame);
        }
    }
}