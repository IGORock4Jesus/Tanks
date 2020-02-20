using SharpDX;
using SharpDX.Direct3D9;
using System;
using System.Threading;

namespace Tanks
{
	class Renderer:IDisposable
	{
		public int Width { get; private set; }
		public int Height { get; private set; }

		Direct3D direct;
		Device device;
		private Thread thread;
		private bool enabled;

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

		public Device Device => device;

		public void Initialize(System.Windows.Forms.Control control)
		{
			this.Width = control.ClientSize.Width;
			this.Height = control.ClientSize.Height;

			direct = new Direct3D();
			device = new Device(direct, 0, DeviceType.Hardware, control.Handle, CreateFlags.HardwareVertexProcessing | CreateFlags.Multithreaded, new PresentParameters
			{
				AutoDepthStencilFormat = Format.D24S8,
				BackBufferCount = 1,
				BackBufferFormat = Format.A8R8G8B8,
				BackBufferHeight = control.ClientSize.Height,
				BackBufferWidth = control.ClientSize.Width,
				DeviceWindowHandle = control.Handle,
				EnableAutoDepthStencil = true,
				SwapEffect = SwapEffect.Discard,
				Windowed = true
			});

			device.SetRenderState(RenderState.Lighting, false);

			thread = new Thread(StartRendering);
			enabled = true;
			thread.Start();
		}

		private void StartRendering()
		{
			while (enabled)
			{
				device.Clear(ClearFlags.All, SharpDX.Color.Black, 1.0f, 0);
				device.BeginScene();

				Matrix view = Matrix.LookAtLH(
					new Vector3(Width / 2, Height / 2, 1000.0f),
					new Vector3(Width / 2, Height / 2, 0.0f),
					new Vector3(0.0f, -1.0f, 0.0f));
				device.SetTransform(TransformState.View, view);

				Matrix proj = Matrix.OrthoLH(Width, Height, 1.0f, 10000.0f);
				device.SetTransform(TransformState.Projection, proj);

				Scene.Instance.Render();

				device.EndScene();
				device.Present();

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

			device.Dispose();
			direct.Dispose();
		}
	}
}
