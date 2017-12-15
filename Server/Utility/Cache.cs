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
                d => d.Id == storage.Id && d.Task == storage.Task);
            if (exist != null)
            {
                if (storage.Arg0 >= 0)
                {
                    exist.Arg0 = storage.Arg0;
                }
                if (storage.Arg1 >= 0)
                {
                    exist.Arg1 = storage.Arg1;
                }
                if (storage.Arg2 >= 0)
                {
                    exist.Arg2 = storage.Arg2;
                }
                if (storage.Arg3 >= 0)
                {
                    exist.Arg3 = storage.Arg3;
                }
                //exist.DateTime = DateTime.UtcNow;
            }
            else
            {
                CachedData.Add(storage);
            }
        }

        public static List<Storage> RetrieveStorageList(int taskNumber)
        {
            return CachedData.Where(d => d.Task == taskNumber).ToList();
        }

        public static Storage GetSeqStorage()
        {
            return RetrieveStorage(0, 0);
        }

        public static Storage RetrieveStorage(int clientId, int taskNumber)
        {
            var retrieved = CachedData.FirstOrDefault(
                d => d.Id == clientId && d.Task == taskNumber);

            if (retrieved != null)
            {
                return retrieved;
            }
            if (taskNumber == 11)
            {
                return new Storage()
                {
                    Id = clientId,
                    Task = taskNumber,
                    Arg0 = 0,
                    Arg1 = 0,
                    Arg2 = 0,
                    Arg3 = 0
                };
            }

            //return null;
            return new Storage()
            {
                Id = clientId,
                Task = taskNumber,
                Arg0 = int.MaxValue,
                Arg1 = int.MaxValue,
                Arg2 = int.MaxValue,
                Arg3 = int.MaxValue
            };
        }
    }
}
