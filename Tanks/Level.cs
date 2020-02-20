using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	class Level
	{
		char[,] blocks;

		public Level(int width, int height)
		{
			Width = width;
			Height = height;

			blocks = new char[width, height];
		}

		public int Width { get; }
		public int Height { get; }

		public char this[int x, int y]
		{
			get
			{
				if (x < 0 || x >= Width || y < 0 || y >= Height)
					throw new ArgumentOutOfRangeException();
				return blocks[x, y];
			}
			set
			{
				if (x < 0 || x >= Width || y < 0 || y >= Height)
					throw new ArgumentOutOfRangeException();
				blocks[x, y] = value;
			}
		}
	}
}
