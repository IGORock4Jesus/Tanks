using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class ForestConstructor : IConstructor
	{
		public Block Construct()
		{
			return new Block
			{
				TextureCoords = ResourceManager.Instance.GetWallCoords(ResourceManager.Wall.Forest),
				Depth=Depth.Covers
			};
		}
	}
}
