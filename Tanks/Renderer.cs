using SharpDX.Direct3D11;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Tanks
{
	class Renderer:IDisposable
	{
		SharpDX.Direct3D11.Device device3d;
		SharpDX.Direct3D11.DeviceContext deviceContext3d;
		private Thread thread;
		private bool enabled;
		SharpDX.DXGI.SwapChain swapChain;
		SharpDX.Direct3D11.RenderTargetView renderTargetView;

		static Renderer instance;
		static object locker = new object();
		Renderer() { }
		public static Renderer Instance
		{
			get
			{
				if (instance == null)
				{
					lock (locker)
					{
						if (instance == null)
							instance = new Renderer();
					}
				}
				return instance;
			}
		}

		public Device Device3D => device3d;

		public void Initialize(System.Windows.Forms.Control control)
		{
			SharpDX.Direct3D11.Device.CreateWithSwapChain(SharpDX.Direct3D.DriverType.Warp, SharpDX.Direct3D11.DeviceCreationFlags.Debug,
				new SharpDX.DXGI.SwapChainDescription
				{
					BufferCount = 1,
					Flags = SharpDX.DXGI.SwapChainFlags.None,
					IsWindowed = true,
					ModeDescription = new SharpDX.DXGI.ModeDescription
					{
						Format = SharpDX.DXGI.Format.R8G8B8A8_UNorm,
						Height = control.ClientSize.Height,
						RefreshRate = new SharpDX.DXGI.Rational(1, 60),
						Width = control.ClientSize.Width
					},
					OutputHandle = control.Handle,
					SampleDescription = new SharpDX.DXGI.SampleDescription(1, 0),
					SwapEffect = SharpDX.DXGI.SwapEffect.Discard,
					Usage = SharpDX.DXGI.Usage.RenderTargetOutput
				},
				out device3d,
				out swapChain
			);
			deviceContext3d = device3d.ImmediateContext;

			var backBuffer = swapChain.GetBackBuffer<Texture2D>(0);
			renderTargetView = new SharpDX.Direct3D11.RenderTargetView(device3d, backBuffer);

			thread = new Thread(StartRendering);
			enabled = true;
			thread.Start();
		}

		private void StartRendering()
		{
			while (enabled)
			{
				deviceContext3d.ClearRenderTargetView(renderTargetView, SharpDX.Color.Black);

				swapChain.Present(0, SharpDX.DXGI.PresentFlags.None);

				Thread.Sleep(0);
			}
		}

		public void Dispose()
		{
			if (enabled)
			{
				enabled = false;
				if (thread.IsAlive)
				{
					thread.Join();
				}
			}

			deviceContext3d.Dispose();
			device3d.Dispose();
			swapChain.Dispose();
		}
	}
}
