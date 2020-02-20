using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class VoidConstructor : IConstructor
	{
		public Block Construct()
		{
			return null;
		}
	}
}
