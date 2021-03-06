﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Flare_Sharp.Memory.CraftSDK
{
    public class LocalPlayer : Entity
    {
        public UInt64 addr;
        public LocalPlayer(UInt64 addr) : base(addr)
        {
            this.addr = addr;
        }

        public void teleport(float x, float y, float z)
        {
            X1 = x;
            X2 = x;
            Y1 = y;
            Y2 = y;
            Z1 = z;
            Z2 = z;
        }

        public int onGround
        {
            get {
                UInt64[] offs = { 0x178 };
                return MCM.readInt(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x178 };
                MCM.writeInt(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public byte isFlying
        {
            get
            {
                UInt64[] offs = { 0xA88 };
                return MCM.readByte(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0xA88 };
                MCM.writeByte(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public int isInWater
        {
            get
            {
                UInt64[] offs = { 0x23D };
                return MCM.readInt(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x23D };
                MCM.writeInt(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public int currentGamemode
        {
            get
            {
                UInt64[] offs = { 0x1D9C };
                return MCM.readInt(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x1D9C };
                MCM.writeInt(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public int viewCreativeItems
        {
            get
            {
                UInt64[] offs = { 0xAA0 };
                return MCM.readInt(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0xAA0 };
                MCM.writeInt(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public int airAcceleration
        {
            get
            {
                UInt64[] offs = { 0x8A4 };
                return MCM.readInt(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x8A4 };
                MCM.writeInt(MCM.evaluatePointer(addr, offs), value);
            }
        }

        public float X1
        {
            get
            {
                UInt64[] offs = { 0x430 };
                return MCM.readFloat(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x430 };
                MCM.writeFloat(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public float Y1
        {
            get
            {
                UInt64[] offs = { 0x434 };
                return MCM.readFloat(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x434 };
                MCM.writeFloat(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public float Z1
        {
            get
            {
                UInt64[] offs = { 0x438 };
                return MCM.readFloat(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x438 };
                MCM.writeFloat(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public float X2
        {
            get
            {
                UInt64[] offs = { 0x43C };
                return MCM.readFloat(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x43C };
                MCM.writeFloat(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public float Y2
        {
            get
            {
                UInt64[] offs = { 0x440 };
                return MCM.readFloat(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x440 };
                MCM.writeFloat(MCM.evaluatePointer(addr, offs), value);
            }
        }
        public float Z2
        {
            get
            {
                UInt64[] offs = { 0x444 };
                return MCM.readFloat(MCM.evaluatePointer(addr, offs));
            }
            set
            {
                UInt64[] offs = { 0x444 };
                MCM.writeFloat(MCM.evaluatePointer(addr, offs), value);
            }
        }
    }
}
