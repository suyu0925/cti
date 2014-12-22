using System;
using System.Collections.Generic;
using System.Text;

namespace DJKeygoe
{
    using DJ_U8 = Byte;
    using DJ_S8 = SByte;
    using DJ_U16 = UInt16;
    using DJ_S16 = Int16;
    using DJ_U32 = UInt32;
    using DJ_S32 = Int32;
    using DJ_U64 = UInt64;
    using DJ_S64 = Int64;
    using DJ_UI32 = UInt32;
    using DJ_SI32 = Int32;
    using DJ_F64 = Double;
    using RetCode_t = Int32;
    using ACSHandle_t = UInt32;
    using InvokeID_t = Int32;
    using LoginID_t = SByte;
    using EventClass_t = Int32;
    using EventType_t = Int32;
    using ACSConfirmation_t = Int32;
    using CallNum_t = SByte;
    using AcsCmdTye_t = Int32;

    using FlowType_t = Int32;
    using FlowChannel_t = Int32;
    using DeviceMain_t = Int16;
    using DeviceSub_t = Int16;
    using DeviceGroup_t = Int16;
    using ModuleID_t = SByte;
    using ChannelID_t = Int16;
    using ParmName_t = SByte;
    using ParmSize_t = Int32;
    using Version_t = Int32;
    using ACSUniversalFailure_t = Int32;
    using PlayCont_t = SByte;
    using FilePath_t = SByte;

    using Acs_Evt_State_t = Int32;
    using Acs_Evt_ErrCode_t = Int32;
    using Acs_MediaProc_Dtmf_t = SByte;
    using DJ_SOCKET = UInt32;
}
