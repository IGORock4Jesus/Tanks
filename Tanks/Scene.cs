using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using Tanks.Game;

namespace Tanks
{
	public class Scene
	{
		#region Singleton
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

		#endregion

		readonly List<GameObject> gameObjects = new List<GameObject>();
		int needForClear;
		readonly Queue<GameObject> adds = new Queue<GameObject>();


		internal void Clear()
		{
			needForClear = 1;
		}

		internal void Add(GameObject gameObject)
		{
			if (gameObject is null)
				throw new ArgumentNullException(nameof(gameObject));

			adds.Enqueue(gameObject);
		}

		public void Render()
		{
			foreach (var gameObject in gameObjects
				.ToList()
				.OrderBy(w => w.Depth?.Value ?? 0.0f)
				.ToList())
			{
				gameObject.Render();
			}
		}

		internal void Update(float elapsedTime)
		{
			if (Interlocked.CompareExchange(ref needForClear, 0, 1) == 1)
			{
				gameObjects.Clear();
			}

			while (adds.Count != 0)
			{
				//lock (gameObjects)
				{
					GameObject item = adds.Dequeue();
					if (item is null)
						throw new NullReferenceException();
					gameObjects.Add(item); 
				}
			}

			foreach (var gameObject in gameObjects)
			{
				gameObject.Update(elapsedTime);
			}
		}
	}
}