using SharpDX;

namespace Tanks.Game
{
	internal class Bullet : GameObject
	{
		public Direction Direction { get; }
		public BulletSpeed Speed { get; set; } = BulletSpeed.Normal;
		public delegate void BulletHandler(Bullet bullet);
		public event BulletHandler Destroy;



		public Bullet(Direction direction)
		{
			Direction = direction;
			Size = new Vector2(LevelConstructor.Instance.MinBlockSize, LevelConstructor.Instance.MinBlockSize);
			TextureCoords = ResourceManager.Instance.GetBulletCoords(direction);
		}

		public override void Update(float elapsedTime)
		{
			// перемещаемся
			float units = (Speed?.Value ?? BulletSpeed.Normal.Value) * elapsedTime;
			if (Direction == Direction.Top)
				Position = new SharpDX.Vector2(Position.X, Position.Y - units);
			else if (Direction == Direction.Bottom)
				Position = new SharpDX.Vector2(Position.X, Position.Y + units);
			else if (Direction == Direction.Right)
				Position = new SharpDX.Vector2(Position.X + units, Position.Y);
			else if (Direction == Direction.Left)
				Position = new SharpDX.Vector2(Position.X - units, Position.Y);
		}
	}

	class BulletSpeed
	{
		public float Value { get; set; }
		public static readonly BulletSpeed Normal = new BulletSpeed(100.0f);
		public static readonly BulletSpeed Fast = new BulletSpeed(200.0f);

		BulletSpeed(float v)
		{
			Value = v;
		}
	}
}