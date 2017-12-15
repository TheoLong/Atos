using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Data.Entity;
using System.Data.Entity.Core.Objects;
using System.Data.Entity.Infrastructure;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Atos.Classes;
using Atos.DBContext;
using Utility;

namespace Atos.DBAccess
{
    public class DBAccess
    {
        static AtosDbEntities entities = new AtosDbEntities();
        
        private static readonly ConcurrentQueue<Message> QueueC = new ConcurrentQueue<Message>();
        static List<Message> messages = new List<Message>();

        // get
        public static IQueryable<Message> GetAllMessages()
        {
            return entities.Messages.Where(m=> m.BadMessage == 0 && m.Legacy == false).OrderByDescending(m => m.DateTime).Take(10000);
        }

        public static Message GetClientStatusByTaskId(int clientId, int taskId)
        {
            return
                entities.Messages
                    .Where(m => m.SourceId == clientId && m.PayloadTaskNumber == taskId)
                    .OrderByDescending(m => m.SequenceNumber).FirstOrDefault();
        }

        // insert
        public static void InsertBadMsg(AtosTcpMessage newTcpMsg)
        {
            Message badMsgDb = new Message()
            {
                Id = Guid.NewGuid(),
                TargetId = 0,
                Raw = newTcpMsg.Raw,
                Hex = newTcpMsg.HexString,
                FromClient = true,
                BadMessage = Constant.Incomplete,
                DateTime = DateTime.UtcNow,
                Legacy = false
            };

            try
            {
                //QueueC.Enqueue(badMsgDb);
                entities.Messages.Add(badMsgDb);
                //messages.Add(badMsgDb);
            }
            catch (Exception)
            {

            }
        }

        public static void InsertBadHashMsg(AtosTcpMessage newTcpMsg)
        {
            var badMsgDb = new Message()
            {
                Id = Guid.NewGuid(),
                TargetId = 0,
                Raw = newTcpMsg.Raw,
                Hex = newTcpMsg.HexString,
                Hash = newTcpMsg.Hash,
                PayloadRaw = newTcpMsg.PayloadString,
                FromClient = true,
                BadMessage = Constant.InvalidHash,
                DateTime = DateTime.UtcNow,
                Legacy = false
            };

            try
            {
                //QueueC.Enqueue(badMsgDb);
                entities.Messages.Add(badMsgDb);
                //messages.Add(badMsgDb);
            }
            catch (Exception e)
            {

            }
        }

        public static void InsertBadJsonMsg(AtosTcpMessage newTcpMsg)
        {
            Message badMsgDb = new Message()
            {
                Id = Guid.NewGuid(),
                TargetId = 0,
                Raw = newTcpMsg.Raw,
                Hex = newTcpMsg.HexString,
                Hash = newTcpMsg.Hash,
                PayloadRaw = newTcpMsg.PayloadString,
                FromClient = true,
                BadMessage = Constant.InvalidJson,
                DateTime = DateTime.UtcNow,
                Legacy = false
            };

            try
            {
                //QueueC.Enqueue(badMsgDb);
                entities.Messages.Add(badMsgDb);
                //messages.Add(badMsgDb);
            }
            catch (Exception e)
            {

            }
        }

        public static void InsertIncompleteJsonMsg(AtosTcpMessage newTcpMsg)
        {
            Message badMsgDb = new Message()
            {
                Id = Guid.NewGuid(),
                Raw = newTcpMsg.Raw,
                Hex = newTcpMsg.HexString,
                Hash = newTcpMsg.Hash,
                PayloadRaw = newTcpMsg.PayloadString,
                FromClient = true,
                BadMessage = Constant.IncompleteJson,
                DateTime = DateTime.UtcNow,
                Legacy = false
            };


            try
            {
                //QueueC.Enqueue(badMsgDb);
                entities.Messages.Add(badMsgDb);
                //messages.Add(badMsgDb);
            }
            catch (Exception e)
            {

            }
        }

