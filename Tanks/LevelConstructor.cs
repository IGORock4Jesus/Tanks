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

		public float BlockSize { get; private set; }
		public int MinBlockCount { get; private set; }
		public float MinBlockSize { get; private set; }


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

			BlockSize = Math.Min(screenSize.Width, screenSize.Height) / level.Width;

			MinBlockCount = level.Width * 2;
			MinBlockSize = BlockSize / 2.0f;

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

					block.Position = new Vector2(x * BlockSize, y * BlockSize);
					block.Size = new Vector2(BlockSize, BlockSize);


					scene.Add(block);
				}
			}

			// add flag
			Flag flag = new Flag
			{
				Position = new Vector2(12 * BlockSize, 24 * BlockSize),
				Depth = Depth.Action,
				Size = new Vector2(BlockSize, BlockSize)*2.0f
			};
			scene.Add(flag);

			// demo: add user tank
			Tank userTank = new Tank(new UserTankController(), 0)
			{
				Position = new Vector2(8 * BlockSize, 24 * BlockSize),
				Size = new Vector2(BlockSize, BlockSize) * 2.0f,
				Depth = Depth.Action,
				TextureCoords = ResourceManager.Instance.TanksCoords(ResourceManager.TankType.User_1, Direction.Top, TankLevel.Level1, 0)
			};
			scene.Add(userTank);
		}
	}
}
