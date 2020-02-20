using System;
using System.Collections.Generic;
using System.IO;
using SharpDX.Direct3D9;

namespace Tanks
{
	class ResourceManager : IDisposable
	{
		ResourceManager() { }
		static ResourceManager instance;
		static object locker = new object();

		internal Texture GetTexture(string name)
		{
			return textures[name];
		}

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

		internal void LoadAll()
		{
			// levels
			foreach (var file in Directory.EnumerateFiles("..\\resources\\levels\\"))
			{
				var name = Path.GetFileNameWithoutExtension(file);

				levels[name] = LoadLevel(file);
			}
			// pictures
			foreach (var file in Directory.EnumerateFiles("..\\resources\\img\\", "*.png"))
			{
				var name = Path.GetFileNameWithoutExtension(file);
				textures[name] = LoadTexture(file);
			}
		}

		private Texture LoadTexture(string file)
		{
			return  Texture.FromFile(Renderer.Instance.Device, file);
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
