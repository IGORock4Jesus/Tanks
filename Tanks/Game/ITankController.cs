using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	interface ITankController
	{
		void Update(Tank tank, float elapsedTime);
		void GetTexture(Tank tank);
	}
}
