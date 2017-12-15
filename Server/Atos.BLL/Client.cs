using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Atos.BLL
{
    public class Client
    {
        public static string GetStatusByClientId(int clientId, int taskId)
        {
            var message = DBAccess.DBAccess.GetClientStatusByTaskId(clientId, taskId);
            int status = 0;
            if (message != null)
            {
                status = message.PayloadArg0;
            }
            return GetStatusTextByIdAndCode(clientId, status);
        }

        public static string GetStatusTextByIdAndCode(int clientId, int statusCode)
        {
            switch (clientId)
            {
                case 1:
                    switch (statusCode)
                    {
                        case 0:
                            return "Init";
                        case 1:
                            return "Paused";
                        case 2:
                            return "Standby";
                        case 3:
                            return "Sweep";
                        case 4:
                            return "Back";
                        case 5:
                            return "Turn right";
                        case 6:
                            return "Turn left";
                        case 7:
                            return "Tare";
                        case 8:
                            return "Pre-dump";
                        case 9:
                            return "Dump";
                        case 10:
                            return "Forward tare";
                        case 11:
                            return "End";
                        case 12:
                            return "Max State";

                        default:
                            return "<Unknown>";
                    }
                case 2:
                    switch (statusCode)
                    {
                        case 1:
                            return "Waiting for Start";
                        case 2:
                            return "Travel to Lori";
                        case 3:
                            return "Arrive at Lori";
                        case 4:
                            return "Waiting for Lori";
                        case 5:
                            return "Travel to Crane";
                        case 6:
                            return "Arrive at Crane";
                        case 7:
                            return "Waiting for Crane";
                        case 8:
                            return "Stopped";
                        default:
                            return "Waiting for Lori";
                    }
                case 3:
                    switch (statusCode)
                    {
                        case 1:
                            return "Getting Ready";
                        case 2:
                            return "Ready";
                        case 3:
                            return "Loading";
                        default:
                            return "Ready";
                    }
                case 4:
                    switch (statusCode)
                    {
                        case 1:
                            return "Idle";
                        case 2:
                            return "Busy";
                        case 3:
                            return "ATTENTION REQUIRED!";
                        default:
                            return "<Unknown>";
                    }
                default:
                    return "<Unknown>";
            }
        }
    }
}
