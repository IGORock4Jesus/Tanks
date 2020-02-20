using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	class GameObject : IDisposable
	{
		public virtual void Dispose()
		{
		}

		public virtual void Update(float elapsedTime)
		{

		}

		public virtual void Render()
		{

		}
	}
}
