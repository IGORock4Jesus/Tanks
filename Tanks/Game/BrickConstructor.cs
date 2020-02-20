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
			return new Brick();
		}
	}
}
