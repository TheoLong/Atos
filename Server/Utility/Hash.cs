using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Utility
{
    public class Hash
    {
        public static uint HashTo(string str)
        {
            uint hash = 5381;
            uint i = 0;

            for (i = 0; i < str.Length; i++)
            {
                hash = ((hash << 5) + hash) + ((byte)str[(int)i]);
            }

            return hash;
        }

        public static bool CheckHash(uint hash, string str)
        {
            uint hashResult = HashTo(str);
            return hash == hashResult;
        }
    }
}
