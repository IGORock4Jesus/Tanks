using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class Concrete : Block
	{
		public Concrete()
		{
			Texture = ResourceManager.Instance.GetTexture("stone");
		}
	}
}
