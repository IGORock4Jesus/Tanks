using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class Flag:GameObject
	{
		public Flag()
		{
			TextureCoords = ResourceManager.Instance.GetFlagCoords();
		}
	}
}
