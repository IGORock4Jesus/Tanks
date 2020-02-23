using System;
using System.Collections.Generic;
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
		
		internal void Clear()
		{
			lock (gameObjects)
			{
				gameObjects.Clear(); 
			}
		}

		internal void Add(GameObject gameObject)
		{
			lock (gameObjects)
			{
				gameObjects.Add(gameObject);
			}
		}

		public void Render()
		{
			lock (gameObjects)
			{
				foreach (var gameObject in gameObjects)
				{
					gameObject.Render();
				} 
			}
		}

		internal void Update(float elapsedTime)
		{
			lock (gameObjects)
			{
				foreach (var gameObject in gameObjects)
				{
					gameObject.Update(elapsedTime);
				}
			}
		}
	}
}