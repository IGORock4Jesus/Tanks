using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices.ComTypes;
using SharpDX;
using SharpDX.Direct3D9;

namespace Tanks
{
	partial class ResourceManager : IDisposable
	{
		ResourceManager() { }

		static ResourceManager instance;
		static object locker = new object();
		public static ResourceManager Instance
		{
			get
			{
				if (instance == null)
				{
					lock (locker)
					{
						if (instance == null)
							instance = new ResourceManager();
					}
				}
				return instance;
			}
		}

		Dictionary<string, Level> levels = new Dictionary<string, Level>();
		Dictionary<string, Texture> textures = new Dictionary<string, Texture>();
		readonly Size2 textureSize = new Size2(1216, 512);


		internal Texture GetTexture(string name)
		{
			return textures[name];
		}

		internal void LoadAll()
		{
			// levels
			foreach (var file in Directory.EnumerateFiles("..\\resources\\levels\\"))
			{
				var name = Path.GetFileNameWithoutExtension(file);

				levels[name] = LoadLevel(file);
			}
			// pictures
			//foreach (var file in Directory.EnumerateFiles("..\\resources\\img\\", "*.png"))
			//{
			//	var name = Path.GetFileNameWithoutExtension(file);
			//	textures[name] = LoadTexture(file);
			//}
			// load one big texture
			textures["main"] = LoadTexture("..\\resources\\png\\texture.png");
		}

		internal enum Pack
		{
			Tanks, Bonuses, Walls, Flags, TankCursors, Protects, ConstructorCursors, Bullets, Generators, FlagExplosions, Explosions, Title
		}

		/// <summary>
		/// Возвращает координаты подкартинки в текстуре.
		/// </summary>
		/// <param name="pack">Тип требуемого изображения.</param>
		/// <param name="direction">Направление.
		/// Если у картинки нет направления - Top.</param>
		/// <param name="frame">Индекс анимационного кадра.</param>
		/// <returns></returns>
		internal RectangleF GetCoords(Pack pack, Direction direction = Direction.Top, int frame = 0, int tankLevel = 1)
		{
			switch (pack)
			{
				case Pack.Tanks:
					//return TanksCoords(direction, frame, tankLevel);
				case Pack.Bonuses:
					break;
				case Pack.Walls:
					break;
				case Pack.Flags:
					break;
				case Pack.TankCursors:
					break;
				case Pack.Protects:
					break;
				case Pack.ConstructorCursors:
					break;
				case Pack.Bullets:
					break;
				case Pack.Generators:
					break;
				case Pack.FlagExplosions:
					break;
				case Pack.Explosions:
					break;
				case Pack.Title:
					break;
				default:
					break;
			}
			throw new NotImplementedException();
		}

		public RectangleF TanksCoords(TankType type, Direction direction, TankLevel tankLevel, int frame)
		{
			const int size = 32;
			tankLevel--;

			int typeIndex = (int)type;
			int dirIndex = (int)direction;

			RectangleF rectangle = new RectangleF(
				typeIndex * size * 4 + dirIndex * size,
				(int)tankLevel * size * 2 + frame * size,
				size, size
				);

			return Convert(rectangle);
		}

		public enum Wall
		{
			Brick_Whole,
			Brick_Top,
			Brick_Right,
			Brick_Bottom,
			Brick_Left,
			Brick_RightTop,
			Brick_RightBottom,
			Brick_LeftTop,
			Brick_LeftBottom,
			Concrete,
			Water_1,
			Water_2,
			Forest,
			Ice,
			Unknown
		}
		public RectangleF GetWallCoords(Wall wall)
		{
			const int x = 928;
			const int size = 16;
			int y = size * (int)wall;
			return Convert(new RectangleF(x, y, size, size));
		}

		private RectangleF Convert(RectangleF rectangle)
		{
			return new RectangleF(
							rectangle.X/textureSize.Width,
							rectangle.Y/textureSize.Height,
							rectangle.Width/ textureSize.Width,
							rectangle.Height/textureSize.Height
							);
		}

		internal RectangleF GetFlagCoords()
		{
			return Convert(new RectangleF(944, 0, 32, 32));
		}


		private Texture LoadTexture(string file)
		{
			return Texture.FromFile(Renderer.Instance.Device, file);
		}

		public void Dispose()
		{
			foreach (var texture in textures)
			{
				texture.Value.Dispose();
			}
		}

		Level LoadLevel(string filename)
		{
			var lines = File.ReadAllLines(filename);
			if (lines.Length == 0)
				throw new Exception("Файл уровня имеет неверный формат.");

			Level level = new Level(lines[0].Length, lines.Length);

			for (int y = 0; y < lines.Length; y++)
			{
				for (int x = 0; x < lines[y].Length; x++)
				{
					level[x, y] = lines[y][x];
				}
			}

			return level;
		}

		public Level GetLevel(string name)
		{
			return levels[name];
		}
	}
}
