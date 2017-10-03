CREATE TABLE [dbo].[Message]
(
    [Id] UNIQUEIDENTIFIER NOT NULL DEFAULT NEWID(), 
    [SourceId] INT NOT NULL DEFAULT 255, 
    [TargetId] INT NOT NULL DEFAULT 255, 
    [Raw] VARBINARY(1024) NULL , 
    [Hex] VARCHAR(1024) NULL , 
    [Hash] BIGINT NOT NULL DEFAULT 0 , 
    [PayloadRaw] VARCHAR(1024) NULL , 
    [SequenceNumber] INT NOT NULL DEFAULT 0, 
    [PayloadType] VARCHAR(4) NULL  ,
    [PayloadTargetId] INT NOT NULL DEFAULT 0, 
    [PayloadTaskNumber] INT NOT NULL DEFAULT 0, 
    [PayloadArg0] INT NOT NULL DEFAULT 0, 
    [PayloadArg1] INT NOT NULL DEFAULT 0, 
    [PayloadArg2] INT NOT NULL DEFAULT 0, 
    [PayloadArg3] INT NOT NULL DEFAULT 0,
	[FromClient] BIT NOT NULL DEFAULT 0, 
    [BadMessage] INT NULL DEFAULT 0, 
    [DateTime] DATETIME NULL DEFAULT GETUTCDATE(), 
    [Legacy] BIT NOT NULL DEFAULT 0, 
    CONSTRAINT [PK_Message] PRIMARY KEY ([Id])
)