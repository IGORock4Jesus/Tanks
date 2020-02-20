using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class Brick : Block
	{
		public Brick()
		{
			Texture = ResourceManager.Instance.GetTexture("brick");
		}
	}
}
