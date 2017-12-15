﻿using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using Atos.Classes;
using Newtonsoft.Json.Linq;
using Utility;

namespace Atos.BLL
{
    public class Server
    {
        public static readonly List<AtosClient> AtosClients = new List<AtosClient>();

        private static readonly ConcurrentQueue<AtosMsgQ> QueueA = new ConcurrentQueue<AtosMsgQ>();
        public static readonly ConcurrentQueue<AtosMsgQ> QueueB = new ConcurrentQueue<AtosMsgQ>();

        private static TcpListener serverSocket;

        public static bool OutToList = false;
        public static bool OutToConsole = true;
        public static Queue<string> Output = new Queue<string>();
        private static string _output = string.Empty;

        public static bool OutToDb = true;

        private static Thread _hThread;
        private static Thread _sThread;

        public static List<Storage> CachedData = Cache.CachedData;

        public static bool clearDb = false;


        public static void StartServer(IPAddress ip, int port)
        {
            var seqStorage = new Storage
            {
                Id = 0,
                Task = 0,
                Arg0 = 0,
                Arg1 = 0,
                Arg2 = 0,
                Arg3 = 0
            };

            Cache.UpdateStorage(seqStorage);

            if (OutToDb)
            {
                DBAccess.DBAccess.UpdateLegacy();
            }

            serverSocket = new TcpListener(ip, port);

            serverSocket.Start();

            _hThread = new Thread(HandlingMsgs);
            _sThread = new Thread(SendMsgs);

            _hThread.Start();
            _sThread.Start();

            var dThread = new Thread(SaveDb);
            if (OutToDb)
            {
                dThread.Start();
            }

            while (true)
            {
                var clientSocket = serverSocket.AcceptTcpClient();
                StartClient(clientSocket);
            }
        }

        public static void CloseServer()
        {
            if (serverSocket != null)
            {
                serverSocket.Stop();
            }
        }

        static void StartClient(TcpClient client)
        {
            var t1 = new Thread(ReceiveMsgs);
            t1.Start(client);
        }

