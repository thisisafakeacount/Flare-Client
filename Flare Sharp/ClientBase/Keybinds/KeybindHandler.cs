﻿using Flare_Sharp.UI;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Flare_Sharp.ClientBase.Keybinds
{
    public class KeybindHandler
    {
        [DllImport("user32", SetLastError = true)]
        public static extern bool GetAsyncKeyState(char vKey);

        public static KeybindHandler handler;
        public static EventHandler<ClientKeyEvent> clientKeyEvent;

        Dictionary<char, uint> keyBuffs = new Dictionary<char, uint>();
        Dictionary<char, bool> noKey = new Dictionary<char, bool>();

        public KeybindHandler()
        {
            handler = this;
            Console.WriteLine("Starting key thread");
            Thread keyThread = new Thread(()=>
            {
                while (true)
                {
                    for (char c = (char)0; c < 0xFF; c++)
                    {
                        noKey[c] = true;
                        if (GetAsyncKeyState(c))
                        {
                            noKey[c] = false;
                            if (keyBuffs[c] > 0)
                            {
                                continue;
                            }
                            keyBuffs[c]++;
                            TabUI.ui.Invalidate();
                            clientKeyEvent.Invoke(this, new ClientKeyEvent(c));
                        }
                        if (noKey[c])
                        {
                            keyBuffs[c] = 0;
                        }
                    }
                    Thread.Sleep(10);
                }
            });
            keyThread.Start();
            Console.WriteLine("key thread started");
        }

        public void onKey(object sender, ClientKeyEvent e)
        {
            
        }
    }
    public class ClientKeyEvent : EventArgs
    {
        public char key;
        public ClientKeyEvent(char key)
        {
            this.key = key;
        }
    }
}
