﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Flare_Sharp.Memory.CraftSDK
{
    public class Pointers
    {
        public static UInt64 entityFacing()
        {
            UInt64[] offs = { 0xA8, 0x20, 0x38, 0x728, 0x0, 0x870 };
            return MCM.baseEvaluatePointer(0x02FEE4B0, offs);
        }
        public static Int64 attackSwing()
        {
            return 0x102460E;
        }
    }
}
