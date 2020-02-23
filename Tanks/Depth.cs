using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	class Depth
	{
		Depth(float value) {
			Value = value;
		}
		public float Value { get; }

		public static readonly Depth Ground = new Depth(0.0f);
		public static readonly Depth Action = new Depth(1.0f);
		public static readonly Depth Covers = new Depth(2.0f);
	}
}
