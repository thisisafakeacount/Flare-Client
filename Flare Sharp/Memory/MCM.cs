﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Flare_Sharp.Memory
{
    /*
     * My awesome memory lib i used in FAKE
     * - ASM
     */
    public class MCM
    {
        [DllImport("kernel32", SetLastError = true)]
        public static extern int ReadProcessMemory(IntPtr hProcess, UInt64 lpBase, ref UInt64 lpBuffer, int nSize, int lpNumberOfBytesRead);
        [DllImport("kernel32", SetLastError = true)]
        public static extern int WriteProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, ref byte lpBuffer, int nSize, int lpNumberOfBytesWritten);
        [DllImport("kernel32", SetLastError = true)]
        public static extern int VirtualProtectEx(IntPtr hProcess, IntPtr lpAddress, int dwSize, Int64 flNewProtect, ref Int64 lpflOldProtect
        );
        [DllImport("kernel32.dll")]
        public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);
        [DllImport("user32.dll")]
        static extern IntPtr GetForegroundWindow();
        [DllImport("user32.dll", SetLastError = true)]
        static extern bool GetWindowRect(IntPtr hWnd, out RECT lpRect);
        [DllImport("user32.dll", SetLastError = true)]
        static extern bool GetWindow(IntPtr hWnd, uint uCmd);
        [DllImport("user32.dll", SetLastError = true)]
        static extern bool IsWindowVisible(IntPtr hWnd);
        [DllImport("user32.dll")]
        static extern int GetWindowText(IntPtr hWnd, StringBuilder text, int count);
        [StructLayout(LayoutKind.Sequential)]
        public struct RECT
        {
            public int Left;
            public int Top;
            public int Right;
            public int Bottom;
        }

        public static IntPtr mcProcHandle;
        public static ProcessModule mcMainModule;
        public static IntPtr mcBaseAddress;
        public static IntPtr mcWinHandle;

        public static void openGame()
        {
            Process[] procs = Process.GetProcessesByName("Minecraft.Windows");
            Process mcw10 = procs[0];
            IntPtr proc = OpenProcess(0x1F0FFF, false, mcw10.Id);
            mcProcHandle = proc;
            mcMainModule = mcw10.MainModule;
            mcBaseAddress = mcMainModule.BaseAddress;
        }
        public static void openWindowHost()
        {
            Process[] procs = Process.GetProcessesByName("ApplicationFrameHost");
            mcWinHandle = procs[0].MainWindowHandle;
        }

        public static RECT getMinecraftRect()
        {
            RECT rectMC = new RECT();
            GetWindowRect(mcWinHandle, out rectMC);
            return rectMC;
        }
        public static bool isMinecraftFocused()
        {
            StringBuilder sb = new StringBuilder("Minecraft".Length + 1);
            GetWindowText(GetForegroundWindow(), sb, "Minecraft".Length + 1);
            return sb.ToString() == "Minecraft";
        }

        public static void unprotectMemory(IntPtr address, int bytesToUnprotect)
        {
            Int64 receiver = 0;
            VirtualProtectEx(mcProcHandle, address, bytesToUnprotect, 0x40, ref receiver);
        }

        //CE bytes to real bytes for ease
        public static byte[] ceByte2Bytes(string byteString)
        {
            string[] byteStr = byteString.Split(' ');
            byte[] bytes = new byte[byteStr.Length];
            int c = 0;
            foreach (string b in byteStr)
            {
                bytes[c] = (Convert.ToByte(b, 16));
                c++;
            }
            return bytes;
        }
        public static int[] ceByte2Ints(string byteString)
        {
            string[] intStr = byteString.Split(' ');
            int[] ints = new int[intStr.Length];
            int c = 0;
            foreach (string b in intStr)
            {
                ints[c] = (int.Parse(b, System.Globalization.NumberStyles.HexNumber));
                c++;
            }
            return ints;
        }

        public static UInt64 baseEvaluatePointer(UInt64 offset, UInt64[] offsets)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, (UInt64)mcBaseAddress + offset, ref buffer, sizeof(UInt64), 0);
            for (int i = 0; i < offsets.Length - 1; i++)
            {
                ReadProcessMemory(mcProcHandle, (UInt64)(buffer + offsets[i]), ref buffer, sizeof(UInt64), 0);
            }
            return buffer + offsets[offsets.Length - 1];
        }
        public static UInt64 evaluatePointer(UInt64 addr, UInt64[] offsets)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, addr, ref buffer, sizeof(UInt64), 0);
            for (int i = 0; i < offsets.Length - 1; i++)
            {
                ReadProcessMemory(mcProcHandle, (UInt64)(buffer + offsets[i]), ref buffer, sizeof(UInt64), 0);
            }
            return buffer + offsets[offsets.Length - 1];
        }

        //Read base
        public static int readBaseByte(int offset)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, (UInt64)(mcBaseAddress + offset), ref buffer, sizeof(byte), 0);
            return (byte)buffer;
        }
        public static int readBaseInt(int offset)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, (UInt64)(mcBaseAddress + offset), ref buffer, sizeof(int), 0);
            return (int)buffer;
        }
        public static UInt64 readBaseInt64(int offset)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, (UInt64)(mcBaseAddress + offset), ref buffer, sizeof(Int64), 0);
            return buffer;
        }

        //Write base
        public static void writeBaseByte(int offset, byte value)
        {
            WriteProcessMemory(mcProcHandle, (mcBaseAddress + offset), ref value, sizeof(byte), 0);
        }
        public static void writeBaseInt(int offset, int value)
        {
            byte[] intByte = BitConverter.GetBytes(value);
            int inc = 0;
            foreach (byte b in intByte)
            {
                writeBaseByte(offset + inc, b);
                inc++;
            }
        }
        public static void writeBaseBytes(int offset, byte[] value)
        {
            int inc = 0;
            foreach (byte b in value)
            {
                writeBaseByte(offset + inc, b);
                inc++;
            }
        }
        public static void writeBaseFloat(int offset, float value)
        {
            byte[] intByte = BitConverter.GetBytes(value);
            int inc = 0;
            foreach (byte b in intByte)
            {
                writeBaseByte(offset + inc, b);
                inc++;
            }
        }

        //Read direct
        public static byte readByte(UInt64 address)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, address, ref buffer, sizeof(byte), 0);
            return (byte)buffer;
        }
        public static int readInt(UInt64 address)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, address, ref buffer, sizeof(int), 0);
            return (int)buffer;
        }
        public static float readFloat(UInt64 address)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, address, ref buffer, sizeof(float), 0);
            return buffer;
        }
        public static UInt64 readInt64(UInt64 address)
        {
            UInt64 buffer = 0;
            ReadProcessMemory(mcProcHandle, address, ref buffer, sizeof(int), 0);
            return buffer;
        }

        //Write direct
        public static void writeByte(UInt64 address, byte value)
        {
            WriteProcessMemory(mcProcHandle, (IntPtr)address, ref value, sizeof(byte), 0);
        }
        public static void writeBytes(UInt64 address, byte[] value)
        {
            int inc = 0;
            foreach (byte b in value)
            {
                writeByte(address + (UInt64)inc, b);
                inc++;
            }
        }
        public static void writeInt(UInt64 address, int value)
        {
            byte[] intByte = BitConverter.GetBytes(value);
            int inc = 0;
            foreach (byte b in intByte)
            {
                writeByte(address + (UInt64)inc, b);
                inc++;
            }
        }
        public static void writeFloat(UInt64 address, float value)
        {
            byte[] intByte = BitConverter.GetBytes(value);
            int inc = 0;
            foreach (byte b in intByte)
            {
                writeByte(address + (UInt64)inc, b);
                inc++;
            }
        }
    }
}
