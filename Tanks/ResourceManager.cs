using SharpDX.Direct3D11;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Tanks.Graphics;
using VertexShader = Tanks.Graphics.VertexShader;
using PixelShader = Tanks.Graphics.PixelShader;


namespace Tanks
{
	class ResourceManager : IDisposable
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
		Dictionary<string, VertexShader> vertexShaders = new Dictionary<string, VertexShader>();
		Dictionary<string, PixelShader> pixelShaders = new Dictionary<string, PixelShader>();
		Dictionary<string, ShaderResourceView> textures = new Dictionary<string, ShaderResourceView>();

		internal void LoadAll()
		{
			// shaders
			foreach (var file in Directory.EnumerateFiles("..\\..\\Shaders\\VertexShaders\\", "*.hlsl"))
			{
				var name = Path.GetFileNameWithoutExtension(file);

				vertexShaders[name] = new VertexShader(file);
			}
			foreach (var file in Directory.EnumerateFiles("..\\..\\Shaders\\PixelShaders\\", "*.hlsl"))
			{
				var name = Path.GetFileNameWithoutExtension(file);

				pixelShaders[name] = new PixelShader(file);
			}
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

		private ShaderResourceView LoadTexture(string file)
		{
			var texture = TextureLoader
			ShaderResourceView shaderResourceView = ShaderResourceView()
		}

		public void Dispose()
		{
			foreach (var shader in pixelShaders)
			{
				shader.Value.Dispose();
			}
			foreach (var shader in vertexShaders)
			{
				shader.Value.Dispose();
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
