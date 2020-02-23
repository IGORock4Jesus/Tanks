using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Tanks
{
	public partial class MainForm : Form
	{
        private Thread updateThread;
        private bool updateEnabled;

        public MainForm()
		{
			InitializeComponent();
		}

		protected override void OnLoad(EventArgs e)
		{
			Renderer.Instance.Initialize(this);
			Screen.Instance.Initialize(ClientSize.Width, ClientSize.Height);
			ResourceManager.Instance.LoadAll();
			
			Renderer.Instance.Device.SetTexture(0, ResourceManager.Instance.GetTexture("main"));
			Renderer.Instance.Device.VertexFormat = SharpDX.Direct3D9.VertexFormat.Position | SharpDX.Direct3D9.VertexFormat.Texture1;

            updateThread = new Thread(StartUpdating);
            updateEnabled = true;
            updateThread.Start();

			LevelConstructor.Instance.Construct(ResourceManager.Instance.GetLevel(28.ToString()));
		}

        private void StartUpdating()
        {
            int oldTime = Environment.TickCount;
            while (updateEnabled)
            {
                int newTime = Environment.TickCount;
                float elapsedTime = (newTime - oldTime) * 0.001f;
                oldTime = newTime;

                Scene.Instance.Update(elapsedTime);

                AnimationManager.Instance.Update(elapsedTime);

                Thread.Sleep(0);
            }
        }

        protected override void OnFormClosed(FormClosedEventArgs e)
		{
            updateEnabled = false;
            if (updateThread.IsAlive)
                updateThread.Join();
			Renderer.Instance.Dispose();
		}

		protected override void OnKeyDown(KeyEventArgs e)
		{
			if (e.KeyCode == Keys.Escape)
				Close();

			Input.Instance[GetKeyName(e.KeyCode)] = true;
		}
		protected override void OnKeyUp(KeyEventArgs e)
		{
			Input.Instance[GetKeyName(e.KeyCode)] = false;
		}

		private string GetKeyName(Keys keyCode)
		{
			switch (keyCode)
			{
                case Keys.Tab:
                    return "Tab";
                case Keys.Enter:
                    return "Enter";
                case Keys.ShiftKey:
                    return "Shift";
                case Keys.ControlKey:
                    return "Control";
                case Keys.Pause:
                    return "Pause";
                case Keys.CapsLock:
                    break;
                case Keys.Escape:
                    return "Escape";
                case Keys.Space:
                    return "Space";
                case Keys.PageUp:
                    break;
                case Keys.PageDown:
                    break;
                case Keys.End:
                    break;
                case Keys.Home:
                    break;
                case Keys.Left:
                    break;
                case Keys.Up:
                    break;
                case Keys.Right:
                    break;
                case Keys.Down:
                    break;
                case Keys.Select:
                    break;
                case Keys.Print:
                    break;
                case Keys.Execute:
                    break;
                case Keys.PrintScreen:
                    break;
                case Keys.Insert:
                    break;
                case Keys.Delete:
                    break;
                case Keys.Help:
                    break;
                case Keys.D0:
                    break;
                case Keys.D1:
                    break;
                case Keys.D2:
                    break;
                case Keys.D3:
                    break;
                case Keys.D4:
                    break;
                case Keys.D5:
                    break;
                case Keys.D6:
                    break;
                case Keys.D7:
                    break;
                case Keys.D8:
                    break;
                case Keys.D9:
                    break;
                case Keys.A:
                    return "A";
                case Keys.B:
                    break;
                case Keys.C:
                    break;
                case Keys.D:
                    return "D";
                case Keys.E:
                    break;
                case Keys.F:
                    break;
                case Keys.G:
                    break;
                case Keys.H:
                    break;
                case Keys.I:
                    return "I";
                case Keys.J:
                    return "J";
                case Keys.K:
                    return "K";
                case Keys.L:
                    break;
                case Keys.M:
                    break;
                case Keys.N:
                    break;
                case Keys.O:
                    break;
                case Keys.P:
                    break;
                case Keys.Q:
                    break;
                case Keys.R:
                    break;
                case Keys.S:
                    return "S";
                case Keys.T:
                    break;
                case Keys.U:
                    return "U";
                case Keys.V:
                    break;
                case Keys.W:
                    return "W";
                case Keys.X:
                    break;
                case Keys.Y:
                    break;
                case Keys.Z:
                    break;
                case Keys.LWin:
                    break;
                case Keys.RWin:
                    break;
                case Keys.Apps:
                    break;
                case Keys.Sleep:
                    break;
                case Keys.NumPad0:
                    break;
                case Keys.NumPad1:
                    break;
                case Keys.NumPad2:
                    break;
                case Keys.NumPad3:
                    break;
                case Keys.NumPad4:
                    break;
                case Keys.NumPad5:
                    break;
                case Keys.NumPad6:
                    break;
                case Keys.NumPad7:
                    break;
                case Keys.NumPad8:
                    break;
                case Keys.NumPad9:
                    break;
                case Keys.Multiply:
                    break;
                case Keys.Add:
                    break;
                case Keys.Separator:
                    break;
                case Keys.Subtract:
                    break;
                case Keys.Decimal:
                    break;
                case Keys.Divide:
                    break;
                case Keys.F1:
                    break;
                case Keys.F2:
                    break;
                case Keys.F3:
                    break;
                case Keys.F4:
                    break;
                case Keys.F5:
                    break;
                case Keys.F6:
                    break;
                case Keys.F7:
                    break;
                case Keys.F8:
                    break;
                case Keys.F9:
                    break;
                case Keys.F10:
                    break;
                case Keys.F11:
                    break;
                case Keys.F12:
                    break;
                case Keys.F13:
                    break;
                case Keys.F14:
                    break;
                case Keys.F15:
                    break;
                case Keys.F16:
                    break;
                case Keys.F17:
                    break;
                case Keys.F18:
                    break;
                case Keys.F19:
                    break;
                case Keys.F20:
                    break;
                case Keys.F21:
                    break;
                case Keys.F22:
                    break;
                case Keys.F23:
                    break;
                case Keys.F24:
                    break;
                case Keys.NumLock:
                    break;
                case Keys.Scroll:
                    break;
                case Keys.LShiftKey:
                    break;
                case Keys.RShiftKey:
                    break;
                case Keys.LControlKey:
                    break;
                case Keys.RControlKey:
                    break;
                case Keys.LMenu:
                    break;
                case Keys.RMenu:
                    break;
                case Keys.BrowserBack:
                    break;
                case Keys.BrowserForward:
                    break;
                case Keys.BrowserRefresh:
                    break;
                case Keys.BrowserStop:
                    break;
                case Keys.BrowserSearch:
                    break;
                case Keys.BrowserFavorites:
                    break;
                case Keys.BrowserHome:
                    break;
                case Keys.VolumeMute:
                    break;
                case Keys.VolumeDown:
                    break;
                case Keys.VolumeUp:
                    break;
                case Keys.MediaNextTrack:
                    break;
                case Keys.MediaPreviousTrack:
                    break;
                case Keys.MediaStop:
                    break;
                case Keys.MediaPlayPause:
                    break;
                case Keys.LaunchMail:
                    break;
                case Keys.SelectMedia:
                    break;
                case Keys.LaunchApplication1:
                    break;
                case Keys.LaunchApplication2:
                    break;
                case Keys.ProcessKey:
                    break;
                case Keys.Packet:
                    break;
                case Keys.Attn:
                    break;
                case Keys.Crsel:
                    break;
                case Keys.Exsel:
                    break;
                case Keys.EraseEof:
                    break;
                case Keys.Play:
                    break;
                case Keys.Zoom:
                    break;
                case Keys.NoName:
                    break;
                case Keys.Pa1:
                    break;
                case Keys.OemClear:
                    break;
                case Keys.Shift:
                    break;
                case Keys.Control:
                    break;
                case Keys.Alt:
                    break;
                default:
                    break;
			}
            return "Unknown";
		}
	}
}
