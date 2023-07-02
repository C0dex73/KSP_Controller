/*
 * Console Application developped by CODEX in 2023
 * interact with ksp from an external micro-controller
 * 
 * **************************** IMPORTANT ****************************
 * Krcp needed
 * Read commands.txt to know how to communicate with it
 * Use config.cfg or type config in the console at start to setup your environnement
 * 
 * 
 */
using KRPC.Client;
using System.IO.Ports;

namespace KSP_Communication {

    class Program
    {
        private static double oldMach = 0;

        public static void Main()
        {
            //Setup environnement and get ControlBoard and KSP connections
            Tuple<bool, SerialPort, Connection, bool> configResult = Configuration();
            
            //if the Configuration didn't Failed (KSP and controlBoard (only if not console commands) connected)
            if (configResult.Item4)
            {
                //Execute instructionsk
                OnWork(configResult);
            }

            //shutdown
            configResult.Item2.Close();
            ConsoleHandler.WriteLine("CONNECTION SHUTTED DOWN", LogLevel.Info);
            Console.ReadKey();
        }

        #region SubScripts

        //Check if all needed parts are here and working
        private static Tuple<bool, SerialPort, Connection, bool> Configuration()
        {
            //delete latest.log as it will be recreated later on
            File.Delete("latest.log");

            //dict to convert YesnNo answer to boolean
            IDictionary<string, bool> cCommandsStr2Bool = new Dictionary<string, bool>()
            {
                {"Y", true},
                {"N", false },
                {"YES", true },
                {"NO", false }
            };

            //Ask if commands are coming from external controller or the internal console
            bool cCommand;
            while (true) {
                ConsoleHandler.WriteLine("Console Commands (Y/N) ?", LogLevel.Default, true);
#pragma warning disable 8600 //nullable string handled below [anwser = anwser == null ? "" : anwser.ToUpper();]
                string anwser = Console.ReadLine();
#pragma warning restore 8600
                anwser = anwser == null ? "" : anwser.ToUpper();
                if (cCommandsStr2Bool.ContainsKey(anwser))
                {
                    cCommand = cCommandsStr2Bool[anwser];
                    break;
                }
                ConsoleHandler.WriteLine("Wrong Input", LogLevel.Default, true);
            }

            
            //Ask the type of informations to display in the console while running (latest.log will contain a log level of : Debug)
            ConsoleHandler.WriteLine("LogLevel ? {Debug, Info, Commentary, Warning}", LogLevel.Default, true);
            while (ConsoleHandler.consoleLogLevel == LogLevel.Default)
            {
#pragma warning disable 8604 //nullable string handled in LogLevelFromString(string str)
                ConsoleHandler.consoleLogLevel = ConsoleHandler.LogLevelFromString(Console.ReadLine());
#pragma warning restore 8604
            }
            ConsoleHandler.WriteLine("LogLevel choosen : " + nameof(ConsoleHandler.consoleLogLevel), LogLevel.Debug);

            //Check if Arduino com is ready, only if console commands are disabled
            SerialPort serialPort = new("COM6", 9600);
            if (!cCommand)
            {
                try
                {
                    serialPort.Open();
                }
                catch (FileNotFoundException)
                {
                    //if not stop the configuration and return the check as false
                    ConsoleHandler.WriteLine("ControlBoard not detected", LogLevel.Warning);
#pragma warning disable 8625 //is null only if Item4 is false so it won't be used
                    return new Tuple<bool, SerialPort, Connection, bool>(cCommand, new SerialPort(), null, false);
#pragma warning restore 8625
                }
                //if it is say it
                ConsoleHandler.WriteLine("ControlBoard connected", LogLevel.Debug);
            }
            
            //check if the kRCP com is ready
            Connection connection;
            try
            {
                connection = new Connection();
            }
            catch (System.Net.Sockets.SocketException)
            {
                //if not stop the configuration and return the check as false
                ConsoleHandler.WriteLine("Could not connect to KRPC Server. Make sure the server is started and the adress is good", LogLevel.Debug);
#pragma warning disable 8625
                return new Tuple<bool, SerialPort, Connection, bool>(cCommand, serialPort, null, false);
#pragma warning restore 8625
            }
            //if it is say it
            ConsoleHandler.WriteLine("Connected to KRCP server", LogLevel.Debug);
            return new Tuple<bool, SerialPort, Connection, bool>(cCommand, serialPort, connection, true);
        }