        public static void InsertReceivedMsgToDb(AtosTcpMessage newTcpMsg)
        {
            var rcvdMsgDb = new Message()
            {
                Id = Guid.NewGuid(),
                SourceId = newTcpMsg.SourceId,
                TargetId = newTcpMsg.TargetId,
                Raw = newTcpMsg.Raw,
                Hex = newTcpMsg.HexString,
                Hash = newTcpMsg.Hash,
                PayloadRaw = newTcpMsg.PayloadString,
                SequenceNumber = newTcpMsg.PayloadSequence,
                PayloadType = newTcpMsg.PayloadType,
                PayloadTargetId = newTcpMsg.PayloadTargetId,
                PayloadTaskNumber = newTcpMsg.PayloadTaskNumber,
                PayloadArg0 = newTcpMsg.PayloadArg0,
                PayloadArg1 = newTcpMsg.PayloadArg1,
                PayloadArg2 = newTcpMsg.PayloadArg2,
                PayloadArg3 = newTcpMsg.PayloadArg3,
                FromClient = newTcpMsg.FromClient,
                BadMessage = Constant.Good,
                DateTime = DateTime.UtcNow,
                Legacy = false
            };

            try
            {
                //QueueC.Enqueue(rcvdMsgDb);
                entities.Messages.Add(rcvdMsgDb);
                //messages.Add(rcvdMsgDb);
            }
            catch (Exception e)
            {

            }
        }

        public static void InsertReplyToDb(AtosTcpMessage replyMessage)
        {
            var replyMsgDb = new Message()
            {
                Id = Guid.NewGuid(),
                SourceId = replyMessage.SourceId,
                TargetId = replyMessage.TargetId,
                Raw = replyMessage.Raw,
                Hex = replyMessage.HexString,
                Hash = replyMessage.Hash,
                PayloadRaw = replyMessage.PayloadString,
                SequenceNumber = replyMessage.PayloadSequence,
                PayloadType = replyMessage.PayloadType.ToString(),
                PayloadTargetId = replyMessage.PayloadTargetId,
                PayloadTaskNumber = replyMessage.PayloadTaskNumber,
                PayloadArg0 = replyMessage.PayloadArg0,
                PayloadArg1 = replyMessage.PayloadArg1,
                PayloadArg2 = replyMessage.PayloadArg2,
                PayloadArg3 = replyMessage.PayloadArg3,
                FromClient = replyMessage.FromClient,
                BadMessage = Constant.Good,
                DateTime = DateTime.UtcNow,
                Legacy = false
            };

            try
            {
                //QueueC.Enqueue(replyMsgDb);
                entities.Messages.Add(replyMsgDb);
                //messages.Add(replyMsgDb);
            }
            catch (Exception e)
            {

            }
        }

        // update

        public static void UpdateLegacy()
        {
            entities.Configuration.AutoDetectChangesEnabled = false;
            var mList = entities.Messages;
            if (mList.Count() > 0)
            {
                foreach (var m in mList)
                {
                    m.Legacy = true;
                }
            }
            entities.SaveChanges();
        }

        // delete

        public static void DeleteAllMessages()
        {
            entities.Database.ExecuteSqlCommand("TRUNCATE TABLE [Message]");
        }

        // save changes
        public static void SaveChanges()
        {
            try
            {
                Message newMsg;

                //Console.WriteLine("Entities messages: " + messages.Count);

                //entities.BulkInsert(messages);
                //entities.BulkSaveChanges();
                //messages.Clear();

                entities.SaveChanges();

                //bool exist = QueueC.TryDequeue(out newMsg);
                //while (exist)
                //{
                //    Console.WriteLine("QueueC: " + QueueC.Count);

                //    entities.Messages.Add(newMsg);
                //    entities.SaveChanges();
                //    exist = QueueC.TryDequeue(out newMsg);
                //}
            }
            catch (Exception e)
            {

            }
        }
    }
}
