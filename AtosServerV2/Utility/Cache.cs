using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Atos.Classes;

namespace Utility
{
    public class Cache
    {
        public static List<Storage> CachedData = new List<Storage>();

        public static void UpdateStorage(Storage storage)
        {
            var exist = CachedData.FirstOrDefault(
                d => d.ClientId == storage.ClientId && d.TaskNumber == storage.TaskNumber);
            if (exist != null)
            {
                exist.Arg0 = storage.Arg0;
                exist.Arg1 = storage.Arg1;
                exist.Arg2 = storage.Arg2;
                exist.Arg3 = storage.Arg3;
                exist.DateTime = DateTime.UtcNow;
            }
            else
            {
                CachedData.Add(storage);
            }
        }

        public static List<Storage> RetrieveStorageList(int taskNumber)
        {
            return CachedData.Where(d => d.TaskNumber == taskNumber).ToList();
        }

        public static Storage RetrieveStorage(int clientId, int taskNumber)
        {
            var retrieved = CachedData.FirstOrDefault(
                d => d.ClientId == clientId && d.TaskNumber == taskNumber);

            if (retrieved != null)
            {
                return retrieved;
            }
            return new Storage()
            {
                ClientId = clientId,
                TaskNumber = taskNumber,
                SequenceNumber = 0,
                Arg0 = int.MaxValue,
                Arg1 = int.MaxValue,
                Arg2 = int.MaxValue,
                Arg3 = int.MaxValue
            };
        }
    }
}
