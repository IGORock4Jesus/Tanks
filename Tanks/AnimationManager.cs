using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	class AnimationManager
	{
		AnimationManager() { }
		static AnimationManager instance;
		static readonly object locker = new object();
		public static AnimationManager Instance
		{
			get
			{
				if(instance == null)
				{
					lock (locker)
					{
						if (instance == null)
							instance = new AnimationManager();
					}
				}
				return instance;
			}
		}

		class Animation
		{
			public float length;
			public float cursor;
			public readonly Dictionary<float, float> frames = new Dictionary<float, float>();
			public Action<float> callback;
			public bool looped;
		}

		readonly List<Animation> animations = new List<Animation>();

		public void Update(float elapsedTime)
		{
			List<Animation> forRemove = new List<Animation>();

			lock (animations)
			{
				foreach (var anim in animations)
				{
					anim.cursor += elapsedTime;

					float newValue = GetValue(anim);

					anim.callback(newValue);

					if(anim.cursor >= anim.length)
					{
						if (anim.looped)
							anim.cursor -= anim.length;
						else
							forRemove.Add(anim);
					}
				}
			}

			foreach (var item in forRemove)
			{
				animations.Remove(item);
			}
		}

		private float GetValue(Animation anim)
		{
			if (anim.frames.Count == 0)
				return 0.0f;
			else if (anim.frames.Count == 1)
				return anim.frames.First().Value;

			if (anim.cursor <= anim.frames.First().Key)
				return anim.frames.First().Value;
			else if (anim.cursor >= anim.frames.Last().Key)
				return anim.frames.Last().Value;

			var begin = anim.frames.Where(w => w.Key >= anim.cursor).Last();
			var end = anim.frames.Where(w => w.Key <= anim.cursor).First();

			float av = (anim.cursor - begin.Key) / (end.Key - begin.Key);

			float val = begin.Value + (end.Value - begin.Value) * av;

			return val;
		}

		public void Add(float length, Action<float> callback, bool looped, params KeyValuePair<float,float>[] frames)
		{
			Animation animation = new Animation
			{
				callback = callback,
				cursor = 0.0f,
				length = length,
				looped = looped
			};
			foreach (var item in frames)
			{
				animation.frames.Add(item.Key, item.Value);
			}
			lock (animations)
				animations.Add(animation);
		}


	}

	interface IAnimator
	{
		void Frame(float value);
	}
}
