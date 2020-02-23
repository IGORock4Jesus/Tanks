using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	class Input
	{
		static Input instance;
		static readonly object locker = new object();
		public static Input Instance
		{
			get
			{
				if (instance == null)
				{
					lock (locker)
					{
						if (instance == null)
							instance = new Input();
					}
				}
				return instance;
			}
		}

		readonly Dictionary<string, bool> keys = new Dictionary<string, bool>();

		public bool this [string key]
		{
			get => keys.ContainsKey(key) ? keys[key] : false;
			set => keys[key] = value;
		}
	}
}
