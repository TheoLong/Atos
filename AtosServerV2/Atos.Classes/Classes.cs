using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace Atos.Classes
{
    public class AtosTcpMessage
    {
        public int SourceId { get; set; }
        public int TargetId { get; set; }
        public byte[] Raw { get; set; }
        public string HexString { get; set; }
        public uint Hash { get; set; }
        public string PayloadString { get; set; }
        public int PayloadSequence { get; set; }
        public string PayloadType { get; set; }
        public int PayloadTargetId { get; set; }
        public int PayloadTaskNumber { get; set; }
        public int PayloadArg0 { get; set; }
        public int PayloadArg1 { get; set; }
        public int PayloadArg2 { get; set; }
        public int PayloadArg3 { get; set; }
        public bool FromClient { get; set; }
    }

    public class Storage
    {
        public int ClientId { get; set; }
        public int SequenceNumber { get; set; }
        public int TaskNumber { get; set; }
        public int Arg0 { get; set; }
        public int Arg1 { get; set; }
        public int Arg2 { get; set; }
        public int Arg3 { get; set; }
        public DateTime DateTime { get; set; }
    }

    public class AtosMsgQ
    {
        public TcpClient Client { get; set; }
        public byte[] Data { get; set; }
    }

    public class AtosClient
    {
        public int Id { get; set; }
        public TcpClient Client { get; set; }
        public int LatestSequence { get; set; }
    }
}
