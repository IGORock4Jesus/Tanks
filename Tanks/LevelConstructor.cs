using SharpDX;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using Tanks.Game;

namespace Tanks
{
	class LevelConstructor
	{
		#region Singleton
		static LevelConstructor instance;
		static object locker = new object();
		public static LevelConstructor Instance
		{
			get
			{
				if (instance == null)
				{
					lock (locker)
					{
						if (instance == null)
							instance = new LevelConstructor();
					}
				}
				return instance;
			}
		}
		LevelConstructor() { }

		#endregion

		readonly Dictionary<char, IConstructor> matching = new Dictionary<char, IConstructor>
		{
			{'.', new VoidConstructor() },
			{'#', new BrickConstructor() },
			{'@', new ConcreteConstructor() },
			{'%', new ForestConstructor() },
			{'~', new WaterConstructor() },
			{'-', new IceConstructor() },
		};

		public void Construct(Level level)
		{
			var screenSize = Screen.Instance.GetSize();
			Scene scene = Scene.Instance;
			scene.Clear();

			float blockSize = Math.Min(screenSize.Width, screenSize.Height) / level.Width;

			for (int y = 0; y < level.Height; y++)
			{
				for (int x = 0; x < level.Width; x++)
				{
					if (matching.ContainsKey(level[x, y]) == false)
						throw new Exception($"Конструктор уравня для элемента '{level[x, y]}' - не реализован!");

					var constructor = matching[level[x, y]];
					var block = constructor.Construct();
					if (block == null)
						continue;

					block.Position = new Vector2(x * blockSize, y * blockSize);
					block.Size = new Vector2(blockSize, blockSize);

					scene.Add(block);
				}
			}
		}
	}
}
