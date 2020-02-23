using SharpDX;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	class GameObject : IDisposable
	{
		public virtual void Dispose()
		{
		}

		public virtual void Update(float elapsedTime)
		{

		}

		public virtual void Render()
		{
			Sprite.Render(Position, Depth?.Value ?? 0.0f, Size, TextureCoords);
		}

		public Vector2 Position { get; set; }
		public Depth Depth { get; set; }
		public Vector2 Size { get; set; }
		public RectangleF TextureCoords { get; set; }
	}
}
