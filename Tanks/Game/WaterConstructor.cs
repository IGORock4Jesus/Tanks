using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class WaterConstructor : IConstructor
	{
		public Block Construct()
		{
			return new Block
			{
				TextureCoords = ResourceManager.Instance.GetWallCoords(ResourceManager.Wall.Water_1),
				Depth = Depth.Ground
			};
		}
	}
}
