﻿using System;
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
				Texture = ResourceManager.Instance.GetTexture("bush")
			};
		}
	}
}