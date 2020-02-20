using SharpDX;
using SharpDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class Block : GameObject
	{
		Sprite sprite = new Sprite();
		private Vector2 position;
		private float depth;
		private Vector2 size;

		public Vector2 Position
		{
			get => position;
			set
			{
				position = value;
				sprite.Position = new Vector3(position, depth);
			}
		}
		public float Depth
		{
			get => depth;
			set
			{
				depth = value;
				sprite.Position = new Vector3(position, depth);
			}
		}
		public Vector2 Size
		{
			get => size;
			set
			{
				size = value;
				sprite.Size = new Vector3(size, 1.0f);
			}
		}
		public Texture Texture
		{
			get => sprite.Texture;
			set => sprite.Texture = value;
		}

		public override void Render()
		{
			sprite.Render();
		}
	}
}