        static void ReceiveMsgs(object c)
        {
            TcpClient client = (TcpClient)c;
            client.ReceiveBufferSize = 65536;
            byte[] bytesFrom = new byte[client.ReceiveBufferSize];

            while (true)
            {
                try
                {
                    NetworkStream networkStream = client.GetStream();
                    networkStream.Read(bytesFrom, 0, client.ReceiveBufferSize);

                    // split received by 0xFF
                    byte[][] recevedBytes = Separate(Decode(bytesFrom), new byte[] { 0xFF });

                    foreach (var v in recevedBytes)
                    {
                        if (v.Length > 5 && v.Length < 256)
                        {
                            AddMsgToRcvQueue(client, v);

                            //Console.WriteLine("QueueA: " + QueueA.Count);
                            //Console.WriteLine("QueueB: " + QueueB.Count);

                            _output = "@@@@@ Received From: " + client.Client.RemoteEndPoint +
                                            Environment.NewLine + " Data(Hex): " + BitConverter.ToString(v) +
                                            Environment.NewLine;

                            if (OutToList)
                            {
                                Output.Enqueue(_output);
                                if (Output.Count > 500)
                                {
                                    Output.Dequeue();
                                }
                            }
                            if (OutToConsole)
                            {
                                Console.WriteLine(_output);
                            }
                        }
                    }
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        static void HandlingMsgs()
        {
            while (true)
            {
                if (QueueA.Count < 1)
                {
                    continue;
                }

                AtosMsgQ newQItem;
                bool exist = QueueA.TryDequeue(out newQItem);
                if (exist)
                {
                    // new message
                    AtosTcpMessage newMsg = new AtosTcpMessage();

                    // get raw and hex string
                    newMsg.Raw = newQItem.Data;
                    newMsg.HexString = BitConverter.ToString(newMsg.Raw);

                    // get hash and payload string
                    try
                    {
                        // hash
                        newMsg.Hash =
                            BitConverter.ToUInt32(
                                new byte[] {newQItem.Data[0], newQItem.Data[1], newQItem.Data[2], newQItem.Data[3]},
                                0);

                        // payload
                        newMsg.PayloadString = Encoding.Default.GetString(newMsg.Raw.Skip(4).ToArray());
                    }
                    catch (Exception)
                    {
                        _output = "##### Action For: " + newQItem.Client.Client.RemoteEndPoint +
                                          Environment.NewLine + " Bad Message: " + newMsg.HexString +
                                          Environment.NewLine;

                        if (OutToList)
                        {
                            Output.Enqueue(_output);
                            if (Output.Count > 500)
                            {
                                Output.Dequeue();
                            }
                        }
                        if (OutToConsole)
                        {
                            Console.WriteLine(_output);
                        }

                        if (OutToDb)
                        {
                            DBAccess.DBAccess.InsertBadMsg(newMsg);
                        }

                        continue;
                    }

                    // valid json
                    bool validJson = Json.ValidateJson(newMsg.PayloadString);
                    if (!validJson)
                    {
                        _output = "##### Action For: " + newQItem.Client.Client.RemoteEndPoint +
                                          Environment.NewLine + " Invalid Json: " + newMsg.PayloadString +
                                          Environment.NewLine;

                        if (OutToList)
                        {
                            Output.Enqueue(_output);
                            if (Output.Count > 500)
                            {
                                Output.Dequeue();
                            }
                        }
                        if (OutToConsole)
                        {
                            Console.WriteLine(_output);
                        }

                        if (OutToDb)
                        {
                            DBAccess.DBAccess.InsertBadJsonMsg(newMsg);
                        }

                        continue;
                    }

                    _output = "##### Action For: " + newQItem.Client.Client.RemoteEndPoint +
                                          Environment.NewLine + " Payload Json: " + newMsg.PayloadString +
                                          Environment.NewLine;

                    if (OutToList)
                    {
                        Output.Enqueue(_output);
                        if (Output.Count > 500)
                        {
                            Output.Dequeue();
                        }
                    }
                    if (OutToConsole)
                    {
                        Console.WriteLine(_output);
                    }

                    // valid hash
                    bool validHash = Hash.CheckHash(newMsg.Hash, newMsg.PayloadString + "\xFF");
                    if (!validHash)
                    {
                        _output = "##### Action For: " + newQItem.Client.Client.RemoteEndPoint +
                                          Environment.NewLine + " Invalid Hash: Actual: " + newMsg.Hash + 
                                          " " + BitConverter.ToString(BitConverter.GetBytes(newMsg.Hash)) +
                                          " |Expected: " + Hash.HashTo(newMsg.PayloadString + "\xFF") +
                                          " " + BitConverter.ToString(BitConverter.GetBytes(Hash.HashTo(newMsg.PayloadString + "\xFF"))) +
                                          Environment.NewLine;

                        if (OutToList)
                        {
                            Output.Enqueue(_output);
                            if (Output.Count > 500)
                            {
                                Output.Dequeue();
                            }
                        }
                        if (OutToConsole)
                        {
                            Console.WriteLine(_output);
                        }

                        if (OutToDb)
                        {
                            DBAccess.DBAccess.InsertBadHashMsg(newMsg);
                        }

                        continue;
                    }

                    // parse json object
                    JObject payload = Json.JsonParseObject(newMsg.PayloadString);
                    try
                    {
                        // new received msg
                        newMsg.PayloadSequence = Json.JsonParseSequence(payload);
                        newMsg.PayloadType = Json.JsonParseType(payload);
                        newMsg.SourceId = Json.JsonParseId(payload);
                        newMsg.TargetId = 0;
                        newMsg.PayloadTargetId = Json.JsonParseTargetId(payload);
                        newMsg.PayloadTaskNumber = Json.JsonParseTaskNumber(payload);
                        newMsg.PayloadArg0 = Json.JsonParseArg0(payload);
                        newMsg.PayloadArg1 = Json.JsonParseArg1(payload);
                        newMsg.PayloadArg2 = Json.JsonParseArg2(payload);
                        newMsg.PayloadArg3 = Json.JsonParseArg3(payload);
                        newMsg.FromClient = true;

                        //clearDb = SaveSeq(newMsg);

                        _output = "##### Action For: " + newQItem.Client.Client.RemoteEndPoint +
                                          Environment.NewLine + " Parsed: " + newMsg.PayloadString +
                                          Environment.NewLine;

                        if (OutToList)
                        {
                            Output.Enqueue(_output);
                            if (Output.Count > 500)
                            {
                                Output.Dequeue();
                            }
                        }
                        if (OutToConsole)
                        {
                            Console.WriteLine(_output);
                        }
                    }
                    catch (Exception e)
                    {
                        _output = "##### Action For: " + newQItem.Client.Client.RemoteEndPoint +
                                          Environment.NewLine + " Incompleted Json: " + newMsg.PayloadString +
                                          Environment.NewLine;

                        if (OutToList)
                        {
                            Output.Enqueue(_output);
                            if (Output.Count > 500)
                            {
                                Output.Dequeue();
                            }
                        }
                        if (OutToConsole)
                        {
                            Console.WriteLine(_output);
                        }

                        if (OutToDb)
                        {
                            DBAccess.DBAccess.InsertIncompleteJsonMsg(newMsg);
                        }

                        continue;
                    }

                    // add new client if not recognized
                    AddClient(newQItem.Client, newMsg.SourceId);

                    // save recieved message to db
                    if (OutToDb)
                    {
                        DBAccess.DBAccess.InsertReceivedMsgToDb(newMsg);
                        //if (clearDb)
                        //{
                        //    DBAccess.DBAccess.DeleteAllMessages();
                        //    clearDb = false;
                        //}
                    }

                    // type: store or retrieve
                    if (newMsg.PayloadType == "s")
                    {
                        if (newMsg.PayloadTaskNumber == 255
                            && newMsg.PayloadArg0 == 256
                            && newMsg.PayloadArg1 == 256
                            && newMsg.PayloadArg2 == 256
                            && newMsg.PayloadArg3 == 256)
                        {
                            serverSocket.Server.Close();
                            serverSocket.Stop();
                        }

                        // save to cache
                        SaveStorageToCache(newMsg);
                    }

                    else if (newMsg.PayloadType == "m")
                    {
                        // save to cache
                        SaveStorageToCache(newMsg);
                    }

                    // retrieve
                    else if (newMsg.PayloadType == "r")
                    {
                        // get from cache
                        Storage retrieved = Cache.RetrieveStorage(newMsg.PayloadTargetId, newMsg.PayloadTaskNumber);

                        if (retrieved == null)
                        {
                            return;
                        }

                        // create payload json string
                        string replyPayload = Json.CreateReplyJson(
                            IncrementSeq(newMsg.SourceId),
                            retrieved.Task,
                            retrieved.Arg0,
                            retrieved.Arg1,
                            retrieved.Arg2,
                            retrieved.Arg3
                        );

                        _output = "$$$$$ Sent To: " + newQItem.Client.Client.RemoteEndPoint +
                                          Environment.NewLine + " Data: " + replyPayload +
                                          Environment.NewLine;

                        if (OutToList)
                        {
                            Output.Enqueue(_output);
                            if (Output.Count > 500)
                            {
                                Output.Dequeue();
                            }
                        }
                        if (OutToConsole)
                        {
                            Console.WriteLine(_output);
                        }

                        // create hash
                        uint hash = Hash.HashTo(replyPayload + "\xFF");
                        byte[] hashBytes = BitConverter.GetBytes(hash);
                        var hashBytes4 = new byte[4];
                        var startAt = hashBytes4.Length - hashBytes.Length;
                        Buffer.BlockCopy(hashBytes, 0, hashBytes4, startAt, hashBytes.Length);

                        // create reply bytes
                        byte[][] replyByteArray = new[]
                        {
                            new byte[] {0xFF},
                            hashBytes4,
                            Encoding.ASCII.GetBytes(replyPayload),
                            new byte[] {0xFF}
                        };
                        byte[] replyBytes = CombineByteArray(replyByteArray);

                        QueueB.Enqueue(new AtosMsgQ {Client = newQItem.Client, Data = replyBytes});

                        var replyMessage = ReplyMsgForDb(newMsg, replyBytes, hash, replyPayload, retrieved);

                        if (OutToDb)
                        {                            
                            DBAccess.DBAccess.InsertReplyToDb(replyMessage);                            
                        }
                    }
                }
            }
        }

        static void SendMsgs()
        {
            while (true)
            {
                if (QueueB.Count < 1)
                {
                    continue;
                }
                AtosMsgQ newQItem;
                bool exist = QueueB.TryDequeue(out newQItem);
                if (exist)
                {
                    try
                    {
                        NetworkStream nStream = newQItem.Client.GetStream();
                        nStream.Write(newQItem.Data, 0, newQItem.Data.Length);
                        nStream.Flush();
                    }
                    catch (Exception e)
                    {
                    }
                }
            }
        }
        
        static void SaveDb()
        {
            while (true)
            {
                DBAccess.DBAccess.SaveChanges();
                Thread.Sleep(500);
            }
        }

        private static AtosTcpMessage ReplyMsgForDb(AtosTcpMessage newTcpMsg, byte[] replyBytes, uint hash, string replyPayload,
            Storage retrieved)
        {
            AtosTcpMessage replyMessage = new AtosTcpMessage()
            {
                SourceId = 0,
                TargetId = newTcpMsg.SourceId,
                Raw = replyBytes,
                HexString = BitConverter.ToString(replyBytes),
                Hash = hash,
                PayloadString = replyPayload,
                PayloadSequence = GetSeq(newTcpMsg.SourceId),
                PayloadType = "a",
                PayloadTargetId = newTcpMsg.SourceId,
                PayloadTaskNumber = retrieved.Task,
                PayloadArg0 = retrieved.Arg0,
                PayloadArg1 = retrieved.Arg1,
                PayloadArg2 = retrieved.Arg2,
                PayloadArg3 = retrieved.Arg3,
                FromClient = false,
            };
            return replyMessage;
        }

        private static int GetSeq(int clientId)
        {
            foreach (var i in AtosClients)
            {
                if (i.Id == clientId)
                {
                    return i.LatestSequence;
                }
            }
            return int.MaxValue;
        }

        public static byte[] CombineByteArray(params byte[][] arrays)
        {
            byte[] rv = new byte[arrays.Sum(a => a.Length)];
            int offset = 0;
            foreach (byte[] array in arrays)
            {
                System.Buffer.BlockCopy(array, 0, rv, offset, array.Length);
                offset += array.Length;
            }
            return rv;
        }

        private static int IncrementSeq(int clientId)
        {
            foreach (var i in AtosClients)
            {
                if (i.Id == clientId)
                {
                    i.LatestSequence = i.LatestSequence + 1;
                }
                return i.LatestSequence;
            }
            return int.MaxValue;
        }

        private static bool SaveSeq(AtosTcpMessage newMsg)
        {
            bool resetDb = false;
            Storage storage = Cache.GetSeqStorage();
            if (newMsg.SourceId == 1)
            {
                if (newMsg.PayloadSequence < storage.Arg0)
                {
                    resetDb = true;
                }
                storage.Arg0 = newMsg.PayloadSequence;
            }
            if (newMsg.SourceId == 2)
            {
                if (newMsg.PayloadSequence < storage.Arg1)
                {
                    resetDb = true;
                }
                storage.Arg1 = newMsg.PayloadSequence;
            }
            if (newMsg.SourceId == 3)
            {
                if (newMsg.PayloadSequence < storage.Arg2)
                {
                    resetDb = true;
                }
                storage.Arg2 = newMsg.PayloadSequence;
            }
            if (newMsg.SourceId == 4)
            {
                if (newMsg.PayloadSequence < storage.Arg3)
                {
                    resetDb = true;
                }
                storage.Arg3 = newMsg.PayloadSequence;
            }

            Cache.UpdateStorage(storage);

            return resetDb;
        }

        private static void SaveStorageToCache(AtosTcpMessage newMsg)
        {
            Storage storage = new Storage
            {
                Id = newMsg.SourceId,
                Task = newMsg.PayloadTaskNumber,
                Arg0 = newMsg.PayloadArg0,
                Arg1 = newMsg.PayloadArg1,
                Arg2 = newMsg.PayloadArg2,
                Arg3 = newMsg.PayloadArg3
            };

            Cache.UpdateStorage(storage);
        }

        private static void AddClient(TcpClient c, int id)
        {
            foreach (var i in AtosClients)
            {
                if (c.Client.RemoteEndPoint == i.Client.Client.RemoteEndPoint)
                {
                    i.Id = id;
                    return;
                }
            }

            var newClient = new AtosClient
            {
                Id = id,
                Client = c
            };

            AtosClients.Add(newClient);
        }

        public static byte[] Decode(byte[] packet)
        {
            var i = packet.Length - 1;
            while (packet[i] == 0)
            {
                --i;
            }
            var temp = new byte[i + 1];
            Array.Copy(packet, temp, i + 1);
            return temp;
        }

        public static byte[][] Separate(byte[] source, byte[] separator)
        {
            var Parts = new List<byte[]>();
            var Index = 0;
            byte[] Part;
            for (var I = 0; I < source.Length; ++I)
            {
                if (Equals(source, separator, I))
                {
                    Part = new byte[I - Index];
                    Array.Copy(source, Index, Part, 0, Part.Length);
                    Parts.Add(Part);
                    Index = I + separator.Length;
                    I += separator.Length - 1;
                }
            }
            Part = new byte[source.Length - Index];
            Array.Copy(source, Index, Part, 0, Part.Length);
            Parts.Add(Part);
            return Parts.ToArray();
        }

        static bool Equals(byte[] source, byte[] separator, int index)
        {
            for (int i = 0; i < separator.Length; ++i)
                if (index + i >= source.Length || source[index + i] != separator[i])
                    return false;
            return true;
        }

        private static void AddMsgToRcvQueue(TcpClient client, byte[] msg)
        {
            QueueA.Enqueue(new AtosMsgQ() { Client = client, Data = msg });
        }
    }
}