        //Setup done, now listening for instructions
        private static void OnWork(Tuple<bool, SerialPort, Connection, bool> parameters)
        {
            //initiate the class that will hold the gameData
            GameData gameData = new(parameters.Item3);

            //work loop
            bool onWork = false;
            while (true)
            {
#pragma warning disable 8600 //null instruction handled 
                string instruction = parameters.Item1 ? Console.ReadLine() : parameters.Item2.ReadLine();
#pragma warning restore 8600
                if (!string.IsNullOrEmpty(instruction))
                {
                    ConsoleHandler.WriteLine(String.Format("Received instruction from {0} : {1}", parameters.Item1 ? "Console" : "ControlBoard", instruction), LogLevel.Debug);
                    //instructions are read by the program in maj only
                    instruction = instruction.ToUpper();

                    //instruction HALT corresponding to the end of the arduino-sided program
                    if (instruction == "HALT")
                    {
                        ConsoleHandler.WriteLine("CONNECTION SHUTING DOWN with instruction : HALT", LogLevel.Info);
                        break;
                    }
                    else if (instruction == "START")
                    {
                        onWork = true;
                        ConsoleHandler.WriteLine("All systems go for launch !", LogLevel.Commentary);
                    }

                    if (onWork)
                    {
                        Tick(gameData);
                        Instructions.instructionDict[instruction.Split(' ')[0]](instruction.Split(' '), gameData);
                    }
                }
            }
        }

        //Will appen every iteration of the main loop
        private static void Tick(GameData gameData)
        {
            //update the game data
            gameData.update();

            #region SoundTraveller
            //Calculating the number of Mach the vessel is at
            double Mach = gameData.flightScene.Speed / gameData.flightScene.SpeedOfSound;

            /*
             * I know that's akward but I dont care
             * subsonique below M0.8
             * transsonique between M0.8 and M1.2
             * supersonique between M1.2 and M5
             * hypersonique above M5
             */
            if (Mach >= 0.8 && oldMach < 0.8)
            {
                ConsoleHandler.WriteLine(gameData.vessel.Name + " is now transsonique.", LogLevel.Commentary);
            }
            else if (Mach <= 0.8 && oldMach > 0.8)
            {
                ConsoleHandler.WriteLine(gameData.vessel.Name + " is now subsonique.", LogLevel.Commentary);
            }
            else if (Mach >= 1.2 && oldMach < 1.2)
            {
                ConsoleHandler.WriteLine(gameData.vessel.Name + " is now supersonique.", LogLevel.Commentary);
            }
            else if (Mach <= 1.2 && oldMach > 1.2)
            {
                ConsoleHandler.WriteLine(gameData.vessel.Name + " is now transsonique.", LogLevel.Commentary);
            }
            else if (Mach >= 5 && oldMach > 5)
            {
                ConsoleHandler.WriteLine(gameData.vessel.Name + " is now hypersonique.", LogLevel.Commentary);
            }
            else if (Mach <= 5 && oldMach > 5)
            {
                ConsoleHandler.WriteLine(gameData.vessel.Name + " is now supersonique.", LogLevel.Commentary);
            }
            #endregion
        }

        #endregion
    }

    //handle all console-related needs
    public static class ConsoleHandler
    {
        public static LogLevel consoleLogLevel = LogLevel.Default;
        private static IDictionary<LogLevel, int> logLevelValues = new Dictionary<LogLevel, int>()
        {
            { LogLevel.Default, -1 },
            {LogLevel.Debug, 0},
            {LogLevel.Warning, 1},
            {LogLevel.Info, 2},
            {LogLevel.Commentary, 3}
        };

        //the same as classic console.WriteLine() but with a logLevel filter
        public static void WriteLine(string msg, LogLevel logLevel, bool Override=false)
        {
            //Write in console if the logLevel is High enought
            if (logLevelValues[logLevel] >= logLevelValues[consoleLogLevel] || Override) {
                
                Console.WriteLine(msg);
            }

            //Write in latest.log
            

            using StreamWriter fs = File.AppendText("latest.log");
            {
                fs.WriteLine(DateTime.Now.ToString() + " --> " + msg);
            }
        }

        //Transform a string into a logLevel
        public static LogLevel LogLevelFromString(string str)
        {
            if (str != null)
            {
                IDictionary<string, LogLevel> logLevelFromString = new Dictionary<string, LogLevel>()
                {
                    { "DEBUG", LogLevel.Debug },
                    { "WARNING", LogLevel.Warning },
                    { "INFO", LogLevel.Info },
                    { "COMMENTARY", LogLevel.Commentary }
                };
                str = str.ToUpper();
                if (logLevelFromString.ContainsKey(str)) { return logLevelFromString[str]; }
            }
            Console.WriteLine("ERROR : choose between {Debug, Info, Commentary, Warning}");
            return LogLevel.Default;
        }

        public static string BoolToOnOff(bool test, string msgBefore = "", string msgAfter = "")
        {
            return msgAfter.Insert(0, test ? "On" : "Off").Insert(0, msgBefore);
        }
    }

    //LogLevel will handle what to display or not into the console
    public enum LogLevel { Default, Debug, Info, Commentary, Warning };
    public static class CommandChecker
    {
        public static void Check(string cmd)
        {
            
        }
    }
}