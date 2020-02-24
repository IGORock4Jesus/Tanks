using SharpDX;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Game
{
	class Tank : GameObject
	{
		private Direction direction;
		private TankLevel level;
		Bullet bullet;


		public TankLevel Level
		{
			get => level;
			set
			{
				level = value;
				Controller.GetTexture(this);
			}
		}
		public ITankController Controller { get; }
		public TankType Type { get; }

		public Direction Direction
		{
			get => direction;
			set
			{
				direction = value;
				Controller.GetTexture(this);
			}
		}

		public Tank(ITankController controller, TankType tankType, TankLevel level)
		{
			if (controller is null)
				throw new ArgumentNullException(nameof(controller));
			Controller = controller;
			Type = tankType;
			Level = level;
			Controller.GetTexture(this);
		}

		internal void Step(Direction direction)
		{
			float speed = 0.1f;

			// если направление не совпадает - меняем
			if (direction != Direction)
			{
				Direction = direction;
			}
			// иначе двигаемся
			else
			{
				// вычисляем в каком мы квадранте
				int x = (int)Math.Round(Position.X / LevelConstructor.Instance.MinBlockSize);
				int y = (int)Math.Round(Position.Y / LevelConstructor.Instance.MinBlockSize);

				// переходим на следующий, в зависимости от направления
				if (Direction == Direction.Top)
				{
					if (y > 0)
						y--;
				}
				else if (Direction == Direction.Bottom)
				{
					if (y < LevelConstructor.Instance.MinBlockCount - 4)
						y++;
				}
				else if (Direction == Direction.Left)
				{
					if (x > 0)
						x--;
				}
				else if (Direction == Direction.Right)
				{
					if (x < LevelConstructor.Instance.MinBlockCount - 4)
						x++;
				}

				AnimationManager.Instance.Add(speed, UpdateX, false, new KeyValuePair<float, float>(0.0f, Position.X),
					new KeyValuePair<float, float>(speed, x * LevelConstructor.Instance.MinBlockSize));

				AnimationManager.Instance.Add(speed, UpdateY, false, new KeyValuePair<float, float>(0.0f, Position.Y),
					new KeyValuePair<float, float>(speed, y * LevelConstructor.Instance.MinBlockSize));
			}
		}

		private void UpdateY(float newY)
		{
			Position = new SharpDX.Vector2(Position.X, newY);
		}

		private void UpdateX(float newX)
		{
			Position = new SharpDX.Vector2(newX, Position.Y);
		}

		public override void Update(float elapsedTime)
		{
			Controller.Update(this, elapsedTime);
		}

		public void Shot()
		{
			if (bullet != null)
				return;

			var b = new Bullet(direction);
			var pos = Position;

			if (direction == Direction.Top)
				pos += new Vector2(Size.X / 2.0f - b.Size.X / 2.0f, -b.Size.Y);
			else if(direction == Direction.Bottom)
				pos += new Vector2(Size.X / 2.0f - b.Size.X / 2.0f, Size.Y);
			else if (direction == Direction.Left)
				pos += new Vector2(-b.Size.X, Size.Y / 2.0f - b.Size.Y / 2.0f);
			else if (direction == Direction.Right)
				pos += new Vector2(Size.X, Size.Y / 2.0f - b.Size.Y / 2.0f);
			
			b.Position = pos;

			bullet = b;
			Scene.Instance.Add(bullet);
		}
	}
}
