using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace Utility
{
    public class Json
    {
        public static bool ValidateJson(string strInput)
        {
            strInput = strInput.Trim();
            if ((strInput.StartsWith("{") && strInput.EndsWith("}")) || //For object
                (strInput.StartsWith("[") && strInput.EndsWith("]"))) //For array
            {
                try
                {
                    var obj = JToken.Parse(strInput);
                    return true;
                }
                catch (JsonReaderException jex)
                {
                    //Exception in parsing json
                    Log.Write(Constant.LogTypeException, jex.Message);
                    return false;
                }
                catch (Exception ex) //some other exception
                {
                    Log.Write(Constant.LogTypeException, ex.Message);
                    return false;
                }
            }
            return false;
        }

        public static JObject JsonParseObject(string jString)
        {
            return JObject.Parse(jString);
        }

        public static int JsonParseId(JObject jObject)
        {
            return (int)jObject["id"];
        }

        public static int JsonParseSequence(JObject jObject)
        {
            return (int)jObject["seq"];
        }

        public static string JsonParseType(JObject jObject)
        {
            return (string)jObject["tp"];
        }

        public static int JsonParseTargetId(JObject jObject)
        {
            return (int)jObject["tgt"];
        }

        public static int JsonParseTaskNumber(JObject jObject)
        {
            return (int)jObject["tsk"];
        }

        public static int JsonParseArg0(JObject jObject)
        {
            return (int)jObject["0"];
        }

        public static int JsonParseArg1(JObject jObject)
        {
            return (int)jObject["1"];
        }
        public static int JsonParseArg2(JObject jObject)
        {
            return (int)jObject["2"];
        }
        public static int JsonParseArg3(JObject jObject)
        {
            return (int)jObject["3"];
        }

        public static string CreateSendJson(int id, int seq, string tp, int tgt, int tsk, int arg0, int arg1, int arg2,
            int arg3)
        {
            JObject newJObject =
                new JObject(
                    new JProperty("id", id),
                    new JProperty("seq", seq),
                    new JProperty("tp", tp),
                    new JProperty("tgt", tgt),
                    new JProperty("tsk", tsk),
                    new JProperty("0", arg0),
                    new JProperty("1", arg1),
                    new JProperty("2", arg2),
                    new JProperty("3", arg3)
                );

            return JsonConvert.SerializeObject(newJObject);
        }

        public static string CreateReplyJson(int seq, int tsk, int arg0, int arg1, int arg2, int arg3)
        {
            JObject newJObject =
                new JObject(
                    new JProperty("seq", seq),
                    new JProperty("tsk", tsk),
                    new JProperty("0", arg0),
                    new JProperty("1", arg1),
                    new JProperty("2", arg2),
                    new JProperty("3", arg3)
                );

            return JsonConvert.SerializeObject(newJObject);
        }
    }
}
