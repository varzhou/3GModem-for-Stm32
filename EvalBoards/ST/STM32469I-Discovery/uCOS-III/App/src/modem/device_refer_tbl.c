static const struct device_refer device_refer_tbl[] =
{
    {
        /* HP LaserJet Professional P1102*/
        /*.TargetClass = 0x0007,*/
        .DefaultVendor = 0x03f0,
        .DefaultProduct = 0x002a,
        .MessageContent = "555342431234567800000000000006d0000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Quanta MU-Q101*/
        /*.TargetVendor = 0x0408,*/
        /*.TargetProduct = 0xea02,*/
        .DefaultVendor = 0x0408,
        .DefaultProduct = 0x1000,
    },
    {
        /* Quanta 1KR / USB-lte 7410*/
        /*.TargetVendor = 0x0408,*/
        /*.TargetProduct = 0xea16,*/
        .DefaultVendor = 0x0408,
        .DefaultProduct = 0xea17,
        .StandardEject = 1,
    },
    {
        /* Quanta 1K3 LTE*/
        /*.TargetVendor = 0x0408,*/
        /*.TargetProduct = 0xea26,*/
        .DefaultVendor = 0x0408,
        .DefaultProduct = 0xea25,
        .ModeMap = QUANTA_MODE,
    },
    {
        /* Quanta MobileGenie 4G lte, Quanta 1K6*/
        /*.TargetVendor = 0x0408,*/
        /*.TargetProductList = "ea47,ea49",*/
        .DefaultVendor = 0x0408,
        .DefaultProduct = 0xea43,
        .StandardEject = 1,
    },
    {
        /* Yota Router (Quanta 1QDLZZZ0ST2)*/
        /*.TargetVendor = 0x0408,*/
        /*.TargetProduct = 0xea03,*/
        .DefaultVendor = 0x0408,
        .DefaultProduct = 0xf000,
        .ModeMap = QUANTA_MODE,
    },
    {
        /* SpeedUp SU-8500U*/
        /*.TargetVendor = 0x0408,*/
        /*.TargetProduct = 0xea03,*/
        .DefaultVendor = 0x0408,
        .DefaultProduct = 0xf001,
        .ModeMap = QUANTA_MODE,
    },
    {
        /* Nokia CS-10*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProduct = 0x060e,*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x060c,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-15*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProduct = 0x0612,*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x0610,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-12*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProduct = 0x0619,*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x0618,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-11*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProduct = 0x061e,*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x061d,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-17*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProduct = 0x0623,*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x0622,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-18*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProductList = "0612,0629",*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x0627,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-19*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProductList = "062d,062f",*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x062c,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-7M-01*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProduct = 0x0632,*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x0632,
        .StandardEject = 1,
    },
    {
        /* Nokia CS-21M-02*/
        /*.TargetVendor = 0x0421,*/
        /*.TargetProduct = 0x0638,*/
        .DefaultVendor = 0x0421,
        .DefaultProduct = 0x0637,
        .StandardEject = 1,
    },
    {
        /* Vodafone MD950 (Wisue Technology)*/
        /*.TargetVendor = 0x1dbc,*/
        /*.TargetProduct = 0x0005,*/
        .DefaultVendor = 0x0471,
        .DefaultProduct = 0x1210,
        .StandardEject = 1,
        .uMa = "Wisue",
    },
    {
        /* Philips (?)*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0471,
        .DefaultProduct = 0x1210,
        .StandardEject = 1,
        .uMa = "Philips",
    },
    {
        /* Philips TalkTalk (NXP Semiconductors "Dragonfly")*/
        /*.TargetVendor = 0x0471,*/
        /*.TargetProductList = "1206,1234",*/
        .DefaultVendor = 0x0471,
        .DefaultProduct = 0x1237,
        .StandardEject = 1,
    },
//     {
//         /* Kyocera W06K CDMA modem*/
//         .DefaultVendor = 0x0482,
//         .DefaultProduct = 0x024d,
//         .Configuration = 2,
//     },
    {
        /* I-O Data WMX2-U Wimax*/
        /*.TargetVendor = 0x04bb,*/
        /*.TargetProduct = 0x0949,*/
        .DefaultVendor = 0x04bb,
        .DefaultProduct = 0xbccd,
        .MessageContent = "55534243f0298d8124000000800006bc626563240000000000000000000000",
    },
    {
        /* Alcatel-Lucent ABS-T920*/
        /*.TargetVendor = 0x04cc,*/
        /*.TargetProductList = "2259,226e",*/
        .DefaultVendor = 0x04cc,
        .DefaultProduct = 0x2251,
        .StandardEject = 1,
    },
//     {
//         /* Alcatel-Lucent T930S*/
//         .DefaultVendor = 0x04cc,
//         .DefaultProduct = 0x225c,
//         .Configuration = 2,
//     },
//     {
//         /* Nexperia TM TD-SCDMA*/
//         .DefaultVendor = 0x04cc,
//         .DefaultProduct = 0x226e,
//         .Configuration = 2,
//     },
//     {
//         /* Nexperia TM TD-SCDMA (Variant)*/
//         .DefaultVendor = 0x04cc,
//         .DefaultProduct = 0x226f,
//         .Configuration = 2,
//     },
    {
        /* Samsung GT-B1110*/
        /*.TargetVendor = 0x04e8,*/
        /*.TargetProduct = 0x6792,*/
        .DefaultVendor = 0x04e8,
        .DefaultProduct = 0x680c,
        .MessageContent = "0902200001010080fa0904000002080650000705010200020007058102000200",
    },
    {
        /* Samsung GT-B3730*/
        /*.TargetVendor = 0x04e8,*/
        /*.TargetProduct = 0x6889,*/
        .DefaultVendor = 0x04e8,
        .DefaultProduct = 0x689a,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
//     {
//         /* Samsung U209*/
//         /*.TargetVendor = 0x04e8,*/
//         /*.TargetProduct = 0x6601,*/
//         .DefaultVendor = 0x04e8,
//         .DefaultProduct = 0xf000,
//         .MessageContent = "55534243123456780000000000000616000000000000000000000000000000",
//         .sMo = "U209",
//     },
    {
        /* Sunplus Techn. SU-3200U*/
        /*.TargetVendor = 0x04fc,*/
        /*.TargetProductList = "0615,1240",*/
        .DefaultVendor = 0x04fc,
        .DefaultProduct = 0x2140,
        .MessageContent = "55534243123456782400000080000612000024000000000000000000000000",
    },
    {
        /* AVM Fritz!Wlan USB Stick N v2*/
        /*.TargetVendor = 0x057c,*/
        /*.TargetProductList = "8501,8502",*/
        .DefaultVendor = 0x057c,
        .DefaultProduct = 0x62ff,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* AVM Fritz!Wlan USB Stick N*/
        /*.TargetVendor = 0x057c,*/
        /*.TargetProduct = 0x8401,*/
        .DefaultVendor = 0x057c,
        .DefaultProduct = 0x84ff,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Axesstel Modems (w/ initial idProduct 0x0010)*/
        /*.TargetVendor = 0x05c6,*/
        /*.TargetProduct = 0x00a0,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x0010,
        .StandardEject = 1,
    },
    {
        /* StrongRising device */
        /*.TargetVendor = 0x028a,*/
        /*.TargetProduct = 0x1006,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "StrongRising",
    },
    {
        /* TechFaith Venus VT-18*/
        /*.TargetVendor = 0x1d09,*/
        /*.TargetProduct = 0x4306,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "Co.,Ltd",
    },
//     {
//         /* Option GlobeTrotter GX0201*/
//         /*.TargetVendor = 0x0af0,*/
//         /*.TargetProduct = 0x6701,*/
//         .DefaultVendor = 0x05c6,
//         .DefaultProduct = 0x1000,
//         .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
//         .NeedResponse = 1,
//         .sVe = "GT",
//     },
    {
        /* Celot K-300*/
        /*.TargetVendor = 0x211f,*/
        /*.TargetProduct = 0x6801,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "CELOT",
    },
    {
        /* AnyDATA devices, Bless UC165*/
        /*.TargetVendor = 0x16d5,*/
        /*.TargetProduct = 0x6502,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "AnyDATA",
    },
    {
        /* Vertex Wireless 100 Series*/
        /*.TargetVendor = 0x1fe7,*/
        /*.TargetProduct = 0x0100,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "Vertex",
    },
//     {
//         /* Older Option devices*/
//         /*.TargetVendor = 0x0af0,*/
//         /*.TargetProductList = "6901,6701,6600",*/
//         .DefaultVendor = 0x05c6,
//         .DefaultProduct = 0x1000,
//         .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
//         .NeedResponse = 1,
//         .sVe = "Option",
//     },
    {
        /* Prolink P2000 CDMA*/
        /*.TargetVendor = 0x05c6,*/
        /*.TargetProduct = 0x6000,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "SSE",
    },
    {
        /* Quirky Option devices*/
        /*.TargetVendor = 0x0af0,*/
        /*.TargetProduct = 0x6901,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
        .NeedResponse = 1,
        .uMa = "Option",
    },
    {
        /* Celot CT-680*/
        /*.TargetVendor = 0x211f,*/
        /*.TargetProduct = 0x6802,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "DGT",
    },
    {
        /* Samsung SGH-Z810*/
        /*.TargetVendor = 0x04e8,*/
        /*.TargetProduct = 0x6601,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .MessageContent = "55534243123456780000000000000616000000000000000000000000000000",
        .uMa = "SAMSUNG",
    },
    {
        /* Qualcomm CDMA Technologies*/
        /*.TargetVendor = 0x05c6,*/
        /*.TargetProduct = 0x6000,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
        .uMa = "Qualcomm",
    },
    {
        /* Various USB modems*/
        /*.TargetVendor = 0x05c6,*/
        /*.TargetProductList = "0015,0016,0018,ce17",*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x2000,
        .MessageContent = "5553424368032c882400000080000612000000240000000000000000000000",
        .NeedResponse = 1,
//        .CheckSuccess = 40,
    },
    {
        /* D-Link DWM-162-U5, DWM-162 C1, Micromax MMX 300c*/
        /*.TargetVendor = 0x1e0e,*/
        /*.TargetProductList = "ce16,ce17,cefe",*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x2001,
        .StandardEject = 1,
    },
    {
        /* AnyDATA APE-540H*/
        /*.TargetVendor = 0x16d5,*/
        /*.TargetProduct = 0x6502,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x6503,
        .StandardEject = 1,
    },
    {
        /* Alcatel-sbell ASB TL131 TD-LTE*/
        /*.TargetVendor = 0x05c6,*/
        /*.TargetProduct = 0x9025,*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0x9024,
        .StandardEject = 1,
    },
    {
        /* Siptune LM-75 ("LinuxModem")*/
        /*.TargetVendor = 0x05c6,*/
        /*.TargetProductList = "0016,9000",*/
        .DefaultVendor = 0x05c6,
        .DefaultProduct = 0xf000,
        .StandardEject = 1,
    },
    {
        /* Qtronix EVDO 3G Modem (for TianYi)*/
        /*.TargetVendor = 0x05c7,*/
        /*.TargetProduct = 0x6000,*/
        .DefaultVendor = 0x05c7,
        .DefaultProduct = 0x1000,
        .MessageContent = "5553424312345678c00000008000069f140000000000000000000000000000",
    },
    {
        /* ZE-3G 7.2Mbs HSPA modem*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProduct = 0x9603,*/
        .DefaultVendor = 0x0685,
        .DefaultProduct = 0x2000,
        .MessageContent = "5553424368032c882400000080000612000000240000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* InfoCert Business Key (SmartCard/Reader emulation)*/
        /*.TargetVendor = 0x072f,*/
        /*.TargetProduct = 0x90cc,*/
        .DefaultVendor = 0x072f,
        .DefaultProduct = 0x100d,
//        .NoDriverLoading = 1,
        .MessageEndpoint = 0x0002,
        .MessageContent = "01b0000000000000000000000000000000000000000000000000000000000000",
    },
    {
        /* D-Link DWM-156 HSUPA 3.75G USB Modem */
        /*.TargetVendor = 0x07d1,*/
        /*.TargetProduct = 0x3e02,*/
        .DefaultVendor = 0x07d1,
        .DefaultProduct = 0xa800,
        .StandardEject = 1,
    },
    {
        /* D-Link DWM-156 HSUPA 3.75G USB Modem*/
        /*.TargetVendor = 0x07d1,*/
        /*.TargetProduct = 0x7e11,*/
        .DefaultVendor = 0x07d1,
        .DefaultProduct = 0xa804,
        .StandardEject = 1,
    },
    {
        /* Dymo LabelManager*/
        /*.TargetVendor = 0x0922,*/
        /*.TargetProduct = 0x1002,*/
        .DefaultVendor = 0x0922,
        .DefaultProduct = 0x1001,
//        .NoDriverLoading = 1,
        .MessageEndpoint = 0x0001,
        .MessageContent = "1b5a01",
//        .ResponseEndpoint = 0x0001,
    },
    {
        /* Dymo LabelManager 420P*/
        /*.TargetVendor = 0x0922,*/
        /*.TargetProduct = 0x1004,*/
        .DefaultVendor = 0x0922,
        .DefaultProduct = 0x1003,
//        .NoDriverLoading = 1,
        .MessageContent = "1b5a01",
    },
    {
        /* Toshiba G450*/
        /*.TargetVendor = 0x0930,*/
        /*.TargetProduct = 0x0d45,*/
        .DefaultVendor = 0x0930,
        .DefaultProduct = 0x0d46,
        .StandardEject = 1,
    },
    {
        /* Zydas ZD1211RW WLAN USB, Sphairon HomeLink 1202 (Variant 1)*/
        .DefaultVendor = 0x0ace,
        .DefaultProduct = 0x2011,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Zydas ZD1211RW WLAN USB, Sphairon HomeLink 1202 (Variant 2)*/
        .DefaultVendor = 0x0ace,
        .DefaultProduct = 0x20ff,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Option iCon 711*/
        /*.TargetVendor = 0x0af0,*/
        /*.TargetProduct = 0x4005,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x4007,
        .ModeMap = SIERRA_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6711,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6731,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6751,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6771,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6791,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6811,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6911,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6951,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x6971,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7011,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7031,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7051,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7071,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7111,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7211,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7251,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7271,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7301,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7311,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7361,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7381,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7401,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7501,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7601,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7701,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7706,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7801,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7901,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7a01,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
    },
    {
        /* Option iCon 461*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x7a05,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
    },
    {
        /* Option Globetrotter (Variant)*/
        /*.TargetVendor = 0x0af0,*/
        /*.TargetProduct = 0x9100,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8006,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8200,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8201,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8300,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8302,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8304,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8400,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8600,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option GI0643 (aka XYFI)*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8700,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8800,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x8900,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x9000,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0x9200,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xc031,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xc100,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
//     {
//         /* Option GlobeTrotter GI1515*/
//         /*.TargetVendor = 0x0af0,*/
//         /*.TargetProductList = "d157,d255,d257",*/
//         .DefaultVendor = 0x0af0,
//         .DefaultProduct = 0xd001,
// //        .NoDriverLoading = 1,
//         .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
//         .Interface = 1,
//     },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd013,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd031,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd033,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd035,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd055,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd057,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd058,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd155,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd157,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd255,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd257,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Option HSO device*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0af0,
        .DefaultProduct = 0xd357,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243785634120100000080000601000000000000000000000000000000",
    },
    {
        /* Olivetti Olicard 100 and others*/
        /*.TargetVendor = 0x0b3c,*/
        /*.TargetProductList = "c000,c001,c002",*/
        .DefaultVendor = 0x0b3c,
        .DefaultProduct = 0xc700,
        .StandardEject = 1,
    },
    {
        /* Olivetti Olicard 145, 155*/
        /*.TargetVendor = 0x0b3c,*/
        /*.TargetProductList = "c003,c004",*/
        .DefaultVendor = 0x0b3c,
        .DefaultProduct = 0xf000,
        .MessageContent = "5553424312345678c000000080010606f50402527000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Olivetti Olicard 160*/
        /*.TargetVendor = 0x0b3c,*/
        /*.TargetProduct = 0xc00a,*/
        .DefaultVendor = 0x0b3c,
        .DefaultProduct = 0xf00c,
        .MessageContent = "55534243123456788000000080000606f50402527000000000000000000000",
    },
    {
        /* Olivetti Olicard 500*/
        /*.TargetVendor = 0x0b3c,*/
        /*.TargetProduct = 0xc00b,*/
        .DefaultVendor = 0x0b3c,
        .DefaultProduct = 0xf017,
        .StandardEject = 1,
    },
//     {
//         /* Ericsson F5521gw*/
//         .DefaultVendor = 0x0bdb,
//         .DefaultProduct = 0x190d,
//         .Configuration = 2,
//     },
//     {
//         /* Ericsson F5521gw (Variant)*/
//         .DefaultVendor = 0x0bdb,
//         .DefaultProduct = 0x1910,
//         .Configuration = 2,
//     },
    {
        /* Atheros Wireless / Netgear WNDA3200*/
        /*.TargetVendor = 0x0cf3,*/
        /*.TargetProduct = 0x7010,*/
        .DefaultVendor = 0x0cf3,
        .DefaultProduct = 0x20ff,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Kobil mIdentity 3G (1)*/
        /*.TargetVendor = 0x0d46,*/
        /*.TargetProduct = 0x45a9,*/
        .DefaultVendor = 0x0d46,
        .DefaultProduct = 0x45a1,
        .ModeMap = KOBIL_MODE,
    },
    {
        /* Kobil mIdentity 3G (2)*/
        /*.TargetVendor = 0x0d46,*/
        /*.TargetProduct = 0x45ad,*/
        .DefaultVendor = 0x0d46,
        .DefaultProduct = 0x45a5,
        .ModeMap = KOBIL_MODE,
    },
    {
        /* Mobile Action ("Smart Cable")*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x0df7,
        .DefaultProduct = 0x0800,
        .ModeMap = MOBILEACTION_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* MediaTek/Medion S4222 and probably others*/
        /*.TargetVendor = 0x0e8d,*/
        /*.TargetProductList = "00a1,00a2,00a5",*/
        .DefaultVendor = 0x0e8d,
        .DefaultProduct = 0x0002,
        .MessageContent = "555342431234567800000000000006f0010300000000000000000000000000",
        .uPr = "Product",
    },
    {
        /* MediaTek MT6276M and others*/
        /*.TargetVendor = 0x0e8d,*/
        /*.TargetProductList = "00a1,00a2,00a5",*/
        .DefaultVendor = 0x0e8d,
        .DefaultProduct = 0x0002,
        .MessageContent = "555342431234567800000000000006f0010300000000000000000000000000",
        .uPr = "MT",
    },
    {
        /* MediaTek Wimax USB Card*/
        /*.TargetVendor = 0x0e8d,*/
        /*.TargetProduct = 0x7118,*/
        .DefaultVendor = 0x0e8d,
        .DefaultProduct = 0x7109,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* BlackBerry Q10 and Z10*/
        /*.TargetVendor = 0x0fca,*/
        /*.TargetProduct = 0x8012,*/
        .DefaultVendor = 0x0fca,
        .DefaultProduct = 0x8020,
        .ModeMap = BLACKBERRY_MODE,
    },
//     {
//         /* Sony Ericsson MD300*/
//         .DefaultVendor = 0x0fce,
//         .DefaultProduct = 0xd0cf,
//         .Configuration = 3,
//     },
//     {
//         /* Sony Ericsson EC400*/
//         .DefaultVendor = 0x0fce,
//         .DefaultProduct = 0xd0df,
//         .Configuration = 2,
//     },
//     {
//         /* Sony Ericsson MD400*/
//         /*.TargetClass = 0x0002,*/
//         .DefaultVendor = 0x0fce,
//         .DefaultProduct = 0xd0e1,
//         .ModeMap = SONY_MODE,
//         .Configuration = 2,
//     },
//     {
//         /* Sony Ericsson MD400G*/
//         /*.TargetClass = 0x0002,*/
//         .DefaultVendor = 0x0fce,
//         .DefaultProduct = 0xd103,
//         .ModeMap = SONY_MODE,
//         .Configuration = 2,
//     },
//     {
//         /* GW D301 (Advinne AMC)*/
//         .DefaultVendor = 0x0fd1,
//         .DefaultProduct = 0x1000,
//         .Configuration = 3,
//     },
    {
        /* LG LDU-1900D EV-DO (Rev. A)*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x1000,
        .MessageContent = "55534243123456780000000000000aff554d53434847000000000000000000",
    },
    {
        /* LG HDM-2100 (EVDO Rev.A USB modem)*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProductList = "6000,6114",*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x607f,
        .MessageContent = "555342431234567803000000800006f1010100000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* LG L-05A*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x6124,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x613a,
        .StandardEject = 1,
    },
    {
        /* LG LUU-2100TI (aka AT&T USBConnect Turbo)*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x6141,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x613f,
        .StandardEject = 1,
    },
    {
        /* LG L-07A*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x6135,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x614e,
        .StandardEject = 1,
    },
    {
        /* LG LUU-2110TI*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x6157,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x6156,
        .StandardEject = 1,
    },
    {
        /* LG AD600*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x61a7,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x6190,
        .StandardEject = 1,
    },
    {
        /* LG VL600*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x61a7,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x61aa,
        .StandardEject = 1,
    },
    {
        /* LG L-02C LTE*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x618f,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x61dd,
        .StandardEject = 1,
    },
    {
        /* LG SD711*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x61e6,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x61e7,
        .StandardEject = 1,
    },
    {
        /* LG L-08C (NTT docomo)*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x61ea,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x61eb,
        .StandardEject = 1,
    },
    {
        /* LG L-03D LTE/3G*/
        /*.TargetVendor = 0x1004,*/
        /*.TargetProduct = 0x6326,*/
        .DefaultVendor = 0x1004,
        .DefaultProduct = 0x6327,
        .MessageContent = "555342431234567800000000000005f1010100000000000000000000000000",
    },
    {
        /* Huawei E630*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1003,*/
        .DefaultVendor = 0x1033,
        .DefaultProduct = 0x0035,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* UTStarcom UM175 (distributor "Alltel")*/
        /*.TargetVendor = 0x106c,*/
        /*.TargetProduct = 0x3715,*/
        .DefaultVendor = 0x106c,
        .DefaultProduct = 0x3b03,
        .MessageContent = "555342431234567824000000800008ff024445564348470000000000000000",
    },
    {
        /* Pantech / UTStarcom UMW190 (Verizon)*/
        /*.TargetVendor = 0x106c,*/
        /*.TargetProduct = 0x3716,*/
        .DefaultVendor = 0x106c,
        .DefaultProduct = 0x3b05,
        .MessageContent = "555342431234567824000000800008ff020000000000000000000000000000",
    },
    {
        /* UTStarcom UM185E (distributor "Alltel")*/
        /*.TargetVendor = 0x106c,*/
        /*.TargetProduct = 0x3717,*/
        .DefaultVendor = 0x106c,
        .DefaultProduct = 0x3b06,
        .MessageContent = "55534243b82e238c24000000800008ff020000000000000000000000000000",
    },
    {
        /* Pantech UML290*/
        /*.TargetVendor = 0x106c,*/
        /*.TargetProduct = 0x3718,*/
        .DefaultVendor = 0x106c,
        .DefaultProduct = 0x3b11,
        .StandardEject = 1,
    },
    {
        /* Option Beemo / Pantech P4200 LTE*/
        /*.TargetVendor = 0x106c,*/
        /*.TargetProduct = 0x3721,*/
        .DefaultVendor = 0x106c,
        .DefaultProduct = 0x3b14,
//        .NoDriverLoading = 1,
        .MessageContent = "555342431234567824000000800008ff024445564348470000000000000000",
    },
    {
        /* Sagem F@ST 9520-35-GLR*/
        /*.TargetVendor = 0x1076,*/
        /*.TargetProduct = 0x7f00,*/
        .DefaultVendor = 0x1076,
        .DefaultProduct = 0x7f40,
        .ModeMap = GCT_MODE,
    },
    {
        /* Hisense E910 EVDO Phone*/
        /*.TargetVendor = 0x109b,*/
        /*.TargetProduct = 0x9114,*/
        .DefaultVendor = 0x109b,
        .DefaultProduct = 0xf009,
        .StandardEject = 1,
    },
//     {
//         /* Pantech/Verizon UML295*/
//         /*.TargetVendor = 0x10a9,*/
//         /*.TargetProductList = "6064",*/
//         .DefaultVendor = 0x10a9,
//         .DefaultProduct = 0x606f,
//         .ModeMap = PANTECH_MODE,
//         .PantechMode = 1,
// //        .NoDriverLoading = 1,
//     },
//     {
//         /* Pantech LTE Modem*/
//         /*.TargetVendor = 0x10a9,*/
//         /*.TargetProduct = 0x6085,*/
//         .DefaultVendor = 0x10a9,
//         .DefaultProduct = 0x6080,
//         .ModeMap = PANTECH_MODE,
//         .PantechMode = 1,
//     },
    {
        /* Sierra devices (specific driver)*/
        /*.TargetVendor = 0x1199,*/
        /*.TargetProductList = "0017,0018,0019,0020,0021,0022,0023,0024,0025,0026,0027,0028,0029,0112,0120,0218,0220,0224,0301,6802,6803,6804,6805,6808,6809,6812,6813,6815,6816,6820,6821,6822,6832,6833,6834,6835,6838,6839,683a,683b,683c,683d,683e,6850,6851,6852,6853,6855,6856,6859,685a,6880,6890,6891,6892,6893,68a2,68a3,68aa,9011,9012,9051",*/
        .DefaultVendor = 0x1199,
        .DefaultProduct = 0x0fff,
        .ModeMap = SIERRA_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Digicom 8E4455 (and all Pirelli devices - EXPERIMENTAL)*/
        /*.TargetVendor = 0x1266,*/
        /*.TargetProductList = "1002,1003,1004,1005,1006,1007,1008,1009,100a,100b,100c,100d,100e,100f,1011,1012",*/
        .DefaultVendor = 0x1266,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
    },
    {
        /* Huawei E169*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1001,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* Huawei E220, E230, E270, E870*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1003,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* Huawei V725 Phone (aka Vodafone 725)*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1009,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* Huawei ETS1201*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1010,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* Huawei U7510 / U7517*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x101e,
    },
    {
        /* Huawei U8220, T-Mobile Pulse (Android smartphone)*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1034,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1030,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243123456780600000080010a11060000000000000000000000000000",
    },
    {
        /* Huawei U8110 / Joy, Vodafone 845 (Android smartphone)*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1035,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1031,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243123456780600000080010a11060000000000000000000000000000",
    },
    {
        /* Huawei EC168*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1413,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* Huawei E180*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1414,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* Huawei, newer modems, and rebrandings*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "1001,1404,1406,140b,140c,1412,1417,141b,1429,1432,1433,1436,14ac,1506,150c,1511",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1446,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E352*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1444,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1449,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone (Huawei) K3806*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14ae,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14ad,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E173 (Viettel 3G)*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "14a8,14aa",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14b5,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone (Huawei) K4511*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14cc,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14b7,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E173u-2, E177*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14d2,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14ba,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone (Huawei) K4605*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14c6,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14c1,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* K5005 Vodafone/Huawei*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14c8,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14c3,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone/Huawei K3771*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14ca,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14c4,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone (Huawei) K4510*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14cb,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14c5,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei K3770*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14c9,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14d1,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* T-Mobile NL (Huawei E352)*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "1506,150f,151d",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x14fe,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei EC156, Huawei E372u-8*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "140b,140c,1506,150f,150a",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1505,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E392u-12, E3131 (Variant)*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "151b,151d,151e",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x151a,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei K3765*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1465,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1520,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei K4505*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1464,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1521,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei R201*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1491,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1523,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei K3772*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14cf,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1526,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E1553*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1001,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1553,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E173*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14a5,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1557,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone (Huawei) R205*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14cd,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x155a,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E171*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1506,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x155b,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E3276s-151 and E3251*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "156b,156c",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x156a,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E3276-s150*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1506,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x157c,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E3331, E3372*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "14db,14dc",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x157d,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei R215 Router*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1588,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1582,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei W5101 Router*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1589,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1583,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E3131*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1506,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x15ca,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E3372*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1506,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x15cd,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E3372s-153*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1506,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x15cf,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei E3531*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1506,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x15e7,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei U2800 Phone*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1805,
        .MessageContent = "55534243123456780600000080000601000000000000000000000000000000",
    },
    {
        /* Huawei E173s*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "1c05,1c07,1c08,1c10",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1c0b,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei GP02 (E587 Variant)*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1506,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1c1b,
        .ModeMap = HUAWEINEW_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Huawei E173 (Moviestar)*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1c12,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1c24,
        .ModeMap = HUAWEINEW_MODE,
    },
//     {
//         /* Huawei ET302*/
//         .DefaultVendor = 0x12d1,
//         .DefaultProduct = 0x1d50,
//         .Configuration = 2,
//     },
    {
        /* Huawei ET8282, Huawei ET127*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1d09,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1da1,
        .ModeMap = HUAWEI_MODE,
    },
    {
        /* Huawei E353 (3.se) and others*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "14db,14dc",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f01,
        .ModeMap = HUAWEINEW_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Huawei E5377*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14dc,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f02,
        .ModeMap = HUAWEINEW_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* KDDI (Huawei) HWD12 LTE*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14db,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f03,
        .ModeMap = HUAWEINEW_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Huawei/Vodafone R226*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x15bf,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f07,
        .ModeMap = HUAWEINEW_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Huawei/Vodafone R216*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1c50,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f09,
        .ModeMap = HUAWEINEW_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Vodafone / Huawei K3773*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x14bc,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f11,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone K4305*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "1400,14f7",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f15,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone K5150*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "14f8,1575",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f16,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone K4201*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1576,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f17,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone K4202*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1577,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f18,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone K4606*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "14fa,1575,1578",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f19,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei Kxxxx*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProduct = 0x1579,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f1b,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei K4203*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "157a,1590",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f1c,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei Kxxxx*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "157b,1591",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f1d,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Vodafone / Huawei Kxxxx*/
        /*.TargetVendor = 0x12d1,*/
        /*.TargetProductList = "157f,1592",*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x1f1e,
        .ModeMap = HUAWEINEW_MODE,
    },
    {
        /* Huawei BM358 WiMAX*/
        /*.TargetClass = 0x0002,*/
        .DefaultVendor = 0x12d1,
        .DefaultProduct = 0x380b,
        .StandardEject = 1,
    },
    {
        /* Cisco AM10 "Valet Connector"*/
        /*.TargetVendor = 0x13b1,*/
        /*.TargetProduct = 0x0031,*/
        .DefaultVendor = 0x1307,
        .DefaultProduct = 0x1169,
        .ModeMap = CISCO_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* Novatel Wireless devices*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProductList = "4100,4400,7030",*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5010,
        .StandardEject = 1,
    },
    {
        /* Novatel MC990D*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProductList = "6000,7001",*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5020,
        .StandardEject = 1,
    },
    {
        /* Novatel MC996D*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProduct = 0x7030,*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5023,
        .StandardEject = 1,
    },
    {
        /* Novatel U760*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProduct = 0x6000,*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5030,
        .StandardEject = 1,
    },
    {
        /* Novatel MC760 3G*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProduct = 0x6002,*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5031,
        .StandardEject = 1,
    },
    {
        /* Novatel Generic MiFi 2352 / Vodafone MiFi 2352*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProductList = "7001,7003",*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5041,
        .StandardEject = 1,
    },
    {
        /* Novatel MiFi 4082*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProduct = 0x6032,*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5055,
        .StandardEject = 1,
    },
    {
        /* Novatel Wireless MC545 HSPA, U679 LTE*/
        /*.TargetVendor = 0x1410,*/
        /*.TargetProductList = "7031,7042",*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x5059,
        .StandardEject = 1,
    },
    {
        /* Novatel Generic MiFi 2372 / Vodafone MiFi 2372*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1410,
        .DefaultProduct = 0x7001,
        .StandardEject = 1,
    },
    {
        /* Sequans SQN1210/SQN1220 (generic chipsets)*/
        /*.TargetClass = 0x0002,*/
        .DefaultVendor = 0x148e,
        .DefaultProduct = 0xa000,
        .ModeMap = SEQUANS_MODE,
    },
    {
        /* Motorola 802.11 bg WLAN (TER/GUSB3-E)*/
        /*.TargetVendor = 0x148f,*/
        /*.TargetProduct = 0x9021,*/
        .DefaultVendor = 0x148f,
        .DefaultProduct = 0x2578,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* China TeleCom CBP7.0*/
        /*.TargetVendor = 0x15eb,*/
        /*.TargetProduct = 0x7152,*/
        .DefaultVendor = 0x15eb,
        .DefaultProduct = 0x7153,
        .StandardEject = 1,
    },
    {
        /* Amoi H-01*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1614,
        .DefaultProduct = 0x0800,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
    },
    {
        /* Amoi H-02*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1614,
        .DefaultProduct = 0x0802,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
    },
    {
        /* C-motech CHU-628S*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x16d8,
        .DefaultProduct = 0x6281,
        .MessageContent = "555342431234567824000000800008ff524445564348470000000000000000",
    },
    {
        /* C-motech D-50 (aka "CDU-680", "CNU-680")*/
        /*.TargetClass = 0x0002,*/
        .DefaultVendor = 0x16d8,
        .DefaultProduct = 0x6803,
        .MessageContent = "555342431234567824000000800008ff524445564348473100000000000000",
    },
    {
        /* C-motech CDU-685a*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x16d8,
        .DefaultProduct = 0x6804,
        .MessageContent = "555342431234567824000000800008ff524445564348470000000000000000",
    },
    {
        /* C-motech CHU-629S*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x16d8,
        .DefaultProduct = 0x700a,
        .MessageContent = "55534243123456782400000080000dfe524445564348473d4e444953000000",
    },
    {
        /* C-motech CHU-629S (Variant)*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x16d8,
        .DefaultProduct = 0x700b,
        .MessageContent = "55534243123456782400000080000dfe524445564348473d4e444953000000",
    },
    {
        /* C-motech CGU-628 (aka "Franklin Wireless CGU-628A" aka "4G Systems XS Stick W12")*/
        /*.TargetVendor = 0x16d8,*/
        /*.TargetProduct = 0x6006,*/
        .DefaultVendor = 0x16d8,
        .DefaultProduct = 0xf000,
        .MessageContent = "55534243d85dd88524000000800008ff524445564348470000000000000000",
    },
    {
        /* Axesstel MU130*/
        /*.TargetVendor = 0x1726,*/
        /*.TargetProduct = 0xa000,*/
        .DefaultVendor = 0x1726,
        .DefaultProduct = 0xf00e,
        .StandardEject = 1,
    },
//     {
//         /* Spreadtrum SC7702*/
//         .DefaultVendor = 0x1782,
//         .DefaultProduct = 0x0003,
//         .Configuration = 2,
//     },
    {
        /* JOA Telecom LM-700r*/
        /*.TargetVendor = 0x198a,*/
        /*.TargetProduct = 0x0002,*/
        .DefaultVendor = 0x198a,
        .DefaultProduct = 0x0003,
        .StandardEject = 1,
    },
    {
        /* Beceem BCSM250*/
        /*.TargetVendor = 0x198f,*/
        /*.TargetProduct = 0x0220,*/
        .DefaultVendor = 0x198f,
        .DefaultProduct = 0xbccd,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243f0298d8124000000800006bc626563240000000000000000000000",
    },
    {
        /* ZTE MU351*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0003,
        .StandardEject = 1,
    },
    {
        /* ZTE AC581*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "0073,0094,0152",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0026,
        .StandardEject = 1,
    },
    {
        /* Vodafone (ZTE) K2525*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0022,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0040,
        .StandardEject = 1,
    },
    {
        /* ZTE MF110 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0031,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0053,
        .StandardEject = 1,
    },
    {
        /* ZTE MF110 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0124,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0083,
        .StandardEject = 1,
        .uPr = "WCDMA",
    },
    {
        /* Vodafone (ZTE) K4505-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0104,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0101,
        .StandardEject = 1,
    },
    {
        /* ZTE MF112*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0031,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0103,
        .StandardEject = 1,
    },
    {
        /* ZTE MF637 (Variant for Orange France)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0121,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0110,
        .StandardEject = 1,
    },
    {
        /* ZTE MF651*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0116,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0115,
        .StandardEject = 1,
    },
    {
        /*ZTE-T A356*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0079,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0120,
        .StandardEject = 1,
//        .Interface = 0,
    },
    {
        /* ZTE MF652 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "0142,0143",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0146,
        .StandardEject = 1,
    },
    {
        /* ZTE MF190 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0124,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0149,
        .StandardEject = 1,
        .MessageContent = "55534243123456702000000080000c85010101180101010101000000000000",
    },
    {
        /* ZTE MF656A, MF668A, MF669*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0124,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0150,
        .StandardEject = 1,
    },
    {
        /* ZTE MF190 (Variant) and others*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "0017,0117,2003",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0154,
        .StandardEject = 1,
    },
    {
        /* ZTE MF820 4G LTE*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0167,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0166,
        .MessageContent = "55534243123456782400000080000685000000240000000000000000000000",
    },
    {
        /* ZTE A371B*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0170,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0169,
        .StandardEject = 1,
    },
    {
        /* Onda MT8205 LTE*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0265,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0266,
        .StandardEject = 1,
        .MessageContent = "55534243d8a523862400000080000685000000240000000000000000000000",
    },
    {
        /* ZTE MF821D (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0349,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0304,
        .StandardEject = 1,
    },
    {
        /* ZTE MF821D/MF826*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "0317,0330",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0318,
        .StandardEject = 1,
    },
    {
        /* ZTE MF821D*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0326,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0325,
        .StandardEject = 1,
    },
    {
        /* ZTE MF90 Mobile Hotspot*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0447,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0388,
        .MessageContent = "55534243123456782400000080000685000000240000000000000000000000",
    },
    {
        /* Telewell TW-LTE 4G*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0412,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x0413,
        .MessageContent = "55534243d8a523862400000080000685000000240000000000000000000000",
    },
    {
        /* Vodafone (ZTE) K3805-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "1002,1003",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1001,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Vodafone (ZTE) K3570-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1008,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1007,
        .StandardEject = 1,
    },
    {
        /* Vodafone (ZTE) K3571-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1010,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1009,
        .StandardEject = 1,
    },
    {
        /* Vodafone (ZTE) K3806-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1015,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1013,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Vodafone K5006Z (MF821)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1018,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1017,
        .StandardEject = 1,
    },
    {
        /* Vodafone K5008-z (MF823)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "1031,1032",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1030,
        .StandardEject = 1,
    },
    {
        /* ZTE / Vodafone K4607-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "1039,1040",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1038,
        .StandardEject = 1,
    },
    {
        /* Vodafone (ZTE) K4510-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1173,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1171,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Vodafone / ZTE K3770-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1177,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1175,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* Vodafone (ZTE) K3772-Z*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1181,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1179,
        .StandardEject = 1,
//        .NoDriverLoading = 1,
    },
    {
        /* ZTE MF691 (T-Mobile Rocket 2.0)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1203,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1201,
        .StandardEject = 1,
    },
    {
        /* ZTE MF192 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1208,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1207,
        .StandardEject = 1,
    },
    {
        /* ZTE MF195*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1211,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1210,
        .StandardEject = 1,
    },
    {
        /* ZTE MF192 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1217,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1216,
        .StandardEject = 1,
    },
    {
        /* ZTE MF192 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "1220,1222",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1219,
        .StandardEject = 1,
    },
    {
        /* ZTE MF190*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0082,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1224,
        .StandardEject = 1,
    },
    {
        /* ZTE MF668 (Variant), MF70*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1405,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1225,
        .StandardEject = 1,
    },
    {
        /* ZTE MF680*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1252,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1227,
        .StandardEject = 1,
    },
    {
        /* ZTE MFxxx*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "1268,2003",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1232,
        .StandardEject = 1,
    },
    {
        /* ZTE MFxxx*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1270,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1233,
        .StandardEject = 1,
    },
    {
        /* ZTE / Vodafone K4201*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0017,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1237,
        .StandardEject = 1,
    },
    {
        /* ZTE MF825A*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0017,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1238,
        .StandardEject = 1,
    },
    {
        /* ZTE MF730*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1405,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1420,
        .StandardEject = 1,
    },
    {
        /* ZTE MFxxx*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1512,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1511,
        .StandardEject = 1,
    },
    {
        /* ZTE MF192 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1515,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1514,
        .MessageContent = "5553424348c4758600000000000010ff000000000000000000000000000000",
    },
    {
        /* ZTE MF192 (Variant)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1519,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1517,
        .StandardEject = 1,
    },
    {
        /* ZTE MF652*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0142,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1520,
        .StandardEject = 1,
    },
    {
        /* ZTE MF591 TMobile*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1525,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1523,
        .StandardEject = 1,
    },
    {
        /* ZTE MF196*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1527,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1528,
        .StandardEject = 1,
    },
    {
        /* ZTE MF190J*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "1537,1538",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1536,
        .StandardEject = 1,
    },
    {
        /* ZTE MF190J*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1544,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1542,
        .StandardEject = 1,
    },
    {
        /* ZTE MF710M Variants*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "1589,1591,1592",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x1588,
        .StandardEject = 1,
        .MessageContent = "55534243123456702000000080000c85010101180101010101000000000000",
    },
    {
        /* ZTE devices*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "0001,0002,0015,0016,0017,0019,0031,0033,0037,0042,0052,0055,0061,0063,0064,0066,0091,0108,0117,0128,0151,0157,0177,1402,2002,2003",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x2000,
        .StandardEject = 1,
        .MessageContent = "55534243123456702000000080000c85010101180101010101000000000000",
    },
    {
        /* ZTE MF60*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x1402,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0x2004,
        .StandardEject = 1,
    },
    {
        /* ZTE AX226 WiMax*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0x0172,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0xbccd,
//        .NoDriverLoading = 1,
        .MessageContent = "555342431234567824000000800006bc626563240000000000000000000000",
    },
    {
        /* ZTE AC682 (a.k.a. SmartFren Connex)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0xffdd,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0xffde,
        .StandardEject = 1,
    },
    {
        /* ZTE "ffe" devices 1 (e.g. Cricket A605)*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0xffe5,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0xffe6,
        .MessageContent = "5553424330f4cf8124000000800108df200000000000000000000000000000",
    },
    {
        /* ZTE "ff" devices 1*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProductList = "ffe4,ffe9,fff1,fffe,ffff",*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0xfff5,
        .MessageContent = "5553424312345678c00000008000069f030000000000000000000000000000",
    },
    {
        /* ZTE "fff" devices 2*/
        /*.TargetVendor = 0x19d2,*/
        /*.TargetProduct = 0xfff1,*/
        .DefaultVendor = 0x19d2,
        .DefaultProduct = 0xfff6,
        .MessageContent = "5553424312345678c00000008000069f030000000000000000000000000000",
    },
    {
        /* BandRich BandLuxe C100, C120, C170, C270, C3xx, C508*/
        /*.TargetVendor = 0x1a8d,*/
        /*.TargetProductList = "1002,1007,1009,100d,2006",*/
        .DefaultVendor = 0x1a8d,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
//        .ReleaseDelay = 4000,
        .NeedResponse = 1,
    },
    {
        /* BandRich BandLuxe C339*/
        /*.TargetVendor = 0x1a8d,*/
        /*.TargetProduct = 0x2006,*/
        .DefaultVendor = 0x1a8d,
        .DefaultProduct = 0x2000,
        .StandardEject = 1,
    },
    {
        /* Hummer DTM5731, Aircard 901 */
        /*.TargetVendor = 0x1ab7,*/
        /*.TargetProductList = "2000,5731",*/
        .DefaultVendor = 0x1ab7,
        .DefaultProduct = 0x5700,
        .StandardEject = 1,
    },
    {
        /* EpiValley SEC-7089 (featured by Alegro and Starcomms / iZAP)*/
        /*.TargetVendor = 0x1b7d,*/
        /*.TargetProduct = 0x0001,*/
        .DefaultVendor = 0x1b7d,
        .DefaultProduct = 0x0700,
        .MessageContent = "555342431234567824000000800008FF05B112AEE102000000000000000000",
    },
    {
        /* ETCOM E300*/
        /*.TargetVendor = 0x1bbb,*/
        /*.TargetProduct = 0x000f,*/
        .DefaultVendor = 0x1bbb,
        .DefaultProduct = 0x000f,
        .StandardEject = 1,
    },
    {
        /* Alcatel OT-X080C*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1bbb,
        .DefaultProduct = 0x00ca,
        .MessageContent = "55534243123456788000000080000606f50402527000000000000000000000",
    },
    {
        /* Haier EVDO Rev. A*/
        /*.TargetVendor = 0x1bbb,*/
        /*.TargetProduct = 0x0106,*/
        .DefaultVendor = 0x1bbb,
        .DefaultProduct = 0x011f,
        .StandardEject = 1,
    },
//     {
//         /* Alcatel X602D*/
//         .DefaultVendor = 0x1bbb,
//         .DefaultProduct = 0x022c,
//         .Configuration = 2,
//     },
    {
        /* Alcatel X200/X200L/X060S/L100V, Archos G9 3G Key*/
        /*.TargetVendor = 0x1bbb,*/
        /*.TargetProductList = "0000,0017,00b7,011e,0191,0195",*/
        .DefaultVendor = 0x1bbb,
        .DefaultProduct = 0xf000,
        .MessageContent = "55534243123456788000000080000606f50402527000000000000000000000",
    },
    {
        /* Alcatel OT-X220D, L100V*/
        /*.TargetVendor = 0x1bbb,*/
        /*.TargetProductList = "0017,011e,0203",*/
        .DefaultVendor = 0x1bbb,
        .DefaultProduct = 0xf017,
        .MessageContent = "55534243123456788000000080000606f50402527000000000000000000000",
    },
    {
        /* Alcatel OT X220L*/
        /*.TargetVendor = 0x1bbb,*/
        /*.TargetProduct = 0x0052,*/
        .DefaultVendor = 0x1bbb,
        .DefaultProduct = 0xf052,
        .MessageContent = "55534243123456788000000080000606f50402527000000000000000000000",
    },
    {
        /* Alcatel One Touch X020*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProductList = "6060,6061",*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x1001,
        .MessageContent = "55534243123456780000000000000606f50402527000000000000000000000",
    },
    {
        /* TU930, IVIO IV-2010u*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x6000,
//        .NoDriverLoading = 1,
        .MessageContent = "55534243123456780000000000000601000000000000000000000000000000",
    },
    {
        /* Vibe 3G Modem */
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x6061,
        .MessageContent = "55534243123456780000000000000606f50402527000000000000000000000",
        .uPr = "Storage",
    },
    {
        /* Emobile D12LC*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProduct = 0x9104,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x9101,
        .MessageContent = "55534243123456780000000000000606f50402527000000000000000000000",
    },
    {
        /* MyWave SW006 Sport Phone/Modem Combination*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProduct = 0x9202,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x9200,
        .MessageContent = "55534243123456780000000000000606f50402527000000000000000000000",
    },
    {
        /* Emobile D21LC*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProduct = 0x9404,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x9401,
        .MessageContent = "55534243123456780000000000000606f50402527000000000000000000000",
    },
    {
        /* Longcheer SU9800*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x9800,
        .MessageContent = "55534243123456788000000080000606f50402527000000000000000000000",
    },
    {
        /* Telewell TW-3G HSPA+, FS01BU 3G, SmartBro WM66E*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProductList = "6801,9801,9803",*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x98ff,
        .MessageContent = "55534243123456780000000080000606f50402527000000000000000000000",
    },
    {
        /* Prolink PCM100*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x9d00,
        .MessageContent = "55534243123456780000000000000606f50402527000000000000000000000",
    },
    {
        /* BSNL Capitel*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x9e00,
        .MessageContent = "55534243123456780000000000000606f50402527000000000000000000000",
    },
    {
        /* Explay Slim*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProduct = 0x9e18,*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0x9e08,
        .ModeMap = SIERRA_MODE,
//        .NoDriverLoading = 1,
    },
    {
        /* MobiData MBD-200HU and others*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProductList = "9000,9603,9605,9607,9900,9a00",*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0xf000,
        .MessageContent = "55534243123456788000000080000606f50402527000000000000000000000",
        .uMa = "USB",
    },
    {
        /* Longcheer/Longsoon (aka Omega Technology) devices*/
        /*.TargetVendor = 0x1c9e,*/
        /*.TargetProductList = "9000,9603,9605,9607,9900",*/
        .DefaultVendor = 0x1c9e,
        .DefaultProduct = 0xf000,
        .MessageContent = "555342431234567800000000000001ff000000000000000000000000000000",
    },
    {
        /* TechFaith BSNL Capitel*/
        /*.TargetVendor = 0x1d09,*/
        /*.TargetProduct = 0x1010,*/
        .DefaultVendor = 0x1d09,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
    },
    {
        /* Aiko 81D*/
        /*.TargetVendor = 0x1d09,*/
        /*.TargetProduct = 0x1010,*/
        .DefaultVendor = 0x1d09,
        .DefaultProduct = 0x1021,
        .StandardEject = 1,
    },
    {
        /* TechFaith FlyingLARK46*/
        /*.TargetVendor = 0x1d09,*/
        /*.TargetProduct = 0x1026,*/
        .DefaultVendor = 0x1d09,
        .DefaultProduct = 0x1025,
        .StandardEject = 1,
    },
    {
        /* Qisda H21 Flying Beetle*/
        /*.TargetVendor = 0x1da5,*/
        /*.TargetProduct = 0x4512,*/
        .DefaultVendor = 0x1da5,
        .DefaultProduct = 0xf000,
        .ModeMap = QISDA_MODE,
    },
//     {
//         /* Wisue W340*/
//         .DefaultVendor = 0x1dbc,
//         .DefaultProduct = 0x0669,
//         .Configuration = 2,
//     },
    {
        /* Solomon S3Gm-660*/
        /*.TargetVendor = 0x1dd6,*/
        /*.TargetProduct = 0x1002,*/
        .DefaultVendor = 0x1dd6,
        .DefaultProduct = 0x1000,
        .MessageContent = "55534243123456781200000080000603000000020000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Philips PicoPix 1020 Projector*/
        /*.TargetVendor = 0x21e7,*/
        /*.TargetProduct = 0x000e,*/
        .DefaultVendor = 0x1de1,
        .DefaultProduct = 0x1101,
        .MessageContent = "55534243123456780000000000000cff020000000000000000000000000000",
    },
    {
        /* Option iCON 210, PROLiNK PHS100 + PH300, Hyundai MB-810, A-Link 3GU*/
        /*.TargetVendor = 0x1e0e,*/
        /*.TargetProductList = "9000,9100,9200",*/
        .DefaultVendor = 0x1e0e,
        .DefaultProduct = 0xf000,
        .MessageContent = "555342431234567800000000000006bd000000020000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* 3GO 3GO11 HSUPA*/
        /*.TargetVendor = 0x1e89,*/
        /*.TargetProduct = 0x1a20,*/
        .DefaultVendor = 0x1e89,
        .DefaultProduct = 0xf000,
        .MessageContent = "5553424312345678800000008000060619181a207000000000000000000000",
    },
//     {
//         /* AirPlus MCD-800*/
//         .DefaultVendor = 0x1edf,
//         .DefaultProduct = 0x6003,
//         .Configuration = 2,
//     },
    {
        /* Onda MV815U*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x0004,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0003,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MW833UP*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x000b,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0009,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MW833UP + MW835UP*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProductList = "0011,0012,0014",*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0013,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MO835UP*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x0017,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0018,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MW836UP-K*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProductList = "003e,003f",*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0040,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MDC655*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x0044,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0045,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MDC655*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x0049,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x004a,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
    },
    {
        /* Onda MDC655 Variant*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x004e,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x004f,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MW875UP*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x0053,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0054,
        .MessageContent = "555342431234567800000000000010ff000000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Onda MSA 14.4 (TIM Brasil)*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x005f,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0060,
        .MessageContent = "555342431234567800000000000008ff000000000000030000000000000000",
    },
    {
        /* Onda TM201 14.4 (TIM Italy)*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x0064,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0063,
        .MessageContent = "555342431234567800000000000008ff000000000000030000000000000000",
    },
    {
        /* Onda WM301*/
        /*.TargetVendor = 0x1ee8,*/
        /*.TargetProduct = 0x0069,*/
        .DefaultVendor = 0x1ee8,
        .DefaultProduct = 0x0068,
        .MessageContent = "555342431234567800000000000008ff000000000000030000000000000000",
    },
    {
        /* Cricket A600*/
        /*.TargetVendor = 0x1f28,*/
        /*.TargetProduct = 0x0020,*/
        .DefaultVendor = 0x1f28,
        .DefaultProduct = 0x0021,
        .MessageContent = "555342431234567824000000800108df200000000000000000000000000000",
    },
//     {
//         /* Franklin Wireless U210 (Variant)*/
//         .DefaultVendor = 0x1fac,
//         .DefaultProduct = 0x0032,
//         .Configuration = 2,
//     },
    {
        /* Franklin Wireless U210*/
        /*.TargetVendor = 0x1fac,*/
        /*.TargetProduct = 0x0131,*/
        .DefaultVendor = 0x1fac,
        .DefaultProduct = 0x0130,
        .MessageContent = "555342431234567824000000800108df200000000000000000000000000000",
    },
    {
        /* Franklin Wireless U600*/
        /*.TargetVendor = 0x1fac,*/
        /*.TargetProduct = 0x0151,*/
        .DefaultVendor = 0x1fac,
        .DefaultProduct = 0x0150,
        .MessageContent = "555342431234567824000000800108df200000000000000000000000000000",
    },
//     {
//         /* Franklin Wireless U600*/
//         .DefaultVendor = 0x1fac,
//         .DefaultProduct = 0x0151,
//         .Configuration = 2,
//     },
    {
        /* D-Link DWM-157 B1*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7d02,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0x00a6,
        .StandardEject = 1,
    },
    {
        /* D-Link DWM-221*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7e16,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0x98ff,
        .MessageContent = "55534243f8d2e6838000000080000606f50402527000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* D-Link DWM-221 B1*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7e19,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa401,
        .MessageContent = "5553424312345678000000000000061e000000000000000000000000000000",
        .MessageContent2 = "5553424312345679000000000001061b000000010000000000000000000000",
        .MessageContent3 = "5553424312345670000000000000061b000000020000000000000000000000",
    },
    {
        /* D-Link DWM-156 A8, DWP-157 B1*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProductList = "7d0b,7d0c",*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa403,
        .StandardEject = 1,
    },
    {
        /* D-Link DWM-167 A1*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7d0d,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa405,
        .StandardEject = 1,
    },
    {
        /* D-Link DWM-156 A7*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7d01,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa706,
        .StandardEject = 1,
    },
    {
        /* D-Link DWM-157 B1*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7d02,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa707,
        .StandardEject = 1,
    },
    {
        /* D-Link DWM-158 D1*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7d03,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa708,
        .StandardEject = 1,
    },
    {
        /* D-Link DWR-510*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7e12,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa805,
        .StandardEject = 1,
    },
    {
        /* D-Link DWM-156 (Variant)*/
        /*.TargetVendor = 0x2001,*/
        /*.TargetProduct = 0x7d00,*/
        .DefaultVendor = 0x2001,
        .DefaultProduct = 0xa80b,
        .MessageContent = "555342431234567800000000000003f0010100000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Haier CE682 (EVDO)*/
        /*.TargetVendor = 0x201e,*/
        /*.TargetProduct = 0x1022,*/
        .DefaultVendor = 0x201e,
        .DefaultProduct = 0x1023,
        .MessageContent = "55534243123456780000000000000600000000000000000000000000000000",
        .MessageContent2 = "5553424312345679c000000080000671030000000000000000000000000000",
        .NeedResponse = 1,
    },
    {
        /* Haier CE 100 */
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x201e,
        .DefaultProduct = 0x2009,
        .StandardEject = 1,
    },
    {
        /* Mediatek MT6229, Micromax MMX 377G, Olicard 300*/
        /*.TargetVendor = 0x2020,*/
        /*.TargetProductList = "2000,4000,4010",*/
        .DefaultVendor = 0x2020,
        .DefaultProduct = 0x0002,
        .MessageContent = "555342430820298900000000000003f0010100000000000000000000000000",
    },
    {
        /* SpeedUp SU-8000*/
        /*.TargetVendor = 0x2020,*/
        /*.TargetProduct = 0x1008,*/
        .DefaultVendor = 0x2020,
        .DefaultProduct = 0xf00e,
        .StandardEject = 1,
    },
    {
        /* SpeedUp SU-8000U*/
        /*.TargetVendor = 0x2020,*/
        /*.TargetProduct = 0x1005,*/
        .DefaultVendor = 0x2020,
        .DefaultProduct = 0xf00f,
        .StandardEject = 1,
    },
    {
        /* Changhong CH690, D-Link DWM-163 + DWM-168*/
        /*.TargetVendor = 0x2077,*/
        /*.TargetProductList = "7001,7010,7011",*/
        .DefaultVendor = 0x2077,
        .DefaultProduct = 0x1000,
        .StandardEject = 1,
    },
    {
        /* Telenet 3G dongle (T&W WU160) and others*/
        /*.TargetVendor = 0x2077,*/
        /*.TargetProductList = "9000,9062,a000",*/
        .DefaultVendor = 0x2077,
        .DefaultProduct = 0xf000,
        .StandardEject = 1,
        .MessageContent = "55534243123456700000000000000616aa0000000000000000000000000000",
    },
    {
        /* Intex 3.5G*/
        /*.TargetVendor = 0x20a6,*/
        /*.TargetProduct = 0x1105,*/
        .DefaultVendor = 0x20a6,
        .DefaultProduct = 0xf00e,
        .StandardEject = 1,
    },
    {
        /* Tlaytech TEU800*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x20b9,
        .DefaultProduct = 0x1682,
        .StandardEject = 1,
    },
    {
        /* StrongRising (China Telcom), Air FlexiNet*/
        /*.TargetVendor = 0x21f5,*/
        /*.TargetProduct = 0x2008,*/
        .DefaultVendor = 0x21f5,
        .DefaultProduct = 0x1000,
        .MessageContent = "5553424312345678c000000080000671010000000000000000000000000000",
    },
    {
        /* StrongRising STD808*/
        /*.TargetVendor = 0x21f5,*/
        /*.TargetProduct = 0x1101,*/
        .DefaultVendor = 0x21f5,
        .DefaultProduct = 0x3010,
        .StandardEject = 1,
    },
    {
        /* Viettel VT100*/
        /*.TargetVendor = 0x2262,*/
        /*.TargetProduct = 0x0002,*/
        .DefaultVendor = 0x2262,
        .DefaultProduct = 0x0001,
        .MessageContent = "5553424340799288C000000080010A16000000C00000000000000000000000",
    },
    {
        /* WeTelecom WM-D200*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x22de,
        .DefaultProduct = 0x6801,
        .StandardEject = 1,
    },
    {
        /* WeTelecom WM-D300*/
        /*.TargetVendor = 0x22de,*/
        /*.TargetProduct = 0x6801,*/
        .DefaultVendor = 0x22de,
        .DefaultProduct = 0x6803,
        .StandardEject = 1,
    },
    {
        /* Tata Photon+*/
        /*.TargetClass = 0x00ff,*/
        .DefaultVendor = 0x22f4,
        .DefaultProduct = 0x0021,
        .StandardEject = 1,
    },
//     {
//         /* Linktop LW272/LW273 (BSNL Teracom)*/
//         .DefaultVendor = 0x230d,
//         .DefaultProduct = 0x0001,
//         .Configuration = 3,
//     },
//     {
//         /* Linktop LW272/LW273 (BSNL Teracom)*/
//         .DefaultVendor = 0x230d,
//         .DefaultProduct = 0x0003,
//         .Configuration = 3,
//     },
//     {
//         /* Visiontek 82GH 3G*/
//         .DefaultVendor = 0x230d,
//         .DefaultProduct = 0x0007,
//         .Configuration = 3,
//     },
//     {
//         /* Zoom 3G*/
//         .DefaultVendor = 0x230d,
//         .DefaultProduct = 0x000b,
//         .Configuration = 3,
//     },
//     {
//         /* Intex Speed 3G v7.2*/
//         .DefaultVendor = 0x230d,
//         .DefaultProduct = 0x000d,
//         .Configuration = 3,
//     },
//     {
//         /* Linktop LW272/LW273*/
//         .DefaultVendor = 0x230d,
//         .DefaultProduct = 0x0101,
//         .Configuration = 2,
//     },
//     {
//         /* Teracom LW272*/
//         .DefaultVendor = 0x230d,
//         .DefaultProduct = 0x0103,
//         .Configuration = 2,
//     },
    {
        /* TP-Link MA180*/
        /*.TargetVendor = 0x2357,*/
        /*.TargetProduct = 0x0201,*/
        .DefaultVendor = 0x2357,
        .DefaultProduct = 0x0200,
        .StandardEject = 1,
    },
    {
        /* TP-Link MA260*/
        /*.TargetVendor = 0x2357,*/
        /*.TargetProduct = 0x9000,*/
        .DefaultVendor = 0x2357,
        .DefaultProduct = 0xf000,
        .StandardEject = 1,
    },
    {
        /* Titan 3.5G*/
        /*.TargetVendor = 0x23a2,*/
        /*.TargetProduct = 0x1234,*/
        .DefaultVendor = 0x23a2,
        .DefaultProduct = 0x1010,
        .MessageContent = "555342431234567800000000000006161f6d62706b00000000000000000000",
    },
    {
        /* Unknown devices*/
        /*.TargetVendor = 0x257a,*/
        /*.TargetProductList = "1601,161f,162f,261f,262f,361f,362f",*/
        .DefaultVendor = 0x257a,
        .DefaultProduct = 0xa000,
        .StandardEject = 1,
    },
    {
        /* Unknown devices*/
        /*.TargetVendor = 0x257a,*/
        /*.TargetProductList = "1601,161f,162f,261f,262f,361f,362f",*/
        .DefaultVendor = 0x257a,
        .DefaultProduct = 0xb000,
        .StandardEject = 1,
    },
    {
        /* Unknown devices*/
        /*.TargetVendor = 0x257a,*/
        /*.TargetProductList = "1601,161f,162f,261f,262f,361f,362f",*/
        .DefaultVendor = 0x257a,
        .DefaultProduct = 0xc000,
        .StandardEject = 1,
    },
    {
        /* Unknown devices*/
        /*.TargetVendor = 0x257a,*/
        /*.TargetProductList = "1601,161f,162f,261f,262f,361f,362f",*/
        .DefaultVendor = 0x257a,
        .DefaultProduct = 0xd000,
        .StandardEject = 1,
    },
    {
        /* Exiss Mobile E-190 series (made by C-motech)*/
        /*.TargetVendor = 0x16d8,*/
        /*.TargetProduct = 0x6533,*/
        .DefaultVendor = 0x8888,
        .DefaultProduct = 0x6500,
        .MessageContent = "5553424398e2c4812400000080000bff524445564348473d43440000000000",
    },
    {
        /* Aiko 81D, fw with wrong vendor ID*/
        /*.TargetVendor = 0xed09,*/
        /*.TargetProduct = 0x1010,*/
        .DefaultVendor = 0xed09,
        .DefaultProduct = 0x1021,
        .StandardEject = 1,
    },
    { } /* Terminating entry */
};
