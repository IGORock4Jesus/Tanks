using SharpDX;
using SharpDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Tanks
{
	struct Vertex
	{
		public Vector3 position;
		public Vector2 texel;
	}

	class Sprite : IDisposable
	{
		Matrix translation = Matrix.Identity;
		Matrix rotation = Matrix.Identity;
		Matrix scaling = Matrix.Scaling(1.0f);

		private VertexBuffer vertexBuffer;
		private IndexBuffer indexBuffer;
		private Vector3 size = new Vector3(1.0f);
		private Vector3 position;

		public Sprite()
		{
			vertexBuffer = new VertexBuffer(Renderer.Instance.Device, Marshal.SizeOf<Vertex>() * 4, Usage.Dynamic, VertexFormat.Position | VertexFormat.Texture1, Pool.Default);
			Vertex[] vertices = new Vertex[]
			{
				new Vertex()
				{
					position = new Vector3(0.0f, 0.0f, 0.0f),
					texel    = new Vector2(0.0f, 0.0f)
				},
				new Vertex()
				{
					position = new Vector3(1.0f, 0.0f, 0.0f),
					texel    = new Vector2(1.0f, 0.0f)
				},
				new Vertex()
				{
					position = new Vector3(1.0f, 1.0f, 0.0f),
					texel    = new Vector2(1.0f, 1.0f)
				},
				new Vertex()
				{
					position = new Vector3(0.0f, 1.0f, 0.0f),
					texel    = new Vector2(0.0f, 1.0f)
				}
			};
			var data = vertexBuffer.Lock(0, 0, LockFlags.None);
			data.WriteRange(vertices);
			vertexBuffer.Unlock();

			ushort[] indices = new ushort[]
			{
				0,1,2, 0,2,3
			};

			indexBuffer = new IndexBuffer(Renderer.Instance.Device, sizeof(ushort) * 6, Usage.Dynamic, Pool.Default, true);
			var indexData = indexBuffer.Lock(0, 0, LockFlags.None);
			indexData.WriteRange(indices);
			indexBuffer.Unlock();
		}

		public void Render()
		{
			var device = Renderer.Instance.Device;
			device.SetStreamSource(0, vertexBuffer, 0, Marshal.SizeOf<Vertex>());
			device.VertexFormat = VertexFormat.Position | VertexFormat.Texture1;
			device.Indices = indexBuffer;
			device.SetTransform(TransformState.World,
				scaling * rotation * translation);
			device.DrawIndexedPrimitive(PrimitiveType.TriangleList, 0, 0, 6, 0, 2);
		}

		public void Dispose()
		{
			indexBuffer.Dispose();
			vertexBuffer.Dispose();
		}

		public Vector3 Size
		{
			get => size;
			set
			{
				size = value;
				scaling = Matrix.Scaling(size);
			}
		}

		public Vector3 Position
		{
			get => position;
			set
			{
				position = value;
				translation = Matrix.Translation(position);
			}
		}

		internal static void Render(Vector2 position, float depth, Vector2 size, RectangleF textureCoords)
		{
			Vertex[] vertices = new Vertex[]
			{
				new Vertex
				{
					 position =new Vector3(position, depth),
					 texel = textureCoords.TopLeft
				},
				new Vertex
				{
					position = new Vector3(position.X+size.X,position.Y,depth),
					texel = textureCoords.TopRight
				},
				new Vertex
				{
					position=new Vector3(position+size,depth),
					texel   =textureCoords.BottomRight
				},
				new Vertex
				{
					position=new Vector3(position.X, position.Y+size.Y,depth),
					texel   =textureCoords.BottomLeft
				}
			};

			var device = Renderer.Instance.Device;
			device.DrawUserPrimitives(PrimitiveType.TriangleFan, 2, vertices);
		}

	}
}
