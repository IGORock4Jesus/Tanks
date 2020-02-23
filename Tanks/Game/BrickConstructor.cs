using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class BrickConstructor : IConstructor
	{
		public Block Construct()
		{
			return new Block
			{
				TextureCoords = ResourceManager.Instance.GetWallCoords(ResourceManager.Wall.Brick_Whole),
				Depth = Depth.Action
			};
		}
	}
}
