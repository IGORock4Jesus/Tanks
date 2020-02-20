using SharpDX.D3DCompiler;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tanks.Graphics
{
	class VertexShader : Shader, IDisposable
	{
		SharpDX.Direct3D11.VertexShader shader;

		public VertexShader(string filename)
		{
			compilationResult = ShaderBytecode.CompileFromFile(filename, "main", "vs_4_0", ShaderFlags.Debug);

			shader = new SharpDX.Direct3D11.VertexShader(Renderer.Instance.Device3D, compilationResult.Bytecode);
		}

		private CompilationResult compilationResult;

		public void Dispose()
		{
			compilationResult.Dispose();
			shader.Dispose();
		}
	}
}
