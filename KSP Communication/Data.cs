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
 
namespace KSP_Communication
{
    public class Config
    {
        
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
