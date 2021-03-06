USE [DataBase]
GO
/****** Object:  Table [dbo].[Yield_Result]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Yield_Result](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[LayerName] [varchar](64) NOT NULL,
	[LayerAlias] [varchar](64) NULL,
	[Number] [varchar](16) NULL,
	[DepSt] [float] NULL,
	[DepEn] [float] NULL,
	[DepHD] [float] NULL,
	[DepHD1] [float] NULL,
	[WorkType] [float] NULL,
	[Temp] [float] NULL,
	[Press] [float] NULL,
	[WaterRatio] [float] NULL,
	[Injection] [float] NULL,
	[Lith] [varchar](64) NULL,
	[OilOut] [float] NULL,
	[GasOut] [float] NULL,
	[WaterOut] [float] NULL,
	[OilPercent] [float] NULL,
	[GasPercent] [float] NULL,
	[WaterPercent] [float] NULL,
	[Conclusion] [varchar](64) NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_Yield_Result] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Yield_Project]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Yield_Project](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[ProjectName] [varchar](64) NOT NULL,
	[ProjectAlias] [varchar](64) NULL,
	[LogDate] [datetime] NULL,
	[LogStDep] [float] NULL,
	[LogEnDep] [float] NULL,
	[DepRatio] [float] NULL,
	[LogDevice] [varchar](64) NULL,
	[LogTeam] [varchar](128) NULL,
	[LogCompany] [varchar](256) NULL,
	[LogLeader] [varchar](64) NULL,
	[LogEngineer] [varchar](64) NULL,
	[TopPres] [float] NULL,
	[FlangeType] [varchar](64) NULL,
	[BottomPres] [float] NULL,
	[FluidType] [varchar](64) NULL,
	[HornDep] [float] NULL,
	[CasingPres] [float] NULL,
	[OilOut] [float] NULL,
	[GasOut] [float] NULL,
	[WaterOut] [float] NULL,
	[Glib] [float] NULL,
	[OilPipeSize] [float] NULL,
	[OilPipePres] [float] NULL,
	[OilPipeDep] [float] NULL,
	[H2S] [float] NULL,
	[DeviceNote] [varchar](256) NULL,
	[AuditUser] [varchar](64) NULL,
	[AuditDate] [datetime] NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_Yield_Project] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[WorkSpace]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[WorkSpace](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[WorkSpaceName] [varchar](128) NOT NULL,
	[Alias] [varchar](128) NULL,
	[Area] [float] NULL,
	[Region] [varchar](256) NULL,
	[Oilfield] [varchar](64) NULL,
	[ViewX] [float] NULL,
	[ViewY] [float] NULL,
	[Longitude] [float] NULL,
	[Latitude] [float] NULL,
	[GeoDescribe] [varchar](2048) NULL,
	[FormDescribe] [varchar](2048) NULL,
	[DrillDescribe] [varchar](2048) NULL,
	[OilDescribe] [varchar](2048) NULL,
	[ImageType] [varchar](16) NULL,
	[ImageSize] [int] NULL,
	[CreateDate] [datetime] NULL,
	[DataByte] [varbinary](max) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_WorkSpace] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Well]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Well](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[WellName] [varchar](64) NOT NULL,
	[Alias] [varchar](64) NULL,
	[Structure] [varchar](64) NULL,
	[Oilfield] [varchar](64) NULL,
	[Owner] [varchar](64) NULL,
	[Region] [varchar](128) NULL,
	[Location] [varchar](128) NULL,
	[Line_Location] [varchar](128) NULL,
	[ElevationGd] [float] NULL,
	[Elevation0] [float] NULL,
	[DepOffset] [float] NULL,
	[OilOffset] [float] NULL,
	[PipeOffset] [float] NULL,
	[MagneticV] [float] NULL,
	[WellDepth] [float] NULL,
	[WellBottom] [float] NULL,
	[StartDate] [datetime] NULL,
	[EndDate] [datetime] NULL,
	[WellX] [float] NULL,
	[WellY] [float] NULL,
	[Longitude] [float] NULL,
	[Latitude] [float] NULL,
	[WellType] [varchar](32) NULL,
	[WellKind] [varchar](32) NULL,
	[DrillAim] [varchar](4096) NULL,
	[AimLayer] [varchar](64) NULL,
	[ReservoirType] [varchar](32) NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__Well__E955CC1C7F60ED59] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Template]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Template](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[TempName] [varchar](128) NOT NULL,
	[TempType] [varchar](16) NULL,
	[TempKind] [varchar](64) NULL,
	[TempSize] [int] NULL,
	[TempCreDate] [datetime] NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[DataZip] [int] NULL,
	[DataByte1] [image] NULL,
	[DataByte2] [image] NULL,
	[DataByte3] [image] NULL,
	[DataByte4] [image] NULL,
	[DataByte5] [image] NULL,
	[DataByte6] [image] NULL,
	[DataByte7] [image] NULL,
	[DataByte8] [image] NULL,
	[DataByte9] [image] NULL,
	[DataByte10] [image] NULL,
PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Structure]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Structure](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[StructureName] [varchar](128) NOT NULL,
	[Alias] [varchar](128) NULL,
	[Area] [float] NULL,
	[Region] [varchar](256) NULL,
	[Oilfield] [varchar](64) NULL,
	[ViewX] [float] NULL,
	[ViewY] [float] NULL,
	[Longitude] [float] NULL,
	[Latitude] [float] NULL,
	[GeoDescribe] [varchar](2048) NULL,
	[FormDescribe] [varchar](2048) NULL,
	[DrillDescribe] [varchar](2048) NULL,
	[OilDescribe] [varchar](2048) NULL,
	[ImageType] [varchar](16) NULL,
	[ImageSize] [int] NULL,
	[CreateDate] [datetime] NULL,
	[DataByte] [varbinary](max) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__COM_Stru__4A1C074B03317E3D] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Storage]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Storage](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[StorageName] [varchar](64) NOT NULL,
	[StorageAlias] [varchar](64) NULL,
	[StorageKind] [varchar](32) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[Describe] [varchar](512) NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__Storage__8A247E3708EA5793] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Result]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Result](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[LayerName] [varchar](64) NOT NULL,
	[LayerAlias] [varchar](64) NULL,
	[Number] [varchar](16) NULL,
	[DepSt] [float] NULL,
	[DepEn] [float] NULL,
	[DepHD] [float] NULL,
	[DepHD1] [float] NULL,
	[POR] [float] NULL,
	[PERMA] [float] NULL,
	[SW] [float] NULL,
	[SH] [float] NULL,
	[Conclusion] [varchar](64) NULL,
	[SP] [float] NULL,
	[GR] [float] NULL,
	[CGR] [float] NULL,
	[DEN] [float] NULL,
	[CNL] [float] NULL,
	[AC] [float] NULL,
	[RT] [float] NULL,
	[RXO] [float] NULL,
	[RS] [float] NULL,
	[PorMax] [float] NULL,
	[SwMax] [float] NULL,
	[HoleNum] [float] NULL,
	[HolePor] [float] NULL,
	[HoleDia] [float] NULL,
	[CrackNum] [float] NULL,
	[CrackLength] [float] NULL,
	[CrackWidth] [float] NULL,
	[CrackWaterWidth] [float] NULL,
	[CrackPor] [float] NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__Result__976902280CBAE877] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[RawData]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[RawData](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[ProjectName] [varchar](64) NOT NULL,
	[ProjectAlias] [varchar](64) NULL,
	[LogDate] [datetime] NULL,
	[LogStDep] [float] NULL,
	[LogEnDep] [float] NULL,
	[DepRatio] [float] NULL,
	[LogDevice] [varchar](64) NULL,
	[LogTeam] [varchar](128) NULL,
	[LogCompany] [varchar](256) NULL,
	[LogLeader] [varchar](64) NULL,
	[LogEngineer] [varchar](64) NULL,
	[DeviceNote] [varchar](256) NULL,
	[LogMode] [varchar](32) NOT NULL,
	[FileType] [varchar](32) NOT NULL,
	[FileFormat] [varchar](32) NOT NULL,
	[FileName] [varchar](256) NOT NULL,
	[StorageMode] [varchar](32) NOT NULL,
	[FilePath] [varchar](256) NOT NULL,
	[DataSize] [bigint] NULL,
	[PieceSize] [bigint] NULL,
	[DataZip] [tinyint] NULL,
	[DataStID] [bigint] NULL,
	[DataPieceNum] [int] NULL,
	[AuditUser] [varchar](64) NULL,
	[AuditDate] [datetime] NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_RawData] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[RawBody]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[RawBody](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[Number] [int] NULL,
	[DataSize] [bigint] NULL,
	[UpperID] [bigint] NOT NULL,
	[DataByte] [varbinary](max) NULL,
 CONSTRAINT [PK_RawBody] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Project]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Project](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[ProjectName] [varchar](64) NOT NULL,
	[ProjectAlias] [varchar](64) NULL,
	[LogDate] [datetime] NULL,
	[LogStDep] [float] NULL,
	[LogEnDep] [float] NULL,
	[DepRatio] [float] NULL,
	[LogDevice] [varchar](64) NULL,
	[LogTeam] [varchar](128) NULL,
	[LogCompany] [varchar](256) NULL,
	[LogLeader] [varchar](64) NULL,
	[LogEngineer] [varchar](64) NULL,
	[CasingNote] [varchar](128) NULL,
	[BitNote] [varchar](128) NULL,
	[FluidType] [varchar](64) NULL,
	[FluidDen] [float] NULL,
	[FluidVis] [float] NULL,
	[FluidRm] [float] NULL,
	[FluidTem] [float] NULL,
	[BottomDep] [float] NULL,
	[BottomTem] [float] NULL,
	[DeviceNote] [varchar](256) NULL,
	[AuditUser] [varchar](64) NULL,
	[AuditDate] [datetime] NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__LOG_Proj__761ABED02D27B809] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Production]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Production](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[DocName] [varchar](64) NOT NULL,
	[DocType] [varchar](16) NULL,
	[DocTitle] [varchar](64) NULL,
	[DocAuthor] [varchar](32) NULL,
	[DocCreDate] [datetime] NULL,
	[Describe] [varchar](512) NULL,
	[FileFormat] [varchar](32) NULL,
	[FileName] [varchar](256) NULL,
	[StorageMode] [varchar](32) NULL,
	[FilePath] [varchar](256) NULL,
	[DataSize] [bigint] NULL,
	[PieceSize] [bigint] NULL,
	[DataZip] [tinyint] NULL,
	[DataStID] [bigint] NULL,
	[DataPieceNum] [int] NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__Producti__D5D9A2F51273C1CD] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[OilTestOpenDep]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[OilTestOpenDep](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[OpenDepSt] [varchar](64) NULL,
	[OpenDepEn] [varchar](64) NULL,
	[UpperID] [bigint] NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[OilTest]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[OilTest](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[LayerName] [varchar](64) NOT NULL,
	[LayerAlias] [varchar](64) NULL,
	[TestMethod] [varchar](10) NULL,
	[OutMethod] [varchar](10) NULL,
	[Conclusion] [varchar](10) NULL,
	[TestDate] [datetime] NULL,
	[Reference] [varchar](128) NULL,
	[ReferDate] [datetime] NULL,
	[DepSt] [float] NULL,
	[DepEn] [float] NULL,
	[PorePlate] [float] NULL,
	[Glib] [float] NULL,
	[CasingPres] [float] NULL,
	[OilPres] [float] NULL,
	[FlowPres] [float] NULL,
	[TopPres] [float] NULL,
	[TopTemp] [float] NULL,
	[ClosePres] [float] NULL,
	[LayerPres] [float] NULL,
	[OilOut] [float] NULL,
	[GasOut] [float] NULL,
	[WaterOut] [float] NULL,
	[Describe] [varchar](1024) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[LithSymbol]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[LithSymbol](
	[RecordID] [int] IDENTITY(1,1) NOT NULL,
	[LithName] [varchar](64) NULL,
	[LithAlias] [varchar](64) NULL,
	[DataType] [varchar](16) NULL,
	[DataSize] [int] NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[LithByte] [image] NULL,
PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Layer]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Layer](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[LayerName] [varchar](64) NOT NULL,
	[LayerAlias] [varchar](64) NULL,
	[DepLog] [float] NULL,
	[TVLog] [float] NULL,
	[DepGeo] [float] NULL,
	[TVGeo] [float] NULL,
	[RemOption] [varchar](10) NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__LOG_Laye__83790DA21273C1CD] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[DrillTool]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[DrillTool](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[BitSize] [float] NULL,
	[BitDep] [float] NULL,
	[CasingSize] [float] NULL,
	[CasingDep] [float] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_DrillToolcasing] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[DrillShow]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[DrillShow](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[LayerName] [varchar](64) NOT NULL,
	[LayerAlias] [varchar](64) NULL,
	[DepSt] [float] NULL,
	[DepEn] [float] NULL,
	[Conclusion] [varchar](10) NULL,
	[LithDescribe] [varchar](2048) NULL,
	[ShowDescribe] [varchar](2048) NULL,
	[imageType] [varchar](16) NULL,
	[ImageSize] [int] NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
	[DataByte] [varbinary](max) NULL,
 CONSTRAINT [PK_DrillShow] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[DrillSample]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[DrillSample](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[LayerName] [varchar](64) NOT NULL,
	[LayerAlias] [varchar](64) NULL,
	[DepSt] [float] NULL,
	[DepEn] [float] NULL,
	[SampleNote] [varchar](2048) NULL,
	[imageType] [varchar](16) NULL,
	[ImageSize] [int] NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
	[DataByte] [varbinary](max) NULL,
 CONSTRAINT [PK_DrillSample] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[DocBody]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[DocBody](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[Number] [int] NULL,
	[DataSize] [bigint] NULL,
	[UpperID] [bigint] NOT NULL,
	[DataByte] [varbinary](max) NULL,
 CONSTRAINT [PK_DocBody] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[CurveBody]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[CurveBody](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[Number] [int] NULL,
	[DataSize] [bigint] NULL,
	[UpperID] [bigint] NOT NULL,
	[DataByte] [varbinary](max) NULL,
 CONSTRAINT [PK_CurveBody] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Curve]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Curve](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[CurveName] [varchar](32) NOT NULL,
	[CurveAlias] [varchar](32) NULL,
	[Dimension] [tinyint] NULL,
	[DepUnit] [varchar](8) NULL,
	[DepSt] [float] NULL,
	[DepEn] [float] NULL,
	[DepRlev] [float] NULL,
	[XName] [varchar](32) NULL,
	[XUnit] [varchar](8) NULL,
	[XMin] [float] NULL,
	[XMax] [float] NULL,
	[XRlev] [float] NULL,
	[XNPS] [int] NULL,
	[DataType] [tinyint] NULL,
	[DataUnit] [varchar](8) NULL,
	[CreateDate] [datetime] NULL,
	[DataSize] [bigint] NULL,
	[PieceSize] [bigint] NULL,
	[DataZip] [int] NULL,
	[DataStID] [bigint] NULL,
	[DataPieceNum] [int] NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK__Curve__8FECEFD921B6055D] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Cemente_Result]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Cemente_Result](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[Number] [varchar](16) NULL,
	[NormMax] [float] NULL,
	[NorMin] [float] NULL,
	[DepThick] [float] NULL,
	[ThickPercent] [float] NULL,
	[Conclusion] [varchar](64) NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_Cemente_Result] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Cemente_Project]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Cemente_Project](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[ProjectName] [varchar](64) NOT NULL,
	[ProjectAlias] [varchar](64) NULL,
	[LogDate] [datetime] NULL,
	[LogStDep] [float] NULL,
	[LogEnDep] [float] NULL,
	[DepRatio] [float] NULL,
	[LogDevice] [varchar](64) NULL,
	[LogTeam] [varchar](128) NULL,
	[LogCompany] [varchar](256) NULL,
	[LogLeader] [varchar](64) NULL,
	[LogEngineer] [varchar](64) NULL,
	[CasingNote] [varchar](128) NULL,
	[FluidType] [varchar](128) NULL,
	[CementType] [varchar](64) NULL,
	[CementDen] [float] NULL,
	[ReturnDep] [float] NULL,
	[CementDate] [datetime] NULL,
	[OpenWellDate] [datetime] NULL,
	[BottomDep] [float] NULL,
	[BottomTem] [float] NULL,
	[DeviceNote] [varchar](256) NULL,
	[AuditUser] [varchar](64) NULL,
	[AuditDate] [datetime] NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_Cemente_Project] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
/****** Object:  Table [dbo].[Cemente_ExResult]    Script Date: 04/12/2016 14:33:11 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Cemente_ExResult](
	[RecordID] [bigint] IDENTITY(1,1) NOT NULL,
	[Number] [varchar](16) NULL,
	[DepSt] [float] NULL,
	[DepEn] [float] NULL,
	[CBLMax] [float] NULL,
	[CBLMin] [float] NULL,
	[CBLAverage] [float] NULL,
	[Conclusion] [varchar](64) NULL,
	[ConCode] [int] NULL,
	[ConCodeColor] [bigint] NULL,
	[Describe] [varchar](512) NULL,
	[FillUser] [varchar](64) NULL,
	[FillDate] [datetime] NULL,
	[UpperID] [bigint] NOT NULL,
 CONSTRAINT [PK_Cemente_ExResult] PRIMARY KEY CLUSTERED 
(
	[RecordID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
