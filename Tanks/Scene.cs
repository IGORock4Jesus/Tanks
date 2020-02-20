using System;

namespace Tanks
{
	public class Scene
	{
		static Scene instance;
		static object locker = new object();
		public static Scene Instance
		{
			get
			{
				if (instance == null)
				{
					lock (locker)
					{
						if (instance == null)
							instance = new Scene();
					}
				}
				return instance;
			}
		}
		Scene() { }

		internal void Clear()
		{
			throw new NotImplementedException();
		}
	}
}