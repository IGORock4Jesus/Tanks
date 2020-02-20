using SharpDX;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	class Screen
	{
		const float aspect = 4.0f / 3.0f;


		static Screen instance;
		static object locker = new object();
		public static Screen Instance
		{
			get
			{
				if (instance == null)
				{
					lock (locker)
					{
						if (instance == null)
							instance = new Screen();
					}
				}
				return instance;
			}
		}
		Screen() { }

		float width, height;
		internal void Initialize(int width, int height)
		{
			this.width = width;
			this.height = height;
		}
		internal Size2F GetSize()
		{
			return new Size2F(width, height);
		}
	}
}
