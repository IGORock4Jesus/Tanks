using SharpDX.Mathematics.Interop;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class UserTankController : ITankController
	{
		public void GetTexture(Tank tank)
		{
			tank.TextureCoords = ResourceManager.Instance.TanksCoords(ResourceManager.TankType.User_1, tank.Direction, TankLevel.Level1, 0);
		}

		public void Update(Tank tank, float elapsedTime)
		{
			Input input = Input.Instance;

			if (input["W"])
			{
				tank.Step(Direction.Top);
			}
			else if (input["D"])
			{
				tank.Step(Direction.Right);
			}
			else if(input["S"])
			{
				tank.Step(Direction.Bottom);
			}
			else if (input["A"])
			{
				tank.Step(Direction.Left);
			}
		}
	}
}
