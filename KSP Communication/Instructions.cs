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
using KRPC.Client.Services.SpaceCenter;

namespace KSP_Communication
{
    static class Instructions
    {
        // control all sas parameters
        static public void SAS(string[] parameters, GameData gameData)
        {
            //dict to convert string to SAS modes
            IDictionary<string, SASMode> sasModes = new Dictionary<string, SASMode>()
            {
                {"PG", SASMode.Prograde},
                {"RG", SASMode.Retrograde },
                {"NO", SASMode.Normal },
                {"AN", SASMode.AntiNormal },
                {"RD", SASMode.Radial },
                {"AR", SASMode.AntiRadial },
                {"MV", SASMode.Maneuver },
                {"ST", SASMode.StabilityAssist },
                {"TA", SASMode.Target },
                {"AT", SASMode.AntiTarget }
            };

            //if the command specify a sas mode then get it and set it
            if (parameters[1] == "MODE")
            {
                gameData.vessel.Control.SASMode = sasModes[parameters[2]];
                ConsoleHandler.WriteLine("SAS mode set to " + sasModes[parameters[2]].ToString(), LogLevel.Info);
            }
            //else it specify if it is on or off, get the state and set it
            else
            {
                bool sas = Convert.ToBoolean(Convert.ToInt32(parameters[1]));
                if (sas) { ConsoleHandler.WriteLine("SAS going on", LogLevel.Info); }
                else { ConsoleHandler.WriteLine("SAS going off", LogLevel.Info); }
                gameData.vessel.AutoPilot.SAS = sas;
            }
        }

        //control all rcs parameters
        static public void RCS(string[] parameters, GameData gameData)
        {
            //RCD command specify the state (on/off) so get it and set it
            bool rcs = Convert.ToBoolean(Convert.ToInt32(parameters[1]));
            if (rcs) { ConsoleHandler.WriteLine("RCS going on", LogLevel.Info); }
            else { ConsoleHandler.WriteLine("RCS going off", LogLevel.Info); }
            gameData.vessel.AutoPilot.SAS = rcs;
        }

        //control staging
        static public void Stage(string[] parameters, GameData gameData)
        {
            //enable next stage (equal to spacebar in KSP no keybind modifications made)
            gameData.vessel.Control.ActivateNextStage();
            ConsoleHandler.WriteLine("Stage separation confirmed", LogLevel.Commentary);
        }

        //control action groups
        static public void Action(string[] parameters, GameData gameData)
        {
            //dict to convert string to Actions
            IDictionary<string, Action<string[], Vessel>> subActionInstruction = new Dictionary<string, Action<string[], Vessel>>()
            {
                {"BR", Break },
                {"GR", Gears },
                {"LI", Lights },
                {"AB", Abort }
            };
            
            //if it is a special action group execute the corresponding void
            if (subActionInstruction.ContainsKey(parameters[1]))
            {
                subActionInstruction[parameters[1]](parameters, gameData.vessel);
            }
            //else execute basic action group instructions handled by kRCP
            else
            {
                gameData.vessel.Control.SetActionGroup(Convert.ToUInt32(parameters[1]), Convert.ToBoolean(Convert.ToInt32(parameters[2])));
            }

            //handle special action group "Breakes"
            static void Break(string[] parameters, Vessel vessel)
            {
                vessel.Control.Brakes = Convert.ToBoolean(Convert.ToInt32(parameters[2]));
                ConsoleHandler.WriteLine(ConsoleHandler.BoolToOnOff(vessel.Control.Brakes, "Breakes going "), LogLevel.Info);
            }

            //handle special action group "Lights"
            static void Lights(string[] parameters, Vessel vessel)
            {
                vessel.Control.Lights = Convert.ToBoolean(Convert.ToInt32(parameters[2]));
                ConsoleHandler.WriteLine(ConsoleHandler.BoolToOnOff(vessel.Control.Lights, "Lights going "), LogLevel.Info);
            }

            //handle special action group "Gear"
            static void Gears(string[] parameters, Vessel vessel)
            {
                vessel.Control.Gear = Convert.ToBoolean(Convert.ToInt32(parameters[2]));
                ConsoleHandler.WriteLine(ConsoleHandler.BoolToOnOff(vessel.Control.Gear, "Gears going "), LogLevel.Info);
            }

            //handle special action group "Abort"
            static void Abort(string[] parameters, Vessel vessel)
            {
                vessel.Control.Abort = Convert.ToBoolean(Convert.ToInt32(parameters[2]));
                ConsoleHandler.WriteLine(@"/!\ WE HAVE AN ABORT /!\", LogLevel.Commentary);
            }
        }

        //control the thrust
        static public void Thrust(string[] parameters, GameData gameData)
        {
            float value = (float)Convert.ToDecimal(parameters[1]);
            gameData.vessel.Control.Throttle = value;
            ConsoleHandler.WriteLine("Throttle set at " + (value * 100).ToString() + "%", LogLevel.Info);
        }
        
        //control the request command to give gameedata to the controller
        static public void Request(string[] parameters, GameData gameData)
        {
            
        }

        //control the Maneuvers in flight Scene
        static public void Maneuver(string[] parameters, GameData gameData)
        {
            //if the command is to create a node, it will be created a minute ahead
            if(parameters[1] == "CREATE") {
                gameData.vessel.Control.AddNode(gameData.connection.SpaceCenter().UT+60);
                ConsoleHandler.WriteLine("Node Created", LogLevel.Info);
            }
            else if (gameData.vessel.Control.Nodes.Count != 0)
            {
                if (parameters[1] == "DELETE") { gameData.vessel.Control.Nodes.First<Node>().Remove(); }
                else
                {
                    //for each type of modif, a parameter in the first node is modified
                    Dictionary<string, Action<double>> modif = new Dictionary<string, Action<double>>()
                    {
                        {"PR", (double i) => {gameData.vessel.Control.Nodes.First<Node>().Prograde += i; } },
                        {"RA", (double i) => {gameData.vessel.Control.Nodes.First<Node>().Radial += i; } },
                        {"NO", (double i) => {gameData.vessel.Control.Nodes.First<Node>().Normal += i; } },
                        {"TI", (double i) => {gameData.vessel.Control.Nodes.First<Node>().UT += i; } }
                    };

                    modif[parameters[1]](Convert.ToDouble(parameters[2]));
                    ConsoleHandler.WriteLine("Node modified : " + parameters[1] + parameters[2], LogLevel.Debug);
                }
            }
        }

        static public void Message(string[] parameters, GameData gameData)
        {
            ConsoleHandler.WriteLine(parameters[1], ConsoleHandler.LogLevelFromString(parameters[2]));
        }

        //contain all the commands (withoput arguments)
        public static IDictionary<string, Action<string[], GameData>> instructionDict = new Dictionary<string, Action<string[], GameData>>()
        {
            {"SAS", SAS},
            {"RCS", RCS},
            {"STAGE", Stage},
            {"THRUST", Thrust},
            {"MANEUVER", Maneuver},
            {"REQUEST", Request},
            {"MSG", Message }
        };
    }
}